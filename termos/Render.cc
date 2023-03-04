#include "Render.hh"
#include "Widget.hh"

namespace Termos {

Render::Render(WINDOW* window, Widget& widget) : window(window)
{
	werase(window);
	box(window, 0, 0);

	if(widget.focused)
		mvwprintw(window, 0, 3, "Focused");
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
