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
	auto& test1_1 = test1.addMenu("test1_1");

	addMenu.onClick = [&test1]()
	{
		test1.addMenu("new menu");
	};

	auto& test1_1_1 = test1_1.addMenu("test1_1_1", true);
	auto& test1_1_2 = test1_1.addMenu("test1_1_2");

	auto& test1_1_1_1 = test1_1_1.addMenu("test1_1_1_1");
	auto& test1_1_2_1 = test1_1_2.addMenu("test1_1_2_1");
	auto& test1_1_2_2 = test1_1_2.addMenu("test1_1_2_2");

	auto& test2 = menu.addMenu("test2");

	//text.onSubmit = [&text](const std::string& value)
	//{
	//	DBG_LOG("User typed", value);
	//	text.clear();
	//};

	ui.run();
}
