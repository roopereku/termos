#include "Logger.hh"

namespace Termos {

void Logger::onRender(Render& render)
{
	for(size_t i = 0; i < logs.size(); i++)
		render.text(0, i, logs[i].c_str());
}

}