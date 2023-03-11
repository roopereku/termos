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

class Submenu : public MenuEntry
{
public:
	Submenu(const std::string& name, bool expanded = false);

	template <typename T, typename... Args>
	T& add(const std::string& name, Args&& ...args)
	{
		entries.push_back(std::make_shared <T> (name, std::forward <Args> (args)...));
		prepareEntry();
		return static_cast <T&> (*entries.back());
	}

	Submenu& addMenu(const std::string& name, bool expanded = false) { return add <Submenu> (name, expanded); }


protected:
	void onRender(Render& render, size_t x, size_t& y) override;
	const char* getPrefix() override;
	bool isSubmenu() override { return true; };
	void onTrigger() override;

	MenuEntry* findSelection(size_t& index);
	bool isSelectionHere();

	bool expanded;

private:
	void prepareEntry();
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
