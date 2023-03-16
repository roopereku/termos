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
	auto& toggle1 = menu.addToggle("test toggle");

	auto& menu2 = tabs.tab <Termos::Menu> ("test2");
	auto& toggle2 = menu2.addToggle("toggle test");

	ui.run();
}
