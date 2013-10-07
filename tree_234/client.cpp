// *************************************************************************
// FILE NAME: client.cpp                                                   *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 03/14/2002                                                   *
// UPDATED  : 04/08/2002                                                   *
// *************************************************************************

#include "client.h"

Client::Client (void)
{
    _fName = _lName = _id = "\0";
    _balance = 0;
}

Client::Client (const string& fName, const string& lName, const string& id, double balance)
{
    SetFName (fName);
    SetLName (lName);
    SetId (id);
    SetBalance (balance);
}

string Client::GetFName (void) const
{
    return _fName;
}

void Client::SetFName (const string& fName)
{
    _fName = fName;

    /*
    transform (_fName.begin (), _fName.end (), _fName.begin (), tolower);
    _fName.at (0) = toupper (_fName.at (0));

    for (unsigned i = 0; i < _fName.length (); i++)
        if (_fName.at (i) == '-')
            _fName.at (++i) = toupper (_fName.at (i));
    */
}

string Client::GetLName (void) const
{
    return _lName;
}

void Client::SetLName (const string& lName)
{
    _lName = lName;

    /*
    transform (_lName.begin (), _lName.end (), _lName.begin (), tolower);
    _lName.at (0) = toupper (_lName.at (0));

    for (unsigned i = 0; i < _lName.length (); i++)
        if (_lName.at (i) == '-')
            _lName.at (++i) = toupper (_lName.at (i));
    */
}

string Client::GetId (void) const
{
    return _id;
}

void Client::SetId (const string& id)
{
    _id = id;
}

double Client::GetBalance (void) const
{
    return _balance;
}

void Client::SetBalance (double balance)
{
    _balance = balance;
}

void Client::Deposit (double deposit)
{
    _balance += deposit;
}

void Client::Withdraw (double withdraw)
{
    _balance -= withdraw;
}

Client& Client::operator = (const Client& client)
{
    _fName   = client._fName;
    _lName   = client._lName;
    _id      = client._id;
    _balance = client._balance;

    return *this;
}

istream& operator >> (istream& ins, Client& client)
{
    ins >> client._fName >> client._lName >> client._id >> client._balance;

    return ins;
}

ostream& operator << (ostream& outs, const Client& client)
{
    outs << "\033[1;32m" << client._fName << "\033[0m "
         << "\033[1;32m" << client._lName << "\033[0m "
         << "\033[1;35m" << client._id  << "\033[0m "
         << setprecision (2) << setiosflags (ios::showpoint | ios::fixed)
         << "\033[1;34m$" << client._balance << "\033[0m";

    return outs;
}

int operator == (const Client& c1, const Client& c2)
{
    return ((c1._fName == c2._fName) && (c1._lName == c2._lName));
}

int operator != (const Client& c1, const Client& c2)
{
    return (! (c1 == c2));
}

int operator > (const Client& c1, const Client& c2)
{
    if (c1._fName > c2._fName)
        return 1;

    if (c1._fName < c2._fName)
        return 0;

    if (c1._lName > c2._lName)
        return 1;

    return 0;
}

int operator >= (const Client& c1, const Client& c2)
{
    if (c1._fName > c2._fName)
        return 1;

    if (c1._fName < c2._fName)
        return 0;

    if (c1._lName >= c2._lName)
        return 1;

    return 0;
}

int operator < (const Client& c1, const Client& c2)
{
    if (c1._fName < c2._fName)
        return 1;

    if (c1._fName > c2._fName)
        return 0;

    if (c1._lName < c2._lName)
        return 1;

    return 0;
}

int operator <= (const Client& c1, const Client& c2)
{
    if (c1._fName < c2._fName)
        return 1;

    if (c1._fName > c2._fName)
        return 0;

    if (c1._lName <= c2._lName)
        return 1;

    return 0;
}
