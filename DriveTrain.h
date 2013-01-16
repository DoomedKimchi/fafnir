#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "Constants.h"
#include "WPILabs.h"

class DriveTrain {
private:
  ShifterMode gear; //ShifterMode is defined in Constants.h
  Encoder leftFrontEnc;
  Encoder leftBackEnc;
  Encoder rightFrontEnc;
  Encoder rightBackEnc;
  bool periodicAuto();

public:
  bool driveSpd(double);
  bool driveDist(double);
  bool driveTo(double, double);

  bool rotateSpd(double);
  bool rotateDist(double);

  ShifterMode getGear();
  bool setGear(ShifterMode mode);

  bool update();
};

#endif /* DRIVE_TRAIN_H */
