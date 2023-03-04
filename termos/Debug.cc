#include "Debug.hh"

namespace Termos {

static Logger* debugLogger = nullptr;

void setDebugLogger(Logger& logger)
{
	debugLogger = &logger;
}

Logger& getDebugLogger()
{
	return *debugLogger;
}

}
