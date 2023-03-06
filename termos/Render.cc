#include "Render.hh"
#include "Widget.hh"
#include "Debug.hh"

#include <unordered_map>

namespace Termos {

Render::Render(Widget* widget) : widget(widget)
{
	werase(widget->window);
	setColor(Color::White, Color::Black);

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

struct ColorPair
{
	ColorPair(Color fg, Color bg) : fg(fg), bg(bg) {}

	bool operator==(const ColorPair& other) const
	{
		return fg == other.fg && bg == other.bg;
	}

	Color fg;
	Color bg;
};

class colorPairHash
{
public:
	size_t operator()(const ColorPair& c) const
	{
		return (size_t)c.fg * (size_t)c.bg;
	}
};

void Render::setColor(Color foreground, Color background)
{
	static short colors[]
	{
		COLOR_RED, COLOR_GREEN, COLOR_BLUE,
		COLOR_YELLOW, COLOR_MAGENTA, COLOR_CYAN,
		COLOR_BLACK, COLOR_WHITE
	};

	static std::unordered_map <ColorPair, int, colorPairHash> pairs;

	// Find the given color pair from initialized colors
	auto it = pairs.find(ColorPair(foreground, background));
	int index;

	// The color pair doesn't exist
	if(it == pairs.end())
	{
		// Create the given color pair
		index = pairs.size() + 1;
		init_pair(index, colors[static_cast <size_t> (foreground)], colors[static_cast <size_t> (background)]);
		pairs[ColorPair(foreground, background)] = index;
	}

	else index = it->second;

	// Activate the given color
	wattron(widget->window, COLOR_PAIR(index));
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
