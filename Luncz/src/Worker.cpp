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

  if(parseError.error==QJsonParseError::NoError)  //JSON is in the correct format
  {
    qDebug()<<"json file correct";

    QJsonObject result;

    QJsonObject jsonMethod = in_json.object();
    QJsonObject::const_iterator i_method = jsonMethod.find("method");

    //TODO throw exception and send parse error message
    if (i_method == jsonMethod.end())
      return;

    // get received frame ID (required for RPC prot)
    QJsonValue frame_id = lrpcRes.getFrameId(jsonMethod);

    // get method from received data
    LRpcMethod rpc_met = i_method.value().toString();

    // get params from received data
    QJsonValue jparams = lrpcRes.getParams(jsonMethod);

    // prepare result frame
    result = lrpcRes.getResultObj(rpc_met);
    result["id"] = frame_id;

    // TODO could prepare result class to be a base class for differents results classes
    // this base class would have virtual result method.
    switch ( rpc_met.getId() )
    {
      case M_LIST_USERS:
        result["result"] = lrpcRes.ListUsers();
        break;

      case M_ADD_USER:
        result["result"] = lrpcRes.AddUser(jparams);
        break;

      case M_LIST_ORDERS:
        result["result"] = lrpcRes.ListOrders();
        break;

      case M_DELETE_USER:
        result["result"] = lrpcRes.DeleteUser(jparams);
        break;

      case M_MODIFY_USER:
        result["result"] = lrpcRes.ModifyUser(jparams);
        break;

      case M_ADD_ORDER:
        result["result"] = lrpcRes.AddOrder(jparams);
        break;

      case M_DELETE_ORDER:
        result["result"] = lrpcRes.DeleteOrder(jparams);
        break;

      case M_MODIFY_ORDER:
        result["result"] = lrpcRes.ModifyOrder(jparams);
        break;

      default:
        qDebug() << "error - invalid request";
        break;
    }

    // prepare byte array data to be send
    out_json.setObject(result);
  }
  else
  {
    qDebug()<<"json format error!";

    out_json.setObject(lrpcRes.getErrorObj("e_32700"));
  }


  emit signal_newResponse(socket_desc, out_json.toJson(QJsonDocument::Compact));
}


