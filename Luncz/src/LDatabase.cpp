#include <QFile>
#include <QDebug>

#include "LDatabase.h"

#define TESTS

static const string database_file = "luncz.db3";

LDatabase::LDatabase() :
  db(database_file, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE),
  uList(db),
  oList(db),
  lunchRpc(QJsonDocument::fromJson(getRpcFile("../json/lunch_prot.json")))
{
#ifdef TESTS
  this->db.exec("DROP TABLE IF EXISTS USERS_LIST");
  this->db.exec("DROP TABLE IF EXISTS ORDER_LIST");
#endif
}

//**************************************************************************************
//* getRpcFile()
//*
//**************************************************************************************
QByteArray LDatabase::getRpcFile(const char * file_name)
{
  QFile file;

  file.setFileName(file_name);
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QByteArray out_data = file.readAll();
  file.close();

  return out_data;
}


//**************************************************************************************
//* ListUsers()
//*
//**************************************************************************************
QJsonValue LDatabase::ListUsers()
{
  //TODO throw exceptions

  QJsonObject objMethod = this->lunchRpc.object();
  QJsonObject::const_iterator i_method = objMethod.find("r_list_users");

  if (i_method == objMethod.end())
    throw "parse error";

  QJsonObject objResult = i_method.value().toObject();
  QJsonObject::const_iterator i_result = objResult.find("result");

  if (i_result == objResult.end())
    throw "parse error";

  QJsonObject res_obj = i_result.value().toArray().at(0).toObject();

  QJsonArray result;
  int ucnt = this->uList.GetUserCounter();
  for (int i = 0; i < ucnt; i++)
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
      qDebug() << "user exception!";
    }
  }

  return QJsonValue(result);
}
