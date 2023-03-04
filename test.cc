#include "termos/Termos.hh"
#include "termos/Logger.hh"
#include "termos/Debug.hh"

int main()
{
	TermosUI ui(Termos::Split::Horizontally);

	auto& left = ui.add <Termos::View> (Termos::Split::Vertically);
	auto& right = ui.add <Termos::View> (Termos::Split::Vertically);

	auto& ltest2 = left.add <Termos::Logger> ();
	auto& rtest2 = right.add <Termos::Logger> ();
	Termos::setDebugLogger(ltest2);

	ui.run();
}
