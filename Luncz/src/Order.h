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
    Order() : m_menuItem{},
              m_price{0},
              m_uId{0},
              m_oId{0},
              m_oDate{"----"},
              m_uInitials{"--"}
     {}

    int Price()     { return m_price; }
    int MenuItem()  { return m_menuItem; }
    string Date()   { return m_oDate; }
    int UserId()    { return m_uId; }
    int OrderId()   { return m_oId; }
    string UserInitials() { return m_uInitials; }

    void Price    ( int price )   { m_price = price; }
    void MenuItem ( int mitem )   { m_menuItem = mitem; }
    void Date     ( string date ) { m_oDate = date; }
    void UserId   ( int uid )     { m_uId = uid; }
    void OrderId  ( int oid )     { m_oId = oid; }
    void UserInitials(string initials) { m_uInitials = initials; }

  private:
    int m_menuItem;
    int m_price;
    int m_uId;
    int m_oId;
    string m_oDate;
    string m_uInitials;
};

#endif /* ORDER_H_ */
