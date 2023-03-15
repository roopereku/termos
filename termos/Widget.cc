#include <termos/Widget.hh>
#include <termos/Debug.hh>
#include <termos/View.hh>

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
}

void Widget::renderSelf()
{
	Render render(this);
	onRender(render);
}

void Widget::renderAll()
{
	if(next) next->renderAll();
	renderSelf();
}

Size Widget::getSize()
{
	return Size(
		size.x - 2,
		size.y - 2
	);
}

void Widget::limitMaximumSize(unsigned limit)
{
	Widget* first = findFirst();
	sizeLimit = limit + 2;

	first->resize();
	first->renderAll();
}

bool Widget::isView()
{
	return false;
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
	return	point.x > position.x && point.x < position.x + size.x &&
			point.y > position.y && point.y < position.y + size.y;
}

void Widget::getPartitionIncrement(unsigned& increment, unsigned& nonLimited, bool horizontally)
{
	if(sizeLimit)
	{
		unsigned diff = (horizontally ? size.x : size.y) - sizeLimit;
		bool overflow = false;

		if(horizontally)
		{
			if(size.x > sizeLimit)
			{
				size.x = sizeLimit;
				overflow = true;
			}
		}

		else if(size.y > sizeLimit)
		{
			size.y = sizeLimit;
			overflow = true;
		}

		if(overflow)
			increment += diff;

		else nonLimited++;
	}

	else nonLimited++;

	if(next)
		next->getPartitionIncrement(increment, nonLimited, horizontally);
}

void Widget::adjustSizeAndPosition(unsigned partitionIncrement, bool horizontally)
{
	// TODO A limited widget that hasn't reached it's max size could grow with the increment
	if(!sizeLimit)
	{
		if(horizontally) size.x += partitionIncrement;
		else size.y += partitionIncrement;
	}

	// If there's a previous widget, use it as an offset
	if(previous)
	{
		position = Point(
			previous->position.x + (horizontally ? previous->size.x + 1 : 0),
			previous->position.y + (horizontally ? 0 : previous->size.y)
		);
	}

	else position = parent->position;

	// Move and resize the widget
	mvwin(window, position.y, position.x);
	wresize(window, size.y, size.x);

	onResize();

	if(next)
		next->adjustSizeAndPosition(partitionIncrement, horizontally);
}

void Widget::resize()
{
	if(!parent)
		return;

	View* view = static_cast <View*> (parent);
	bool horizontally = view->getSplitDirection() == Split::Horizontally;

	/* Depending on the parent splitting direction, partition one of the
	 * dimensions in a way that all of the widgets can fit in the parent view */
	Size partition(
		(float)view->size.x / (horizontally ? view->getWidgetCount() : 1) - 1,
		(float)view->size.y / (horizontally ? 1 : view->getWidgetCount())
	);

	resize(partition, horizontally);
}

void Widget::resize(Size partition, bool horizontally)
{
	// Create a window if one doesn't exist
	if(!window)
		window = newwin(1, 1, 1, 1);

	size = partition;

	// Resize the next widget
	if(next) next->resize();

	// If there's no next, start processing positions and sizes
	else
	{
		unsigned increment = 0;
		unsigned nonLimited = 0;

		// What's the first widget inside the current view?
		Widget* first = findFirst();

		// How much can non-limited widgets grow?
		first->getPartitionIncrement(increment, nonLimited, horizontally);

		// If non-limited widgets == 0, we get an FPU fault
		if(nonLimited > 0)
		{
			// Split the increment with all of the non-limited widgets
			increment = increment / nonLimited;
		}

		first->adjustSizeAndPosition(increment, horizontally);
	}
}

}
