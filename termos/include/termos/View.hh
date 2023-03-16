#ifndef TERMOS_VIEW_HH
#define TERMOS_VIEW_HH

#include "Widget.hh"

#include <memory>
#include <vector>

namespace Termos {

enum class Split
{
	Horizontally,
	Vertically
};

class View : public Widget
{
public:
	View(Split direction);

	Split getSplitDirection();
	size_t getWidgetCount();

	template <typename T, typename... Args>
	T& add(Args&& ...args)
	{
		auto ptr = std::make_shared <T> (std::forward <Args> (args)...);
		widgetCount++;
		return static_cast <T&> (addNextChild(ptr));
	}

	friend class Widget;

protected:
	void renderAll() override;
	void resizeChildren();

	Widget* findMouseDestination(Point point) override;
	Widget& addNextChild(const std::shared_ptr <Widget>& widget);

private:
	bool isView() override;
	void resize() override;

	size_t widgetCount = 0;
	Split direction;

	std::shared_ptr <Widget> firstChild;
};
}

#endif
