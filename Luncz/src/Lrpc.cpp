#include "Lrpc.h"

#include <QFile>
#include <QDebug>


//**************************************************************************************
//* constructor
//*
//**************************************************************************************
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

//**************************************************************************************
//* getErrorObj()
//*
//**************************************************************************************
QJsonObject LRpc::getErrorObj(const char *err_name)
{
  QJsonObject::const_iterator i_error = this->rpcObj.find(err_name);
  return i_error.value().toObject();
}

//**************************************************************************************
//* getResultObj()
//*
//**************************************************************************************
QJsonObject LRpc::getResultObj(const QString & res_name)
{
  //TODO throw exceptions

  QJsonObject::const_iterator i_method = this->rpcObj.find(res_name);

  if (i_method == this->rpcObj.end())
  {
    qDebug() << "getResultObj parse error";
    throw "parse error";
  }

  return i_method.value().toObject();
}

//**************************************************************************************
//* getResultValue()
//*
//**************************************************************************************
QJsonValue LRpc::getResultValue(const QString & res_name)
{
  //TODO throw exceptions

  QJsonObject::const_iterator i_method = this->rpcObj.find(res_name);

  if (i_method == this->rpcObj.end())
  {
    qDebug() << "getResultValue OBJ parse error";
    throw "parse error";
  }


  QJsonObject objResult = i_method.value().toObject();
  QJsonObject::const_iterator i_result = objResult.find("result");

  if (i_result == objResult.end())
  {
    qDebug() << "getResultValue RES parse error";
    throw "parse error";
  }

  return i_result.value();
}

//**************************************************************************************
//* getFrameId()
//*
//**************************************************************************************
QJsonValue LRpc::getFrameId(const QJsonObject &frameObj)
{
  return frameObj.value("id");
}
