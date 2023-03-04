#include "Logger.hh"

namespace Termos {

void Logger::onRender(Render& render)
{
	for(size_t i = 0; i < logs.size(); i++)
		render.text(0, i, logs[i].c_str());
}

void Logger::onMouseClick(Point at)
{
	add("Mouse clicked at", at.x, at.y);
}

}
