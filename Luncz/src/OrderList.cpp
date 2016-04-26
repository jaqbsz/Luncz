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

#ifdef TESTS
  this->db.exec("DROP TABLE IF EXISTS ORDER_LIST");
#endif

  try
  {
    // Test if the 'ORDER_LIST' table exists
    if ( !this->db.tableExists(table_name) )
    {
      // Begin transaction
      SQLite::Transaction transaction(this->db);

      // Compile a SQL query
      this->db.exec("CREATE TABLE ORDER_LIST    \
                    (id        INTEGER PRIMARY KEY AUTOINCREMENT,\
                     date      TEXT NOT NULL, \
                     user_id   INTEGER NOT NULL, \
                     price     INTEGER NOT NULL, \
                     menu_item TEXT NOT NULL, \
                     FOREIGN KEY(user_id) REFERENCES USERS_LIST(id))");

      // Commit transaction
      transaction.commit();
    }
    else
    {
      this->order_cnt = db.execAndGet("SELECT Count(*) FROM ORDER_LIST");
    }
  }catch(exception& e)
  {

  }


  {
    Order order = Order(this->db, 2);
    DeleteOrder(order);
  }
}

OrderList::~OrderList()
{

}

Order OrderList::AddOrder(User & user, int price, int menu_item)
{
  //TODO catch exception
  //TODO check if user already exists

  // insert new order
  try
  {
    // Compile a SQL query
    SQLite::Statement insert(this->db, "INSERT INTO ORDER_LIST (date, user_id, price, menu_item) VALUES(:date, :u_id, :prc, :m_item)");

    // Bind parameters of the SQL query
    string date = db.execAndGet("SELECT date('now')").getText("???");
    insert.bind(":date", date);
    insert.bind(":u_id", user.GetId());
    insert.bind(":prc", price);
    insert.bind(":m_item", menu_item);

    // Begin, execute and commit transaction
    SQLite::Transaction transaction(this->db);
    insert.exec();
    transaction.commit();

    // update order counter
    this->order_cnt = db.execAndGet("SELECT Count(*) FROM ORDER_LIST");
  }
  catch (exception& e)
  {

  }

  Order order = Order(this->db, this->db.getLastInsertRowid());

  return order;
}

int OrderList::DeleteOrder(User & user)
{
  //TODO recalculate order IDs!!!

  int del_cnt = 0;

  // delete elements
  try
  {
    // Compile a SQL query
    SQLite::Statement del(this->db, "DELETE FROM ORDER_LIST WHERE user_id = :u_id");

    // Bind parameters of the SQL query
    del.bind(":u_id", user.GetId());

    del_cnt = del.executeStep();

    // update order counter
    this->order_cnt = db.execAndGet("SELECT Count(*) FROM ORDER_LIST");
  }
  catch (exception& e)
  {

  }

  return del_cnt;
}

void OrderList::DeleteOrder(Order & order)
{
  //TODO recalculate order IDs

  // delete elements
  try
  {
    int orderId = order.GetId();

    // Compile a SQL query
    SQLite::Statement del(this->db, "DELETE FROM ORDER_LIST WHERE id = :o_id");

    // Bind parameters of the SQL query
    del.bind(":o_id", orderId);

    // execute sql query
    del.executeStep();

    // update order counter
    this->order_cnt = db.execAndGet("SELECT Count(*) FROM ORDER_LIST");

    // update id to nextid-1
    for (int i = 0; i < this->order_cnt; i++)
    {
      //prepare update statement
      SQLite::Statement upd(this->db, "UPDATE ORDER_LIST SET id = :new_id WHERE id = :old_id");

      upd.bind(":new_id", orderId+i);
      upd.bind(":old_id", orderId+i+1);

      upd.executeStep();
    }

    // reset autoincrement base value
    db.exec("UPDATE SQLITE_SEQUENCE SET seq = 0 WHERE NAME = 'ORDER_LIST'");
  }
  catch (exception& e)
  {

  }
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


