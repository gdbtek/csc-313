// *************************************************************************
// FILE NAME: hash_main.h                                                  *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 05/01/2002                                                   *
// UPDATED  : 05/15/2002                                                   *
// *************************************************************************

#ifndef HASH_MAIN_H
#define HASH_MAIN_H

#include <unistd.h>
#include <iostream>
#include <ctype.h>
#include <pwd.h>
#include "hash.h"

using namespace std;

string INS  = "data/";
string OUTS = "data/save.txt";

Hash hash;

void User (void);
void Input (void);
void Menu (void);
char Choice (void);

void GetSize (void);
void Open (void);
void Insert (void);

void Delete (void);

void IsMember (void);
void Retrieve (void);

void Print (void);
void Erase (void);

void ChangeKey (void);
void ChangeDescription (void);
void ChangeReorder (void);
void ChangeInventory (void);

void Save (void);

void GetKey (string&, const string&);
void GetDescription (string&);
void GetReorder (int&);
void GetInventory (int&);

bool IsValidNumber (const string&);

void Title (char *);
void Continue (void);

#endif
