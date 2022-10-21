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


        //Relates the distance you want the robot to move to the AMOUNT OF ENCODER TICKS THE MOTOR NEEDS TO TURN
        double distToTicks(double dist){
            double ticks = dist;
            ticks /= wheelCirc;
            ticks *= ticksInRev;
            ticks /= gearR;
            return ticks;
        }

        //Returns ticks to move in order to reach a certain direction
        double degToDist(double degrees){
            double angleRatio = degrees/360; //ratio of the degrees to turn -> degrees in a circle (360)
            double dist = wheelCirc * angleRatio; //inches needed to turn to a certain orientation (clockwise);
            double ticks = distToTicks(dist);
            return ticks;
            
        }


};
