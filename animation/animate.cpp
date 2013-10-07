// *************************************************************************
// FILE NAME: animation.cpp                                                *
// BY       : Nam Nguyen                                                   *
// CREATED  : 05/15/2002                                                   *
// UPDATED  : 05/23/2002                                                   *
// COMPILE  : g++ -Wall -o animation animation.cpp                         *
// PURPOSE  : Text animation without using ncurses library.                *
// *************************************************************************

#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace std;

void LeftToRight (const char *);
void RightToLeft (const char *);

int main (void)
{
    LeftToRight ("ncurses using without right to left from text Moving");
    RightToLeft ("Moving text from right to left without using ncurses");

    return 0;
}

void LeftToRight (const char *msg)
{
    cout << "\n";

    for (int i = strlen (msg) - 1; i >= 0; i--)
    {
        usleep (200000);

        cout << &msg [i] << flush;

        for (unsigned j = strlen (msg) - i; j > 0; j--)
            cout << "\b";
    }
}

void RightToLeft (const char *msg)
{
    cout << setw (strlen (msg)) << " ";

    for (unsigned i = 0; i < strlen (msg); i++)
    {
        usleep (200000);

        for (unsigned j = 0; j <= i; j++)
            cout << "\b";

        for (unsigned j = 0; j <= i; j++)
            cout << msg [j];

        cout << flush;
    }

    cout << "\n\n";
}
