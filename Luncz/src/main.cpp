
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

    // Begin transaction
    SQLite::Transaction transaction(db);

    // create test table
    db.exec("CREATE TABLE test (id        INT       NOT NULL, \
                                initials  CHAR(5)   NOT NULL, \
                                f_name    CHAR(20)  NOT NULL, \
                                l_name    CHAR(20)  NOT NULL, \
                                PRIMARY   KEY(ID))");

    // Commit transaction
    transaction.commit();

    // Test if the 'test' table exists
    const bool bExists = db.tableExists("test");
    std::cout << "SQLite table 'test' exists=" << bExists << "\n";
  } catch (exception& e)
  {
    cout << "!!Exception: " << e.what() << std::endl;
  }
}
