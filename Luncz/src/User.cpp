/*
 * User.cpp
 *
 *  Created on: 22 lut 2016
 *      Author: jszme
 */

#include "User.h"

int User::usercnt = 0;

User::User(string f_n, string l_n)
{
  this->usercnt++;
  this->id = this->usercnt;
  this->f_name = f_n;
  this->l_name = l_n;

  //check if this user already exists
  // if yes throw exception
}

User::~User()
{
  this->usercnt--;
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

string User::GetType()
{
  return "Normal user";
}

int User::GetUserCnt()
{
  return usercnt;
}
