#ifndef TERMOS_TABBED_VIEW_HH
#define TERMOS_TABBED_VIEW_HH

#include "TabSelector.hh"
#include "View.hh"

#include <functional>
#include <string>

namespace Termos {
class TabbedView : public View
{
public:
	TabbedView();

	template <typename T, typename... Args>
	T& tab(const std::string& name, Args&& ...args)
	{
		T& ret = View::add <T> (std::forward <Args> (args)...);
		prepareTab(name, ret);
		return ret;
	}

	template <typename T, typename... Args>
	T& add(Args&& ...args) = delete;

	std::function <void(Widget&)> onSwitchTab;

private:
	void prepareTab(const std::string& name, Widget& widget);
	void switchTab(size_t index);

	Widget* selected = nullptr;
	TabSelector& tabs;
};
}

#endif
