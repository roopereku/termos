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

	auto& text = ui.add <Termos::TextInput> ();
	text.onSubmit = [&text](const std::string& value)
	{
		DBG_LOG("User typed", value);
		text.clear();
	};

	ui.run();
}
