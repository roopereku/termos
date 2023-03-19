#ifndef TERMOS_TAB_SELECTOR_HH
#define TERMOS_TAB_SELECTOR_HH

#include <termos/Widget.hh>

#include <functional>
#include <vector>
#include <string>

namespace Termos {
class TabSelector : public Widget
{
public:
	TabSelector();

	void add(const std::string& name);
	void select(size_t index);
	size_t getTabCount();

	void onRender(Render& render) override;
	void onMouseClick(Point at) override;

	std::function <void(size_t index)> onSelectTab;

private:
	std::vector <std::string> tabs;
	size_t selected = 0;
};
}

#endif
