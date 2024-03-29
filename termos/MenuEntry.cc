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
	/* The given depth will not be found if it is greater than the
	 * depth of this MenuEntry since the depth only gets smaller */
	if(depth > this->depth)
		return nullptr;

	// If the depth matches, the callee is inside this submenu
	if(this->depth == depth && isSubmenu())
		return static_cast <Submenu*> (this);

	// While there is a parent, recursively look for the given parent
	return parent ? parent->findParent(depth) : nullptr;
}

void MenuEntry::setHighlight(Color color)
{
	hasHighlight = true;
	highlight = color;

	menu->render();
}

void MenuEntry::removeHighlight()
{
	hasHighlight = false;
	menu->render();
}

void MenuEntry::onRender(Render& render, size_t x, size_t& y)
{
	if(y >= menu->getSize().y)
		return;

	if(name.empty())
		return;

	if(this == &menu->getSelection())
	{
		render.invertColor();
		render.blankLine(y);

	}

	Color oldFg = render.getForegroundColor();
	if(hasHighlight) render.setForeground(highlight);

	const char* prefix = getPrefix();

	render.text(prefix, x, y);
	render.text(name, x + strlen(prefix), y++);

	if(hasHighlight)
		render.setForeground(oldFg);

	if(this == &menu->getSelection())
		render.invertColor();
}

}
