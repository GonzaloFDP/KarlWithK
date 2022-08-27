#include "main.h"

#define FR_MOTOR 10
#define FL_MOTOR 20
#define BR_MOTOR 1
#define BL_MOTOR 11
#define FLOPPY 4
#define FLYWHEEL 6

pros::Controller master (pros::E_CONTROLLER_MASTER);

pros::Motor FLmotor(FL_MOTOR, false);
pros::Motor FRmotor(FR_MOTOR, true);
pros::Motor BLmotor(BL_MOTOR, false);
pros::Motor BRmotor(BR_MOTOR, true);

pros::Motor Floppy(FLOPPY, MOTOR_GEARSET_6);
pros::Motor Flywheel(FLYWHEEL, MOTOR_GEARSET_6);
