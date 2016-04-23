#include "LRpcMethod.h"

#include <cstring>

typedef struct
{
    T_RPCMETHODID id;
    const char * name;
}T_RPCMETHOD;

static const T_RPCMETHOD resp_obj[] = {{M_LIST_USERS  , "r_list_users"  },
                                       {M_LIST_ORDERS , "r_list_orders" },
                                       {M_ADD_USER    , "r_add_user"    },
                                       {M_DELETE_USER , "r_delete_user" },
                                       {M_MODIFY_USER , "r_modify_user" },
                                       {M_ADD_ORDER   , "r_add_order"   },
                                       {M_DELETE_ORDER, "r_delete_order"},
                                       {M_MODIFY_ORDER, "r_modify_order"}};

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
      this->m_id = static_cast<T_RPCMETHODID>(i);
      this->m_nameObj = method_obj[i].name;
      this->m_name = method[i].name;
      this->m_respObj = resp_obj[i].name;
      break;
    }
  }

  if (i == LRPC_MAX)
  {
    this->m_id = LRPC_MAX;
    this->m_name = "null";
    this->m_nameObj = "null";
    this->m_respObj = "null";
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
      this->m_id = static_cast<T_RPCMETHODID>(i);
      this->m_nameObj = method_obj[i].name;
      this->m_name = method[i].name;
      this->m_respObj = resp_obj[i].name;
      break;
    }
  }

  if (i == LRPC_MAX)
  {
    this->m_id = LRPC_MAX;
    this->m_name = "null";
    this->m_nameObj = "null";
    this->m_respObj = "null";
    // TODO throw exception
  }
}
