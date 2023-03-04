#include "Render.hh"
#include "Widget.hh"

namespace Termos {

Render::Render(WINDOW* window, Widget& widget) : window(window)
{
	werase(window);
	box(window, 0, 0);
}

Render::~Render()
{
	wrefresh(window);
}

void Render::text(unsigned x, unsigned y, const char* str)
{
	mvwprintw(window, y + 1, x + 1, "%s", str);
}

}
