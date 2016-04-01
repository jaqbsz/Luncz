#ifndef LDATABASE_H
#define LDATABASE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "SQLite\sqlite3.h"
#include "SQLiteCpp\SQLiteCpp.h"

#include "OrderList.h"
#include "UserList.h"
#include "Lrpc.h"

class LDatabase : public LRpc
{
  public:
    LDatabase();

    // TODO use interface for this
    QJsonValue ListUsers();
//    QJsonValue ListOrders();
//    QJsonValue AddUser(const QJsonValue &params);
//    QJsonValue AddOrder(const QJsonValue &params);
//    QJsonValue ModifyUser(const QJsonValue &params);
//    QJsonValue ModifyOrder(const QJsonValue &params);

  private:
    SQLite::Database db;         ///< Database connection
    UserList uList;
    OrderList oList;
};

#endif // LDATABASE_H
