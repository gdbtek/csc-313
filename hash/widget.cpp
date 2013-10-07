// *************************************************************************
// FILE NAME: widget.cpp                                                   *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 05/01/2002                                                   *
// UPDATED  : 05/15/2002                                                   *
// *************************************************************************

#include "widget.h"

Widget::Widget (const string& key, const string& des, int reo, int inv)
{
    _key = key;
    _des = des;
    _reo = reo;
    _inv = inv;
}

string Widget::GetKey (void) const
{
    return _key;
}

string Widget::GetDescription (void) const
{
    return _des;
}

void Widget::SetDescription (const string& des)
{
    _des = des;
}

int Widget::GetReorder (void) const
{
    return _reo;
}

void Widget::SetReorder (int reo)
{
    _reo = reo;
}

int Widget::GetInventory (void) const
{
    return _inv;
}

void Widget::SetInventory (int inv)
{
    _inv = inv;
}

ostream& operator << (ostream& outs, const Widget& widget)
{
    outs << "\033[1;32mKey:\033[0m " << widget._key << "\n" << "\033[1;35mDescription:\033[0m " << widget._des << "\n"
         << "\033[1;34mReorder:\033[0m " << widget._reo << "\n" << "\033[1;33mInventory:\033[0m " << widget._inv << "\n";

    return outs;
}

fstream& operator << (fstream& outs, const Widget& widget)
{
    outs << widget._key << "\n" << widget._des << "\n" << widget._reo << "\n" << widget._inv << "\n";

    return outs;
}
