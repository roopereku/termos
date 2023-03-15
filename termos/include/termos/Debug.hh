#ifndef TERMOS_DEBUG_HH
#define TERMOS_DEBUG_HH

#include "Logger.hh"

#ifdef DEBUG
#define DBG(...) __VA_ARGS__
#define DBG_LOG(...) if(Termos::getDebugLogger()) Termos::getDebugLogger()->add(__VA_ARGS__)

#else
#define DBG(...)
#define DBG_LOG(...)

#endif

namespace Termos {

void setDebugLogger(Logger& logger);
DBG(Logger* getDebugLogger());

}

#endif
