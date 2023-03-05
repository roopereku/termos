#ifndef TERMOS_RENDER_HH
#define TERMOS_RENDER_HH

#include <string>

namespace Termos {

class Widget;
class Render
{
public:
	~Render();

	void text(unsigned x, unsigned y, const char* str, unsigned maxLength = 0);
	void text(unsigned x, unsigned y, const std::string& str, unsigned maxLength = 0);

	void verticalLine(unsigned x, unsigned y, unsigned length);
	void horizontalLine(unsigned x, unsigned y, unsigned length);

	// Only Widget has access to the constructor
	friend class Widget;

private:
	Render(Widget* widget);
	Widget* widget;
};
}

#endif
