/*
 * Order.cpp
 *
 *  Created on: 5 mar 2016
 *      Author: jszme
 */

#include "Order.h"


Order::Order(SQLite::Database& Db_link, int id) :
  db(Db_link)
{
  // TODO catch exception
  try
  {
    // Compile a SQL query
    SQLite::Statement select(this->db, "SELECT * FROM ORDER_LIST WHERE id=:id");

    // Bind parameters of the SQL query
    select.bind(":id", id);

    // Loop to execute the query step by step, to get rows of result
    if (select.executeStep())
    {
      this->id = select.getColumn(0).getInt();
      this->date = string(select.getColumn(1).getText());
      this->user_id = select.getColumn(2).getInt();
      this->price = select.getColumn(3).getInt();
      this->menu_item = select.getColumn(4).getInt();
    }
  }
  catch (exception& e)
  {

  }
}
