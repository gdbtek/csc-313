// *************************************************************************
// FILE NAME: color.cpp                                                    *
// BY       : Nam Nguyen                                                   *
// CREATED  : 05/15/2002                                                   *
// UPDATED  : 05/23/2002                                                   *
// COMPILE  : g++ -Wall -o color color.cpp                                 *
// PURPOSE  : Display all possible colors under a Unix/Linux terminal      *
//            emulators.                                                   *
// *************************************************************************

#include <iostream>
#include <iomanip>

using namespace std;

int main (void)
{
    char *fg [16] = { "30m", "1;30m", "31m", "1;31m", "32m", "1;32m", "33m", "1;33m", "34m", "1;34m", "35m", "1;35m",
                      "36m", "1;36m", "37m", "1;37m" };

    char *bg [8]  = { "40m", "41m", "42m", "43m", "44m", "45m", "46m", "47m" };

    cout << "\n   ";

    for (int i = 0; i < 8; i++)
        cout << setw (9) << bg [i];

    cout << "\n";

    for (int i = 0; i < 16; i++)
    {
        cout << setw (6) << fg [i];

        for (int j = 0; j < 8; j++)
            cout << " \033[" << fg [i] << "\033[" << bg [j] << ((fg [i][0] != '1') ? " Normal " : "  Bold  ") << "\033[0m";

        cout << "\n";
    }

    cout << "\n"
         << setw (6)  << "1m" << setw (15) << "\033[1mBold\033[0m"
         << setw (8)  << "4m" << setw (20) << "\033[4mUnderscore\033[0m"
         << setw (7)  << "7m" << setw (19) << "\033[7mInverse\033[0m\n"
         << setw (6)  << "2m" << setw (16) << "\033[2mItalic\033[0m"
         << setw (7)  << "5m" << setw (17) << "\033[5mBlink\033[0m"
         << setw (10) << "8m" << setw (21) << "\033[8mInvisible\033[0m\n\n";

    return 0;
}
