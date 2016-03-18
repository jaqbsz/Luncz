/*
 * OrderList.cpp
 *
 *  Created on: 6 mar 2016
 *      Author: jszme
 */

#include "OrderList.h"
#include <iostream>

OrderList::OrderList(SQLite::Database& Db_link) :
  db(Db_link),
  table_name("ORDER_LIST"),
  order_cnt(0)
{
  //TODO recalculate user IDs?
  //TODO catch exception
  //TODO add unique for initials

  try
  {
    // Test if the 'ORDER_LIST' table exists
    if ( !this->db.tableExists(table_name) )
    {
      // Begin transaction
      SQLite::Transaction transaction(this->db);

      // Compile a SQL query
      this->db.exec("CREATE TABLE ORDER_LIST    \
                    (id        INTEGER NOT NULL, \
                     date      TEXT NOT NULL, \
                     user_id   INTEGER NOT NULL, \
                     price     INTEGER NOT NULL, \
                     menu_item TEXT NOT NULL, \
                     FOREIGN KEY(user_id) REFERENCES USERS_LIST(id), \
                     PRIMARY KEY(ID))");

      // Commit transaction
      transaction.commit();
    }
  }catch(exception& e)
  {

  }
}

OrderList::~OrderList()
{

}

bool OrderList::AddNewOrder(User & user, int price, int menu_item)
{
  //TODO catch exception
  //TODO check if user already exists
  bool ret = false;
  string date;

  // update order counter
  try
  {
    this->order_cnt = db.execAndGet("SELECT Count(*) FROM ORDER_LIST");
    date = db.execAndGet("SELECT date('now')").getText("???");
  }
  catch (exception& e)
  {

  }

  // insert new order
  try
  {
    // Compile a SQL query
    SQLite::Statement insert(this->db, "INSERT INTO ORDER_LIST (date, user_id, price, menu_item) VALUES(:date, :u_id, :prc, :m_item)");

    // Bind parameters of the SQL query
    insert.bind(":date", date);
    insert.bind(":u_id", user.GetId());
    insert.bind(":prc", price);
    insert.bind(":m_item", menu_item);


    // Begin, execute and commit transaction
    SQLite::Transaction transaction(this->db);
    insert.exec();
    transaction.commit();
  }
  catch (exception& e)
  {

  }

  return ret;
}

int OrderList::DeleteOrder(User & user)
{
  int del_cnt = 0;

  // delete elements
  try
  {
    // Compile a SQL query
    SQLite::Statement del(this->db, "DELETE FROM ORDER_LIST WHERE user_id = :u_id");

    // Bind parameters of the SQL query
    del.bind(":u_id", user.GetId());

    del_cnt = del.executeStep();
  }
  catch (exception& e)
  {

  }

  // recalculate order counter
  try
  {
    this->order_cnt = db.execAndGet("SELECT Count(*) FROM ORDER_LIST");
  }
  catch (exception& e)
  {

  }

  return del_cnt;
}

int OrderList::GetOrderCounter()
{
  return this->order_cnt;
}

int OrderList::GetOrderCounterDate(string date)
{
  //TODO validate date string

  int ret_cnt = 0;

  // count orders
  try
  {
    // Compile a SQL query
    SQLite::Statement sel(this->db, "SELECT Count(date) FROM ORDER_LIST WHERE date=:date");

    // Bind parameters of the SQL query
    sel.bind(":date", date);

    // Execute the query
    if (sel.executeStep())
    {
      ret_cnt = sel.getColumn(0).getInt();
    }
  }
  catch (exception& e)
  {

  }

  return ret_cnt;
}

int OrderList::GetOrderCounterToday()
{
  int ret_cnt = 0;

  // count orders
  try
  {
    string date = db.execAndGet("SELECT date('now')").getText("???");

    // Compile a SQL query
    SQLite::Statement sel(this->db, "SELECT Count(date) FROM ORDER_LIST WHERE date=:date");

    // Bind parameters of the SQL query
    sel.bind(":date", date);

    // Execute the query
    if (sel.executeStep())
    {
      ret_cnt = sel.getColumn(0).getInt();
    }
  }
  catch (exception& e)
  {

  }

  return ret_cnt;
}

int OrderList::GetOrderPriceSum()
{
  int ret_val = 0;

  string date;

  // get current date
  try
  {
    date = db.execAndGet("SELECT date('now')").getText("???");
  }
  catch (exception& e)
  {

  }

  // select orders for specified day
  try
  {
    // Compile a SQL query
    SQLite::Statement sel(this->db, "SELECT price FROM ORDER_LIST WHERE date=:date");

    // Bind parameters of the SQL query
    sel.bind(":date", date);

    // Execute the query
    while ( sel.executeStep() )
    {
      ret_val += sel.getColumn(0).getInt();
    }
  }
  catch (exception& e)
  {

  }

  return ret_val;
}

int OrderList::GetOrderPriceSum(string date)
{
  int ret_val = 0;

  // select orders for specified day
  try
  {
    // Compile a SQL query
    SQLite::Statement sel(this->db, "SELECT price FROM ORDER_LIST WHERE date=:date");

    // Bind parameters of the SQL query
    sel.bind(":date", date);

    // Execute the query
    while ( sel.executeStep() )
    {
      ret_val += sel.getColumn(0).getInt();
    }
  }
  catch (exception& e)
  {

  }

  return ret_val;
}


