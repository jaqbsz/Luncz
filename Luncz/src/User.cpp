/*
 * User.cpp
 *
 *  Created on: 22 lut 2016
 *      Author: jszme
 */

#include "User.h"

User::User(SQLite::Database& Db_link, string f_n, string l_n) : type(NORMAL), db(Db_link)
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
      // Demonstrate how to get some typed column value
      this->id = select.getColumn(0).getInt();
      this->f_name = string(select.getColumn(1).getText());
      this->l_name = string(select.getColumn(2).getText());
      this->initials = string(select.getColumn(3).getText());
    }
  }
  catch (exception& e)
  {

  }
}

User::User(SQLite::Database& Db_link, string initials) : type(NORMAL), db(Db_link)
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
    }
  }
  catch (exception& e)
  {

  }
}

User::User(SQLite::Database& Db_link, int id) : type(NORMAL), db(Db_link)
{
  // TODO catch exception
  try
  {
    // Compile a SQL query
    SQLite::Statement select(this->db, "SELECT * FROM USERS_LIST WHERE id=:id");

    // Bind parameters of the SQL query
    select.bind(":id", id);

    // Loop to execute the query step by step, to get rows of result
    if (select.executeStep())
    {
      // Demonstrate how to get some typed column value
      this->id = select.getColumn(0).getInt();
      this->f_name = string(select.getColumn(1).getText());
      this->l_name = string(select.getColumn(2).getText());
      this->initials = string(select.getColumn(3).getText());
    }
  }
  catch (exception& e)
  {

  }
}

User::~User()
{

}

int User::GetId()
{
  return this->id;
}

string User::GetInitials()
{
  return this->initials;
}

string User::GetFName()
{
  return this->f_name;
}

string User::GetLName()
{
  return this->l_name;
}

usrtype User::GetType()
{
  return this->type;
}

void User::AddOrder(int menu_item, int cost)
{

}
void User::AddOrder(int menu_item, int cost, User & user)
{

}

void User::DeleteOrder()
{

}

void User::DeleteOrder(User & user)
{

}

void User::MakeOrder()
{

}
