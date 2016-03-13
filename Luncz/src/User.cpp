/*
 * User.cpp
 *
 *  Created on: 22 lut 2016
 *      Author: jszme
 */

#include "User.h"

User::User(string f_n, string l_n)
{

}

User::User(string initials)
{

}

User::User(int id)
{

}

User::~User()
{

}

int User::GetId()
{
  return this->id;
}

string User::GetInitials()
{
  return this->initials;
}

string User::GetFName()
{
  return this->f_name;
}

string User::GetLName()
{
  return this->l_name;
}

usrtype User::GetType()
{
  return this->type;
}

void User::AddOrder(int menu_item, int cost)
{

}
void User::AddOrder(int menu_item, int cost, User & user)
{

}

void User::DeleteOrder()
{

}

void User::DeleteOrder(User & user)
{

}

void User::MakeOrder()
{

}
