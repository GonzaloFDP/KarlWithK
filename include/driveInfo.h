#include "main.h"
#include "functions.h"

class driveInfo{
    public:
        driveInfo() = default;

        driveInfo(double wheelD, double wheelDist){
            wheelDia = wheelD;
            wheelCirc = wheelD*M_PI;
            Left2Cent = wheelDist/2;
            Right2Cent = wheelDist/2;
        }

        double wheelDia;
        double wheelCirc;
        double gearR = 7.0/5;
        double Left2Cent;
        double Right2Cent;
        double Back2Cent;
        double ticksInRev = 900;


        double distToTicks(double dist){
            double ticks = dist;
            ticks /= wheelCirc;
            ticks *= ticksInRev;
            ticks /= gearR;
            return ticks;
        }


};
