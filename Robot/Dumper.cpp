#include "Dumper.h"

Dumper::Dumper()
  :
  motor1(PORT_DUMPER_VIC_1)
  ,	motor2(PORT_DUMPER_VIC_2)
  ,	motor3(PORT_DUMPER_VIC_3)
  ,	motor4(PORT_DUMPER_VIC_4)
{
  // stuff
}

void Dumper::setState(DumperState state) {
  // only print the speed if its absolute value is greater than 0.1
  switch state {
    case RETURNING:
      printf("Dumper returning\n");
      motor.set(-DUMP_SPEED);
    case STOPPED:
      printf("Dumper stopping\n");
      motor.Set(0);
    case DUMPING:
      printf("Dumper dumping\n");
      motor.Set(DUMP_SPEED);
  }
}

  dump(DUMP_SPEED); // start dump
  //printf("waiting for %f seconds\n", DUMP_TIME);
  Wait(DUMP_TIME); // pause execution of method (the motors keep turning)
  dump(0);
  Wait(DUMP_PAUSE_TIME);

  printf("move dumper back\n");
  dump(-UNDUMP_SPEED); // return dumper to original position
  //printf("waiting for %f seconds\n", UNDUMP_TIME);
  Wait(UNDUMP_TIME);
  printf("stopping motor\n");
  dump(0);

  printf("Dump complete\n");
}

void Dumper::rotateS() {

}

void Dumper::update() {
}
