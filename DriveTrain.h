#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "Constants.h"

class DriveTrain {
 private:
  enum ShifterMode { LOW_GEAR, HIGH_GEAR, AUTO };

 public:
  boolean setMode(ShifterMode mode);
  boolean update();
};

#endif /* DRIVE_TRAIN_H */
