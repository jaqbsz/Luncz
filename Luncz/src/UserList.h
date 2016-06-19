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
    explicit UserList(SQLite::Database& Db_link);

    ~UserList();

    /**
     * @brief Adds new user to the user list
     */
    User AddUser(string f_n, string l_n, string initials);

    /**
     * @brief Gets existing user by id
     */
    User GetUser(int id);

    /**
     * @brief Gets existing user by initials
     */
    User GetUser(string initials);

    /**
     * @brief Gets existing user by fname and lname
     */
    User GetUser(string f_n, string l_n);

    /**
     * @brief Deletes user with provided id number
     */
    bool DeleteUser(int id);

    /**
     * @brief Returns number of available users
     */
    int GetUserCounter() { return m_userCnt; }

  private:
    SQLite::Database& m_db;         ///< Database connection
    const char *table_name;
    int m_userCnt;
};

#endif /* USERLIST_H_ */
