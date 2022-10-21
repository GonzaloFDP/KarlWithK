#include "main.h"
#include "motorSetup.h"

//Important Constants
 int floppySpeed = 0;
 int flySpeed = 0;
 int hottest = 0;
 double driveKP = 0.125;
 double driveKD = 0.02;



//Driver Control function
void drive(double right, double left){
  /*
  int ratio = right/left;
  if(right > 200){
    right = 200;
    //left = right/ratio;
  } else if (right < -200){
    right = -200;
    //left = right/ratio;
  }
  if(left > 200){
    left  = 200;
    //right = left*ratio;
  } else if (left < -200){
    left = -200;
    //right = left*ratio;
  }*/
  FLmotor.move_velocity(left);
  BLmotor.move_velocity(left);
  FRmotor.move_velocity(right);
  BRmotor.move_velocity(right);
}

int linearSpeedScaling(double input){
  double output = (input * 200)/127;
  return output;
}

int cubicSpeedScaling(double input){
  //y = ((x)^3)*(200/(127)^3)
  double output = (input*input*input)*(0.0001);
  return output;
}


//////////////MISC functions/////////////////////////

//Function that prints a String to the controller
void screenPrintString(int row, int col, std::string i){
  master.print(row,col,"%s",i.c_str());
}

//Converts radians -> degrees
double radToDeg(double rad){
  double deg = rad*(180/M_PI);
  return deg;
}

//Converts degrees -> radians
double degToRad(double deg){
  double rad = deg*(M_PI/180);
  return rad;
}

//Auton Selector
int len = 3;
std::string autons[3] = {"rollerOnly", "rollerPreloadLeft", "rollerPreloadRight"};
int counter = 0;


int autonSelector(){
  while(true){
    screenPrintString(1, 0, autons[counter]);
    if(master.get_digital_new_press(DIGITAL_RIGHT)){
      master.clear();
      counter = (counter + 1 + len) % len;
    } else if(master.get_digital_new_press(DIGITAL_LEFT)){
      master.clear();
      counter = (counter - 1 + len) % len;
    }
    screenPrintString(1,0,autons[counter]);
    if(master.get_digital_new_press(DIGITAL_A)){
      break;
    }
  }
  return counter;
}

//Reset Robot to Base Position
void totalReset(){
  FLmotor.tare_position();
  FRmotor.tare_position();
  BLmotor.tare_position();
  BRmotor.tare_position();
  diskIndexer.set_value(false);
	expansion.set_value(true);
}

//Motor reset
void motorReset(){
  FLmotor.tare_position();
  FRmotor.tare_position();
  BLmotor.tare_position();
  BRmotor.tare_position();
}

//PD (Proportional Derivative) loop
void moveDistance(double ticks, double kP, double kD, int waitTime){
  FLmotor.tare_position();
  FRmotor.tare_position();
  BLmotor.tare_position();
  BRmotor.tare_position();

  double error;
  double prevError = 0;
  double derivative;
  double tVal = ticks;
  double timeElapsed = 0;

  double avgLeftSide = (FLmotor.get_position()+BLmotor.get_position())/2;
  double avgRightSide = (FRmotor.get_position()+BRmotor.get_position())/2;
  double avgTotalPos = (avgLeftSide+avgRightSide)/2;

  while(true){
    if(timeElapsed >= waitTime){
      break;
    }
    error = tVal-avgTotalPos;
    derivative = error-prevError;
    avgLeftSide = (FLmotor.get_position()+BLmotor.get_position())/2;
    avgRightSide = (FRmotor.get_position()+BRmotor.get_position())/2;
    avgTotalPos = (avgLeftSide+avgRightSide)/2;
    double motorPower = kP*error + kD*derivative;
    if(motorPower>200){
      motorPower = 200;
    } else if (motorPower<-200){
      motorPower = -200;
    }
    drive(motorPower,motorPower);
    prevError = error;
    pros::delay(20);
    timeElapsed += 20;
  }
}

void turnDistance(double ticks,double kP, double kD, int waitTime){
  FLmotor.tare_position();
  FRmotor.tare_position();
  BLmotor.tare_position();
  BRmotor.tare_position();

  double tVal = ticks;
  double timeElapsed = 0;

  //left
  double leftError;
  double leftPrevError = 0;
  double leftDerivative;

  //right
  double rightError;
  double rightPrevError = 0;
  double rightDerivative;

  double avgLeftSide = (FLmotor.get_position()+BLmotor.get_position())/2;
  double avgRightSide = (FRmotor.get_position()+BRmotor.get_position())/2;

  while(true){
    if(timeElapsed >= waitTime){
      break;
    }

    // Left Side

    leftError = tVal-avgLeftSide;
    leftDerivative = leftError-leftPrevError;
    leftPrevError = leftError;
    avgLeftSide = (FLmotor.get_position()+BLmotor.get_position())/2;
    double leftMotorPower = (kP*leftError + kD*leftDerivative);
    if(leftMotorPower>200){
      leftMotorPower = 200;
    } else if (leftMotorPower<-200){
      leftMotorPower = -200;
    }

    // Right Side
    rightError = (-1*tVal) - avgRightSide; //the target value is NEGATIVE because to turn clockwise, right wheel has to move BACKWARDS
    rightDerivative = rightError - rightPrevError;
    rightPrevError = rightError;
    avgRightSide = (FRmotor.get_position()+BRmotor.get_position())/2;

    double rightMotorPower = (kP * rightError + kD * rightDerivative);
    if(rightMotorPower>200){
      rightMotorPower = 200;
    } else if (rightMotorPower < -200){
      rightMotorPower = -200;
    }

    drive(rightMotorPower,leftMotorPower);
    pros::delay(20);
    timeElapsed += 20;
  }
}

void turnHehe(double ticks,double kP, double kD, int waitTime){
  FLmotor.tare_position();
  FRmotor.tare_position();
  BLmotor.tare_position();
  BRmotor.tare_position();

  double avgLeftSide = (FLmotor.get_position()+BLmotor.get_position())/2;
  double avgRightSide = (FRmotor.get_position()+BRmotor.get_position())/2;

  while(true){
    double leftMotorPower = (ticks-avgLeftSide)/2;

    drive(-1*leftMotorPower,leftMotorPower);
    pros::delay(20);
  }
}
