#ifndef LRPC_H
#define LRPC_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "LRpcMethod.h"

class LRpc
{
  public:
    explicit LRpc(const char * file_name);

    QJsonObject getRpcObj();

    QJsonObject getResultObj(const LRpcMethod & method);

    QJsonObject getErrorObj(const char * err_name);

    QJsonValue getResultValue(const LRpcMethod & method);

  private:
    QJsonObject rpcObj;

};

#endif // LRPC_H
