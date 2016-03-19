/*
 * Order.h
 *
 *  Created on: 5 mar 2016
 *      Author: jszme
 */

#ifndef ORDER_H_
#define ORDER_H_

#include "User.h"

class Order
{
  public:
    Order(SQLite::Database& Db_link, int id);

    int GetPrice()
    {
      return this->price;
    }

    int GetMenuItem()
    {
      return this->menu_item;
    }

    string GetDate()
    {
      return this->date;
    }

    int GetUserId()
    {
      return this->user_id;
    }

    int GetId()
    {
      return this->id;
    }

  private:
    int menu_item;
    int price;
    int user_id;
    int id;
    string date;

    SQLite::Database& db;
};

#endif /* ORDER_H_ */
