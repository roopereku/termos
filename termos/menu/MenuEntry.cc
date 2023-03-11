#include "MenuEntry.hh"
#include "../Menu.hh"

#include <cstring>

namespace Termos {

MenuEntry::MenuEntry(const std::string& name) : name(name)
{
}

void MenuEntry::onRender(Render& render, size_t x, size_t& y)
{
	if(name.empty())
		return;

	if(this == &menu->getSelection())
	{
		render.invertColor();
		render.blankLine(y);

	}

	const char* prefix = getPrefix();

	render.text(prefix, x, y);
	render.text(name, x + strlen(prefix), y++);

	if(this == &menu->getSelection())
		render.invertColor();
}

}
