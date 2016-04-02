#include "LRpcMethod.h"

#include <cstring>

typedef struct
{
    T_RPCMETHODID id;
    const char * name;
}T_RPCMETHOD;

static const T_RPCMETHOD method_obj[] = {{M_LIST_USERS  , "m_list_users"  },
                                         {M_LIST_ORDERS , "m_list_orders" },
                                         {M_ADD_USER    , "m_add_user"    },
                                         {M_DELETE_USER , "m_delete_user" },
                                         {M_MODIFY_USER , "m_modify_user" },
                                         {M_ADD_ORDER   , "m_add_order"   },
                                         {M_DELETE_ORDER, "m_delete_order"},
                                         {M_MODIFY_ORDER, "m_modify_order"}};

static const T_RPCMETHOD method[] = {{M_LIST_USERS  , "list_users", },
                                     {M_LIST_ORDERS , "list_orders",},
                                     {M_ADD_USER    , "add_user",   },
                                     {M_DELETE_USER , "delete_user",},
                                     {M_MODIFY_USER , "modify_user",},
                                     {M_ADD_ORDER   , "add_order",  },
                                     {M_DELETE_ORDER, "delete_order"},
                                     {M_MODIFY_ORDER, "modify_order"}};


//**************************************************************************************
//* converting constructor
//*
//**************************************************************************************
LRpcMethod::LRpcMethod(const QString &method_name)
{
  int i = 0;
  for (; i < LRPC_MAX; i++)
  {
    if ( ( method_name == method[i].name ) || ( method_name == method_obj[i].name ) )
    {
      this->id = static_cast<T_RPCMETHODID>(i);
      this->nameObj = method_obj[i].name;
      this->name = method[i].name;
      break;
    }
  }

  if (i == LRPC_MAX)
  {
    this->id = LRPC_MAX;
    this->name = "null";
    this->nameObj = "null";
    // TODO throw exception
  }
}

//**************************************************************************************
//* converting constructor
//*
//**************************************************************************************
LRpcMethod::LRpcMethod(const char *method_name)
{
  int i = 0;
  for (; i < LRPC_MAX; i++)
  {
    if ( ( strcmp(method_name, method[i].name) == 0 ) || ( strcmp(method_name, method_obj[i].name) == 0 ) )
    {
      this->id = static_cast<T_RPCMETHODID>(i);
      this->nameObj = method_obj[i].name;
      this->name = method[i].name;;
      break;
    }
  }

  if (i == LRPC_MAX)
  {
    this->id = LRPC_MAX;
    this->name = "null";
    this->nameObj = "null";
    // TODO throw exception
  }
}
