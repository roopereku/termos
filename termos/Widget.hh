#ifndef TERMOS_WIDGET_HH
#define TERMOS_WIDGET_HH

#include "Render.hh"
#include "Vec2.hh"

#include <ncurses.h>

#include <memory>

class TermosUI;

namespace Termos {
class Widget
{
public:
	Widget();

	void setMaximumSize(Size size);

	Widget& addNext(const std::shared_ptr <Widget>& widget, Widget* parent);

	// Termos and View needs direct access to window
	friend class ::TermosUI;
	friend class View;
	friend class Render;

protected:
	void render();

	virtual void onRender(Render& render) {};
	virtual void onMouseClick(Point at) {};

	Sizef getSize();

private:
	virtual void renderAll();
	void renderSelf();

	virtual Widget* findMouseDestination(Point point);
	bool isMouseInside(Point point);

	virtual void resize();
	void init(Widget* parent);

	Widget* findFirst();

	WINDOW* window = nullptr;

	Size maxSize;
	Point position;
	Sizef size;

	Widget* parent = nullptr;
	Widget* previous = nullptr;
	std::shared_ptr <Widget> next;

	int id = 0;
};
}

#endif
