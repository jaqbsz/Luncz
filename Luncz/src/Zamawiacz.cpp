/*
 * Zamawiacz.cpp
 *
 *  Created on: 5 mar 2016
 *      Author: jszme
 */

#include "Zamawiacz.h"

Zamawiacz::Zamawiacz(string f_n, string l_n) : User(f_n, l_n)
{
  this->id = User::GetId();
}

Zamawiacz::~Zamawiacz()
{
  // TODO Auto-generated destructor stub
}

string Zamawiacz::GetType()
{
  return "Zamawiacz";
}

int Zamawiacz::GetId()
{
  return this->id;
}

void Zamawiacz::MakeOrder(OrderList * o_list)
{
  o_list->ListOrders();
  o_list->GetOrderListValue();
}
