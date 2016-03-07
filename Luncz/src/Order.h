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
  private:
    User * user;
    int menu_item;
    int price;

  public:
    Order(int m_i, User * u, int p) : user(u), menu_item(m_i), price(p){};
    int GetPrice()
    {
      return this->price;
    }
    int GetMenuItem()
    {
      return this->menu_item;
    }
    User * GetUser()
    {
      return this->user;
    }
};

#endif /* ORDER_H_ */
