#include "main.h"
#include "odometry.h"

void startToRoller(driveInfo karlDrive){ //needs tuning
    moveDistance(karlDrive.distToTicks(2),0.01,0,5000);
}

void rollerToStart(driveInfo karlDrive){//same tuning as "startToRoller"
    moveDistance(karlDrive.distToTicks(-2),0,0,500);
}

void startToShootingSpot(driveInfo karlDrive){//needs tuning
    moveDistance(karlDrive.distToTicks(57.1),0,0,2000);
}

void turn90DegRight(driveInfo karlDrive){//needs tuning
    turnDistance(karlDrive.distToTicks(karlDrive.degToDist(90)),0,0,2000);
}

void turn45DegRight(driveInfo karlDrive){//needs tuning
    turnDistance(karlDrive.distToTicks(karlDrive.degToDist(45)),0,0,2000);
}

void turn90DegLeft(driveInfo karlDrive){//same tuning as "turn90DegRight"
    turnDistance(karlDrive.distToTicks(karlDrive.degToDist(-90)),0,0,2000);
}

void turn45DegLeft(driveInfo karlDrive){//same tuning as "turn45DegRight"
    turnDistance(karlDrive.distToTicks(karlDrive.degToDist(-45)),0,0,2000);
}

void rollerOnly(driveInfo karlDrive){
    moveDistance(karlDrive.distToTicks(2), driveKP, driveKD, 700);
    Floppy.move_velocity(-50);
    pros::delay(700);
    Floppy.move_velocity(0);
    moveDistance(karlDrive.distToTicks(-4), driveKP, driveKD, 700);
}
//haha funni
void rollerPreloadLeft(driveInfo karlDrive){
    rollerOnly(karlDrive);
    turn45DegRight(karlDrive);
    startToShootingSpot(karlDrive);
    turn90DegLeft(karlDrive);
    Flywheel.move_velocity(600);
    pros::delay(500);
    for(int i = 0; i < 3; i++){
		diskIndexer.set_value(true);
		pros::delay(100);
		diskIndexer.set_value(false);
        pros::delay(200);
    }
    Flywheel.move_velocity(0);
}

void rollerPreloadRight(driveInfo karlDrive){
    
    rollerOnly(karlDrive);
    turn45DegLeft(karlDrive);
    startToShootingSpot(karlDrive);
    turn90DegRight(karlDrive);
    Flywheel.move_velocity(600);
    pros::delay(500);
    for(int i = 0; i < 3; i++){
		diskIndexer.set_value(true);
		pros::delay(100);
		diskIndexer.set_value(false);
        pros::delay(200);
    }
    Flywheel.move_velocity(0);
}