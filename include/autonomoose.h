#include "main.h"
#include "odometry.h"

void rollerOnlyLeft(driveInfo karlDrive){
    moveDistance(karlDrive.distToTicks(2), karlDrive.driveKP, karlDrive.driveKD, 700);
    Floppy.move_velocity(-50);
    pros::delay(700);
    Floppy.move_velocity(0);
    moveDistance(karlDrive.distToTicks(-6), karlDrive.driveKP, karlDrive.driveKD, 700);
    brake();
}

void rollerOnlyRight(driveInfo karlDrive){
    moveDistance(karlDrive.distToTicks(24), karlDrive.driveKP, karlDrive.driveKD, 3000);
    brake();
    turnDistance(karlDrive.degToTicks(90),karlDrive.turningKP, karlDrive.turningKD, 1500);
    moveDistance(karlDrive.distToTicks(5),karlDrive.driveKP,karlDrive.driveKD, 1500);
    brake();
    Floppy.move_velocity(-50);
    pros::delay(700);
    Floppy.move_velocity(0);
    moveDistance(karlDrive.distToTicks(-2), karlDrive.driveKP, karlDrive.driveKD, 2000);
    brake();
    turnDistance(karlDrive.degToTicks(-90), karlDrive.turningKP, karlDrive.turningKD,2000);
}

//haha funni
void rollerPreloadLeft(driveInfo karlDrive){
    rollerOnlyLeft(karlDrive);
    turnDistance(karlDrive.degToTicks(39), karlDrive.turningKP, karlDrive.turningKD, 1000);
    moveDistance(karlDrive.distToTicks(-53), karlDrive.driveKP, karlDrive.driveKD, 2000);
    turnDistance(karlDrive.degToTicks(-83), karlDrive.turningKP, karlDrive.turningKD, 1500);
    moveDistance(karlDrive.distToTicks(-2), karlDrive.driveKP, karlDrive.driveKD, 2000);
    brake();
    Flywheel.move_velocity(600);
    pros::delay(6000);
    for(int i = 0; i < 3; i++){
		diskIndexer.set_value(true);
		pros::delay(100);
		diskIndexer.set_value(false);
        pros::delay(500);
    }
    Flywheel.move_velocity(0);
}

void rollerPreloadRight(driveInfo karlDrive){
    rollerOnlyRight(karlDrive);
    turnDistance(karlDrive.degToTicks(-39), karlDrive.turningKP, karlDrive.turningKD, 1000);
    moveDistance(karlDrive.distToTicks(-53), karlDrive.driveKP, karlDrive.driveKD, 2000);
    turnDistance(karlDrive.degToTicks(80), karlDrive.turningKP, karlDrive.turningKD, 1500);
    moveDistance(karlDrive.distToTicks(-2), karlDrive.driveKP, karlDrive.driveKD, 1000);
    brake();
    Flywheel.move_velocity(600);
    pros::delay(6000);
    for(int i = 0; i < 3; i++){
		diskIndexer.set_value(true);
		pros::delay(100);
		diskIndexer.set_value(false);
        pros::delay(500);
    }
    Flywheel.move_velocity(0);
}

void rollerPreloadLOWRight(driveInfo karlDrive){
    rollerOnlyRight(karlDrive);
    brake();
    Flywheel.move_velocity(400);
    pros::delay(1500);
    for(int i = 0; i < 2; i++){
		diskIndexer.set_value(true);
		pros::delay(100);
		diskIndexer.set_value(false);
        pros::delay(600);
    }
    Flywheel.move_velocity(0);
}

void rollerPreloadLOWLeft(driveInfo karlDrive){
    rollerOnlyLeft(karlDrive);
    turnDistance(karlDrive.degToTicks(90), karlDrive.turningKP, karlDrive.turningKD, 1800);
    brake();
    Flywheel.move_velocity(600);
    pros::delay(1500);
    for(int i = 0; i < 2; i++){
		diskIndexer.set_value(true);
		pros::delay(100);
		diskIndexer.set_value(false);
        pros::delay(600);
    }
    Flywheel.move_velocity(0);
}



void progSkills(driveInfo karlDrive){
    rollerOnlyLeft(karlDrive);
    turnDistance(karlDrive.degToTicks(45),karlDrive.turningKP, karlDrive.turningKD, 1000);
    brake();
    moveDistance(karlDrive.distToTicks(-20),karlDrive.turningKP, karlDrive.turningKD, 3000);
    brake();
    pros::delay(1000);
    expansion.set_value(true);
}