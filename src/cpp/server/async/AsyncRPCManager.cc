/**
 * @file AsyncRPCManager.cc
 *
 * @brief This class provides the implementation for the AsyncRPCManager class.
 *
 * @author Lorenzo Arena
 *
 */

#include "AsyncRPCManager.h"

#include "Logger.h"

AsyncRPCManager::AsyncRPCManager(grpc::ServerCompletionQueue *cq, bool notifyWhenDone)
    : cq_(cq), finished_(false), started_(false), status_(CREATE)
{
    if (notifyWhenDone)
    {
        ctx_.AsyncNotifyWhenDone(this);
    }
}

void AsyncRPCManager::Cancel()
{
    if (!finished_ && started_)
    {
        ctx_.TryCancel();
        finished_ = true;
    }
}

void AsyncRPCManager::Proceed(bool ok)
{
    switch (status_)
    {
    case RPCStatus::CREATE:
        createHandler(ok);
        break;

    case RPCStatus::POSTCREATE:
        postCreateHandler(ok);
        break;

    case RPCStatus::PROCESS:
        processHandler(ok);
        break;

    case RPCStatus::WAITING:
        waitingHandler(ok);
        break;

    case RPCStatus::CANCELLED:
        cancelledHandler(ok);
        break;

    case RPCStatus::FINISH:
        finishHandler(ok);
        break;
    default:
        break;
    }
}

bool AsyncRPCManager::Finished()
{
    return finished_;
}
