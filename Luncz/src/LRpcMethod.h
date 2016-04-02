#ifndef LRPCMETHOD_H
#define LRPCMETHOD_H

#include <QString>

// when modyfing this remember to modify const char * method[LRPC_MAX]
typedef enum
{
  M_LIST_USERS = 0,      //  "m_list_users"
  M_LIST_ORDERS,         //  "m_list_orders"
  M_ADD_USER,            //  "m_add_user"
  M_DELETE_USER,         //  "m_delete_user"
  M_MODIFY_USER,         //  "m_modify_user"
  M_ADD_ORDER,           //  "m_add_order"
  M_DELETE_ORDER,        //  "m_delete_order"
  M_MODIFY_ORDER,        //  "m_modify_order"
  LRPC_MAX
}T_RPCMETHODID;

class LRpcMethod
{
  public:
    LRpcMethod(const QString & method_name);
    LRpcMethod(const char * method_name);

    T_RPCMETHODID getId() const
    {
      return this->id;
    }

    const char * getName() const
    {
      return this->name;
    }

    const char * getNameObj() const
    {
      return this->nameObj;
    }

  private:
    T_RPCMETHODID id;
    const char * name;
    const char * nameObj;
};

#endif // LRPCMETHOD_H
