#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "Constants.h"
#include "WPILib.h"

class DriveTrain {
private:
  ShifterMode gear; //ShifterMode is enumerated in Constants.h
  
  Solenoid leftSol;
  Solenoid rightSol;
  
  Encoder leftFrontEnc;
  Encoder leftBackEnc;
  Encoder rightFrontEnc;
  Encoder rightBackEnc;
  
  Victor leftFrontVic;
  Victor leftBackVic;
  Victor rightFrontVic;
  Victor rightBackVic;

  Gyro gyro;

  int speed;
  int rotateSpeed;

  void engageHigh();
  void engageLow();
  void engageAuto();

  float targetSpeed;
  float targetDist;
  float targetAngle;

public:
  bool driveSpd(double);
  bool driveDist(double);
  bool driveTo(double, double);

  bool rotate(double); //distance
  //we should have rotate speed as well

  ShifterMode getMode();
  void setMode(ShifterMode mode);
  
  void update();
};

#endif /* DRIVE_TRAIN_H */
