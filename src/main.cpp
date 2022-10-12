#include "main.h"
#include "autonomoose.h"
#include "pros/misc.h"

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
	driveInfo karl(4,15.25);
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
		case 0: auton1();
		case 1: auton2();
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
   Flywheel.move_velocity(flySpeed);
	 Flywheel_Two.move_velocity(flySpeed);
   pros::delay(30);
 }

 void temperature(void *param) {
	 if(BLmotor.get_temperature()>hottest){
		 hottest = BLmotor.get_temperature();
		 screenPrintString(1, 0, "BLmotor");
	 }
	 if(FLmotor.get_temperature()>hottest){
		 hottest = FLmotor.get_temperature();
		 screenPrintString(1, 0, "FLmotor");
	 }
	 if(BRmotor.get_temperature()>hottest){
		 hottest = BRmotor.get_temperature();
		 screenPrintString(1, 0, "BRmotor");
	 }
	 if(FRmotor.get_temperature()>hottest){
		 hottest = FRmotor.get_temperature();
		 screenPrintString(1, 0, "FRmotor");
	 }
	 if(Floppy.get_temperature()>hottest){
		 hottest = Floppy.get_temperature();
		 screenPrintString(1, 0, "Floppy");
	 }
	 if(Flywheel.get_temperature()>hottest)
	 hottest = Flywheel.get_temperature();{
		 screenPrintString(1, 0, "Flywheel");
	 }
 }



void odomContainer(){
  m_odom.update((FLmotor.get_position()+BLmotor.get_position())/2, (FRmotor.get_position()+BRmotor.get_position())/2);
  pros::screen::print(TEXT_MEDIUM, 3, "X: %d, Y: %d, H: %d", m_odom.gPos.first,m_odom.gPos.second, m_odom.odomHeading);
}

void opcontrol() {

	bool  runConveyor = false;
	bool  runFlywheel = false;
	bool indexerOut = false;
	bool intakeRev = false;
	double intakeDir = 1;
	while (true) {
		pros::Task intake_task(intake);
		pros::Task temp_task(temperature);
		pros::Task fly_task(flywheel);
		pros::Task odom_task(odomContainer);

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

		if(runFlywheel == true){
			flySpeed = 550;
		} else {
			flySpeed = 0;

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
			expansion.set_value(false);
		}

		double power = master.get_analog(ANALOG_LEFT_Y);
		double turn = master.get_analog(ANALOG_RIGHT_X);
		drive(cubicSpeedScaling(power)-turn,cubicSpeedScaling(power)+turn);
		master.clear();
		pros::delay(20);
	}
}
