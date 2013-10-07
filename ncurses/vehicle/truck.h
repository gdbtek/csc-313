// *************************************************************************
// FILE NAME: truck.h                                                      *
// CREATED  : 01/30/2002                                                   *
// UPDATED  : 02/19/2002                                                   *
// *************************************************************************

#ifndef TRUCK_H
#define TRUCK_H

#include "vehicle.h"

class Truck : public Vehicle
{
    public:
        Truck (int);
        virtual int Pass (void);
};

#endif
