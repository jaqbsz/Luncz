/*
 * User.h
 *
 *  Created on: 22 lut 2016
 *      Author: jszme
 */

#ifndef USER_H_
#define USER_H_

#include <string>
#include "SQLite\sqlite3.h"
#include "SQLiteCpp\SQLiteCpp.h"

using namespace std;

enum class UType : int
{
  U_TYPE_NORMAL,     // normal user
  U_TYPE_CALLER,     // user that sends summarized info
  U_TYPE_MAX
};

const string u_type[static_cast< std::size_t >( UType::U_TYPE_MAX )] = {"NORMAL", "CALLER"};

class User
{
  public:
    User() :  m_id{0},
              m_fname{"---"},
              m_lname{"---"},
              m_initials{"--"},
              m_type{UType::U_TYPE_NORMAL}
    {}

    string  FName()   { return m_fname; }
    string  LName()   { return m_lname; }
    string  Initials(){ return m_initials; }
    int     Id()      { return m_id; }
    UType   Type()    { return m_type; }
    string  TypeStr() { return u_type[static_cast <std::size_t>( m_type )]; }

    void FName    ( string fname )    { m_fname = fname; }
    void LName    ( string lname)     { m_lname = lname; }
    void Initials ( string initials ) { m_initials = initials; }
    void Id       ( int id )          { m_id = id; }
    void Type     ( UType type )      { m_type = type; }

  private:
    int     m_id;
    string  m_fname;
    string  m_lname;
    string  m_initials;
    UType   m_type;
};

#endif /* USER_H_ */
