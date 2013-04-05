#include "Dumper.h"

Dumper::Dumper() : motor(PORT_DUMPER_VIC), targetSpeed(0) {

}

void Dumper::setState(DumperState newState) {
  state = newState;

  switch (state) {
    case RETURNING:
      printf("Dumper returning\n");
      break;
    case STOPPED:
      printf("Dumper stopping\n");
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
  switch (state) {
    case RETURNING:
      motor.Set(-DUMP_SPEED);
      break;
    case STOPPED:
      motor.Set(0);
      break;
    case DUMPING:
      motor.Set(DUMP_SPEED);
      break;
    case HUMAN:
      if(targetSpeed < .1 || targetSpeed > .1)
	printf("Dumper speed: %f\n", targetSpeed);
      targetSpeed = 0;
      break;
    default:
      break;
  }
}
