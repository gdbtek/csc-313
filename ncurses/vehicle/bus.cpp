// *************************************************************************
// FILE NAME: bus.cpp                                                      *
// CREATED  : 01/30/2002                                                   *
// UPDATED  : 02/19/2002                                                   *
// *************************************************************************

#include "bus.h"

Bus::Bus (int distance) : Truck (distance)
{
    // Empty
}

int Bus::Pass (void)
{
    return ((--position >= destination) ? 1 : 0);
}
