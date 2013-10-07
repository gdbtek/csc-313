// *************************************************************************
// FILE NAME: vehicle.h                                                    *
// CREATED  : 01/30/2002                                                   *
// UPDATED  : 02/19/2002                                                   *
// *************************************************************************

#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle
{
    public:
        Vehicle (int);
        int Drive (void);
        void Reverse (void);
        int Position (void);
        virtual int Pass (void);

    protected:
        int position, destination, forward;
};

#endif
