/**
 * @file AsyncServer.h
 *
 * @brief This class provides an asynchronous gRPC server.
 *
 * @author Lorenzo Arena
 *
 */

#ifndef ASYNC_SERVER_H
#define ASYNC_SERVER_H

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <grpcpp/grpcpp.h>
#include <grpcpp/alarm.h>

#include "boiler.grpc.pb.h"
#include "AsyncRPCManager.h"

class AsyncServer final
{
  public:
    AsyncServer() = default;
    ~AsyncServer();

    void AddManager(std::unique_ptr<AsyncRPCManager> manager);
    auto CompletionQueue() -> grpc::ServerCompletionQueue *;
    auto AsyncService() -> boiler::plate::Boilerplate::AsyncService *;
    auto Run(const std::string &server_url) -> bool;

  private:
    void mainLoop();

    std::unique_ptr<grpc::ServerCompletionQueue> cq_;
    std::unique_ptr<grpc::Server> server_;
    std::unique_ptr<boiler::plate::Boilerplate::AsyncService> boilerplateService_;
    std::vector<std::unique_ptr<AsyncRPCManager>> managers_;
    bool isStopped_ = false;
    std::thread mainloop_;
};

#endif
