#include <termos/TabbedView.hh>
#include <termos/TextInput.hh>
#include <termos/Termos.hh>
#include <termos/Logger.hh>
#include <termos/Button.hh>
#include <termos/Table.hh>
#include <termos/Debug.hh>
#include <termos/Menu.hh>

int main()
{
	TermosUI ui(Termos::Split::Horizontally);

	auto& logger = ui.add <Termos::Logger> ();
	Termos::setDebugLogger(logger);

	auto& tabs = ui.add <Termos::TabbedView> (); 

	auto& menu = tabs.tab <Termos::Menu> ("test1");
	auto& menu1 = menu.addMenu("test menu 1");
	auto& toggle1_1 = menu1.addToggle("(t1) inside 1");
	auto& menu1_1 = menu1.addMenu("(m1) inside 1");
	auto& toggle1_2 = menu1.addToggle("(t2) inside 1");

	auto& toggle1_1_1 = menu1_1.addToggle("(t1) inside 1_1");

	auto& menu2 = menu.addMenu("test menu 2");

	DBG_LOG("menu1", &menu1);
	DBG_LOG("menu2", &menu2);

	menu.onSelect = [&menu1, &menu2](Termos::MenuEntry& entry)
	{
		auto* relative = entry.findParent(0);

		if(relative == &menu1)
			DBG_LOG("Inside menu1");

		if(relative == &menu2)
			DBG_LOG("Inside menu2");
	};

	ui.run();
}
