// *************************************************************************
// FILE NAME: truck.cpp                                                    *
// CREATED  : 01/30/2002                                                   *
// UPDATED  : 02/19/2002                                                   *
// *************************************************************************

#include "truck.h"

Truck::Truck (int distance) : Vehicle (distance)
{
    // Empty
}

int Truck::Pass (void)
{
    position += 3;

    return ((position >= destination) ? 1 : 0);
}
