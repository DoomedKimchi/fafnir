#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "Constants.h"
#include "WPILib.h"

class DriveTrain {
private:
  ShifterMode mode; //ShifterMode is enumerated in Constants.h
  
  Solenoid leftSol;
  Solenoid rightSol;
  
  Encoder leftEnc;
  Encoder rightEnc;
  
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
  bool driveD(double); //distance
  bool driveS(double); //speed
  bool driveTo(double, double);
  
  bool rotateD(double); //distance
  bool rotateS(double); //speed
  
  ShifterMode getMode();
  void setMode(ShifterMode mode);
  
  void update();
};

#endif /* DRIVE_TRAIN_H */
