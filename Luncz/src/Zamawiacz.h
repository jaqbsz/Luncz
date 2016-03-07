/*
 * Zamawiacz.h
 *
 *  Created on: 5 mar 2016
 *      Author: jszme
 */

#ifndef ZAMAWIACZ_H_
#define ZAMAWIACZ_H_

#include "User.h"
#include "OrderList.h"

class Zamawiacz: public User
{
  private:
    int id;

  public:
    Zamawiacz(string f_n, string l_n);
    ~Zamawiacz();

    void MakeOrder(OrderList * o_list); //as argument a list of orders
    int GetId();
    string GetType();
};

#endif /* ZAMAWIACZ_H_ */
