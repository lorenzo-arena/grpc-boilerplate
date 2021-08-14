/**
 * @file BoilerplateService.h
 *
 * @brief This class provides the implementation for the Boilerplate service RPCs.
 *
 * @author Lorenzo Arena
 *
 */

#ifndef BOILERPLATE_SERVICE_H
#define BOILERPLATE_SERVICE_H

#include "boiler.grpc.pb.h"

#include <grpcpp/grpcpp.h>

class BoilerplateService final : public boiler::plate::Boilerplate::Service
{
  public:
    BoilerplateService() = default;
    ~BoilerplateService() = default;

    auto UnaryRequest(grpc::ServerContext* context, const boiler::plate::Request* request,
                      boiler::plate::Response* response) -> grpc::Status override;

    auto StreamRequest(grpc::ServerContext* context, const boiler::plate::Request* request,
                       grpc::ServerWriter<boiler::plate::Response>* writer) -> grpc::Status override;

    auto ClientStreamRequest(grpc::ServerContext* context, grpc::ServerReader<boiler::plate::Request>* reader,
                             boiler::plate::Response* response) -> grpc::Status override;

    auto BidiStreamRequest(grpc::ServerContext* context,
                           grpc::ServerReaderWriter<boiler::plate::Response, boiler::plate::Request>* stream) -> grpc::Status override;
};

#endif
