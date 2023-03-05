#include "termos/Termos.hh"
#include "termos/Logger.hh"
#include "termos/Button.hh"
#include "termos/Debug.hh"

int main()
{
	TermosUI ui(Termos::Split::Horizontally);

	auto& logger = ui.add <Termos::Logger> ();
	Termos::setDebugLogger(logger);

	DBG_LOG("moi");
	DBG_LOG("joona", "on", "homo");

	ui.run();
}
