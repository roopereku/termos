#include "Render.hh"
#include "Widget.hh"

namespace Termos {

Render::Render(Widget* widget) : widget(widget)
{
	werase(widget->window);

	if(!widget->isView())
		box(widget->window, 0, 0);

	mvwprintw(widget->window, 0, 1, "%d", widget->id);

	if(widget->focused)
		mvwprintw(widget->window, 0, 5, "Focused");
}

Render::~Render()
{
	wrefresh(widget->window);
}

void Render::text(unsigned x, unsigned y, const std::string& str, unsigned maxLength)
{
	text(x, y, str.c_str(), maxLength);
}

void Render::text(unsigned x, unsigned y, const char* str, unsigned maxLength)
{
	if(maxLength == 0)
		mvwprintw(widget->window, y + 1, x + 1, "%s", str);

	else mvwprintw(widget->window, y + 1, x + 1, "%.*s", maxLength, str);
}

void Render::verticalLine(unsigned x, unsigned y, unsigned length)
{
	mvwvline(widget->window, y + 1, x + 1, 0, length);
}

void Render::horizontalLine(unsigned x, unsigned y, unsigned length)
{
	mvwhline(widget->window, y + 1, x + 1, 0, length);
}

}
