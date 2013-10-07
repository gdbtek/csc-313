#include <ncurses.h>
#include <cstdlib>
#include <time.h>

void Number (int, char **);

int main (int argc, char **argv)
{
    Number (argc, argv);

    return 0;
}

void Number (int argc, char **argv)
{
    initscr ();
    noecho ();
    start_color ();
    clear ();
    refresh ();

    init_pair (1, COLOR_RED, COLOR_BLACK);
    init_pair (2, COLOR_GREEN, COLOR_BLACK);
    init_pair (3, COLOR_YELLOW, COLOR_BLACK);
    init_pair (4, COLOR_BLUE, COLOR_BLACK);
    init_pair (5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair (6, COLOR_CYAN, COLOR_BLACK);
    init_pair (7, COLOR_WHITE, COLOR_BLACK);

    srand (time (NULL));

    for (int count = 0; count < atoi ((argc == 2) ? argv [1] : "5"); count++)
    {
        for (int r = 0, l = LINES - 1; r < LINES && l >= 0; r++, l--)
        {
            for (int c = 0; c < COLS; c += 2)
            {
                attrset (A_BOLD | COLOR_PAIR (1 + rand () % 8));
                mvprintw (l, c + 1, "%i", rand () % 10);
                attrset (A_NORMAL);
                attrset (A_BOLD | COLOR_PAIR (1 + rand () % 8));
                mvprintw (r, c, "%i", rand () % 10);
                attrset (A_NORMAL);
            }
            move (LINES / 2, COLS / 2);
            refresh ();
        }

        for (int c = 0, v = COLS - 1; c < COLS && v >= 0; c++, v--)
        {
            for (int r = 0; r < LINES; r += 2)
            {
                mvaddch (r, c, ' ');
                mvaddch (r + 1, v, ' ');
            }
            move (LINES / 2, COLS / 2);
            refresh ();
        }

        for (int c = 0, v = COLS - 1; c < COLS && v >= 0; c++, v--)
        {
            for (int r = 0; r < LINES; r += 2)
            {
                attrset (A_BOLD | COLOR_PAIR (1 + rand () % 8));
                mvprintw (r, c, "%i", rand () % 2);
                attrset (A_NORMAL);
                attrset (A_BOLD | COLOR_PAIR (1 + rand () % 8));
                mvprintw (r + 1, v, "%i", rand () % 2);
                attrset (A_NORMAL);
            }
            move (LINES / 2, COLS / 2);
            refresh ();
        }

        for (int r = 0, l = LINES - 1; r < LINES && l >= 0; r++, l--)
        {
            for (int c = 0; c < COLS; c += 2)
            {
                mvaddch (l, c + 1, ' ');
                mvaddch (r, c, ' ');
            }
            move (LINES / 2, COLS / 2);
            refresh ();
        }
    }

    move (LINES - 1, COLS - 1);
    clear ();
    refresh ();
    endwin ();
}
