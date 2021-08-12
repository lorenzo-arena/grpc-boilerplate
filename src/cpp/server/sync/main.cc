#include <signal.h>
#include <cstdlib>
#include <unistd.h>

#include "Logger.h"
#include "SyncServer.h"

void handler(__attribute((unused)) int s)
{
    Logger::Debug("CTRL+C pressed, exiting.. ");
}

int main()
{
    /* Set up CTRL+C handling */
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    std::string url = "localhost:8080";

    auto server = std::make_unique<SyncServer>();
    auto runResult = server->Run(url);

    if(!runResult)
    {
        Logger::Debug("Failed to start the gRPC server");
        return -1;
    }

    pause();

    return 0;
}
