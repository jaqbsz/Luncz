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

    QJsonObject result;

    QJsonObject jsonMethod = in_json.object();
    QJsonObject::const_iterator i_method = jsonMethod.find("method");

    //TODO throw exception and send parse error message
    if (i_method == jsonMethod.end())
      return;

    // make an object from received method
    LRpcMethod rpc_met = i_method.value().toString();

    // get received frame ID (required for RPC prot)
    QJsonValue frame_id = lrpcRes.getFrameId(jsonMethod);

    // TODO could prepare result class to be a base class for differents results classes
    // this base class would have virtual result method.
    switch ( rpc_met.getId() )
    {
      case M_LIST_USERS:
        {
          // prepare result frame
          result = lrpcRes.getResultObj("r_list_users");

          // prepare the result params and put it to the frame
          result["result"] = lrpcRes.ListUsers();
        }
        break;

      case M_ADD_USER:
        {
          // prepare result frame
          result = lrpcRes.getResultObj("r_add_user");

          // get params from received data
          QJsonObject::const_iterator i_params = jsonMethod.find("params");

          // prepare the result params and put it to the frame
          result["result"] = lrpcRes.AddUser(i_params.value());
        }
        break;

      case M_LIST_ORDERS:
        {
          // prepare result frame
          result = lrpcRes.getResultObj("r_list_orders");

          // prepare the result params and put it to the frame
          result["result"] = lrpcRes.ListOrders();
        }
        break;

      case M_DELETE_USER:
        {
          // prepare result frame
          result = lrpcRes.getResultObj("r_delete_user");

          // get params from received data
          QJsonObject::const_iterator i_params = jsonMethod.find("params");

          // prepare the result params and put it to the frame
          result["result"] = lrpcRes.DeleteUser(i_params.value());
        }
        break;

      case M_MODIFY_USER:
        {
          // prepare result frame
          result = lrpcRes.getResultObj("r_modify_user");

          // get params from received data
          QJsonObject::const_iterator i_params = jsonMethod.find("params");

          // prepare the result params and put it to the frame
          result["result"] = lrpcRes.ModifyUser(i_params.value());
        }
        break;

      case M_ADD_ORDER:
        {
          // prepare result frame
          result = lrpcRes.getResultObj("r_add_order");

          // get params from received data
          QJsonObject::const_iterator i_params = jsonMethod.find("params");

          // prepare the result params and put it to the frame
          result["result"] = lrpcRes.AddOrder(i_params.value());
        }
        break;

      case M_DELETE_ORDER:
        {
          // prepare result frame
          result = lrpcRes.getResultObj("r_delete_order");

          // get params from received data
          QJsonObject::const_iterator i_params = jsonMethod.find("params");

          // prepare the result params and put it to the frame
          result["result"] = lrpcRes.DeleteOrder(i_params.value());
        }
        break;

      case M_MODIFY_ORDER:
        {
          // prepare result frame
          result = lrpcRes.getResultObj("r_modify_order");

          // get params from received data
          QJsonObject::const_iterator i_params = jsonMethod.find("params");

          // prepare the result params and put it to the frame
          result["result"] = lrpcRes.ModifyOrder(i_params.value());
        }
        break;

      default:
        qDebug() << "error - invalid request";
        result = lrpcRes.getErrorObj("e_32601");
        break;
    }

    // send back frame id
    result["id"] = frame_id;

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


