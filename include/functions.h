#include "main.h"
#include "motorSetup.h"

//Important Constants
const double wheelCircumfrence = 5.6*3.14159265;



//Driver Control function
void drive(int right, int left){
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
  }
  FLmotor.move_velocity(left);
  BLmotor.move_velocity(left);
  FRmotor.move_velocity(right);
  BRmotor.move_velocity(right);
}

double speedScaling(int input){
  double output = (input * 200)/127;
  return output;
}


//////////////MISC functions/////////////////////////

//Function that prints a String to the Brain
void screenPrintString(int row, int col, std::string i){
  master.print(row,col,"%s",i.c_str());
}

double intToTicks(double dist){
  double ticks = dist;
  ticks /= wheelCircumfrence;
  ticks *= 900;
  return ticks;
}
//Auton Selector
int len = 2;
std::string autons[2] = {"auton_1", "auton_2"};
int counter = 0;


int autonSelector(){
  while(true){
    master.clear();
    if(master.get_digital_new_press(DIGITAL_RIGHT)){
      counter = (counter + 1 + len) % len;
    } else if(master.get_digital_new_press(DIGITAL_LEFT)){
      counter = (counter - 1 + len) % len;
    }
    screenPrintString(1,0,autons[counter]);
    if(master.get_digital_new_press(DIGITAL_A)){
      break;
    }
  }
  return counter;
}

void moveDistance(int dist, int kP, int kD){
  FLmotor.tare_position();
  FRmotor.tare_position();
  BLmotor.tare_position();
  BRmotor.tare_position();

  int error;
  int prevError;
  int derivative;
  int tVal = dist;

  double avgLeftSide = (FLmotor.get_position()+BLmotor.get_position())/2;
  double avgRightSide = (FRmotor.get_position()+BRmotor.get_position())/2;
  double avgTotalPos = (avgLeftSide+avgRightSide)/2;

  while(true){
    error = tVal-avgTotalPos;
    derivative = error-prevError;
    avgLeftSide = (FLmotor.get_position()+BLmotor.get_position())/2;
    avgRightSide = (FRmotor.get_position()+BRmotor.get_position())/2;
    avgTotalPos = (avgLeftSide+avgRightSide)/2;
    double motorPower = (kP*error + kD*derivative);
    if(motorPower>200){
      motorPower = 200;
    } else if (motorPower<-200){
      motorPower = -200;
    }
    drive(motorPower,motorPower);
    prevError = error;
    pros::delay(20);
  }
}
