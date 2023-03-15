#ifndef TERMOS_MENU_ENTRY_HH
#define TERMOS_MENU_ENTRY_HH

#include "Widget.hh"

namespace Termos {

class Menu;
class Submenu;

class MenuEntry
{
public:
	MenuEntry(const std::string& name);

	friend class Submenu;

	virtual void onTrigger()=0;
	virtual bool isSubmenu() { return false; };

protected:
	virtual const char* getPrefix()=0;

	Menu* menu;

private:
	const std::string name;
	virtual void onRender(Render& render, size_t x, size_t& y);
};

}

#endif
