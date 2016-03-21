#ifndef DEBUG_H
#define DEBUG_H

#define _DEBUG_


#ifdef _DEBUG_
#define DEBUG(x) (std::cerr<<"DBG: "<<x)
#else
#define DEBUG(x)
#endif



#endif // DEBUG_H
