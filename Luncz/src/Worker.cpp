#include <QDebug>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include "Worker.h"

//**************************************************************************************
//* constructor
//*
//**************************************************************************************
Worker::Worker(QObject *parent) :
  QObject(parent),
  ldb(),
  lunchRpc(QJsonDocument::fromJson(getRpcFile("../json/lunch_prot.json")))
{
}

//**************************************************************************************
//* slot_newRequest()
//*
//* note: in_data is a copy here - check intertherad communication in QT
//**************************************************************************************
void Worker::slot_newRequest(void * socket_desc, const QByteArray &in_data)
{
  QJsonDocument out_json;

  qDebug() << "new request received..." << QString(in_data) << endl;

  QJsonParseError parseError;
  QJsonDocument in_json(QJsonDocument::fromJson(in_data, &parseError));

  if(parseError.error==QJsonParseError::NoError)  //JSON is the correct format
  {
    qDebug()<<"json file correct";

    QJsonObject jsonMethod = in_json.object();
    QJsonObject::const_iterator i_method = jsonMethod.find("method");

    if (i_method == jsonMethod.end())
      return;

    QString str = i_method.value().toString();

    if (str == "list_users")
    {
      out_json(ldb.ListUsers().toObject());
    }
    else
    {
      qDebug() << "error - invalid request";
    }
  }
  else
  {
    qDebug()<<"json format error!";

    QJsonObject objError = this->lunchRpc.object();
    QJsonObject::const_iterator i_error = objError.find("e_32700");
    out_json(i_error);
  }


  emit signal_newResponse(socket_desc, out_json.toJson());
}


