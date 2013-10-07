// *************************************************************************
// FILE NAME: p0.cpp                                                       *
// CREATED  : 01/30/2002                                                   *
// UPDATED  : 02/25/2002                                                   *
// *************************************************************************

#include "p0.h"

int main (int argc, char **argv)
{
    initscr ();
    noecho ();

    Welcome ();
    Selection (argc, argv);

    endwin ();

    return 0;
}

void Welcome (void)
{
    clear ();

    attrset (A_BOLD);
    border ('|', '|', '-', '-', '/', '\\', '\\', '/');
    attrset (A_NORMAL);
    attrset (A_BLINK | A_BOLD);
    mvaddstr (8, 23, "PROJECT 0 - THE VEHICLE SIMULATOR");
    attrset (A_NORMAL);
    mvaddstr (10, 34, "Nam Nguyen");
    mvaddstr (11, 30, "breakins@excite.com");
    mvaddstr (12, 29, "www.breakins.cjb.net");
    mvaddstr (14, 34, __DATE__);
    mvaddstr (15, 35, __TIME__);
    mvaddstr (21, 25, "Press any key to continue...");

    refresh ();
    getch ();
}

void Selection (int argc, char **argv)
{
    clear ();
    refresh ();
    flushinp ();

    struct passwd *user = getpwnam (getlogin ());

    attrset (A_BOLD);
    box (stdscr, 0, 0);
    attrset (A_NORMAL);
    mvaddstr (4, 3,  "   OOOOOOOOOO O");
    mvaddstr (5, 3,  " O        OOO  OOOOOOO");
    mvaddstr (6, 3,  "O                     O");
    mvaddstr (7, 3,  "OOOOOOOOOOOOOOOOOOOOOOOO");
    mvaddstr (8, 3,  "  OOOOO         OOOOO");
    mvaddstr (9, 3,  "   OOO           OOO");
    mvaddstr (2, 34, "         /--\\                /--\\");
    mvaddstr (3, 34, "        / || \\              / || \\");
    mvaddstr (4, 34, "       /  ||  \\            /  ||  \\");
    mvaddstr (5, 34, "      /   ||   \\          /   ||   \\");
    mvaddstr (6, 34, "     /    ||    \\        /    ||    \\");
    mvaddstr (7, 34, "    /     ||     \\______/     ||     \\");
    mvaddstr (8, 34, "   /      ||                  ||      \\");
    mvaddstr (9, 34, "__/       ||                  ||       \\__");
    attrset (A_STANDOUT);
    mvaddstr (11, 1,  ":::::::::::::::...");
    mvaddstr (11, 59, "...:::::::::::::::::");
    attrset (A_NORMAL);
    attrset (A_REVERSE);
    mvaddstr (11, 19, "WELCOME TO THE VEHICLE DRIVING SIMULATOR");
    attrset (A_NORMAL);
    mvaddstr (13, 4,  "With the freeway under construction traffic has ");
    mvaddstr (13, 52, "reached critical mass.");
    mvprintw (14, 4,  "%s, what kind of vehicle would you like to drive?", user->pw_gecos);
    attrset (A_BOLD | A_BLINK);
    mvprintw (2,  6,  "Hi %s!", user->pw_name);
    attrset (A_NORMAL);
    attrset (A_BOLD);
    mvprintw (14, 4,  "%s", user->pw_gecos);
    mvaddstr (16, 23, "For a regular car, press..... C");
    mvaddstr (17, 23, "For a fast truck, press...... T");
    mvaddstr (18, 23, "For a slow bus, press........ B");
    mvaddstr (19, 23, "To quit simulator, press..... ESC");
    attrset (A_NORMAL);
    mvaddstr (22, 19, "Your vehicle will be illustrated in bold.");

    int distance = DEFAULT_DISTANCE, again = 1;

    while (again)
        switch (getch ())
        {
            case 'c':
            case 'C':
            case '\n':
                SelectDistance (argc, argv, distance);
                Simulator (new Car (distance), "Car", distance);
                again = 0;
                break;
            case 't':
            case 'T':
                SelectDistance (argc, argv, distance);
                Simulator (new Truck (distance), "Truck", distance);
                again = 0;
                break;
            case 'b':
            case 'B':
                SelectDistance (argc, argv, distance);
                Simulator (new Bus (distance), "Bus", distance);
                again = 0;
                break;
            case 033:
                clear ();
                refresh ();
                endwin ();
                exit (0);
            default:
                beep ();
                again = 1;
        }
}

void SelectDistance (int argc, char **argv, int& distance)
{
    if (argc >= 2)
        distance = abs (atoi (argv [1]));
    else
    {
        echo ();
        attrset (A_BOLD);
        mvaddstr (20, 23, "How far do you want to drive? ");
        scanw ("%i", &distance);
        distance = abs (distance);
        attrset (A_NORMAL);
        noecho ();
        refresh ();
    }
}

