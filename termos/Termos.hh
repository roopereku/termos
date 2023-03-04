#ifndef TERMOS_HH
#define TERMOS_HH

#include "Widget.hh"
#include "View.hh"

class TermosUI : public Termos::View
{
public:
	TermosUI(Termos::Split direction);
	~TermosUI();

	void run();

private:
	Widget* focused = nullptr;
	WINDOW* root;
};

#endif
