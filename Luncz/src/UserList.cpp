/*
 * UserList.cpp
 *
 *  Created on: 6 mar 2016
 *      Author: jszme
 */

#include "UserList.h"
#include <iostream>
#include <typeinfo>

//**************************************************************************************
//* constructor
//*
//**************************************************************************************
UserList::UserList(SQLite::Database& Db_link) :
    m_db(Db_link),
    table_name("USERS_LIST"),
    m_userCnt(0)
{
  //TODO catch exception
  //TODO add unique for initials

#ifdef TESTS
  db.exec("DROP TABLE IF EXISTS USERS_LIST");
#endif

  try
  {
    // check if the 'USERS_LIST' table exists
    if ( !m_db.tableExists(table_name) )
    {
      // Begin transaction
      SQLite::Transaction transaction(m_db);

      // Compile a SQL query
      m_db.exec("CREATE TABLE USERS_LIST    \
                (id        INTEGER PRIMARY KEY AUTOINCREMENT, \
                 f_name    TEXT NOT NULL, \
                 l_name    TEXT NOT NULL, \
                 initials  TEXT NOT NULL, \
                 type      TEXT NOT NULL)");

      // Commit transaction
      transaction.commit();
    }
    else
    {
      m_userCnt = m_db.execAndGet("SELECT Count(*) FROM USERS_LIST");
    }
  }catch(exception& e)
  {

  }
}

//**************************************************************************************
//* deconstructor
//*
//**************************************************************************************
UserList::~UserList()
{
  ;
}

//**************************************************************************************
//* AddUser
//*
//**************************************************************************************
User UserList::AddUser(string f_n, string l_n, string initials)
{
  //TODO add auto initials generation
  //TODO catch exception
  //TODO check if user already exists

  // insert new user
  try
  {
    // Compile a SQL query
    SQLite::Statement insert(m_db, "INSERT INTO USERS_LIST (f_name, l_name, initials, type) VALUES(:f_n, :l_n, :initials, :type)");

    int type = static_cast <std::size_t>( UType::U_TYPE_NORMAL );

    // Bind parameters of the SQL query
    insert.bind(":initials", initials);
    insert.bind(":f_n", f_n);
    insert.bind(":l_n", l_n);
    insert.bind(":type", type );

    // Begin, execute and commit transaction
    SQLite::Transaction transaction(m_db);
    insert.exec();
    transaction.commit();

    // update user count
    m_userCnt = m_db.execAndGet("SELECT Count(*) FROM USERS_LIST");
  }
  catch (exception& e)
  {

  }

  return GetUser(m_db.getLastInsertRowid());
}

//**************************************************************************************
//* GetUser
//*
//**************************************************************************************
User UserList::GetUser(int id)
{
  // TODO catch exception

  User usr;

  try
  {
    // Compile a SQL query
    SQLite::Statement select(m_db, "SELECT * FROM USERS_LIST WHERE id=:id");

    // Bind parameters of the SQL query
    select.bind(":id", id);

    // execute the query
    if (select.executeStep())
    {
      usr.Id(select.getColumn(0).getInt());
      usr.FName(string(select.getColumn(1).getText()));
      usr.LName(string(select.getColumn(2).getText()));
      usr.Initials(string(select.getColumn(3).getText()));
      usr.Type(static_cast<UType> (select.getColumn(4).getInt()));
    }
  }
  catch (exception& e)
  {

  }

  return usr;
}

//**************************************************************************************
//* GetUser
//*
//**************************************************************************************
User UserList::GetUser(string initials)
{
  // TODO catch exception

  User usr;

  try
  {
    // Compile a SQL query
    SQLite::Statement select(m_db, "SELECT * FROM USERS_LIST WHERE initials=:initials");

    // Bind parameters of the SQL query
    select.bind(":initials", initials);

    // Loop to execute the query step by step, to get rows of result
    if (select.executeStep())
    {
      usr.Id(select.getColumn(0).getInt());
      usr.FName(string(select.getColumn(1).getText()));
      usr.LName(string(select.getColumn(2).getText()));
      usr.Initials(string(select.getColumn(3).getText()));
      usr.Type(static_cast<UType> (select.getColumn(4).getInt()));
    }
  }
  catch (exception& e)
  {

  }

  return usr;
}

//**************************************************************************************
//* GetUser
//*
//**************************************************************************************
User UserList::GetUser(string f_n, string l_n)
{
  // TODO catch exception

  User usr;

  try
  {
    // Compile a SQL query
    SQLite::Statement select(m_db, "SELECT * FROM USERS_LIST WHERE f_name=:f_n AND l_name=:l_n");

    // Bind parameters of the SQL query
    select.bind(":f_n", f_n);
    select.bind(":l_n", l_n);

    // Loop to execute the query step by step, to get rows of result
    if (select.executeStep())
    {
      usr.Id(select.getColumn(0).getInt());
      usr.FName(string(select.getColumn(1).getText()));
      usr.LName(string(select.getColumn(2).getText()));
      usr.Initials(string(select.getColumn(3).getText()));
      usr.Type(static_cast<UType> (select.getColumn(4).getInt()));
    }
  }
  catch (exception& e)
  {

  }
  return usr;
}

//**************************************************************************************
//* DeleteUser
//*
//**************************************************************************************
bool UserList::DeleteUser(int id)
{
  //TODO catch exception
  //TODO recalculate user IDs

  bool ret = false;

  try
  {
    // Compile a SQL query
    SQLite::Statement del(m_db, "DELETE FROM USERS_LIST WHERE id = :id");

    // Bind parameters of the SQL query
    del.bind(":id", id);

    ret = static_cast <bool> (del.executeStep());

    // update user count
    m_userCnt = m_db.execAndGet("SELECT Count(*) FROM USERS_LIST");

    // update id to nextid-1
    for (int i = 0; i < m_userCnt; i++)
    {
      //prepare update statement
      SQLite::Statement upd(m_db, "UPDATE USERS_LIST SET id = :new_id WHERE id = :old_id");

      upd.bind(":new_id", id+i);
      upd.bind(":old_id", id+i+1);

      upd.executeStep();
    }

    // reset autoincrement base value
    m_db.exec("UPDATE SQLITE_SEQUENCE SET seq = 0 WHERE NAME = 'USERS_LIST'");
  }
  catch (exception& e)
  {

  }

  return ret;
}
