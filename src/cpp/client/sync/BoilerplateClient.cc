/**
 * @file BoilerplateClient.cc
 *
 * @brief This file provides the implementation for the BoilerplateClient class.
 *
 * @author Lorenzo Arena
 *
 */

#include "BoilerplateClient.h"

#include "Logger.h"

#define GOOD_REQUEST "request"

BoilerplateClient::BoilerplateClient(const std::string &url)
{
    auto channel = grpc::CreateChannel(url, grpc::InsecureChannelCredentials());
    stub_ = boiler::plate::Boilerplate::NewStub(channel);
}

void BoilerplateClient::UnaryRequest()
{
    grpc::ClientContext context;
    boiler::plate::Request req;
    boiler::plate::Response resp;

    req.set_text(GOOD_REQUEST);

    Logger::Debug("BoilerplateClient: sending UnaryRequest request with text: ", req.text());
    auto status = stub_->UnaryRequest(&context, req, &resp);
    Logger::Debug("BoilerplateClient: UnaryRequest ended with status ", status.ok() ? "OK" : "NOT OK");
}

void BoilerplateClient::StreamRequest()
{
    grpc::ClientContext context;
    boiler::plate::Request req;
    boiler::plate::Response resp;

    req.set_text(GOOD_REQUEST);

    Logger::Debug("BoilerplateClient: sending StreamRequest request with text: ", req.text());
    auto reader = stub_->StreamRequest(&context, req);
    while (reader->Read(&resp))
    {
        Logger::Debug("BoilerplateClient: received stream data: ", resp.text());
    }

    auto status = reader->Finish();
    Logger::Debug("BoilerplateClient: StreamRequest ended with status ", status.ok() ? "OK" : "NOT OK");
}

void BoilerplateClient::ClientStreamRequest()
{
    grpc::ClientContext context;
    boiler::plate::Request req;
    boiler::plate::Response resp;

    Logger::Debug("BoilerplateClient: starting streaming..");
    auto writer = stub_->ClientStreamRequest(&context, &resp);
    int index;
    for (index = 0; index < 10; index++)
    {
        req.set_text("Request " + std::to_string(index));
        writer->Write(req);
    }

    writer->WritesDone();

    auto status = writer->Finish();
    Logger::Debug("BoilerplateClient: ClientStreamRequest ended with status ",
                  status.ok() ? "OK " : "NOT OK ",
                  "and response: ",
                  resp.text());
}

void BoilerplateClient::BidiStreamRequest()
{
    grpc::ClientContext context;
    boiler::plate::Request req;
    boiler::plate::Response resp;

    Logger::Debug("BoilerplateClient: starting bidi streaming..");
    auto stream = stub_->BidiStreamRequest(&context);
    int index;
    for (index = 0; index < 10; index++)
    {
        req.set_text("Request " + std::to_string(index));
        stream->Write(req);
    }

    stream->WritesDone();

    while (stream->Read(&resp))
    {
        Logger::Debug("BoilerplateClient: received stream data: ", resp.text());
    }

    auto status = stream->Finish();
    Logger::Debug("BoilerplateClient: BidiStreamRequest ended with status ", status.ok() ? "OK" : "NOT OK");
}
