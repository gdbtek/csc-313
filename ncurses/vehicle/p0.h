// *************************************************************************
// FILE NAME: p0.h                                                         *
// BY       : Nam Nguyen    <breakins@sfsu.edu>    <www.breakins.cjb.net>  *
// CREATED  : 01/30/2002                                                   *
// UPDATED  : 02/24/2002                                                   *
// CLASS    : CSC 313                                                      *
// SECTION  : 01                                                           *
// PURPOSE  : A simulation of the operation of three kinds of traffic      *
//            vehicles.                                                    *
// *************************************************************************

#ifndef P0_H
#define P0_H

#include <ncurses.h>
#include <cstdlib>
#include <pwd.h>
#include "car.h"
#include "bus.h"

#define DEFAULT_DISTANCE 40

void Welcome (void);
void Selection (int, char **);
void SelectDistance (int, char **, int&);
void Simulator (Vehicle *, char *, int);
void InitScreen (int, char *);
void Moving (Vehicle *, int, int, int, int, char *);
void Crashing (Vehicle *, int, int, int, int);
void Statistics (int, int, int, int);

#endif
