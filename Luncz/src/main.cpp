
#include <iostream>
#include <typeinfo>
#include "SQLite\sqlite3.h"
#include "SQLiteCpp\SQLiteCpp.h"

#include "Zamawiacz.h"
#include "OrderList.h"
#include "UserList.h"

using namespace std;


static const string database_file = "luncz.db3";

const int USER_CNT = 10;
const int ORDER_CNT = 10;

int main(int argc, char **argv)
{
  cout << "SQlite3 version " << SQLITE_VERSION << endl;
  cout << "SQliteC++ version " << SQLITECPP_VERSION << endl;

  try
  {
    SQLite::Database db(database_file, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
    std::cout << "SQLite database file '" << db.getFilename().c_str()<< "' opened successfully\n";

    db.exec("DROP TABLE IF EXISTS USERS_LIST");
    db.exec("DROP TABLE IF EXISTS ORDER_LIST");

    UserList u_list = UserList(db);
    OrderList o_list = OrderList(db);

    User jk = u_list.AddUser("Janek", "Kos", "jk");
    cout<<"User:"<<jk.GetFName()<<" "<<jk.GetLName()<<endl;

    User jmc = u_list.AddUser("John", "McClain", "jmc");
    cout<<"User:"<<jmc.GetFName()<<" "<<jmc.GetLName()<<endl;

    Order order1 = o_list.AddNewOrder(jmc, 13, 21);
    o_list.AddNewOrder(jk, 13, 22);

    o_list.DeleteOrder(order1);

    cout<<"number :"<<o_list.GetOrderCounterToday()<<endl;
    cout<<"need to pay :"<<o_list.GetOrderPriceSum()<<endl;

  } catch (exception& e)
  {
    cout << "!!Exception: " << e.what() << std::endl;
  }
}
