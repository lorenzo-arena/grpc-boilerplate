/**
 * @file main.cc
 *
 * @brief Main file for async server example.
 *
 * @author Lorenzo Arena
 *
 */

#include <signal.h>
#include <cstdlib>
#include <unistd.h>

#include "Logger.h"
#include "AsyncServer.h"
#include "UnaryRequestManager.h"
#include "StreamRequestManager.h"

void handler(__attribute((unused)) int s)
{
    Logger::Debug("CTRL+C pressed, exiting.. ");
}

int main()
{
    /* Setup CTRL+C handling */
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    std::string url = "localhost:8080";
    auto server = std::make_shared<AsyncServer>();
    auto runResult = server->Run(url);

    if (!runResult)
    {
        Logger::Debug("Failed to start the gRPC async server");
        return -1;
    }

    /* Instantiate the managers which will serve the requests */
    auto unaryRequestManager = std::make_unique<UnaryRequestManager>(server.get());
    server->AddManager(std::move(unaryRequestManager));
    auto streamRequestManager = std::make_unique<StreamRequestManager>(server.get());
    server->AddManager(std::move(streamRequestManager));

    pause();

    return 0;
}
