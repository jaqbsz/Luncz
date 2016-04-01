#include "LRpcMethod.h"

#include <cstring>

LRpcMethod::LRpcMethod(QString method_name)
{
  for (int i = 0; i < LRPC_MAX; i++)
  {
    if ( method_name == this->method[i] )
    {
      this->id = static_cast<T_RPCMETHODID>(i);
      break;
    }
  }
}

T_RPCMETHODID LRpcMethod::getId()
{
  return this->id;
}
