/*
 * OrderList.h
 *
 *  Created on: 6 mar 2016
 *      Author: jszme
 */

#ifndef ORDERLIST_H_
#define ORDERLIST_H_

using namespace std;

#include "Order.h"
#include "User.h"

class OrderList
{
  public:
    OrderList(SQLite::Database& Db_link);
    ~OrderList();

    /**
     * @brief Adds new order to the list
     */
    Order AddNewOrder(User & user, int price, int menu_item);

    /**
     * @brief Deletes orders added for provided user
     * @return Returns number of deleted elements
     */
    int DeleteOrder(User & user);
    /**
     * @brief Deletes privided order from the list
     */
    void DeleteOrder(Order & order);

    /**
     * @brief Returns total number of orders
     */
    int GetOrderCounter();
    /**
     * @brief Returns number of orders for specified day
     */
    int GetOrderCounterDate(string date);
    /**
     * @brief Returns number of orders for today
     */
    int GetOrderCounterToday();

    /**
     * @brief Returns value of orders for today
     */
    int GetOrderPriceSum();
    /**
     * @brief Returns value of orders for specified day
     */
    int GetOrderPriceSum(string date);

  private:
    SQLite::Database& db;         ///< Database connection
    const char *table_name;
    int order_cnt;
};

#endif /* ORDERLIST_H_ */
