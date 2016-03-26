#include <QDebug>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include "Worker.h"

//**************************************************************************************
//* constructor
//*
//**************************************************************************************
Worker::Worker(QObject *parent) : QObject(parent)
{
}

//**************************************************************************************
//* slot_newRequest()
//*
//**************************************************************************************
void Worker::slot_newRequest(void * socket_desc, QByteArray data)
{
  QByteArray ret_data = 0;

  qDebug() << "new request received..." << QString(data) << endl;

  QJsonParseError parseError;
  QJsonDocument jsonDoc(QJsonDocument::fromJson(data,&parseError));

  if(parseError.error==QJsonParseError::NoError)  //JSON is the correct format
  {
    qDebug()<<"json file correct";

    QJsonObject jsonObj = jsonDoc.object();
    jsonObj.insert("F_NAME", "Janek");
    jsonObj.insert("L_NAME", "Kos");

    QJsonDocument new_jsonDoc(jsonObj);
    ret_data = new_jsonDoc.toJson();
  }
  else
  {
    qDebug()<<"json format error!";
  }

  emit signal_newResponse(socket_desc, ret_data);
}
