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

    QJsonObject getRpcObj() { return m_rpcObj; }

    QJsonObject getErrorObj   (const char * err_name);
    QJsonObject getResultObj  (const QString &res_name);
    QJsonObject getResultObj  (const LRpcMethod &lrpcMeth);
    QJsonValue  getResultValue(const QString &res_name);
    QJsonValue  getFrameId    (const QJsonObject & frameObj);
    QJsonValue  getParams     (const QJsonObject & frameObj);

  private:
    QJsonObject m_rpcObj;

};

#endif // LRPC_H
