#include "Termos.hh"

TermosUI::TermosUI(Termos::Split direction) : View(direction)
{
	Termos::Widget::window = initscr();
	size = Sizef(COLS, LINES);

	// Hide the cursor
	curs_set(0);

	// Enable arrow keys, resize events and mouse events
	keypad(window, true);
	mousemask(BUTTON1_PRESSED | BUTTON2_PRESSED, NULL);
}

TermosUI::~TermosUI()
{
	endwin();
}

void TermosUI::run()
{
	renderAll();
	bool running = true;

	while(running)
	{
		// Check for keypresses / events
		int key = getch();

		switch(key)
		{
			// Did the window size change?
			case KEY_RESIZE:
			{
				size = Sizef(COLS, LINES);

				// Recursively resize all children and re-render them
				resizeChildren();
				renderAll();

				break;
			}

			// Did a mouse click happen
			case KEY_MOUSE:
			{
				MEVENT mouse;
				if(getmouse(&mouse) == OK)
				{
				}
			}
		}
	}
}
