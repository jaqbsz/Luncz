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

      res_obj["F_NAME"]   = usr.GetFName().c_str();
      res_obj["L_NAME"]   = usr.GetLName().c_str();
      res_obj["INITIALS"] = usr.GetInitials().c_str();
      res_obj["U_ID"]     = usr.GetId();

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
//* ListOrders()
//*
//**************************************************************************************
QJsonValue LRpcResult::ListOrders()
{
  //TODO throw exceptions

  QJsonArray result;

  QJsonObject res_obj = this->getResultValue("r_list_orders").toArray().at(0).toObject();

  int ocnt = this->oList.GetOrderCounter();

  for (int i = 1; i <= ocnt; i++)
  {
    try
    {
      Order order = Order(this->db, i);

      res_obj["MENU_ITEM"]  = order.GetMenuItem();
      res_obj["PRICE"]      = order.GetPrice();
      res_obj["U_INITIALS"] = order.GetUserInitials().c_str();
      res_obj["O_ID"]       = order.GetId();
      res_obj["DATE"]       = order.GetDate().c_str();

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

//**************************************************************************************
//* AddOrder()
//*
//**************************************************************************************
QJsonValue LRpcResult::AddOrder(const QJsonValue &params)
{
  //TODO throw/handle exceptions

  QJsonObject par_obj = params.toObject();

  // user that orders
  User user = User(this->db, par_obj.value("U_INITIALS").toString().toStdString());
  //TODO send error code in case no such user

  // add new order
  Order new_order = oList.AddOrder(user,
                                   par_obj["PRICE"].toInt(),
                                   par_obj["MENU_ITEM"].toInt());


  QJsonObject res_obj = this->getResultValue("r_add_order").toObject();

  // fill up the response
  res_obj["MENU_ITEM"]  = new_order.GetMenuItem();
  res_obj["PRICE"]      = new_order.GetPrice();
  res_obj["U_INITIALS"] = new_order.GetUserInitials().c_str();
  res_obj["O_ID"]       = new_order.GetId();
  res_obj["DATE"]       = new_order.GetDate().c_str();

  return QJsonValue(res_obj);
}

//**************************************************************************************
//* DeleteUser()
//*
//**************************************************************************************
QJsonValue LRpcResult::DeleteUser(const QJsonValue &params)
{
  //TODO throw exceptions

  QJsonArray result;

  QJsonObject res_obj = this->getResultValue("r_delete_user").toArray().at(0).toObject();

  QJsonObject par_obj = params.toObject();

  this->uList.DeleteUser(par_obj.value("U_ID").toInt());

  int ucnt = this->uList.GetUserCounter();

  for (int i = 1; i <= ucnt; i++)
  {
    try
    {
      User usr = User(this->db, i);

      res_obj["F_NAME"]   = usr.GetFName().c_str();
      res_obj["L_NAME"]   = usr.GetLName().c_str();
      res_obj["INITIALS"] = usr.GetInitials().c_str();
      res_obj["U_ID"]     = usr.GetId();

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
//* DeleteOrder()
//*
//**************************************************************************************
QJsonValue LRpcResult::DeleteOrder(const QJsonValue &params)
{
  //TODO throw exceptions

  QJsonArray result;

  QJsonObject res_obj = this->getResultValue("r_delete_order").toArray().at(0).toObject();

  QJsonObject par_obj = params.toObject();

  {
    Order order = Order(this->db, par_obj.value("O_ID").toInt());
    this->oList.DeleteOrder(order);
  }

  int ocnt = this->oList.GetOrderCounter();

  for (int i = 1; i <= ocnt; i++)
  {
    try
    {
      Order order = Order(this->db, i);

      res_obj["MENU_ITEM"]  = order.GetMenuItem();
      res_obj["PRICE"]      = order.GetPrice();
      res_obj["U_INITIALS"] = order.GetUserInitials().c_str();
      res_obj["O_ID"]       = order.GetId();
      res_obj["DATE"]       = order.GetDate().c_str();

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
//* ModifyUser()
//*
//**************************************************************************************
QJsonValue LRpcResult::ModifyUser(const QJsonValue &params)
{
  //TODO throw/handle exceptions

  QJsonObject par_obj = params.toObject();


  User modified_user = User(this->db, par_obj.value("U_ID").toInt());
  // TODO modify user!!
  // ...

  QJsonObject res_obj = this->getResultValue("r_modify_user").toObject();

  // fill up the response
  res_obj["F_NAME"]   = modified_user.GetFName().c_str();
  res_obj["L_NAME"]   = modified_user.GetLName().c_str();
  res_obj["INITIALS"] = modified_user.GetInitials().c_str();
  res_obj["U_ID"]     = modified_user.GetId();

  return QJsonValue(res_obj);
}

//**************************************************************************************
//* ModifyOrder()
//*
//**************************************************************************************
QJsonValue LRpcResult::ModifyOrder(const QJsonValue &params)
{
  //TODO throw/handle exceptions

  QJsonObject par_obj = params.toObject();


  Order modified_order = Order(this->db, par_obj.value("O_ID").toInt());
  // TODO modify order!!
  // ...

  QJsonObject res_obj = this->getResultValue("r_modify_order").toObject();

  // fill up the response
  res_obj["MENU_ITEM"]  = modified_order.GetMenuItem();
  res_obj["PRICE"]      = modified_order.GetPrice();
  res_obj["U_INITIALS"] = modified_order.GetUserInitials().c_str();
  res_obj["O_ID"]       = modified_order.GetId();
  res_obj["DATE"]       = modified_order.GetDate().c_str();

  return QJsonValue(res_obj);
}
