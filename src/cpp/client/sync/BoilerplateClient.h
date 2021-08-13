/**
 * @file BoilerplateClient.h
 *
 * @brief This file provides the definition for the BoilerplateClient class.
 *
 * @author Lorenzo Arena
 *
 */

#ifndef BOILERPLATE_CLIENT_H
#define BOILERPLATE_CLIENT_H

#include <grpcpp/grpcpp.h>

#include "boiler.grpc.pb.h"

class BoilerplateClient
{
  public:
    BoilerplateClient(const std::string &url);

    void UnaryRequest();
    void StreamRequest();

  private:
    std::unique_ptr<boiler::plate::Boilerplate::Stub> stub_;
};

#endif
