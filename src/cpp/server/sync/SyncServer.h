/**
 * @file SyncServer.h
 *
 * @brief This class provides a synchronous gRPC server.
 *
 * @author Lorenzo Arena
 *
 */

#ifndef SYNC_SERVER_H
#define SYNC_SERVER_H

#include <string>

#include "BoilerplateService.h"

class SyncServer
{
  public:
    SyncServer() = default;
    ~SyncServer();

    bool Run(const std::string &url);

  private:
    std::unique_ptr<BoilerplateService> service_;
    std::unique_ptr<grpc::Server> server_;
};

#endif
