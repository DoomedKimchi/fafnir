#ifndef DUMPER_H
#define DUMPER_H

#include <WPILib.h>
#include "Constants.h"
#include "NumberPID.h"
#include "LinearVictor.h"

class Dumper {
 private:
  LinearVictor motor;
  DumperState state;

  float targetSpeed;

 public:
  Dumper();

  void setState(DumperState newState);
  void setSpeed(float spd);
  void update();
};

#endif /* DUMPER_H */
