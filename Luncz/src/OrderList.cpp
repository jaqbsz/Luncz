/*
 * OrderList.cpp
 *
 *  Created on: 6 mar 2016
 *      Author: jszme
 */

#include "OrderList.h"
#include <iostream>

//**************************************************************************************
//* constructor
//*
//**************************************************************************************
OrderList::OrderList(SQLite::Database& Db_link) :
  m_db(Db_link),
  m_tableName("ORDER_LIST"),
  m_orderCnt(0)
{
  //TODO recalculate user IDs?
  //TODO catch exception
  //TODO add unique for initials

#ifdef TESTS
  m_db.exec("DROP TABLE IF EXISTS ORDER_LIST");
#endif

  try
  {
    // Test if the 'ORDER_LIST' table exists
    if ( !m_db.tableExists(m_tableName) )
    {
      // Begin transaction
      SQLite::Transaction transaction(m_db);

      // Compile a SQL query
      m_db.exec("CREATE TABLE ORDER_LIST    \
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
      m_orderCnt = m_db.execAndGet("SELECT Count(*) FROM ORDER_LIST");
    }
  }catch(exception& e)
  {

  }
}

//**************************************************************************************
//* deconstructor
//*
//**************************************************************************************
OrderList::~OrderList()
{

}

//**************************************************************************************
//* AddOrder
//*
//**************************************************************************************
Order OrderList::AddOrder(User & user, int price, int menu_item)
{
  //TODO catch exception
  //TODO check if user already exists

  // insert new order
  try
  {
    // Compile a SQL query
    SQLite::Statement insert(m_db, "INSERT INTO ORDER_LIST (date, user_id, price, menu_item) VALUES(:date, :u_id, :prc, :m_item)");

    // Bind parameters of the SQL query
    string date = m_db.execAndGet("SELECT date('now')").getText("???");
    insert.bind(":date", date);
    insert.bind(":u_id", user.Id());
    insert.bind(":prc", price);
    insert.bind(":m_item", menu_item);

    // Begin, execute and commit transaction
    SQLite::Transaction transaction(m_db);
    insert.exec();
    transaction.commit();

    // update order counter
    m_orderCnt = m_db.execAndGet("SELECT Count(*) FROM ORDER_LIST");
  }
  catch (exception& e)
  {

  }

  return GetOrder(m_db.getLastInsertRowid());
}

//**************************************************************************************
//* GetOrder
//*
//**************************************************************************************
Order OrderList::GetOrder(int id)
{
  // TODO catch exception

  Order order;

  try
  {
    // Compile a SQL query
    SQLite::Statement select(m_db, "SELECT * FROM ORDER_LIST WHERE id=:id");

    // Bind parameters of the SQL query
    select.bind(":id", id);

    // Loop to execute the query step by step, to get rows of result
    if (select.executeStep())
    {
      order.OrderId(select.getColumn(0).getInt());
      order.Date(string(select.getColumn(1).getText()));
      order.UserId(select.getColumn(2).getInt());
      order.Price(select.getColumn(3).getInt());
      order.MenuItem(select.getColumn(4).getInt());
      order.UserInitials(UserInitials(order.UserId()));
    }
  }
  catch (exception& e)
  {

  }

  return order;
}

//**************************************************************************************
//* UserInitials
//*
//**************************************************************************************
string OrderList::UserInitials(int uid)
{
  // TODO catch exception

  string initials = "--";

  try
  {
    // Compile a SQL query
    SQLite::Statement select(m_db, "SELECT * FROM USERS_LIST WHERE id=:u_id");

    // Bind parameters of the SQL query
    select.bind(":u_id", uid);

    // Loop to execute the query step by step, to get rows of result
    if (select.executeStep())
    {
      initials = string(select.getColumn(3).getText());
    }
  }
  catch (exception& e)
  {

  }

  return initials;
}

//**************************************************************************************
//* DeleteOrder
//*
//**************************************************************************************
int OrderList::DeleteOrder(User & user)
{
  int del_cnt = 0;

  try
  {
    // Compile a SQL query
    SQLite::Statement del(m_db, "DELETE FROM ORDER_LIST WHERE user_id = :u_id");

    // Bind parameters of the SQL query
    del.bind(":u_id", user.Id());

    del_cnt = del.executeStep();

    // update order counter
    m_orderCnt = m_db.execAndGet("SELECT Count(*) FROM ORDER_LIST");

    //TODO update id to nextid-1
  }
  catch (exception& e)
  {

  }

  return del_cnt;
}

//**************************************************************************************
//* DeleteOrder
//*
//**************************************************************************************
void OrderList::DeleteOrder(Order & order)
{
  try
  {
    int orderId = order.OrderId();

    // Compile a SQL query
    SQLite::Statement del(m_db, "DELETE FROM ORDER_LIST WHERE id = :o_id");

    // Bind parameters of the SQL query
    del.bind(":o_id", orderId);

    // execute sql query
    del.executeStep();

    // update order counter
    m_orderCnt = m_db.execAndGet("SELECT Count(*) FROM ORDER_LIST");

    // update id to nextid-1
    for (int i = 0; i < m_orderCnt; i++)
    {
      //prepare update statement
      SQLite::Statement upd(m_db, "UPDATE ORDER_LIST SET id = :new_id WHERE id = :old_id");

      upd.bind(":new_id", orderId+i);
      upd.bind(":old_id", orderId+i+1);

      upd.executeStep();
    }

    // reset autoincrement base value
    m_db.exec("UPDATE SQLITE_SEQUENCE SET seq = 0 WHERE NAME = 'ORDER_LIST'");
  }
  catch (exception& e)
  {

  }
}

//**************************************************************************************
//* GetOrderCounter
//*
//**************************************************************************************
int OrderList::GetOrderCounter()
{
  return m_orderCnt;
}

//**************************************************************************************
//* GetOrderCounterDate
//*
//**************************************************************************************
int OrderList::GetOrderCounterDate(string date)
{
  //TODO validate date string

  int ret_cnt = 0;

  // count orders
  try
  {
    // Compile a SQL query
    SQLite::Statement sel(m_db, "SELECT Count(date) FROM ORDER_LIST WHERE date=:date");

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

//**************************************************************************************
//* GetOrderCounterToday
//*
//**************************************************************************************
int OrderList::GetOrderCounterToday()
{
  int ret_cnt = 0;

  // count orders
  try
  {
    string date = m_db.execAndGet("SELECT date('now')").getText("???");

    // Compile a SQL query
    SQLite::Statement sel(m_db, "SELECT Count(date) FROM ORDER_LIST WHERE date=:date");

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

//**************************************************************************************
//* GetOrderPriceSum
//*
//**************************************************************************************
int OrderList::GetOrderPriceSum()
{
  int ret_val = 0;

  string date;

  // get current date
  try
  {
    date = m_db.execAndGet("SELECT date('now')").getText("???");
  }
  catch (exception& e)
  {

  }

  // select orders for specified day
  try
  {
    // Compile a SQL query
    SQLite::Statement sel(m_db, "SELECT price FROM ORDER_LIST WHERE date=:date");

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

//**************************************************************************************
//* GetOrderPriceSum
//*
//**************************************************************************************
int OrderList::GetOrderPriceSum(string date)
{
  int ret_val = 0;

  // select orders for specified day
  try
  {
    // Compile a SQL query
    SQLite::Statement sel(m_db, "SELECT price FROM ORDER_LIST WHERE date=:date");

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


