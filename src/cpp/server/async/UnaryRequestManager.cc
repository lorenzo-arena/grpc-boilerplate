/**
 * @file UnaryRequestManager.cc
 *
 * @brief This class provides the implementation for the UnaryRequestManager class.
 *
 * @author Lorenzo Arena
 *
 */

#include "UnaryRequestManager.h"

#include <grpcpp/grpcpp.h>

#include "Logger.h"
#include "AsyncServer.h"

/**
 * Calls the super constructor without setting the "notify when done"
 * event, since it's not a streaming RPC
 */
UnaryRequestManager::UnaryRequestManager(std::shared_ptr<AsyncServer> server)
    : AsyncRPCManager(server->CompletionQueue(), false), server_(std::move(server)), responder_(&ctx_)
{
    Logger::Debug("UnaryRequestManager: allocating");

    /* Fire the state machine */
    Proceed(true);
}

UnaryRequestManager::~UnaryRequestManager()
{
    Logger::Debug("Destroying unary request manager -> ", this);
}

void UnaryRequestManager::createHandler(__attribute__((unused)) bool ok)
{
    /* Make this instance progress to the POSTCREATE state as soon as a request is received */
    status_ = POSTCREATE;

    Logger::Debug("UnaryRequestManager: starting wait for request..");
    server_->AsyncService()->RequestUnaryRequest(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void UnaryRequestManager::postCreateHandler(__attribute__((unused)) bool ok)
{
    Logger::Debug("UnaryRequestManager: creating new request..");
    auto unaryRequestManager = std::make_unique<UnaryRequestManager>(server_);
    server_->AddManager(std::move(unaryRequestManager));

    /* Move in the state machine */
    status_ = PROCESS;
    Proceed(true);
}

void UnaryRequestManager::processHandler(__attribute__((unused)) bool ok)
{
    status_ = FINISH;

    Logger::Debug("UnaryRequestManager: finishing request..");
    response_.set_text("Here is the response");
    responseStatus_ = grpc::Status::OK;
    responder_.Finish(response_, responseStatus_, this);
}

void UnaryRequestManager::waitingHandler(__attribute__((unused)) bool ok)
{
}

void UnaryRequestManager::cancelledHandler(__attribute__((unused)) bool ok)
{
}

void UnaryRequestManager::finishHandler(__attribute__((unused)) bool ok)
{
    Logger::Debug("UnaryRequestManager: finished");
    finished_ = true;
}
