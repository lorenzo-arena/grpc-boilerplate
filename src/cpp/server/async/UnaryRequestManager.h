/**
 * @file UnaryRequestManager.h
 *
 * @brief This class provides the manager for UnaryRequest RPC.
 *
 * @author Lorenzo Arena
 *
 */

#ifndef UNARY_REQUEST_MANAGER_H
#define UNARY_REQUEST_MANAGER_H

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <grpcpp/grpcpp.h>

#include "boiler.grpc.pb.h"
#include "AsyncRPCManager.h"
#include "AsyncServer.h"

class UnaryRequestManager final : public AsyncRPCManager
{
  public:
    UnaryRequestManager(AsyncServer *server);
    ~UnaryRequestManager();

  private:
    void createHandler(bool ok) override;
    void postCreateHandler(bool ok) override;
    void processHandler(bool ok) override;
    void waitingHandler(bool ok) override;
    void cancelledHandler(bool ok) override;
    void finishHandler(bool ok) override;

    AsyncServer *server_;
    boiler::plate::Request request_;
    boiler::plate::Response response_;
    grpc::Status responseStatus_;
    grpc::ServerAsyncResponseWriter<boiler::plate::Response> responder_;
};

#endif
