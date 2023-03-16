#include <termos/TabbedView.hh>
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

	auto& left = ui.add <Termos::View> (Termos::Split::Vertically);
	auto& right = ui.add <Termos::View> (Termos::Split::Vertically);

	auto& logger = left.add <Termos::Logger> ();
	Termos::setDebugLogger(logger);

	auto& menu = left.add <Termos::Menu> ();

	auto& toggle1 = menu.addToggle("Toggle 1", true);
	auto& toggle2 = menu.addToggle("Toggle 2", true);
	auto& toggle3 = menu.addToggle("Toggle 3", true);
	auto& toggle4 = menu.addToggle("Toggle 4", true);

	auto& m1 = right.add <Termos::Menu> ();
	auto& m2 = right.add <Termos::Menu> ();
	auto& m3 = right.add <Termos::Menu> ();
	auto& m4 = right.add <Termos::Menu> ();

	toggle1.onToggle = [&m1](bool on) { m1.setVisible(on); };
	toggle2.onToggle = [&m2](bool on) { m2.setVisible(on); };
	toggle3.onToggle = [&m3](bool on) { m3.setVisible(on); };
	toggle4.onToggle = [&m4](bool on) { m4.setVisible(on); };

	ui.run();
}
