#include "main.h"
#include "driveTrain.h"

class odomController{
  public:
    driveTrain i_drive;
    odomController(driveTrain m_drive){
      i_drive = m_drive;
      gPos.first = 0;
      gPos.second = 0;
    }
    double gOrinent = 0;
    std::pair<double, double> gPos;
    double odomHeading = 0;
    double prevLeftEnc = 0;
    double prevRightEnc = 0;
    double unitsPerRev = 900;

    void update(double leftEnc, double rightEnc){
      std::pair<double, double> localOffset;
      double leftDelta = (leftEnc - prevLeftEnc)*i_drive.wheelCircumfrence*i_drive.gearScale /unitsPerRev;
      double rightDelta = (rightEnc - prevRightEnc)*i_drive.wheelCircumfrence*i_drive.gearScale /unitsPerRev;
      prevLeftEnc = leftEnc;
      prevRightEnc = rightEnc;
      double orientDelta = (rightDelta-leftDelta)/(i_drive.wheelToWheel);
      if(orientDelta == 0){
        localOffset.first = 0;
        localOffset.second = rightDelta*sin(gOrinent);
      }
      else{
        double offset = 2*((leftDelta/orientDelta)+(i_drive.wheelToWheel/2))*sin(orientDelta/2);
        double yDelta = offset * cos(gOrinent+ (orientDelta/2));
        double xDelta = offset * sin(gOrinent+ (orientDelta/2));
        gOrinent += orientDelta;
        localOffset.first+=xDelta;
        localOffset.second+=yDelta;
      }
      gPos.first+=localOffset.first;
      gPos.second+=localOffset.second;
      odomHeading = gOrinent*180/M_PI;
    }
};