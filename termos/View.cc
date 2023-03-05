#include "View.hh"

namespace Termos {

View::View(Split direction) : direction(direction)
{
}

Split View::getSplitDirection()
{
	return direction;
}

size_t View::getWidgetCount()
{
	return widgetCount;
}

bool View::isView()
{
	return true;
}

void View::renderAll()
{
	Widget::renderAll();
	if(firstChild) firstChild->renderAll();
}

void View::resize()
{
	Widget::resize();
	resizeChildren();
}

void View::resizeChildren()
{
	if(firstChild)
		firstChild->resize();
}

Widget* View::findMouseDestination(Point point)
{
	// If the mouse is inside this view, check if the user clicked on a child widget
	if(isMouseInside(point))
		return firstChild ? firstChild->findMouseDestination(point) : nullptr;

	// The mouse isn't inside this widget so check if next was clicked
	return next ? next->findMouseDestination(point) : nullptr;
}

Widget& View::addNextChild(const std::shared_ptr <Widget>& widget)
{
	// If the first child exists, add a next for it
	if(firstChild)
	{
		Widget& ret = firstChild->addNext(widget, this);
		renderAll();

		return ret;
	}

	// Initialize the first child
	firstChild = widget;
	firstChild->init(this);

	firstChild->render();
	return *firstChild;
}

}
