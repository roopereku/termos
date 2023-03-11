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

	auto& menu = ui.add <Termos::Menu> ();
	auto& test1 = menu.addMenu("test1");
	auto& test1_1 = test1.addMenu("test1_1");

	auto& test1_1_1 = test1_1.addMenu("test1_1_1");
	auto& test1_1_2 = test1_1.addMenu("test1_1_2");

	auto& test2 = menu.addMenu("test2");

	//text.onSubmit = [&text](const std::string& value)
	//{
	//	DBG_LOG("User typed", value);
	//	text.clear();
	//};

	ui.run();
}
