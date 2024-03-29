#include <termos/Menu.hh>
#include <termos/Debug.hh>

#include <algorithm>
#include <cstring>

namespace Termos {

void Menu::onRender(Render& render)
{
	size_t y = 0;
	Submenu::onRender(render, 0, y);
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

		if(onSelect)
			onSelect(*selected);
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

			else if(onSelect)
				onSelect(*selected);

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

			else if(onSelect)
				onSelect(*selected);

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

Menu::Menu() : Submenu("")
{
	depth = -1;
	menu = this;
	expanded = true;
	MenuEntry::parent = nullptr;
}

MenuEntry& Menu::getSelection()
{
	return *selected;
}

size_t Menu::getSelectionIndex()
{
	return selectedIndex;
}

}
