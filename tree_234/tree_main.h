// *************************************************************************
// FILE NAME: tree_main.h                                                  *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 03/14/2002                                                   *
// UPDATED  : 04/08/2002                                                   *
// *************************************************************************

#ifndef TREE_MAIN_H
#define TREE_MAIN_H

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <pwd.h>
#include "client.h"
#include "tree_234.h"

using namespace std;

char *INS  = "data/data.txt";
char *OUTS = "data/save.txt";

Tree_234<Client> tree_234;

void User (void);
void Menu (void);
char Choice (void);

void Open (void);
void Erase (void);

void Insert (void);
void Delete (void);

void Find (void);
void Change (void);

void Print (void);
void Save (void);

void Preorder (void);
void Inorder (void);
void Postorder (void);
void LevelByLevel (void);

void GetName (Client&);
void GetId (Client&, char *);
void GetMoney (Client&, char *, int);

bool IsValidName (const string&);
bool IsValidId (const string&);
bool IsValidMoney (const string&);

void Title (char *);
void Continue (void);

#endif
