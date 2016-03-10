
#include <iostream>
#include <typeinfo>
#include "SQLite\sqlite3.h"
#include "SQLiteCpp\SQLiteCpp.h"

#include "Zamawiacz.h"
#include "OrderList.h"
#include "UserList.h"

using namespace std;

const int USER_CNT = 10;
const int ORDER_CNT = 10;

int main(int argc, char **argv)
{
  cout << "SQlite3 version " << SQLITE_VERSION << endl;
  cout << "SQliteC++ version " << SQLITECPP_VERSION << endl;


}
