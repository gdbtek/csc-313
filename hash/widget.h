// *************************************************************************
// FILE NAME: widget.h                                                     *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 05/01/2002                                                   *
// UPDATED  : 05/15/2002                                                   *
// *************************************************************************

#ifndef WIDGET_H
#define WIDGET_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Widget
{
    public:
        Widget (const string&, const string&, int, int);

        string GetKey (void) const;

        string GetDescription (void) const;
        void SetDescription (const string&);

        int GetReorder (void) const;
        void SetReorder (int);

        int GetInventory (void) const;
        void SetInventory (int);

        friend ostream& operator << (ostream&, const Widget&);
        friend fstream& operator << (fstream&, const Widget&);

    private:
        string _key, _des;
        int _reo, _inv;
};

#endif
