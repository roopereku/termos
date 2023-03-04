#include "Widget.hh"
#include "View.hh"

#include <cmath>

namespace Termos {

Widget::Widget()
{
	static int ids = 0;
	id = ids;
	ids++;
}

void Widget::render()
{
	renderSelf();
	if(parent)
		parent->render();
}

void Widget::renderSelf()
{
	Render render(window, *this);
	onRender(render);
}

void Widget::renderAll()
{
	if(next) next->renderAll();
	renderSelf();
}

void Widget::setMaximumSize(Size size)
{
	maxSize = size;
}

Sizef Widget::getSize()
{
	return size;
}

Widget& Widget::addNext(const std::shared_ptr <Widget>& widget, Widget* parent)
{
	// If next already exists, set it's next widget
	if(next) return next->addNext(widget, parent);

	next = widget;

	// The parent widget can't be the previous one
	if(this != parent)
		next->previous = this;

	next->init(parent);
	return *next;
}

Widget* Widget::findFirst()
{
	if(previous == nullptr)
		return this;

	return previous->findFirst();
}

void Widget::init(Widget* parent)
{
	this->parent = parent;

	// We need to resize the previous widgets too
	findFirst()->resize();
}

Widget* Widget::findMouseDestination(Point point)
{
	if(isMouseInside(point))
		return this;

	// If the mouse isn't inside this widget, check next if it exists
	return next ? next->findMouseDestination(point) : nullptr;
}

bool Widget::isMouseInside(Point point)
{
	// Is the given point inside the borders of this widget
	return	point.x >= position.x && point.x <= position.x + size.x &&
			point.y >= position.y && point.y <= position.y + size.y;
}

void Widget::resize()
{
	// The root window doesn't follow the same logic
	if(!parent)
		return;

	// Create a window if one doesn't exist
	if(!window)
		window = newwin(1, 1, 1, 1);

	View* view = static_cast <View*> (parent);
	bool horizontally = view->getSplitDirection() == Split::Horizontally;

	/* Depending on the parent splitting direction, partition one of the
	 * dimensions in a way that all of the widgets can fit in the parent view */
	size = Sizef(
		(float)view->size.x / (horizontally ? view->getWidgetCount() : 1) - 4,
		(float)view->size.y / (horizontally ? 1 : view->getWidgetCount()) - 2
	);

	// If there's a previous widget, use it as an offset
	if(previous)
	{
		position = Point(
			previous->position.x + (horizontally ? previous->size.x : 0),
			previous->position.y + (horizontally ? 0 : previous->size.y)
		);
	}

	else
	{
		position = Point(
			parent->position.x + 2,
			parent->position.y + 1
		);
	}

	// Move and resize the widget
	mvwin(window, position.y, position.x);
	wresize(window, size.y, size.x);

	// Resize the next widget
	if(next) next->resize();
}

}
