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

	void verticalLine(unsigned x, unsigned y, unsigned length);
	void horizontalLine(unsigned x, unsigned y, unsigned length);

	void setColor(Color foreground, Color background);

	// Only Widget has access to the constructor
	friend class Widget;

private:
	Render(Widget* widget);
	Widget* widget;
};
}

#endif
