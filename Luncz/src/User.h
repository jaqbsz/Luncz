/*
 * User.h
 *
 *  Created on: 22 lut 2016
 *      Author: jszme
 */

#ifndef USER_H_
#define USER_H_

#include <string>
#include "SQLite\sqlite3.h"
#include "SQLiteCpp\SQLiteCpp.h"

using namespace std;

enum usrtype
{
  NORMAL,     // normal user
  CALLER,     // user that sends summarized info
};

class User
{
  private:
    string  f_name;
    string  l_name;
    string  initials;
    usrtype type;
    int id;

    SQLite::Database& db;    ///< Database connection

  public:
    User(SQLite::Database& Db_link, string f_n, string l_n);
    User(SQLite::Database& Db_link, string initials);
    User(SQLite::Database& Db_link, int id);
    ~User();

    string GetFName();
    string GetLName();
    string GetInitials();
    int GetId();
    usrtype GetType();

    void AddOrder(int menu_item, int cost);
    void AddOrder(int menu_item, int cost, User & user);

    void DeleteOrder();
    void DeleteOrder(User & user);

    void MakeOrder();
};

#endif /* USER_H_ */
