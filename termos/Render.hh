#ifndef TERMOS_RENDER_HH
#define TERMOS_RENDER_HH

#include <ncurses.h>

namespace Termos {
class Widget;
class Render
{
public:
	Render(WINDOW* window, Widget& widget);
	~Render();

	void text(unsigned x, unsigned y, const char* str);

private:
	WINDOW* window;
};
}

#endif
