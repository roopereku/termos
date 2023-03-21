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

	auto& menu = ui.add <Termos::Menu> ();
	auto& test = menu.addMenu("no color");
	auto& red = menu.addMenu("red");
	auto& green = menu.addToggle("green");
	auto& blue = menu.addMenu("blue");

	red.setHighlight(Termos::Color::Red);
	green.setHighlight(Termos::Color::Green);
	blue.setHighlight(Termos::Color::Blue);

	ui.run();
}
