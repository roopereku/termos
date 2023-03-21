#ifndef TERMOS_HH
#define TERMOS_HH

#include "Widget.hh"
#include "View.hh"

#include <chrono>

class TermosUI : public Termos::View
{
public:
	TermosUI(Termos::Split direction);
	~TermosUI();

	void run(unsigned delayMs = 50);

private:
	std::chrono::time_point <std::chrono::high_resolution_clock> previous;

	Widget* focused = nullptr;
	WINDOW* root;
};

#endif
