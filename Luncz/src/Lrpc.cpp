#include "Lrpc.h"

#include <QFile>

LRpc::LRpc(const char *file_name)
{
  QFile file;

  file.setFileName(file_name);
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QByteArray file_data = file.readAll();
  file.close();

  QJsonDocument jsonDoc = QJsonDocument::fromJson(file_data);
  this->rpcObj = jsonDoc.object();
}

QJsonObject LRpc::getRpcObj()
{
  return this->rpcObj;
}

QJsonObject LRpc::getResultObj(const LRpcMethod &method)
{
  QJsonObject obj;
  return obj;
}

QJsonObject LRpc::getErrorObj(const char *err_name)
{
  QJsonObject::const_iterator i_error = this->rpcObj.find(err_name);
  return i_error.value().toObject();
}

QJsonValue LRpc::getResultValue(const LRpcMethod &method)
{
  QJsonValue val;
  return val;
}
