#include <termos/Termos.hh>
#include <termos/Debug.hh>

#include <thread>

TermosUI::TermosUI(Termos::Split direction) : View(direction)
{
	window = initscr();
	start_color();

	size = Size(COLS, LINES);

	// Hide the cursor
	curs_set(0);

	// Don't echo characters typed by the user
	noecho();

	// Enable arrow keys, resize events and mouse events
	keypad(window, true);
	mousemask(BUTTON1_PRESSED | BUTTON2_PRESSED, NULL);

	// Make getch non-blocking
	nodelay(window, true);
}

TermosUI::~TermosUI()
{
	endwin();
}

void TermosUI::run(unsigned delayMs)
{
	renderAll();
	bool running = true;
	previous = std::chrono::high_resolution_clock::now();

	while(running)
	{
		// Check for keypresses / events
		int key = getch();

		switch(key)
		{
			// Did the window size change?
			case KEY_RESIZE:
			{
				size = Size(COLS, LINES);

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
						at.x -= clickAt->position.x + 1;
						at.y -= clickAt->position.y + 1;

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

				break;
			}

			default:
			{
				if(focused)
					focused->onKeyPress(key);
			}
		}

		auto now = std::chrono::high_resolution_clock::now();

		// What's the difference between previous and now in milliseconds
		using ms = std::chrono::duration<float, std::milli>;
		auto delta = std::chrono::duration_cast <ms> (now - previous).count();

		// Update all widgets. Delta is divided by 1000 to make 100 ms look like 0.1s
		onUpdate(delta / 1000);

		// Sleep for the given amount to reduce CPU usage
		std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));

		previous = now;
	}
}
