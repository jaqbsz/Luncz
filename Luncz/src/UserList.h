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
  public:
    UserList(SQLite::Database& Db_link);
    ~UserList();

    /**
     * @brief Adds new user to the user list
     */
    User AddUser(string f_n, string l_n, string initials);

    /**
     * @brief Deletes user with provided id number
     */
    bool DeleteUser(int id);

    /**
     * @brief Returns number of available users
     */
    int GetUserCounter()
    {
      return this->user_cnt;
    }

  private:
    SQLite::Database& db;         ///< Database connection
    const char *table_name;
    int user_cnt;
};

#endif /* USERLIST_H_ */
