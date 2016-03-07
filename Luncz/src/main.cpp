
#include <iostream>
#include <typeinfo>
#include "Zamawiacz.h"
#include "OrderList.h"
#include "UserList.h"

using namespace std;

const int USER_CNT = 10;
const int ORDER_CNT = 10;

int main(int argc, char **argv)
{
  User *u_table[USER_CNT];
  for (int i = 0; i < USER_CNT;i++){u_table[i] = NULL;}

  cout<<"Luncz v0.1"<<endl;

  UserList u_list = UserList(u_table, USER_CNT);

  u_list.AddUser("Marian", "Bibi");
  u_list.AddUser("Jurek", "Zaraz");
  u_list.AddUser("Janek", "Beza", true);

  u_list.ListUsers();
  u_list.DeleteUser(2);
  u_list.ListUsers();

  OrderList o_list = OrderList(ORDER_CNT);

  try
  {
    o_list.AddNewOrder(u_list.GetUser(1), 13, 23);
    o_list.AddNewOrder(u_list.GetUser(3), 14, 24);
    o_list.AddNewOrder(u_list.GetUser(5), 14, 24);
  }
  catch (int id)
  {
    cout<<"\n!Failed to add order for user ID "<<id<<"!"<<endl;
  }

  Zamawiacz * zam = dynamic_cast<Zamawiacz*>(u_list.GetUser(u_list.GetZamawiaczId()));

  if ( zam )
    zam->MakeOrder(&o_list);

  o_list.DeleteOrder(u_list.GetUser(1));

  if ( zam )
    zam->MakeOrder(&o_list);

  cout<<"End"<<endl;
}
