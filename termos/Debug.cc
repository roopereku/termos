#include <termos/Debug.hh>

namespace Termos {

DBG(static Logger* debugLogger = nullptr);

void setDebugLogger(Logger& logger)
{
	DBG(debugLogger = &logger);
}

DBG(Logger* getDebugLogger()
{
	return debugLogger;
})

}
