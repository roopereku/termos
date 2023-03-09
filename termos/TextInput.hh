#ifndef TEXT_INPUT_HH
#define TEXT_INPUT_HH

#include "Widget.hh"
#include "EditableString.hh"

#include <functional>

namespace Termos {
class TextInput : public Widget
{
public:
	TextInput();

	void onRender(Render& render) override;
	void onKeyPress(int key) override;
	void onResize() override;

	void clear();

	std::function <void(const std::string&)> onSubmit;

private:
	EditableString value;
};
}

#endif
