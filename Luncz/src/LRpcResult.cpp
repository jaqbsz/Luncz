#include <QFile>
#include <QDebug>

#include "LRpcResult.h"

static const string database_file = "luncz.db3";

LRpcResult::LRpcResult() :
  LRpc("../json/lunch_prot.json"),
  m_db(database_file, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE),
  m_uList(m_db),
  m_oList(m_db)
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

  QJsonObject res_obj = getResultValue("r_list_users").toArray().at(0).toObject();

  int ucnt = m_uList.GetUserCounter();

  for (int i = 1; i <= ucnt; i++)
  {
    try
    {
      User usr = m_uList.GetUser(i);

      res_obj["F_NAME"]   = usr.FName().c_str();
      res_obj["L_NAME"]   = usr.LName().c_str();
      res_obj["INITIALS"] = usr.Initials().c_str();
      res_obj["U_ID"]     = usr.Id();

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

  QJsonObject res_obj = getResultValue("r_list_orders").toArray().at(0).toObject();

  int ocnt = m_oList.GetOrderCounter();

  for (int i = 1; i <= ocnt; i++)
  {
    try
    {
      Order order = m_oList.GetOrder(i);

      res_obj["MENU_ITEM"]  = order.MenuItem();
      res_obj["PRICE"]      = order.Price();
      res_obj["U_INITIALS"] = order.UserInitials().c_str();
      res_obj["O_ID"]       = order.OrderId();
      res_obj["DATE"]       = order.Date().c_str();

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
  User new_user = m_uList.AddUser(par_obj["F_NAME"].toString().toStdString(),
                                  par_obj["L_NAME"].toString().toStdString(),
                                  par_obj["INITIALS"].toString().toStdString());


  QJsonObject res_obj = getResultValue("r_add_user").toObject();

  // fill up the response
  res_obj["F_NAME"]   = new_user.FName().c_str();
  res_obj["L_NAME"]   = new_user.LName().c_str();
  res_obj["INITIALS"] = new_user.Initials().c_str();
  res_obj["U_ID"]     = new_user.Id();

  return QJsonValue(res_obj);
}

//**************************************************************************************
//* AddOrder()
//*
//**************************************************************************************
QJsonValue LRpcResult::AddOrder(const QJsonValue &params)
{
  //TODO throw/handle exceptions
  QJsonObject res_obj;

  QJsonObject par_obj = params.toObject();

  // user that orders
  User user = m_uList.GetUser(par_obj.value("U_INITIALS").toString().toStdString());
  //TODO send error code in case no such user

  if ( user.Id() )
  {
    // add new order
    Order new_order = m_oList.AddOrder(user,
                                     par_obj["PRICE"].toInt(),
                                     par_obj["MENU_ITEM"].toInt());


    res_obj = getResultValue("r_add_order").toObject();

    // fill up the response
    res_obj["MENU_ITEM"]  = new_order.MenuItem();
    res_obj["PRICE"]      = new_order.Price();
    res_obj["U_INITIALS"] = new_order.UserInitials().c_str();
    res_obj["O_ID"]       = new_order.OrderId();
    res_obj["DATE"]       = new_order.Date().c_str();
  }
  else
    res_obj = getErrorObj("e_32500");

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

  QJsonObject res_obj = getResultValue("r_delete_user").toArray().at(0).toObject();

  QJsonObject par_obj = params.toObject();

  m_uList.DeleteUser(par_obj.value("U_ID").toInt());

  int ucnt = m_uList.GetUserCounter();

  for (int i = 1; i <= ucnt; i++)
  {
    try
    {
      User usr = m_uList.GetUser(i);

      res_obj["F_NAME"]   = usr.FName().c_str();
      res_obj["L_NAME"]   = usr.LName().c_str();
      res_obj["INITIALS"] = usr.Initials().c_str();
      res_obj["U_ID"]     = usr.Id();

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

  QJsonObject res_obj = getResultValue("r_delete_order").toArray().at(0).toObject();

  QJsonObject par_obj = params.toObject();

  {
    Order order = m_oList.GetOrder(par_obj.value("O_ID").toInt());
    m_oList.DeleteOrder(order);
  }

  int ocnt = m_oList.GetOrderCounter();

  for (int i = 1; i <= ocnt; i++)
  {
    try
    {
      Order order = m_oList.GetOrder(i);

      res_obj["MENU_ITEM"]  = order.MenuItem();
      res_obj["PRICE"]      = order.Price();
      res_obj["U_INITIALS"] = order.UserInitials().c_str();
      res_obj["O_ID"]       = order.OrderId();
      res_obj["DATE"]       = order.Date().c_str();

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

  User modified_user;// = User(this->db, par_obj.value("U_ID").toInt());
  // TODO modify user!!
  // ...

  QJsonObject res_obj = getResultValue("r_modify_user").toObject();

  // fill up the response
  res_obj["F_NAME"]   = modified_user.FName().c_str();
  res_obj["L_NAME"]   = modified_user.LName().c_str();
  res_obj["INITIALS"] = modified_user.Initials().c_str();
  res_obj["U_ID"]     = modified_user.Id();

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


  Order modified_order = m_oList.GetOrder(par_obj.value("O_ID").toInt());
  // TODO modify order!!
  // ...

  QJsonObject res_obj = getResultValue("r_modify_order").toObject();

  // fill up the response
  res_obj["MENU_ITEM"]  = modified_order.MenuItem();
  res_obj["PRICE"]      = modified_order.Price();
  res_obj["U_INITIALS"] = modified_order.UserInitials().c_str();
  res_obj["O_ID"]       = modified_order.OrderId();
  res_obj["DATE"]       = modified_order.Date().c_str();

  return QJsonValue(res_obj);
}
