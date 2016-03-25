#ifndef DEBUG_H
#define DEBUG_H

#define _DEBUG_

#include <iostream>

namespace std
{
  #ifdef _DEBUG_
  #define DEBUG(x) (std::cerr<<"DBG: "<<x)
  #else
  #define DEBUG(x)
  #endif
}

#endif // DEBUG_H
