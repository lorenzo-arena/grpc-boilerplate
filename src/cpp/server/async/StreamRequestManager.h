/**
 * @file StreamRequestManager.h
 *
 * @brief This class provides the manager for StreamRequest RPC.
 *
 * @author Lorenzo Arena
 *
 */

#ifndef STREAM_REQUEST_MANAGER_H
#define STREAM_REQUEST_MANAGER_H

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <grpcpp/grpcpp.h>
#include <grpcpp/alarm.h>

#include "boiler.grpc.pb.h"
#include "AsyncRPCManager.h"
#include "AsyncServer.h"

class StreamRequestManager final : public AsyncRPCManager
{
  public:
    StreamRequestManager(AsyncServer *server);
    ~StreamRequestManager();

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
    grpc::ServerAsyncWriter<boiler::plate::Response> writer_;
    int counter_;
    grpc::Alarm wakeAlarm_;
    int finishCounter_;
};

#endif
