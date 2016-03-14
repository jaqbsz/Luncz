
#include <iostream>
#include <typeinfo>
#include "SQLite\sqlite3.h"
#include "SQLiteCpp\SQLiteCpp.h"

#include "Zamawiacz.h"
#include "OrderList.h"
#include "UserList.h"

using namespace std;

/// Example Database
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

    UserList u_list = UserList(db, USER_CNT);

    User jk = User(db, u_list.AddUser("Janek", "Kos", "jk"));
    cout<<"User:"<<jk.GetFName()<<" "<<jk.GetLName()<<endl;

    User jmc = User(db, u_list.AddUser("John", "McClain", "jmc"));
    cout<<"User:"<<jmc.GetFName()<<" "<<jmc.GetLName()<<endl;

  } catch (exception& e)
  {
    cout << "!!Exception: " << e.what() << std::endl;
  }
}
