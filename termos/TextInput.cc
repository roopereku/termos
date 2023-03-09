#include "TextInput.hh"

namespace Termos {

TextInput::TextInput()
{
	limitMaximumSize(1);
}

void TextInput::onRender(Render& render)
{
	value.onRender(render, 0, 0);
}

void TextInput::clear()
{
	value = EditableString();
	render();
}

void TextInput::onResize()
{
	value.setMaximumVisible(getSize().x);
}

void TextInput::onKeyPress(int key)
{
	// If the enter key was pressed, submit the value
	if(key == '\n' || key == '\r')
	{
		if(onSubmit)
			onSubmit(value);

		return;
	}

	// Forward the key to the editable string
	value.onKeyPress(key);
	render();
}

}
