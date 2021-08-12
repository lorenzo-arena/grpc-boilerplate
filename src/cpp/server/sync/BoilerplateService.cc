/**
 * @file BoilerplateService.cc
 *
 * @brief This class provides the implementation for the BoilerplateServce class.
 *
 * @author Lorenzo Arena
 *
 */

#include "BoilerplateService.h"

#include "Logger.h"

#define GOOD_REQUEST "request"

#define INVALID_ARGUMENT_DESC "Invalid argument"

auto BoilerplateService::UnaryRequest(__attribute((unused)) grpc::ServerContext* context,
                                      const boiler::plate::Request* request,
                                      boiler::plate::Response* response) -> grpc::Status
{
    Logger::Debug("BoilerplateService: received UnaryRequest");

    /* Example request check with bad request status return */
    if (request->text() != GOOD_REQUEST)
    {
        Logger::Debug("BoilerplateService: invalid argument");
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, INVALID_ARGUMENT_DESC);
    }

    response->set_text("response");

    Logger::Debug("BoilerplateService: sending OK status");
    return grpc::Status::OK;
}
