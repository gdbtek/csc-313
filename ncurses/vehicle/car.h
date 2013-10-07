// *************************************************************************
// FILE NAME: car.h                                                        *
// CREATED  : 01/30/2002                                                   *
// UPDATED  : 02/19/2002                                                   *
// *************************************************************************

#ifndef CAR_H
#define CAR_H

#include "vehicle.h"

class Car : public Vehicle
{
    public:
        Car (int);
        virtual int Pass (void);
};

#endif
