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

class LRpcResult : public LRpc
{
  public:
    LRpcResult();

    QJsonValue ListUsers();
    QJsonValue ListOrders();

    QJsonValue AddUser(const QJsonValue &params);
    QJsonValue AddOrder(const QJsonValue &params);

    QJsonValue DeleteUser(const QJsonValue &params);
    QJsonValue DeleteOrder(const QJsonValue &params);

    QJsonValue ModifyUser(const QJsonValue &params);
    QJsonValue ModifyOrder(const QJsonValue &params);

  private:
    SQLite::Database m_db;         ///< Database connection
    UserList m_uList;
    OrderList m_oList;
};

#endif // LDATABASE_H
