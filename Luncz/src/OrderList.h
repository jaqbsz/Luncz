/*
 * OrderList.h
 *
 *  Created on: 6 mar 2016
 *      Author: jszme
 */

#ifndef ORDERLIST_H_
#define ORDERLIST_H_

using namespace std;

#include <list>
#include "Order.h"
#include "User.h"

class OrderList
{
  private:
   const int max_orders;
   list<Order> o_list ;

  public:
    OrderList(int max_orders);
    ~OrderList();
    bool AddNewOrder(User * user, int price, int menu_item);
    void ListOrders();
    int GetOrderListValue();
    int DeleteOrder(User * user);
};

#endif /* ORDERLIST_H_ */
