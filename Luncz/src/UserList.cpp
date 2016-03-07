/*
 * UserList.cpp
 *
 *  Created on: 6 mar 2016
 *      Author: jszme
 */

#include "UserList.h"
#include "Zamawiacz.h"
#include <iostream>
#include <typeinfo>

UserList::UserList(User ** u_l, int max_usr) : max_users(max_usr), u_list(u_l)
{
  ;
}

UserList::~UserList()
{
  // TODO Auto-generated destructor stub
}

int UserList::AddUser(string f_n, string l_n, bool zam)
{
  int ret_id = 0;

  User * u = NULL;

  if ( zam )
  {
    u = new Zamawiacz(f_n, l_n);
  }
  else
  {
    u = new User(f_n, l_n);
  }

  int ucnt = u->GetUserCnt();

  if (ucnt < max_users)
  {
    for (int i = 0; i < max_users ; i++)
    {
      if ( u_list[i] == NULL )
      {
        u_list[i] = u;
        ret_id = u->GetId();
        break;
      }
    }
  }
  else
  {
    delete u;
  }

  return ret_id;
}

void UserList::ListUsers()
{
  cout<<"\nID: \t First name: \t Last name: \t Type:"<<endl;
  for(int i = 0; i < max_users ; i++)
  {
    if ( u_list[i] )
    {
      User * u = u_list[i];
      cout<<u->GetId();
      cout<<"\t ";
      cout<<u->GetFName();
      cout<<"\t\t ";
      cout<<u->GetLName();
      cout<<"\t\t";
      cout<<u->GetType();
      cout<<endl;
    }
  }
  cout<<"User count: "<<User::GetUserCnt()<<endl;
}

bool UserList::DeleteUser(int id)
{
  bool ret = false;

  for(int i = 0; i < max_users ; i++)
  {
    if ( u_list[i] && (u_list[i]->GetId() == id) )
    {
      delete u_list[i];
      u_list[i] = NULL;
      ret = true;
      break;
    }
  }

  return ret;
}

User * UserList::GetUser(int id)
{
  User * u = NULL;

  for(int i = 0; i < max_users ; i++)
  {
    if (u_list[i] && u_list[i]->GetId() == id)
    {
      u = u_list[i];
      break;
    }
  }

  if (u == NULL)
  {
    throw id;
  }

  return u;
}

int UserList::GetZamawiaczId()
{
  int ret = 0;

  for(int i = 0; i < max_users ; i++)
  {
    if ( u_list[i] && u_list[i]->GetType().compare("Zamawiacz") == 0)
    {
      ret = u_list[i]->GetId();
    }
  }

  return ret;
}
