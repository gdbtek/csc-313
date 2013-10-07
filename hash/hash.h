// *************************************************************************
// FILE NAME: hash.h                                                       *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 05/01/2002                                                   *
// UPDATED  : 05/15/2002                                                   *
// *************************************************************************

#ifndef HASH_H
#define HASH_H

#include <fstream>
#include <string>
#include <time.h>
#include <map>
#include "widget.h"

using namespace std;

#define MAX 1000001

class Hash
{
    public:
        Hash (void);
        ~Hash (void);

        bool SetSize (int);
        int  GetSize (void) const;

        bool Open (const char *) const;
        bool Save (const char *) const;
        bool Erase (void);

        bool Insert (const string&, const string&, int, int) const;
        bool Delete (const string&) const;

        Widget Retrieve (const string&) const;
        bool Print (void) const;

        bool ChangeKey (const string&, const string&) const;
        bool ChangeDescription (const string&, const string&) const;
        bool ChangeReorder (const string&, int) const;
        bool ChangeInventory (const string&, int) const;

        int  IsMember (const string&) const ;
        bool IsEmpty (void) const;

    protected:
        int _Index (const string&) const;

    private:
        int _size;
        map<const string, Widget> **_hash;
};

#endif
