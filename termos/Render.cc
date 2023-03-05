#include "Render.hh"
#include "Widget.hh"

namespace Termos {

Render::Render(WINDOW* window, Widget& widget) : window(window)
{
	werase(window);

	if(!widget.isView())
		box(window, 0, 0);

	mvwprintw(window, 0, 1, "%d", widget.id);

	if(widget.focused)
		mvwprintw(window, 0, 5, "Focused");
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
