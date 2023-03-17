#include <termos/MenuEntry.hh>
#include <termos/Debug.hh>
#include <termos/Menu.hh>

#include <cstring>

namespace Termos {

MenuEntry::MenuEntry(const std::string& name) : name(name)
{
}

Submenu* MenuEntry::findParent(int depth)
{
	// If the depth matches, the callee is inside this submenu
	if(this->depth == depth && isSubmenu())
		return static_cast <Submenu*> (this);

	// While the depth is >= 0, recursively look for the given parent
	return depth >= 0 ? parent->findParent(depth) : nullptr;
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
