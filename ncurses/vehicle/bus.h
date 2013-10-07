// *************************************************************************
// FILE NAME: bus.h                                                        *
// CREATED  : 01/30/2002                                                   *
// UPDATED  : 02/19/2002                                                   *
// *************************************************************************

#ifndef BUS_H
#define BUS_H

#include "truck.h"

class Bus : public Truck
{
    public:
        Bus (int);
        virtual int Pass (void);
};

#endif
