#include "termos/TextInput.hh"
#include "termos/Termos.hh"
#include "termos/Logger.hh"
#include "termos/Button.hh"
#include "termos/Table.hh"
#include "termos/Debug.hh"

int main()
{
	TermosUI ui(Termos::Split::Horizontally);

	auto& logger = ui.add <Termos::Logger> ();
	Termos::setDebugLogger(logger);

	auto& view = ui.add <Termos::View> (Termos::Split::Vertically);
	auto& button = view.add <Termos::Button> ("Button test");
	auto& text = view.add <Termos::TextInput> ();

	auto& table = view.add <Termos::Table> (5);
	auto& row1 = table.addRow();
	table.addRow();
	table.addRow();
	table.addRow();

	//text.onSubmit = [&text](const std::string& value)
	//{
	//	DBG_LOG("User typed", value);
	//	text.clear();
	//};

	ui.run();
}
