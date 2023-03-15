#ifndef TERMOS_EDITABLE_STRING_HH
#define TERMOS_EDITABLE_STRING_HH

#include "Render.hh"

#include <string>

namespace Termos {
class EditableString
{
public:
	EditableString();

	EditableString& operator=(const std::string& str);
	void setMaximumVisible(size_t value);

	void onRender(Render& render, unsigned x, unsigned y, bool showCursor = true);
	void onKeyPress(int key);

	operator const std::string&();

private:
	size_t maxVisible = 0;
	size_t selected = 0;

	std::string value;
};
}

#endif
