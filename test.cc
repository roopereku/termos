#include <termos/TabSelector.hh>
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

	auto& view = ui.add <Termos::View> (Termos::Split::Vertically);
	auto& tabs = view.add <Termos::TabSelector> ();

	tabs.add("moi");
	tabs.add("test");
	tabs.add("jfgdkl");

	ui.run();
}
