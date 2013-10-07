// *************************************************************************
// FILE NAME: hash.cpp                                                     *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 05/01/2002                                                   *
// UPDATED  : 05/15/2002                                                   *
// *************************************************************************

#include "hash.h"

Hash::Hash (void)
{
    _size = 0;
    _hash = NULL;
}

Hash::~Hash (void)
{
    Erase ();
}

bool Hash::SetSize (int size)
{
    if (size < 1 || size > MAX)
        return false;

    _size = size;
    _hash = new map<const string, Widget> *[_size];

    cout << "\n\033[1;32mInitializing Hash-Table size " << _size << "...\033[0m" << flush;

    for (int i = 0; i < _size; i++)
        _hash [i] = new map<const string, Widget>;

    return true;
}

int Hash::GetSize (void) const
{
    return _size;
}

bool Hash::Open (const char *file) const
{
    fstream ins (file, ios::in);

    if (ins.bad ())
        return false;

    string key, des;
    int reo, inv, size;

    ins >> size;

    cout << "\n\033[1;32mInserting " << size << " records...\033[0m" << flush;

    time_t start = clock ();

    for (int i = 0; i < size && ! ins.eof (); i++)
    {
        ins >> key >> des >> reo >> inv;
        Insert (key, des, reo, inv);
    }

    cout << "\n\n\033[1;31mInserted in " << ((double (clock ()) - start) / CLOCKS_PER_SEC) << " second(s)\033[0m";

    ins.close ();

    return true;
}

bool Hash::Save (const char *file) const
{
    fstream outs (file, ios::out);

    if (outs.bad ())
        return false;

    cout << "\033[1;32mSaving...\033[0m" << flush;

    if (! IsEmpty ())
        outs << _size << "\n";

    time_t start = clock ();

    for (int i = 0 ; i < _size; i++)
        for (map<const string, Widget>::iterator cur = _hash [i]->begin (); cur != _hash [i]->end (); cur++)
            outs << cur->second;

    cout << "\n\n\033[1;31mSaved in " << ((double (clock ()) - start) / CLOCKS_PER_SEC) << " second(s)\033[0m";

    outs.close ();

    return true;
}

bool Hash::Erase (void)
{
    if (! _size)
        return false;

    cout << "\033[1;32mErasing records...\033[0m" << flush;

    time_t start = clock ();

    for (int i = 0; i < _size; i++)
        _hash [i]->clear ();

    _size = 0;
    delete [] _hash;

    cout << "\n\n\033[1;31mErased in " << ((double (clock ()) - start) / CLOCKS_PER_SEC) << " second(s)\033[0m\n\n";

    return true;
}

bool Hash::Insert (const string& key, const string& des, int reo, int inv) const
{
    Widget widget (key, des, reo, inv);

    return (_hash [_Index (key)]->insert (make_pair (key, widget)).second);
}

bool Hash::Delete (const string& key) const
{
    int i = _Index (key);

    map<const string, Widget>::iterator cur = _hash [i]->find (key);

    if (cur == _hash [i]->end ())
        return false;

    _hash [i]->erase (cur);

    return true;
}

Widget Hash::Retrieve (const string& key) const
{
    return (_hash [_Index (key)]->find (key)->second);
}

bool Hash::Print (void) const
{
    if (IsEmpty ())
        return false;

    int count = 0;

    for (int i = 0 ; i < ((_size <= 100) ? _size : 100); i++)
    {
        count = 0;

        cout << "\033[1;31m" << i << "\033[0m";

        if (! _hash [i]->empty ())
            for (map<const string, Widget>::iterator cur = _hash [i]->begin (); cur != _hash [i]->end (); cur++)
            {
                if (count++ >= 9)
                    break;

                cout << "->\033[1;32m" << cur->second.GetKey () << "\033[0m";
            }
        else
            cerr << "->\033[1;33mEmpty\033[0m";

        cout << "\n\t\033[1;34mBucket:\033[0m " << "\033[1;35m" << _hash [i]->size () << "\033[0m\n";
    }

    return true;
}

bool Hash::ChangeKey (const string& old_key, const string& new_key) const
{
    int i = _Index (old_key);

    map<const string, Widget>::iterator cur = _hash [i]->find (old_key);

    if (cur == _hash [i]->end () ||
        ! Insert (new_key, cur->second.GetDescription (), cur->second.GetReorder (), cur->second.GetInventory ()))
        return false;

    _hash [i]->erase (cur);

    return true;
}

bool Hash::ChangeDescription (const string& key, const string& des) const
{
    int i = _Index (key);

    map<const string, Widget>::iterator cur = _hash [i]->find (key);

    if (cur == _hash [i]->end ())
        return false;

    cur->second.SetDescription (des);

    return true;
}

bool Hash::ChangeReorder (const string& key, int reo) const
{
    int i = _Index (key);

    map<const string, Widget>::iterator cur = _hash [i]->find (key);

    if (cur == _hash [i]->end ())
        return false;

    cur->second.SetReorder (reo);

    return true;
}

bool Hash::ChangeInventory (const string& key, int inv) const
{
    int i = _Index (key);

    map<const string, Widget>::iterator cur = _hash [i]->find (key);

    if (cur == _hash [i]->end ())
        return false;

    cur->second.SetInventory (inv);

    return true;
}

int Hash::IsMember (const string& key) const
{
    int i = _Index (key), probe = 1;

    for (map<const string, Widget>::iterator cur = _hash [i]->begin (); cur != _hash [i]->end (); cur++, probe++)
        if (cur->first == key)
        {
            cout << "\n\033[1;31mFound at index " << i << "\033[0m\n";

            return probe;
        }

    cout << "\n\033[1;31mNot found in " << probe << ((probe > 1) ? " probes" : " probe") << "\033[0m\n";

    return 0;
}

bool Hash::IsEmpty (void) const
{
    for (int i = 0; i < _size; i++)
        if (! _hash [i]->empty ())
            return false;

    return true;
}

int Hash::_Index (const string& key) const
{
    int sum = 0;

    for (unsigned i = 1; i < key.length () - 1; i++)
        sum = sum * 10 + key [i] - '0';

    return (abs ((key [0] + sum + key [key.length () - 1]) % _size));
}
