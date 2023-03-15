#ifndef TERMOS_BUTTON_HH
#define TERMOS_BUTTON_HH

#include "Widget.hh"

#include <string>
#include <functional>

namespace Termos {
class Button : public Widget
{
public:
	Button(const std::string& textValue);
	Button();

	void onRender(Render& render) override;
	void onMouseClick(Point at) override;

	void setText(const std::string& value);
	std::function <void()> onClick;

private:
	std::string text;
};
}

#endif
