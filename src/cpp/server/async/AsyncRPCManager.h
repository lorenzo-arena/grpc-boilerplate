/**
 * @file AsyncRPCManager.h
 *
 * @brief This class provides a generic manager for async requests.
 *
 * @author Lorenzo Arena
 *
 */

#ifndef ASYNC_RPC_MANAGER_H
#define ASYNC_RPC_MANAGER_H

#include <grpcpp/grpcpp.h>

class AsyncRPCManager
{
  public:
    AsyncRPCManager(grpc::ServerCompletionQueue *cq, bool notifyWhenDone);
    virtual ~AsyncRPCManager()
    {
    }

    void Cancel();
    void Proceed(bool ok);
    bool Finished();

  protected:
    virtual void createHandler(bool ok) = 0;
    virtual void postCreateHandler(bool ok) = 0;
    virtual void processHandler(bool ok) = 0;
    virtual void waitingHandler(bool ok) = 0;
    virtual void cancelledHandler(bool ok) = 0;
    virtual void finishHandler(bool ok) = 0;

    grpc::ServerCompletionQueue *cq_;
    grpc::ServerContext ctx_;
    bool finished_;

    enum RPCStatus
    {
        CREATE,
        POSTCREATE,
        PROCESS,
        WAITING,
        CANCELLED,
        FINISH
    };

    RPCStatus status_;
};

#endif
