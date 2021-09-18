/**
 * @file AsyncServer.cc
 *
 * @brief This class provides the implementation for the AsyncServer class.
 *
 * @author Lorenzo Arena
 *
 */

#include "AsyncServer.h"

#include <grpcpp/grpcpp.h>
#include <sstream>
#include <thread>
#include <algorithm>
#include <chrono>

#include "Logger.h"

#include "boiler.grpc.pb.h"

AsyncServer::~AsyncServer()
{
    Logger::Debug("AsyncServer: destructing..");

    isStopped_ = true;

    /* Trigger an event so that isStopped_ is evaluated in the mainloop */
    if (cq_)
    {
        auto alarm = std::make_shared<grpc::Alarm>();
        alarm->Set(cq_.get(), std::chrono::system_clock::now(), nullptr);
    }

    try
    {
        if (mainloop_.joinable())
        {
            mainloop_.join();
        }
    }
    catch (const std::exception &e)
    {
        Logger::Debug("AsyncServer: error while joining async mainloop: ", e.what());
    }

    if (server_)
    {
        /* Shutdown with immediate cancel of connections */
        server_->Shutdown(std::chrono::system_clock::now());
    }

    /* Always shutdown the completion queue after the server. */
    if (cq_)
    {
        cq_->Shutdown();

        Logger::Debug("AsyncServer: draining the completion queue..");
        void *tag;
        bool ok;
        while (cq_->Next(&tag, &ok))
        {
            if (tag != nullptr)
            {
                auto *manager = static_cast<AsyncRPCManager *>(tag);
                manager->Cancel();
            }
        }

        while (managers_.size() > 0)
        {
            managers_.pop_back();
        }
    }
}

auto AsyncServer::Run(const std::string &server_url) -> bool
{
    boilerplateService_ = std::make_unique<boiler::plate::Boilerplate::AsyncService>();

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_url, grpc::InsecureServerCredentials());
    builder.RegisterService(boilerplateService_.get());

    cq_ = builder.AddCompletionQueue();

    server_ = builder.BuildAndStart();
    if (server_ == nullptr)
    {
        Logger::Error("AsyncServer: error while startin async server on: ", server_url);
        return false;
    }

    Logger::Debug("AsyncServer: listening on ", server_url);

    mainloop_ = std::thread(&AsyncServer::mainLoop, this);

    return true;
}

void AsyncServer::AddManager(std::unique_ptr<AsyncRPCManager> manager)
{
    managers_.push_back(std::move(manager));
}

auto AsyncServer::CompletionQueue() -> grpc::ServerCompletionQueue *
{
    return cq_.get();
}

auto AsyncServer::AsyncService() -> boiler::plate::Boilerplate::AsyncService *
{
    return boilerplateService_.get();
}

void AsyncServer::mainLoop()
{
    void *tag;
    bool ok;

    while (!isStopped_)
    {
        if (cq_->Next(&tag, &ok))
        {
            if (tag != nullptr)
            {
                auto *manager = static_cast<AsyncRPCManager *>(tag);
                manager->Proceed(ok);

                /**
                 * If the manager has finished with the current RPC, pop it from the
                 * managers list
                 */
                if (manager->Finished())
                {
                    auto pos = std::find_if(managers_.begin(), managers_.end(),
                        [manager] (const std::unique_ptr<AsyncRPCManager>& m) { return m.get() == manager; } );

                    if (pos != managers_.end())
                    {
                        managers_.erase(pos);
                    }
                }
            }
        }
    }
}
