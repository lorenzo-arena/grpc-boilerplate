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

auto BoilerplateService::StreamRequest(__attribute((unused)) grpc::ServerContext* context,
                                       const boiler::plate::Request* request,
                                       grpc::ServerWriter<boiler::plate::Response>* writer) -> grpc::Status
{
    Logger::Debug("BoilerplateService: received StreamRequest");

    /* Example request check with bad request status return */
    if (request->text() != GOOD_REQUEST)
    {
        Logger::Debug("BoilerplateService: invalid argument");
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, INVALID_ARGUMENT_DESC);
    }

    Logger::Debug("BoilerplateService: starting streaming..");
    boiler::plate::Response resp;
    int index;
    for (index = 0; index < 10; index++)
    {
        resp.set_text("Response " + std::to_string(index));
        writer->Write(resp);
    }

    Logger::Debug("BoilerplateService: sending OK status");
    return grpc::Status::OK;
}

auto BoilerplateService::ClientStreamRequest(__attribute((unused)) grpc::ServerContext* context,
                                              grpc::ServerReader<boiler::plate::Request>* reader,
                                              boiler::plate::Response* response) -> grpc::Status
{
    Logger::Debug("BoilerplateService: received ClientStreamRequest");

    boiler::plate::Request req;
    while (reader->Read(&req))
    {
        Logger::Debug("BoilerplateService: ClientStreamRequest received request with text ", req.text());
    }

    Logger::Debug("BoilerplateService: ClientStreamRequest sending response");
    response->set_text("response");
    return grpc::Status::OK;
}

auto BoilerplateService::BidiStreamRequest(__attribute((unused)) grpc::ServerContext* context,
                                           grpc::ServerReaderWriter<boiler::plate::Response, boiler::plate::Request>* stream) -> grpc::Status
{
    Logger::Debug("BoilerplateService: received BidiStreamRequest");

    boiler::plate::Request req;
    std::list<boiler::plate::Request> reqList;
    while (stream->Read(&req))
    {
        Logger::Debug("BoilerplateService: BidiStreamRequest received request with text ", req.text());
        reqList.push_back(req);
    }

    Logger::Debug("BoilerplateService: BidiStreamRequest starting response stream.. ", req.text());
    for (const auto &reqElement: reqList)
    {
        boiler::plate::Response resp;
        resp.set_text("Response for " + reqElement.text());
        stream->Write(resp);
    }

    return grpc::Status::OK;
}
