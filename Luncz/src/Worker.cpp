#include <QDebug>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include "Worker.h"
#include "LRpcMethod.h"

//**************************************************************************************
//* constructor
//*
//**************************************************************************************
Worker::Worker(QObject *parent) :
  QObject(parent),
  lrpcRes()
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

    //TODO throw exception and send parse error message
    if (i_method == jsonMethod.end())
      return;

    LRpcMethod rpc_met = i_method.value().toString();

    switch ( rpc_met.getId() )
    {
      case M_LIST_USERS:
        {
          QJsonObject result = lrpcRes.getResultObj("r_list_users");

          result["result"] = lrpcRes.ListUsers();
          out_json.setObject(result);
        }
        break;

      case M_ADD_USER:
        {
          QJsonObject result = lrpcRes.getResultObj("r_add_user");
          QJsonObject::const_iterator i_params = jsonMethod.find("params");

          result["result"] = lrpcRes.AddUser(i_params.value());
          out_json.setObject(result);
        }
        break;

      case M_LIST_ORDERS:
      case M_DELETE_USER:
      case M_MODIFY_USER:
      case M_ADD_ORDER:
      case M_DELETE_ORDER:
      case M_MODIFY_ORDER:

      default:
        qDebug() << "error - invalid request";
        out_json.setObject(lrpcRes.getErrorObj("e_32601"));
        break;
    }
  }
  else
  {
    qDebug()<<"json format error!";

    out_json.setObject(lrpcRes.getErrorObj("e_32700"));
  }


  emit signal_newResponse(socket_desc, out_json.toJson(QJsonDocument::Compact));
}


