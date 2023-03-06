#include "Button.hh"

namespace Termos {

Button::Button(const std::string& textValue)
{
	text = textValue;
}

Button::Button()
{
}

void Button::onRender(Render& render) 
{
	if(text.empty())
		return;

	Point middle(
		getSize().x / 2 - text.length() + 1,
		getSize().y / 2 - 1
	);

	render.text(text.c_str(), middle.x, middle.y);
}

void Button::onMouseClick(Point)
{
	if(onClick)
		onClick();
}

void Button::setText(const std::string& value)
{
	text = value;
	render();
}

}
