/*
 * UserList.h
 *
 *  Created on: 6 mar 2016
 *      Author: jszme
 */

#ifndef USERLIST_H_
#define USERLIST_H_

using namespace std;
#include <list>
#include "User.h"

class UserList
{
  private:
    const int max_users;
    User **u_list;

  public:
    UserList(User ** u_l, int max_usr);
    ~UserList();

    int AddUser(string f_n, string l_n, bool zam = false);
    User * GetUser(int id);
    int GetZamawiaczId();
    void ListUsers();
    bool DeleteUser(int id);
};

#endif /* USERLIST_H_ */