void Simulator (Vehicle *vehicle, char *type, int distance)
{
    srand (time (NULL));

    int clock = 0, obstacle = 0, at_destination = 0;

    InitScreen (distance, type);

    attrset (A_BOLD);

    while (! at_destination && distance > 0)
    {
        mvaddstr (17, 19, "Driving...                              ");
        Moving (vehicle, clock++, obstacle, distance, 0, "[]O>");
        at_destination = vehicle->Drive ();

        if ((rand () % 10) == 0 && ! at_destination)
        {
            Crashing (vehicle, clock++, obstacle++, distance, 1);
            mvaddstr (17, 19, "Backing up...                           ");
            vehicle->Reverse ();
            Moving (vehicle, clock++, obstacle, distance,  0, "<O[]");
            Moving (vehicle, clock++, obstacle, distance, -1, "<O[]");
            mvaddstr (17, 19, "Passing...                              ");
            Moving (vehicle, clock++, obstacle, distance, -1, "[]O>");
            vehicle->Reverse ();
            at_destination = vehicle->Pass ();
        }
    }

    mvaddstr (17, 19, "Turning off...                          ");
    Moving (vehicle, clock++, obstacle, distance, 0, "[]O>");

    attrset (A_NORMAL);
    refresh ();
}

void InitScreen (int distance, char *type)
{
    clear ();
    refresh ();

    attrset (A_REVERSE);
    mvaddstr (1, 10,
              "LIFE IN THE FAST LANE. THE VEHICLE SIMULATOR BY NAM NGUYEN");
    attrset (A_NORMAL);
    mvaddstr (3,  36, "|   :   |");
    mvaddstr (4,  36, "|   :   |");
    mvaddstr (5,  36, "|   :   |");
    mvaddstr (6,  36, "|   :   |");
    mvaddstr (7,  2,  "|------------------|---------------");
    mvaddstr (7,  44, "---------------|------------------|");
    mvaddstr (9,  3,  ".................................");
    mvaddstr (9,  45, ".................................");
    mvaddstr (11, 2,  "|------------------|---------------");
    mvaddstr (11, 44, "---------------|------------------|");
    mvaddstr (12, 36, "|   :   |");
    mvaddstr (13, 36, "|   :   |");
    mvaddstr (14, 36, "|   :   |");
    mvaddstr (15, 36, "|   :   |");
    mvaddstr (17, 10, "Status =");
    mvaddstr (18, 10, "Elapsed time =                Current time =");
    mvaddstr (19, 10, "Position =                    Destination =");
    mvaddstr (20, 10, "Remain =                      Number of obstacles =");
    mvaddstr (21, 10, "Type of vehicle =             Speed =");
    attrset (A_BOLD);
    mvaddstr (6,  2,  "Start");
    mvaddstr (6,  68, "Destination");
    mvaddstr (22, 10, "Press CTRL-C to exit.");
    mvprintw (19, 54, "%i units.", distance);
    mvprintw (21, 28, "%s.", type);
    attrset (A_NORMAL);
}

void Moving (Vehicle *vehicle, int clock, int obstacle, int distance, int col, char *shape)
{
    col += (distance == 0) ? 0 : int (80.0 / distance * vehicle->Position ());

    move (10, 0);
    clrtoeol ();
    attron (A_STANDOUT);

    if (col >= 76)
        mvaddstr (10, 76, shape);
    else if (col < 0)
        mvaddstr (10, 0, shape);
    else
        mvaddstr (10, col, shape);

    attroff (A_STANDOUT);

    Statistics (clock, vehicle->Position (), obstacle, distance);
}

void Crashing (Vehicle *vehicle, int clock, int obstacle, int distance, int col)
{
    col += int (80.0 / distance * vehicle->Position ());

    beep ();
    mvaddstr (17, 19, "Look out! There's something in the road!");

    if (col < 76)
    {
        mvaddstr (9,  col, "\\|/");
        mvaddstr (11, col, "/|\\");
    }
    else
    {
        mvaddstr (9,  76, "\\|/");
        mvaddstr (11, 76, "/|\\");
    }

    Statistics (clock, vehicle->Position (), obstacle, distance);
}

void Statistics (int clock, int position, int obstacle, int distance)
{
    time_t curtime = time (NULL);
    struct tm *loctime = localtime (&curtime);

    mvprintw (18, 25, "%i seconds.", clock);
    mvaddstr (18, 55, asctime (loctime));
    mvprintw (19, 21, "%i units.", position);
    mvprintw (20, 19, "%i units.   ", position - distance);
    mvprintw (20, 62, "%i.", obstacle);
    mvprintw (21, 48, "%f", (clock == 0) ? 0 : float (position) / clock);
    mvaddstr (21, 53, " units/second.");
    move (9, 78);
    refresh ();
    napms (1000);
}
