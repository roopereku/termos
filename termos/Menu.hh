#ifndef TERMOS_MENU_HH
#define TERMOS_MENU_HH

#include "Widget.hh"
#include "menu/Submenu.hh"

namespace Termos {

class Menu : public Widget, public Submenu
{
public:
	Menu();

	void onRender(Render& render) override;
	void onMouseClick(Point at) override;
	void onKeyPress(int key) override;

	MenuEntry& getSelection();
	size_t getSelectionIndex();

	friend class Submenu;

private:
	MenuEntry* selected = this;
	size_t selectedIndex = 0;
};
}

#endif
