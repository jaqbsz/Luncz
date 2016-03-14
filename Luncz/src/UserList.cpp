/*
 * UserList.cpp
 *
 *  Created on: 6 mar 2016
 *      Author: jszme
 */

#include "UserList.h"
#include "Zamawiacz.h"
#include <iostream>
#include <typeinfo>

UserList::UserList(SQLite::Database& Db_link, int max_usr) :
    db(Db_link),
    max_users(max_usr),
    table_name("USERS_LIST")
{
  //TODO recalculate user IDs
  //TODO catch exception

  try
  {
    // Test if the 'USERS_LIST' table exists
    if ( !this->db.tableExists(table_name) )
    {
      // Begin transaction
      SQLite::Transaction transaction(this->db);

      // Compile a SQL query
      this->db.exec("CREATE TABLE USERS_LIST    \
                    (id        INTEGER NOT NULL, \
                     f_name    TEXT NOT NULL, \
                     l_name    TEXT NOT NULL, \
                     initials  TEXT NOT NULL, \
                     PRIMARY   KEY(ID))");

      // Commit transaction
      transaction.commit();
    }
  }catch(exception& e)
  {

  }
}

UserList::~UserList()
{
  ;
}

User* UserList::AddUser(string f_n, string l_n, string initials)
{
  //TODO add initials.toUpperCase();
  //TODO check against too much users
  //TODO return real user ID.
  //TODO catch exception
  //TODO check if user already exists

  int newUsr_id = 0;

  try
  {
    // Compile a SQL query
    SQLite::Statement insert(this->db, "INSERT INTO USERS_LIST (f_name, l_name, initials) VALUES(:f_n, :l_n, :initials)");

    // Bind parameters of the SQL query
    insert.bind(":initials", initials);
    insert.bind(":f_n", f_n);
    insert.bind(":l_n", l_n);

    // Begin transaction
    SQLite::Transaction transaction(this->db);

    // execute earlier prepared query
    insert.exec();

    // Commit transaction
    transaction.commit();
  }
  catch (exception& e)
  {

  }

  return GetUser(newUsr_id);
}

bool UserList::DeleteUser(int id)
{
  //TODO catch exception

  bool ret = false;

  try
  {
    // Compile a SQL query
    SQLite::Statement select(this->db, "DELETE FROM USERS_LIST WHERE id = :id");

    // Bind parameters of the SQL query
    select.bind(":id", id);

    ret = (bool) select.executeStep();
  }
  catch (exception& e)
  {

  }

  return ret;
}

User * UserList::GetUser(int id)
{
  User * u = NULL;

  return u;
}
