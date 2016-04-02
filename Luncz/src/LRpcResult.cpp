#include <QFile>
#include <QDebug>

#include "LRpcResult.h"

static const string database_file = "luncz.db3";

LRpcResult::LRpcResult() :
  LRpc("../json/lunch_prot.json"),
  db(database_file, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE),
  uList(db),
  oList(db)
{
}

//**************************************************************************************
//* ListUsers()
//*
//**************************************************************************************
QJsonValue LRpcResult::ListUsers()
{
  //TODO throw exceptions

  QJsonArray result;

  QJsonObject res_obj = this->getResultValue("r_list_users").toArray().at(0).toObject();

  int ucnt = this->uList.GetUserCounter();

  for (int i = 1; i <= ucnt; i++)
  {
    try
    {
      User usr = User(this->db, i);

      res_obj["F_NAME"] = usr.GetFName().c_str();
      res_obj["L_NAME"] = usr.GetLName().c_str();
      res_obj["INITIALS"] = usr.GetInitials().c_str();
      res_obj["U_ID"] = usr.GetId();

      result.append(res_obj);
    }
    catch (exception& e)
    {
      qDebug() << "User exception!";
    }
  }

  return QJsonValue(result);
}

//**************************************************************************************
//* AddUser()
//*
//**************************************************************************************
QJsonValue LRpcResult::AddUser(const QJsonValue &params)
{
  //TODO throw/handle exceptions

  QJsonObject par_obj = params.toObject();

  // add new user
  User new_user = uList.AddUser(par_obj["F_NAME"].toString().toStdString(),
                                par_obj["L_NAME"].toString().toStdString(),
                                par_obj["INITIALS"].toString().toStdString());


  QJsonObject res_obj = this->getResultValue("r_add_user").toObject();

  // fill up the response
  res_obj["F_NAME"]   = new_user.GetFName().c_str();
  res_obj["L_NAME"]   = new_user.GetLName().c_str();
  res_obj["INITIALS"] = new_user.GetInitials().c_str();
  res_obj["U_ID"]     = new_user.GetId();

  return QJsonValue(res_obj);
}
