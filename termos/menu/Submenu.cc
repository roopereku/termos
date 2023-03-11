#include "Submenu.hh"
#include "../Menu.hh"

namespace Termos {

Submenu::Submenu(const std::string& name, bool expanded)
	: MenuEntry(name), expanded(expanded)
{
}

const char* Submenu::getPrefix()
{
	return expanded ? ". " : "> ";
}

void Submenu::onTrigger()
{
	expanded = !expanded;
}

bool Submenu::isSelectionHere()
{
	for(auto& entry : entries)
	{
		if(entry.get() == menu->selected)
			return true;

		if(entry->isSubmenu() && static_cast <Submenu&> (*entry).isSubmenu())
			return true;
	}

	return false;
}

void Submenu::prepareEntry()
{
	entries.back()->menu = menu;

	// If this is the menu and it just got it's first entry, select said entry
	if(this == menu && entries.size() == 1)
		menu->selected = entries.back().get();

	else
	{
		size_t index = 0;
		MenuEntry* ret = menu->findSelection(index);

		/* If the menu entry at selected index changed,
		 * the new menu entry was added before the selected one.
		 * In this case increment the selected index */
		if(ret != menu->selected)
			menu->selectedIndex++;
	}

	menu->render();

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

		index++;

		if(entry->isSubmenu() && static_cast <Submenu&> (*entry).expanded)
		{
			// Recurse into this submenu
			MenuEntry* ret = static_cast <Submenu&> (*entry).findSelection(index);

			// If there was a return value, return it
			if(ret) return ret;
		}
	}
	
	return nullptr;
}

}
