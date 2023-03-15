#include <termos/Render.hh>
#include <termos/Widget.hh>
#include <termos/Debug.hh>

#include <unordered_map>
#include <cstring>

namespace Termos {

Render::Render(Widget* widget) : widget(widget)
{
	werase(widget->window);
	defaultColor();

	if(!widget->isView())
		box(widget->window, 0, 0);

	//mvwprintw(widget->window, 0, 1, "%d", widget->id);
	//mvwprintw(widget->window, 0, 1, "%d %d", widget->position.x, widget->position.y);

	//if(widget->focused)
	//	mvwprintw(widget->window, 0, 5, "Focused");
}

Render::~Render()
{
	wattroff(widget->window, A_BOLD);
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

void Render::setForeground(Color foreground)
{
	fg = foreground;
	setColor();
}

void Render::setBackground(Color background)
{
	bg = background;
	setColor();
}

void Render::setColor(Color foreground, Color background)
{
	fg = foreground;
	bg = background;

	setColor();
}

void Render::invertColor()
{
	std::swap(fg, bg);
	setColor();
}

void Render::defaultColor()
{
	setColor(Color::White, Color::Black);
}

void Render::setColor()
{
	static short colors[]
	{
		COLOR_RED, COLOR_GREEN, COLOR_BLUE,
		COLOR_YELLOW, COLOR_MAGENTA, COLOR_CYAN,
		COLOR_BLACK, COLOR_WHITE
	};

	static std::unordered_map <ColorPair, int, colorPairHash> pairs;

	// Find the given color pair from initialized colors
	auto it = pairs.find(ColorPair(fg, bg));
	int index;

	// The color pair doesn't exist
	if(it == pairs.end())
	{
		// Create the given color pair
		index = pairs.size() + 1;
		init_pair(index, colors[static_cast <size_t> (fg)], colors[static_cast <size_t> (bg)]);
		pairs[ColorPair(fg, bg)] = index;
	}

	else index = it->second;

	// Activate the given color
	wattron(widget->window, COLOR_PAIR(index));

	if(widget->focused)
		wattron(widget->window, A_BOLD);
}

void Render::text(const std::string& str, unsigned x, unsigned y, unsigned maxLength)
{
	text(str.c_str(), x, y, maxLength);
}

void Render::text(const char* str, unsigned x, unsigned y, unsigned maxLength)
{
	size_t length = strlen(str);
	if(length > maxLength && length >= widget->getSize().x)
		maxLength = widget->getSize().x;

	if(maxLength == 0)
		mvwprintw(widget->window, y + 1, x + 1, "%s", str);

	else mvwprintw(widget->window, y + 1, x + 1, "%.*s", maxLength, str);
}

void Render::character(char ch, unsigned x, unsigned y)
{
	mvwprintw(widget->window, y + 1, x + 1, "%c", ch);
}

void Render::blankLine(unsigned y)
{
	mvwprintw(widget->window, y + 1, 1, "%*c", widget->getSize().x, ' ');
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
