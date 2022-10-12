#include "main.h"
#include "odom.h"
#include "pros/adi.hpp"

#define FR_MOTOR 10
#define FL_MOTOR 20
#define BR_MOTOR 12
#define BL_MOTOR 1
#define FLOPPY 4
#define FLYWHEEL 6
#define FLYWHEEL_TWO 11



pros::Controller master (pros::E_CONTROLLER_MASTER);

pros::Motor FLmotor(FL_MOTOR, false);
pros::Motor FRmotor(FR_MOTOR, true);
pros::Motor BLmotor(BL_MOTOR, true);
pros::Motor BRmotor(BR_MOTOR, false);

pros::Motor Floppy(FLOPPY, MOTOR_GEARSET_18);
pros::Motor Flywheel(FLYWHEEL, MOTOR_GEARSET_6);
pros::Motor Flywheel_Two(FLYWHEEL_TWO, MOTOR_GEARSET_6,true);

pros::ADIDigitalOut diskIndexer ('A');
pros::ADIDigitalOut expansion ('B');

//change these
driveTrain m_drive = driveTrain(3.25, 11.5);
odomController m_odom = odomController(m_drive);