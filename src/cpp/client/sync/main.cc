/**
 * @file main.cc
 *
 * @brief Main file for sync client example.
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
            ("url", "gRPC server URL", cxxopts::value<std::string>()->default_value("localhost:8080"));

        auto result = options.parse(argc, argv);
        auto url = result["url"].as<std::string>();

        /* Create the client and send a sample request */
        Logger::Debug("Creating client for server URL: ", url);
        auto client = std::make_unique<BoilerplateClient>(url);

        client->UnaryRequest();
    }
    catch(const std::exception& e)
    {
        Logger::Error("gRPC client: ", e.what());
        return -1;
    }

    return 0;
}
