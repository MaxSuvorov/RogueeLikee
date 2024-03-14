#include "imports.h"
#include "Game.h"
#include "intro.h"
#include <curses.h>
int main()
{
    int c;

    int cols;
    int rows;

    Game Game;
    Intro Intro;

	initscr();
	start_color();
    use_default_colors();

	init_pair(BLACK, COLOR_BLACK, COLOR_WHITE);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);

	keypad(stdscr, 1);
	noecho();
	curs_set(0);

	getmaxyx(stdscr, rows, cols);

    c = Intro.ui();

    if (c == 27) // 27 == 'ESC'
    {
        endwin();
        return 0;
    }

    while (1)
    {
        c = Game.loop(c, rows - 1, cols - 1);
        if (c == 27)
        {
            endwin();
            return 0;
        }
    }
}
