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

UserList::UserList(SQLite::Database& Db_link) :
    db(Db_link),
    table_name("USERS_LIST"),
    user_cnt(0)
{
  //TODO recalculate user IDs
  //TODO catch exception
  //TODO add unique for initials

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
                     type      TEXT NOT NULL, \
                     PRIMARY   KEY(id))");

      // Commit transaction
      transaction.commit();
    }
    else
    {
      this->user_cnt = db.execAndGet("SELECT Count(*) FROM USERS_LIST");
    }
  }catch(exception& e)
  {

  }
}

UserList::~UserList()
{
  ;
}

User UserList::AddUser(string f_n, string l_n, string initials)
{
  //TODO add auto initials generation
  //TODO catch exception
  //TODO check if user already exists

  // insert new user
  try
  {
    // Compile a SQL query
    SQLite::Statement insert(this->db, "INSERT INTO USERS_LIST (f_name, l_name, initials, type) VALUES(:f_n, :l_n, :initials, :type)");

    // Bind parameters of the SQL query
    insert.bind(":initials", initials);
    insert.bind(":f_n", f_n);
    insert.bind(":l_n", l_n);
    insert.bind(":type", usrtype::U_TYPE_NORMAL);

    // Begin, execute and commit transaction
    SQLite::Transaction transaction(this->db);
    insert.exec();
    transaction.commit();

    // update user count
    this->user_cnt = db.execAndGet("SELECT Count(*) FROM USERS_LIST");
  }
  catch (exception& e)
  {

  }

  User user = User(this->db, this->db.getLastInsertRowid());

  return user;
}

bool UserList::DeleteUser(int id)
{
  //TODO catch exception
  //TODO recalculate user IDs

  bool ret = false;

  try
  {
    // Compile a SQL query
    SQLite::Statement del(this->db, "DELETE FROM USERS_LIST WHERE id = :id");

    // Bind parameters of the SQL query
    del.bind(":id", id);

    ret = (bool) del.executeStep();

    // update user count
    this->user_cnt = db.execAndGet("SELECT Count(*) FROM USERS_LIST");
  }
  catch (exception& e)
  {

  }

  return ret;
}
