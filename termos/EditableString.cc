#include <termos/EditableString.hh>
#include <termos/Debug.hh>

#include <ncurses.h>

namespace Termos {

EditableString::EditableString()
{
}

EditableString& EditableString::operator=(const std::string& str)
{
	value = str;
	selected = value.size();

	return *this;
}

void EditableString::setMaximumVisible(size_t value)
{
	maxVisible = value;
}

void EditableString::onRender(Render& render, unsigned x, unsigned y, bool showCursor)
{
	size_t offset = 0;

	if(maxVisible)
	{
		if(selected + 1 >= maxVisible)
			offset = selected - maxVisible + 1;
	}

	if(!value.empty())
		render.text(value.c_str() + offset, x, y, maxVisible);

	if(!showCursor)
		return;

	// If the character at the given position isn't defined yet, use a space
	auto selectedChar = selected == value.size() ? ' ' : value[selected];

	// Re-render the selected character with a highlight
	render.invertColor();
	render.character(selectedChar, x + selected - offset, y);
	render.invertColor();
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
