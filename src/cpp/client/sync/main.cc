/**
 * @file main.cc
 *
 * @brief Main file for sync client example.
 *
 * @author Lorenzo Arena
 *
 */

#include "Logger.h"
#include "BoilerplateClient.h"

int main()
{
    std::string url = "localhost:8080";

    /* Create the client and send a sample request */
    Logger::Debug("Creating client for server URL: ", url);
    auto client = std::make_unique<BoilerplateClient>(url);

    client->UnaryRequest();

    return 0;
}
