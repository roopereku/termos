#ifndef TERMOS_MENU_TOGGLE_HH
#define TERMOS_MENU_TOGGLE_HH

#include "MenuEntry.hh"

#include <functional>

namespace Termos {
class MenuToggle : public MenuEntry
{
public:
	MenuToggle(const std::string& name, bool on = false);

	const char* getPrefix() override;
	void onTrigger() override;

	std::function <void(bool)> onToggle;

private:
	bool on;
};
}

#endif
