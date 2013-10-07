// *************************************************************************
// FILE NAME: graph_main.h                                                 *
// BY       : Nam Nguyen      <gdbtek@yahoo.com>     <www.gdbtek.com>      *
// CREATED  : 04/10/2002                                                   *
// UPDATED  : 05/01/2002                                                   *
// *************************************************************************

#ifndef GRAPH_MAIN_H
#define GRAPH_MAIN_H

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <pwd.h>
#include "graph.h"

char *INS  = "data/data.txt";
char *OUTS = "data/save.txt";

Graph graph;

void User (void);
void Input (void);
void Menu (void);
char Choice (void);

void OpenFile (void);
void OpenInteractive (void);

void InsertVertex (void);
void InsertEdge (void);

void DeleteVertex (void);
void DeleteEdge (void);
void DeleteGraph (void);

void Print (void);
void PrintBFS (void);
void PrintDFS (void);

void SaveFile (void);

void CheapestPath (void);
void CheapestTable (void);

void MinSpanTree (void);

void GetOrigin (string&);
void GetDestination (string&);
void GetCost (double&);

bool IsValidMoney (const string&);

void Title (char *title);
void Continue (void);

#endif
