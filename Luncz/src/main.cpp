
#include <iostream>
#include <typeinfo>
#include "SQLite\sqlite3.h"

#include "Zamawiacz.h"
#include "OrderList.h"
#include "UserList.h"


using namespace std;

const int USER_CNT = 10;
const int ORDER_CNT = 10;

int main(int argc, char **argv)
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open("test.db", &db);

  if (rc)
  {
    cout<<"Failed!!"<<endl;
  }
  else
  {
    cout<<"Opened database successfully\n";
  }

  sqlite3_close(db);
}
