#ifndef TERMOS_RENDER_HH
#define TERMOS_RENDER_HH

#include <string>

namespace Termos {

enum class Color
{
	Red, Green, Blue,
	Yellow, Purple, Cyan,
	Black, White
};

class Widget;
class Render
{
public:
	~Render();

	void text(const char* str, unsigned x, unsigned y, unsigned maxLength = 0);
	void text(const std::string& str, unsigned x, unsigned y, unsigned maxLength = 0);

	void character(char ch, unsigned x, unsigned y);

	void blankLine(unsigned y);
	void blankLine(unsigned x, unsigned y, unsigned length);

	void verticalLine(unsigned x, unsigned y, unsigned length);
	void horizontalLine(unsigned x, unsigned y, unsigned length);

	void invertColor();
	void defaultColor();

	void setColor(Color foreground, Color background);
	void setForeground(Color foreground);
	void setBackground(Color background);

	Color getForegroundColor() { return fg; }
	Color getBackgroundColor() { return bg; }

	// Only Widget has access to the constructor
	friend class Widget;

private:
	void setColor();

	Color fg;
	Color bg;

	Render(Widget* widget);
	Widget* widget;
};
}

#endif
