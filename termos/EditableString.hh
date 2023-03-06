#ifndef TERMOS_EDITABLE_STRING_HH
#define TERMOS_EDITABLE_STRING_HH

#include "Render.hh"

#include <string>

namespace Termos {
class EditableString
{
public:
	EditableString();

	void onRender(Render& render, unsigned x, unsigned y);
	void onKeyPress(int ch);

	operator const std::string&();

private:
	size_t selected = 0;
	std::string value;
};
}

#endif
