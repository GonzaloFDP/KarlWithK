#include "main.h"
#include "driveInfo.h"

class karlOdom {
    driveInfo karling;
    public:
        karlOdom(driveInfo driveT){
            karlDrive = driveT;
            gPos.first = 0;
            gPos.second = 0;
        }
        std::pair<double,double> gPos;
        double gDir = 0;
        double prevLeft = 0;
        double prevRight = 0;

        void movement(double leftPos, double rightPos){
            //1 rev = 900 ticks
            leftDelta = ((leftPos-prevLeft)/karlDrive.ticksPerRev)*karlDrive.wheelCirc*karlDrive.gearR;
            rightDelta = ((rightPos-prevRight)/karlDrive.ticksPerRev)*karlDrive.wheelCirc*karlDrive.gearR;
            prevLeft = leftDelta;
            prevRight = rightDelta;
        }
};