#include "main.h"
#include "odometry.h"

void rollerOnlyLeft(driveInfo karlDrive){
    moveDistance(karlDrive.distToTicks(2), karlDrive.driveKP, karlDrive.driveKD, 700);
    Intake.move_velocity(-50);
    pros::delay(700);
    Intake.move_velocity(0);
    moveDistance(karlDrive.distToTicks(-6), karlDrive.driveKP, karlDrive.driveKD, 700);
    brake();
}

void rollerOnlyRight(driveInfo karlDrive){
    moveDistance(karlDrive.distToTicks(24), karlDrive.driveKP, karlDrive.driveKD, 1400);
    brake();
    turnDistance(karlDrive.degToTicks(-86),karlDrive.turningKP, karlDrive.turningKD, 1000);
    moveDistance(karlDrive.distToTicks(8),karlDrive.driveKP,karlDrive.driveKD, 1500);
    brake();
    Intake.move_velocity(-50);
    pros::delay(700);
    Intake.move_velocity(0);
    moveDistance(karlDrive.distToTicks(-3), karlDrive.driveKP, karlDrive.driveKD, 700);
    brake();
    turnDistance(karlDrive.degToTicks(-104), karlDrive.turningKP, karlDrive.turningKD,1400);
}

//haha funni
void rollerPreloadLeft(driveInfo karlDrive){
    rollerOnlyLeft(karlDrive);
    Flywheel.move_velocity(-500);
    Flywheel_Two.move_velocity(-500);
    turnDistance(karlDrive.degToTicks(-74), karlDrive.turningKP, karlDrive.turningKD, 2200);  
    brake();
    for(int i = 0; i < 2; i++){
		diskIndexer.set_value(true);
		pros::delay(100);
		diskIndexer.set_value(false);
        pros::delay(500);
    }
    Flywheel.move_velocity(0);
    Flywheel_Two.move_velocity(0);
}

void rollerShootRight(driveInfo karlDrive){
    rollerOnlyRight(karlDrive);
    
    //moveDistance(karlDrive.distToTicks(7), karlDrive.driveKP, karlDrive.driveKD, 2000);
    //turnDistance(karlDrive.degToTicks(-70), karlDrive.turningKP, karlDrive.turningKD, 1500);
    Floppy.move_velocity(180);
    Intake.move_velocity(180);
    moveDistance(karlDrive.distToTicks(45), karlDrive.driveKP/1.5, karlDrive.driveKD, 2400);
    Floppy.move_velocity(0);
    Intake.move_velocity(0);
    Flywheel.move_velocity(-600);
    Flywheel_Two.move_velocity(-600);
    brake();
    turnDistance(karlDrive.degToTicks(85), karlDrive.turningKP, karlDrive.turningKD, 1700);
    moveDistance(karlDrive.distToTicks(-9), karlDrive.driveKP, karlDrive.driveKD, 1000);
    brake();
    for(int i = 0; i < 3; i++){
		diskIndexer.set_value(true);
		pros::delay(100);
		diskIndexer.set_value(false);
        pros::delay(500);
    }
    Flywheel.move_velocity(0);
    Flywheel_Two.move_velocity(0);
}

void rollerDiscRight(driveInfo karlDrive){
    rollerOnlyRight(karlDrive);
    
    //moveDistance(karlDrive.distToTicks(7), karlDrive.driveKP, karlDrive.driveKD, 2000);
    //turnDistance(karlDrive.degToTicks(-70), karlDrive.turningKP, karlDrive.turningKD, 1500);
    Floppy.move_velocity(180);
    Intake.move_velocity(180);
    moveDistance(karlDrive.distToTicks(40), karlDrive.driveKP/1.5, karlDrive.driveKD, 2400);
    Floppy.move_velocity(0);
    Intake.move_velocity(0);
    brake();
}

void rollerPreRight(driveInfo karlDrive){
    rollerOnlyRight(karlDrive);
    Flywheel.move_velocity(-550);
    Flywheel_Two.move_velocity(-550);
    pros::delay(2000);
    turnDistance(160, karlDrive.turningKP*2, karlDrive.turningKD, 3400);
    brake();
    for(int i = 0; i < 2; i++){
		diskIndexer.set_value(true);
		pros::delay(100);
		diskIndexer.set_value(false);
        pros::delay(500);
    }
    Flywheel.move_velocity(0);
    Flywheel_Two.move_velocity(0);
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
    pros::delay(1500);
    Intake.move_velocity(100);
    pros::delay(600);
    moveDistance(karlDrive.distToTicks(4), karlDrive.driveKP, karlDrive.driveKD, 1000);
    pros::delay(1000);
    Intake.move_velocity(0);
    moveDistance(karlDrive.distToTicks(-16), karlDrive.driveKP, karlDrive.driveKD, 2000);
    brake();
    turnDistance(karlDrive.degToTicks(-80), karlDrive.turningKP, karlDrive.turningKD, 2000);
    brake();
    Intake.move_velocity(100);
    moveDistance(karlDrive.distToTicks(27), karlDrive.driveKP, karlDrive.driveKD, 1500);
    brake();
    //pros::delay(1000);
    Intake.move_velocity(0);
    moveDistance(karlDrive.distToTicks(-10), karlDrive.driveKP, karlDrive.driveKD, 1500);
    turnDistance(karlDrive.degToTicks(15), karlDrive.turningKP, karlDrive.turningKD, 1500);
    pros::delay(6000);
    expansion.set_value(true);
	expansion2.set_value(true);
}