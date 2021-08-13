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

    req.set_text("request");

    Logger::Debug("BoilerplateClient: sending UnaryRequest request with text: ", req.text());
    auto status = stub_->UnaryRequest(&context, req, &resp);

    if (status.ok())
    {
        Logger::Debug("BoilerplateClient: unary request status OK, response: ", resp.text());
    }
    else
    {
        Logger::Debug("BoilerplateClient: unary request status NOT OK");
    }
}
