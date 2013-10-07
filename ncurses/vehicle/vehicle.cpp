// *************************************************************************
// FILE NAME: vehicle.cpp                                                  *
// CREATED  : 01/30/2002                                                   *
// UPDATED  : 02/19/2002                                                   *
// *************************************************************************

#include "vehicle.h"

Vehicle::Vehicle (int distance)
{
    position = 0;
    destination = distance;
    forward = 1;
}

int Vehicle::Drive (void)
{
    return ((++position == destination) ? 1 : 0);
}

void Vehicle::Reverse (void)
{
    if (forward)
    {
        position--;
        forward = 0;
    }
    else
        forward = 1;
}

int Vehicle::Position (void)
{
    return position;
}

int Vehicle::Pass (void)
{
    return ((++position >= destination) ? 1 : 0);
}
