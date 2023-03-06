#include "EditableString.hh"
#include "Debug.hh"

#include <ncurses.h>

namespace Termos {

EditableString::EditableString()
{
}

void EditableString::onRender(Render& render, unsigned x, unsigned y)
{
	if(!value.empty())
		render.text(value, x, y);

	// If the character at the given position isn't defined yet, use a space
	char selectedChar = selected == value.size() ? ' ' : value[selected];

	// Re-render the selected character with a highlight
	render.setColor(Color::Black, Color::White);
	render.character(selectedChar, x + selected, y);
}

void EditableString::onKeyPress(int ch)
{
	switch(ch)
	{
		case KEY_BACKSPACE:
		{
			if(selected - 1 < value.size())
			{
				value.erase(value.begin() + selected - 1);
				selected--;
			}

			break;
		}

		case KEY_LEFT:
		{
			if(selected - 1 < value.size())
				selected--;

			break;
		}

		case KEY_RIGHT:
		{
			if(selected + 1 <= value.size())
				selected++;

			break;
		}

		default:
			if(selected < value.size())
				value.insert(value.begin() + selected, ch);

			else value += ch;
			selected++;
	}
}

EditableString::operator const std::string&()
{
	return value;
}

}
