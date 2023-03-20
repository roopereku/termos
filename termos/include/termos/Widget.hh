#ifndef TERMOS_WIDGET_HH
#define TERMOS_WIDGET_HH

#include "Render.hh"
#include "Vec2.hh"

#include <ncurses.h>

#include <memory>

class TermosUI;

namespace Termos {
class View;

class Widget
{
public:
	Widget();

	Widget& addNext(const std::shared_ptr <Widget>& widget, Widget* parent);

	void setVisible(bool visible);
	void show();
	void hide();

	Size getSize();

	// Termos and View needs direct access to window
	friend class ::TermosUI;
	friend class View;
	friend class Render;

protected:
	void render();

	virtual void onRender(Render& render) {};
	virtual void onMouseClick(Point at) {};
	virtual void onKeyPress(int key) {};
	virtual void onResize() {};

	void limitMaximumSize(unsigned limit);

private:
	virtual void renderAll();
	void renderSelf();

	virtual Widget* findMouseDestination(Point point);
	bool isMouseInside(Point point);

	void getPartitionIncrement(unsigned& increment, unsigned& nonLimited, bool horizontally);
	void adjustSizeAndPosition(unsigned partitionIncrement, bool horizontally);

	virtual void resize();
	void resize(Size partition, bool horizontally);

	virtual bool isView();
	void init(Widget* parent);

	Widget* findFirst();

	WINDOW* window = nullptr;
	bool focused = false;

	Point position;
	bool visible = true;

	unsigned sizeLimit = 0;
	Size size;

	Widget* parent = nullptr;
	Widget* previous = nullptr;
	std::shared_ptr <Widget> next;

	int id = 0;
};
}

#endif
