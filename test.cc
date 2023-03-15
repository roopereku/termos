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
	auto& menu = ui.add <Termos::Menu> ();
	menu.addToggle("Onko santeri gay", true);

	auto& toggle = view.add <Termos::Button> ("Toggle visibility");
	toggle.onClick = [&menu]()
	{
		static bool visible = false;
		menu.setVisible(visible);

		visible = !visible;
	};

	ui.run();
}
