/*
 * UserList.h
 *
 *  Created on: 6 mar 2016
 *      Author: jszme
 */

#ifndef USERLIST_H_
#define USERLIST_H_

using namespace std;
#include "SQLite\sqlite3.h"
#include "SQLiteCpp\SQLiteCpp.h"
#include "User.h"

class UserList
{
  private:
    SQLite::Database& db;    ///< Database connection
    const int max_users;          ///< Max number of users
    const char *table_name;

  public:
    UserList(SQLite::Database& Db_link, int max_usr);
    ~UserList();

    /**
     * @brief Adds new user to the user list
     */
    User * AddUser(string f_n, string l_n, string initials);

    /**
     * @brief Returns pointer to User object with data retrieved from the user list table
     */
    User * GetUser(int id);

    /**
     * @brief Deletes user with provided id number
     */
    bool DeleteUser(int id);
};

#endif /* USERLIST_H_ */
