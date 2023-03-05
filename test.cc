#include "termos/Termos.hh"
#include "termos/Logger.hh"
#include "termos/Button.hh"
#include "termos/Debug.hh"

int main()
{
	TermosUI ui(Termos::Split::Horizontally);

	auto& logger = ui.add <Termos::Logger> ();
	Termos::setDebugLogger(logger);

	auto& view = ui.add <Termos::View> (Termos::Split::Vertically);
	auto& logger2 = view.add <Termos::Logger> ();
	auto& logger3 = view.add <Termos::Logger> ();

	auto& view2 = view.add <Termos::View> (Termos::Split::Horizontally);
	auto& button = view2.add <Termos::Button> ("1");

	auto& view3 = view2.add <Termos::View> (Termos::Split::Vertically);
	auto& button2 = view3.add <Termos::Button> ("2");
	auto& button3 = view3.add <Termos::Button> ("3");

	button.onClick = []()
	{
		DBG_LOG("moi");
	};

	ui.run();
}
