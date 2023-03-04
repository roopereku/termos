#include "Termos.hh"
#include "Debug.hh"

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
					Point at(mouse.x, mouse.y);
					Widget* clickAt = findMouseDestination(at);

					if(clickAt)
					{
						// Subtract the widget position to make the mouse start at 0 0
						at.x -= clickAt->position.x;
						at.y -= clickAt->position.y;

						if(focused)
						{
							focused->focused = false;
							focused->render();
						}

						focused = clickAt;
						clickAt->focused = true;
						clickAt->onMouseClick(at);

						focused->render();
					}
				}
			}
		}
	}
}
