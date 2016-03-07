/*
 * User.h
 *
 *  Created on: 22 lut 2016
 *      Author: jszme
 */

#ifndef USER_H_
#define USER_H_

#include <string>
using namespace std;

class User
{
  private:
    string f_name;
    string l_name;
    string initials;
    int id;
    static int usercnt;

    bool SetInitials();

  public:
    User(string f_n, string l_n);
    virtual ~User();
    string GetFName();
    string GetLName();
    string GetInitials();
    virtual int GetId();
    virtual string GetType();
    static int GetUserCnt();
};

#endif /* USER_H_ */
