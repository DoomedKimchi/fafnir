#include "Dumper.h"

Dumper::Dumper() : motor(PORT_DUMPER_VIC), targetSpeed(0) {

}

void Dumper::setState(DumperState state) {
  switch (state) {
    case RETURNING:
      printf("Dumper returning\n");
      targetSpeed = -DUMP_SPEED;
      break;
    case STOPPED:
      printf("Dumper stopping\n");
      targetSpeed = 0;
      break;
    case DUMPING:
      printf("Dumper dumping\n");
      break;
    default:
      break;
  }
}

void Dumper::setSpeed(float spd) {
  targetSpeed = spd;
}

void Dumper::update() {
  if(targetSpeed < .1 || targetSpeed > .1) {
    printf("Dumper speed: %f\n", targetSpeed);
  }
  motor.Set(targetSpeed);
  }
}
