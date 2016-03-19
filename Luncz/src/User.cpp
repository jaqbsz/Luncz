/*
 * User.cpp
 *
 *  Created on: 22 lut 2016
 *      Author: jszme
 */

#include "User.h"
#include "OrderList.h"

User::User(SQLite::Database& Db_link, string f_n, string l_n) : db(Db_link)
{
  // TODO catch exception
  try
  {
    // Compile a SQL query
    SQLite::Statement select(this->db, "SELECT * FROM USERS_LIST WHERE f_name=:f_n AND l_name=:l_n");

    // Bind parameters of the SQL query
    select.bind(":f_n", f_n);
    select.bind(":l_n", l_n);

    // Loop to execute the query step by step, to get rows of result
    if (select.executeStep())
    {
      this->id = select.getColumn(0).getInt();
      this->f_name = string(select.getColumn(1).getText());
      this->l_name = string(select.getColumn(2).getText());
      this->initials = string(select.getColumn(3).getText());
      this->type = static_cast<usrtype> (select.getColumn(4).getInt());
    }
  }
  catch (exception& e)
  {

  }
}

User::User(SQLite::Database& Db_link, string initials) : db(Db_link)
{
  // TODO catch exception
  try
  {
    // Compile a SQL query
    SQLite::Statement select(this->db, "SELECT * FROM USERS_LIST WHERE initials=:initials");

    // Bind parameters of the SQL query
    select.bind(":initials", initials);

    // Loop to execute the query step by step, to get rows of result
    if (select.executeStep())
    {
      // Demonstrate how to get some typed column value
      this->id = select.getColumn(0).getInt();
      this->f_name = string(select.getColumn(1).getText());
      this->l_name = string(select.getColumn(2).getText());
      this->initials = string(select.getColumn(3).getText());
      this->type = static_cast<usrtype> (select.getColumn(4).getInt());
    }
  }
  catch (exception& e)
  {

  }
}

User::User(SQLite::Database& Db_link, int id) : db(Db_link)
{
  // TODO catch exception
  try
  {
    // Compile a SQL query
    SQLite::Statement select(this->db, "SELECT * FROM USERS_LIST WHERE id=:id");

    // Bind parameters of the SQL query
    select.bind(":id", id);

    // execute the query
    if (select.executeStep())
    {
      this->id = select.getColumn(0).getInt();
      this->f_name = string(select.getColumn(1).getText());
      this->l_name = string(select.getColumn(2).getText());
      this->initials = string(select.getColumn(3).getText());
      this->type = static_cast<usrtype> (select.getColumn(4).getInt());
    }
  }
  catch (exception& e)
  {

  }
}

User::~User()
{

}
