/*
 * OrderList.cpp
 *
 *  Created on: 6 mar 2016
 *      Author: jszme
 */

#include "OrderList.h"
#include <iostream>

OrderList::OrderList(int max_orders) : max_orders(max_orders)
{

}

OrderList::~OrderList()
{
  // TODO Auto-generated destructor stub
}

bool OrderList::AddNewOrder(User * user, int price, int menu_item)
{
  bool ret = false;

  if ( user )
  {
    Order o = Order(menu_item, user, price);
    this->o_list.push_back(o);
    ret = true;
  }

  return ret;
}

int OrderList::DeleteOrder(User * user)
{
  int del_cnt = 0;

  for(list<Order>::iterator order = o_list.begin(); order != o_list.end();)
  {
    User *usr = order->GetUser();
    if (usr->GetId() == user->GetId())
    {
      order = this->o_list.erase(order);
      del_cnt++;
    }
    else
      order++;
  }

  return del_cnt;
}

void OrderList::ListOrders()
{
  cout<<"\nOrder list:"<<endl;
  cout<<"User ID: \t Menu item: \t Price:"<<endl;
  for(list<Order>::iterator order = o_list.begin(); order != o_list.end(); order++)
  {
    cout<<order->GetUser()->GetId();
    cout<<"\t\t ";
    cout<<order->GetMenuItem();
    cout<<"\t\t ";
    cout<<order->GetPrice()<<"zl"<<endl;
  }
}

int OrderList::GetOrderListValue()
{
  int sum = 0;

  cout<<"Order list value: ";

  for(list<Order>::iterator order = o_list.begin(); order != o_list.end(); order++)
  {
    sum += order->GetPrice();
  }

  cout<<sum<<"zl"<<endl;
  return sum;
}
