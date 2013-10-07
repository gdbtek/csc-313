// *************************************************************************
// FILE NAME: client.h                                                     *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 03/14/2002                                                   *
// UPDATED  : 04/08/2002                                                   *
// *************************************************************************

#ifndef CLIENT_H
#define CLIENT_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Client
{
    public:
        Client (void);
        Client (const string&, const string&, const string&, double);

        string GetFName (void) const;
        void SetFName (const string&);

        string GetLName (void) const;
        void SetLName (const string&);

        string GetId (void) const;
        void SetId (const string&);

        double GetBalance (void) const;
        void SetBalance (double);

        void Deposit (double);
        void Withdraw (double);

        Client& operator = (const Client&);

        friend istream& operator >> (istream&, Client&);
        friend ostream& operator << (ostream&, const Client&);

        friend int operator == (const Client&, const Client&);
        friend int operator != (const Client&, const Client&);
        friend int operator >  (const Client&, const Client&);
        friend int operator >= (const Client&, const Client&);
        friend int operator <  (const Client&, const Client&);
        friend int operator <= (const Client&, const Client&);

    private:
        string _fName, _lName, _id;
        double _balance;
};

#endif
