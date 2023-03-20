#include <termos/TabbedView.hh>
#include <termos/TextInput.hh>
#include <termos/Termos.hh>
#include <termos/Logger.hh>
#include <termos/Button.hh>
#include <termos/Table.hh>
#include <termos/Debug.hh>
#include <termos/Menu.hh>

class Test : public Termos::Submenu
{
public:
	Test(const std::string& n, int ttl) : Termos::Submenu(n)
	{
		if(ttl == 0)
			return;

		ttl--;
		add <Test> ("moi" + std::to_string(ttl), ttl);
	}
};

int main()
{
	TermosUI ui(Termos::Split::Horizontally);

	auto& logger = ui.add <Termos::Logger> ();
	Termos::setDebugLogger(logger);

	auto& right = ui.add <Termos::View> (Termos::Split::Vertically);

	auto& menu = right.add <Termos::Menu> ();
	auto& test = menu.add <Test> ("root", 5);

	auto& text = right.add <Termos::TextInput> ();

	text.onSubmit = [&text, &test](const std::string& value)
	{
		auto& t = test.addMenu("new menu");
		text.clear();

		t.onExpand = []()
		{
			DBG_LOG("new menu expanded");
		};
	};

	ui.run();
}
