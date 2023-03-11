#ifndef TERMOS_MENU_HH
#define TERMOS_MENU_HH

#include "Widget.hh"

#include <functional>
#include <vector>
#include <memory>
#include <string>

namespace Termos {

class Menu;
class Submenu;

class MenuEntry
{
public:
	MenuEntry(const std::string& name);
	const std::string name;

	virtual void onRender(Render& render, size_t x, size_t& y);
	virtual bool isSubmenu() { return false; };
	virtual void onTrigger() {};

protected:
	Submenu* parent;
	Menu* menu;
};

class Submenu : public MenuEntry
{
public:
	Submenu(const std::string& name);
	Submenu& addMenu(const std::string& name, bool expanded = false);
	bool isSubmenu() override { return true; };

protected:
	void onRender(Render& render, size_t x, size_t& y) override;
	void onTrigger() override;

	MenuEntry* findSelection(size_t& index);
	bool isSelectionHere();

	bool expanded;

private:
	std::vector <std::shared_ptr <MenuEntry>> entries;
};

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
