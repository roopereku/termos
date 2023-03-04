#include "termos/Termos.hh"
#include "termos/Logger.hh"
#include "termos/Button.hh"
#include "termos/Debug.hh"

int main()
{
	TermosUI ui(Termos::Split::Horizontally);

	auto& left = ui.add <Termos::View> (Termos::Split::Vertically);
	auto& right = ui.add <Termos::View> (Termos::Split::Vertically);

	auto& logger = left.add <Termos::Logger> ();

	auto& addButton = right.add <Termos::Button> ("Add a new button");
	addButton.onClick = [&right]()
	{
		static unsigned count = 0;
		count++;

		DBG_LOG("Adding button", count);
		right.add <Termos::Button> ("Button" + std::to_string(count));
	};

	Termos::setDebugLogger(logger);

	ui.run();
}
