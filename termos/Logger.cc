#include <termos/Logger.hh>

namespace Termos {

void Logger::onRender(Render& render)
{
	size_t i = 0;
	if(logs.size() >= getSize().y)
		i = logs.size() - getSize().y;

	for(size_t y = 0; i < logs.size() && y < getSize().y; i++, y++)
		render.text(logs[i], 0, y);
}

}
