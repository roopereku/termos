#ifndef TERMOS_HH
#define TERMOS_HH

#include "View.hh"

class TermosUI : public Termos::View
{
public:
	TermosUI(Termos::Split direction);
	~TermosUI();

	void run();

private:
	WINDOW* root;
};

#endif
