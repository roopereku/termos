#include "termos/TextInput.hh"
#include "termos/Termos.hh"
#include "termos/Logger.hh"
#include "termos/Button.hh"
#include "termos/Table.hh"
#include "termos/Debug.hh"
#include "termos/Menu.hh"

int main()
{
	TermosUI ui(Termos::Split::Horizontally);

	auto& logger = ui.add <Termos::Logger> ();
	Termos::setDebugLogger(logger);

	auto& view = ui.add <Termos::View> (Termos::Split::Vertically);
	auto& menu = view.add <Termos::Menu> ();
	auto& addMenu = view.add <Termos::Button> ("Add a menu");

	auto& test1 = menu.addMenu("test1");
	auto& toggle = test1.addToggle("Test toggle");

	toggle.onToggle = [](bool on)
	{
		DBG_LOG("Toggle", on ? "on" : "off");
	};

	ui.run();
}
