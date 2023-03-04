#include "termos/Termos.hh"
#include "termos/Logger.hh"

int main()
{
	TermosUI ui(Termos::Split::Horizontally);

	auto& left = ui.add <Termos::View> (Termos::Split::Vertically);
	auto& right = ui.add <Termos::View> (Termos::Split::Vertically);

	auto& ltest2 = left.add <Termos::Logger> ();

	ltest2.add("bcd", 1);
	ltest2.add("bcdjkdfjlk", 34);

	ui.run();
}
