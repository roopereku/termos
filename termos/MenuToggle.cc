#include <termos/MenuToggle.hh>

namespace Termos {

MenuToggle::MenuToggle(const std::string& name, bool on) : MenuEntry(name), on(on)
{
}

const char* MenuToggle::getPrefix()
{
	return on ? "[X] " : "[ ] ";
}

void MenuToggle::onTrigger()
{
	on = !on;

	if(onToggle)
		onToggle(on);
}

}
