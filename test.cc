#include <termos/TabbedView.hh>
#include <termos/TextInput.hh>
#include <termos/Termos.hh>
#include <termos/Logger.hh>
#include <termos/Button.hh>
#include <termos/Table.hh>
#include <termos/Debug.hh>
#include <termos/Menu.hh>

class Test : public Termos::Widget
{
public:
	void onUpdate(double delta) override
	{
		elapsed += delta;
		if(elapsed >= 1)
		{
			DBG_LOG("Update test");
			elapsed = 0;
		}
	}

private:
	double elapsed = 0;
};

int main()
{
	TermosUI ui(Termos::Split::Horizontally);

	auto& logger = ui.add <Termos::Logger> ();
	Termos::setDebugLogger(logger);

	auto& right = ui.add <Termos::View> (Termos::Split::Vertically);
	auto& test = right.add <Test> ();

	ui.run();
}
