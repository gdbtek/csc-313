// *************************************************************************
// FILE NAME: car.cpp                                                      *
// CREATED  : 01/30/2002                                                   *
// UPDATED  : 02/19/2002                                                   *
// *************************************************************************

#include "car.h"

Car::Car (int distance) : Vehicle (distance)
{
    // Empty
}

int Car::Pass (void)
{
    return ((position >= destination) ? 1 : 0);
}
