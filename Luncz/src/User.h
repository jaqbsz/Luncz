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
  U_TYPE_NORMAL,     // normal user
  U_TYPE_CALLER,     // user that sends summarized info
  U_TYPE_MAX
};

const string u_type[U_TYPE_MAX] = {"NORMAL", "CALLER"};

class User
{
  public:
    User(SQLite::Database& Db_link, string f_n, string l_n);
    User(SQLite::Database& Db_link, string initials);
    User(SQLite::Database& Db_link, int id);
    ~User();

    string GetFName()
    {
      return this->f_name;
    }

    string GetLName()
    {
      return this->l_name;
    }

    string GetInitials()
    {
      return this->initials;
    }

    int GetId()
    {
      return this->id;
    }

    usrtype GetTypeInt()
    {
      return this->type;
    }

    string GetTypeString()
    {
      return u_type[this->type];
    }

  private:
    string  f_name;
    string  l_name;
    string  initials;
    usrtype type;
    int id;

    SQLite::Database& db;    ///< Database connection
};

#endif /* USER_H_ */
