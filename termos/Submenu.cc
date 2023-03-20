#include <termos/Submenu.hh>
#include <termos/Debug.hh>
#include <termos/Menu.hh>

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

void Submenu::lateInitialize()
{
	for(auto& entry : entries)
	{
		entry->menu = menu;
		entry->parent = parent;
		entry->depth = depth + 1;

		if(entry->isSubmenu())
		{
			Submenu& sub = static_cast <Submenu&> (*entry);
			sub.lateInitialize();
		}
	}
}

void Submenu::prepareEntry()
{
	/* If there's no menu yet but entries have been added,
	 * do nothing yet. This can happen if a custom submenu adds
	 * entries in it's constructor */
	if(!menu && !entries.empty())
		return;

	entries.back()->menu = menu;
	entries.back()->parent = this;
	entries.back()->depth = depth + 1;

	if(entries.back()->isSubmenu())
	{
		Submenu& sub = static_cast <Submenu&> (*entries.back());

		/* If the entry that was just initialized already has children,
		 * initialize the children now */
		if(!sub.entries.empty())
			sub.lateInitialize();
	}

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
