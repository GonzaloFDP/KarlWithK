#include "main.h"
#include "driveInfo.h"

class karlOdom {
    driveInfo karlDrive;
    public:
        karlOdom(driveInfo driveT){
            karlDrive = driveT;
            gPos.first = 0;
            gPos.second = 0;
        }
        std::pair<double,double> gPos;

        double prevLeft = 0;
        double prevRight = 0;
        double leftDelta;
        double rightDelta;
        double totalLeft = 0;
        double totalRight = 0;

        double startOrientation = 0;
        double prevOrient = startOrientation;
        double orientation;
        double deltaOrient;
        double offset;
        double yOffset;
        double xOffset;

        void movement(double leftPos, double rightPos){
            std::pair<double,double> localOff;
            //1 rev = 900 ticks

            //find how much the wheels have move since the last time movement was checked
            leftDelta = ((leftPos-prevLeft)/karlDrive.ticksInRev)*karlDrive.wheelCirc*karlDrive.gearR;
            rightDelta = ((rightPos-prevRight)/karlDrive.ticksInRev)*karlDrive.wheelCirc*karlDrive.gearR;
            totalLeft += leftDelta;
            totalRight += rightDelta;
            prevLeft = leftDelta;
            prevRight = rightDelta;

            //find the orientation of the robot (in radians)
            orientation = startOrientation + ((totalLeft-totalRight)/(karlDrive.Left2Cent+karlDrive.Right2Cent));
            deltaOrient = orientation-prevOrient;
            prevOrient = orientation;

            if(deltaOrient == 0){
                localOff.first = 0;
                localOff.second = rightDelta;
            } else {
              offset = 2 * (sin(deltaOrient/2.0));
              yOffset = offset * ((rightDelta/deltaOrient)+karlDrive.Right2Cent);
              xOffset = offset; //* front/back distance from center of robot to tracking wheel
              localOff.first += xOffset;
              localOff.second += yOffset;
            }
            gPos.first += localOff.first;
            gPos.second += localOff.second;
        }

        double getOrientDeg(){
            return radToDeg(orientation);
        }
};
