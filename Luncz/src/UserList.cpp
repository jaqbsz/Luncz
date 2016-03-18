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
                     PRIMARY   KEY(id))");

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

int UserList::AddUser(string f_n, string l_n, string initials)
{
  //TODO add auto initials generation
  //TODO catch exception
  //TODO check if user already exists

  int newUsr_id = 0;
  int usr_cnt = 0;

  // check user count
  try
  {
    usr_cnt = db.execAndGet("SELECT Count(*) FROM USERS_LIST");
  }
  catch (exception& e)
  {

  }

  if ( usr_cnt < this->max_users )
  {
    // insert new user
    try
    {
      // Compile a SQL query
      SQLite::Statement insert(this->db, "INSERT INTO USERS_LIST (f_name, l_name, initials) VALUES(:f_n, :l_n, :initials)");

      // Bind parameters of the SQL query
      insert.bind(":initials", initials);
      insert.bind(":f_n", f_n);
      insert.bind(":l_n", l_n);

      // Begin, execute and commit transaction
      SQLite::Transaction transaction(this->db);
      insert.exec();
      transaction.commit();
    }
    catch (exception& e)
    {

    }

    // get new id
    try
    {
      // Compile a SQL query
      SQLite::Statement sel(this->db, "SELECT id FROM USERS_LIST WHERE f_name=:f_n AND l_name=:l_n");

      // Bind parameters of the SQL query
      sel.bind(":f_n", f_n);
      sel.bind(":l_n", l_n);

      // Execute the query
      if (sel.executeStep())
      {
        newUsr_id = sel.getColumn(0).getInt();
      }
    }
    catch (exception& e)
    {

    }
  }
  return newUsr_id;
}

bool UserList::DeleteUser(int id)
{
  //TODO catch exception

  bool ret = false;

  try
  {
    // Compile a SQL query
    SQLite::Statement del(this->db, "DELETE FROM USERS_LIST WHERE id = :id");

    // Bind parameters of the SQL query
    del.bind(":id", id);

    ret = (bool) del.executeStep();
  }
  catch (exception& e)
  {

  }

  return ret;
}
