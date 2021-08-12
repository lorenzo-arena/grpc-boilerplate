/**
 * @file SyncServer.cc
 *
 * @brief This class provides the implementation for the SyncServer class.
 *
 * @author Lorenzo Arena
 *
 */

#include "SyncServer.h"

#include <grpcpp/grpcpp.h>

#include "Logger.h"

SyncServer::~SyncServer()
{
    Logger::Debug("Destructing server..");
}

bool SyncServer::Run(const std::string &url)
{
    Logger::Debug("SyncServer: run on URL ", url);

    if (url.empty())
    {
        Logger::Debug("SyncServer: run failed, invalid URL");
        return false;
    }

    service_ = std::make_unique<BoilerplateService>();

    grpc::ServerBuilder builder;

    /* Listen on the given address without any authentication mechanism. */
    builder.AddListeningPort(url, grpc::InsecureServerCredentials());

    /* If necessary, set quota to a certain number of threads */
    // grpc::ResourceQuota quota("syncServerQuota");
    // quota.SetMaxThreads(4);
    // builder.SetResourceQuota(quota);

    // Register "service_" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *asynchronous* service.
    builder.RegisterService(service_.get());

    // Finally assemble the server.
    server_ = builder.BuildAndStart();

    Logger::Debug("SyncServer: listening on ", url);

    return true;
}
