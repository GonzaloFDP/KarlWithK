#include "main.h"
#include "autonomoose.h"
#include "pros/misc.h"
#include "pros/screen.h"
#include "pros/screen.hpp"

driveInfo karl(4,15.25);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//pros::delay(5000);
	
	FLmotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	FRmotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	BLmotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	BRmotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	totalReset();
	Flywheel.set_brake_mode(MOTOR_BRAKE_COAST);
	Flywheel_Two.set_brake_mode(MOTOR_BRAKE_COAST);
	Floppy.set_brake_mode(MOTOR_BRAKE_COAST);
	autonSelector();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	switch (counter) {
		case 0: rollerOnlyLeft(karl);
			break;
		case 1: rollerOnlyRight(karl);
		break;
		case 2: rollerPreloadLOWLeft(karl);
		break;
		case 3: rollerPreloadLOWRight(karl);
		break;
		case 4: progSkills(karl);
		break;
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 void intake(void *param) {
   Floppy.move_velocity(floppySpeed);
   pros::delay(30);
 }

 void flywheel(void *param) {
	if(runFlywheel == true){
   		flywheelCorrector(500, karl.flywheelKP, karl.flywheelKD);
	} else if (runFlywheel == false){
		flywheelCorrector(0, karl.flywheelKP, karl.flywheelKD);
	}
 }

 void temperature(void *param) {
	 if(BLmotor.get_temperature()>hottest){
		 hottest = BLmotor.get_temperature();
		 pros::screen::print(TEXT_MEDIUM, 1, "BL");
	 }
	 if(FLmotor.get_temperature()>hottest){
		 hottest = FLmotor.get_temperature();
		 pros::screen::print(TEXT_MEDIUM, 1, "FL");
	 }
	 if(BRmotor.get_temperature()>hottest){
		 hottest = BRmotor.get_temperature();
		 pros::screen::print(TEXT_MEDIUM, 1, "BR");
	 }
	 if(FRmotor.get_temperature()>hottest){
		 hottest = FRmotor.get_temperature();
		 pros::screen::print(TEXT_MEDIUM, 1, "FR");
	 }
	 if(Floppy.get_temperature()>hottest){
		 hottest = Floppy.get_temperature();
		 pros::screen::print(TEXT_MEDIUM, 1, "Floppy");
	 }
	 if(Flywheel.get_temperature()>hottest)
	 hottest = Flywheel.get_temperature();{
		 pros::screen::print(TEXT_MEDIUM,1,"Flywheel (%d)", FLYWHEEL);
	 }
	 if(Flywheel_Two.get_temperature()>hottest)
	 hottest = Flywheel_Two.get_temperature();{
		 pros::screen::print(TEXT_MEDIUM,1,"Flywheel 2 (%d)", FLYWHEEL_TWO);
	 }
 }



void flywheelChecker(){
  //m_odom.update((FLmotor.get_position()+BLmotor.get_position())/2, (FRmotor.get_position()+BRmotor.get_position())/2);
  //pros::screen::print(TEXT_MEDIUM, 3, "X: %d, Y: %d, H: %d", m_odom.gPos.first,m_odom.gPos.second, m_odom.odomHeading);
  pros::screen::print(TEXT_MEDIUM, 3, "Flywheel (%d) Speed: %d  Flywheel 2 (%d) Speed: %d", FLYWHEEL, Flywheel.get_actual_velocity(), FLYWHEEL_TWO, Flywheel_Two.get_actual_velocity());
}

void opcontrol() {
	while (true) {
		pros::Task intake_task(intake);
		pros::Task temp_task(temperature);
		pros::Task fly_task(flywheel);
		pros::Task flyPrint_task(flywheelChecker);

		if(runConveyor==false && master.get_digital_new_press(DIGITAL_X)){
			runConveyor = true;
		} else if(runConveyor==true && master.get_digital_new_press(DIGITAL_X)){
			runConveyor = false;
		}

		if(runConveyor == true){
			floppySpeed = 180*intakeDir;
		} else {
			floppySpeed = 0;
		}

		if (intakeRev == false && master.get_digital_new_press(DIGITAL_B)){
			intakeRev = true;
			intakeDir = -0.5;
		} else if(intakeRev==true && master.get_digital_new_press(DIGITAL_B)){
			intakeRev = false;
			intakeDir = 1;
		}

		if(runFlywheel==false && master.get_digital_new_press(DIGITAL_Y)){
			runFlywheel = true;
		} else if(runFlywheel==true && master.get_digital_new_press(DIGITAL_Y)){
			runFlywheel = false;
		}

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1) && indexerOut == false){
			indexerOut = true;
			diskIndexer.set_value(true);
			pros::delay(200);
			diskIndexer.set_value(false);
			indexerOut = false;
		} else {

		}

		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
			expansion.set_value(true);
		}

		double power = master.get_analog(ANALOG_LEFT_Y);
		double turn = master.get_analog(ANALOG_RIGHT_X);
		drive(cubicSpeedScaling(power)-turn,cubicSpeedScaling(power)+turn);
		master.clear();
		pros::delay(20);
	}
}
