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
    LRpcMethod(QString method_name);

    T_RPCMETHODID getId();

  private:
    T_RPCMETHODID id;

    const char * method[LRPC_MAX] = {
      "m_list_users",
      "m_list_orders",
      "m_add_user",
      "m_delete_user",
      "m_modify_user",
      "m_add_order",
      "m_delete_order",
      "m_modify_order"
    };
};

#endif // LRPCMETHOD_H
