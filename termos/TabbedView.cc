#include <termos/TabbedView.hh>
#include <termos/Debug.hh>

namespace Termos {

TabbedView::TabbedView() : View(Split::Vertically), tabs(View::add <TabSelector> ())
{
	tabs.onSelectTab = std::bind(&TabbedView::switchTab, this, std::placeholders::_1);
}

void TabbedView::prepareTab(const std::string& name, Widget& widget)
{
	tabs.add(name);

	if(selected) selected->hide();
	selected = &widget;
}

void TabbedView::switchTab(size_t index)
{
	// Find the nth child. Index is incremented so that the selector isn't matched
	Widget* newSelected = findChild(index + 1);

	if(newSelected)
	{
		selected->hide();
		newSelected->show();

		selected = newSelected;
	}
}

}
