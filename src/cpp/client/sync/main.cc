/**
 * @file main.cc
 *
 * @brief Main file for sync client example. cxopt is used for command line options handling, so it can be started using
 *        `./grpc-client-sync --url localhost:8080 --unary
 *
 * @author Lorenzo Arena
 *
 */

#include <cxxopts.hpp>

#include "Logger.h"
#include "BoilerplateClient.h"

int main(int argc, char** argv)
{
    try
    {
        cxxopts::Options options("gRPC++ Boilerplate Client", "Simple gRPC synchronous client");

        options.add_options()
            ("url", "gRPC server URL", cxxopts::value<std::string>()->default_value("localhost:8080"))
            ("unary", "start unary request", cxxopts::value<bool>()->default_value("true"))
            ("streaming", "start streaming request", cxxopts::value<bool>()->default_value("true"))
            ("clientstream", "start client streaming request", cxxopts::value<bool>()->default_value("true"))
            ("bidi", "start bidi streaming request", cxxopts::value<bool>()->default_value("true"));

        auto result = options.parse(argc, argv);
        auto url = result["url"].as<std::string>();
        auto unary = result["unary"].as<bool>();
        auto streaming = result["streaming"].as<bool>();
        auto clientStream = result["clientstream"].as<bool>();
        auto bidi = result["bidi"].as<bool>();

        /* Create the client and send a sample request */
        Logger::Debug("Creating client for server URL: ", url);
        auto client = std::make_unique<BoilerplateClient>(url);

        if (unary)
        {
            Logger::Debug("UnaryRequest option enabled, starting..");
            client->UnaryRequest();
        }

        if (streaming)
        {
            Logger::Debug("StreamRequest option enabled, starting..");
            client->StreamRequest();
        }

        if (clientStream)
        {
            Logger::Debug("ClientStreamRequest option enabled, starting..");
            client->ClientStreamRequest();
        }

        if (bidi)
        {
            Logger::Debug("BidiStreamRequest option enabled, starting..");
            client->BidiStreamRequest();
        }
    }
    catch(const std::exception& e)
    {
        Logger::Error("gRPC client: ", e.what());
        return -1;
    }

    return 0;
}
