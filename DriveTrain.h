#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "Constants.h"
#include "WPILabs.h"

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

  int speed;
  int rotateSpeed;

  void engageHigh();
  void engageLow();
  void engageAuto();

public:
  bool driveSpd(double);
  bool driveDist(double);
  bool driveTo(double, double);

  bool rotateSpd(double);
  bool rotateDist(double);

  ShifterMode getMode();
  void setMode(ShifterMode mode);
  
  void update();
};

#endif /* DRIVE_TRAIN_H */
