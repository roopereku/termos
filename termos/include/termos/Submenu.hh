#ifndef TERMOS_SUBMENU_HH
#define TERMOS_SUBMENU_HH

#include "MenuEntry.hh"
#include "MenuToggle.hh"

#include <functional>
#include <vector>
#include <string>
#include <memory>

namespace Termos {
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
	MenuToggle& addToggle(const std::string& name, bool on = false) { return add <MenuToggle> (name, on); }

	std::function <void()> onExpand;

	size_t entryCount() { return entries.size(); }
	MenuEntry& operator[](size_t index) { return *entries[index]; }

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
	void lateInitialize();

	std::vector <std::shared_ptr <MenuEntry>> entries;
};
}

#endif
