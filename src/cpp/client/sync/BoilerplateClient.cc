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

    if (status.ok())
    {
        Logger::Debug("BoilerplateClient: unary request ended with status OK, response: ", resp.text());
    }
    else
    {
        Logger::Debug("BoilerplateClient: unary request ended with status NOT OK");
    }
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

    if (status.ok())
    {
        Logger::Debug("BoilerplateClient: unary request ended with status OK");
    }
    else
    {
        Logger::Debug("BoilerplateClient: unary request ended with status NOT OK");
    }
}
