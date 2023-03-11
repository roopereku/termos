#include "Menu.hh"
#include "Debug.hh"

#include <algorithm>

namespace Termos {

void Menu::onRender(Render& render)
{
	size_t y = 0;
	Submenu::onRender(render, 0, y);
}

void MenuEntry::onRender(Render& render, size_t x, size_t& y)
{
	if(name.empty())
		return;

	if(this == &menu->getSelection())
	{
		render.invertColor();
		render.blankLine(y);

		render.text(name, x, y++);
		render.invertColor();
	}

	else render.text(name, x, y++);
}

void Submenu::onRender(Render& render, size_t x, size_t& y)
{
	MenuEntry::onRender(render, x, y);
	if(!expanded) return;

	size_t horizontalIncrement = name.empty() ? 0 : 2;

	for(auto& entry : entries)
		entry->onRender(render, x + horizontalIncrement, y);
}

MenuEntry* Submenu::findSelection(size_t& index)
{
	for(auto& entry : entries)
	{
		// If this entry is what the menu has selected, return it
		if(index == menu->getSelectionIndex())
			return entry.get();

		if(entry->isSubmenu() && static_cast <Submenu&> (*entry).expanded)
		{
			// Recurse into this submenu
			index++;
			MenuEntry* ret = static_cast <Submenu&> (*entry).findSelection(index);

			// If there was a return value, return it
			if(ret) return ret;
		}

		else index++;
	}
	
	return nullptr;
}

void Menu::onMouseClick(Point at)
{
	size_t oldSelectionIndex = selectedIndex;
	selectedIndex = at.y;

	size_t index = 0;
	MenuEntry* ret = findSelection(index);

	// If there is a menu entry under the mouse cursor, selected it
	if(ret)
	{
		selected = ret;
		render();
	}

	// If nothing was clicked, revert back to the old index
	else selectedIndex = oldSelectionIndex;
}

void Menu::onKeyPress(int key)
{
	size_t index = 0;
	MenuEntry* previousSelection = selected;

	switch(key)
	{
		case KEY_DOWN:
		{
			selectedIndex++;
			selected = findSelection(index);

			// We've hit the last menu entry if selected is null
			// TODO Wrap around
			if(!selected)
			{
				selectedIndex--;
				selected = previousSelection;
			}

			break;
		}

		case KEY_UP:
		{
			selectedIndex--;
			selected = findSelection(index);

			// We've hit the first menu entry if selected is null
			// TODO Wrap around
			if(!selected)
			{
				selectedIndex++;
				selected = previousSelection;
			}

			break;
		}

		case '\n': case '\r':
		{
			selected->onTrigger();
			break;
		}
	}

	render();
}

MenuEntry::MenuEntry(const std::string& name) : name(name)
{
}

Submenu::Submenu(const std::string& name) : MenuEntry(name)
{
}

Menu::Menu() : Submenu("")
{
	MenuEntry::parent = nullptr;
	menu = this;
	expand();
}

MenuEntry& Menu::getSelection()
{
	return *selected;
}

size_t Menu::getSelectionIndex()
{
	return selectedIndex;
}

void Submenu::onTrigger()
{
	expanded = !expanded;
}

void Submenu::expand()
{
	expanded = true;
	menu->render();
}

void Submenu::collapse()
{
	expanded = false;
	menu->render();
}

Submenu& Submenu::addMenu(const std::string& name)
{
	entries.push_back(std::make_shared <Submenu> (name));

	static_cast <Submenu&> (*entries.back()).menu = menu;
	static_cast <Submenu&> (*entries.back()).parent = this;

	// If this is the menu and it just got it's first entry, select said entry
	if(this == menu && entries.size() == 1)
		menu->selected = entries.back().get();

	menu->render();

	return static_cast <Submenu&> (*entries.back());
}

}
