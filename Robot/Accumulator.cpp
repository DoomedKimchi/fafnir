#include "Accumulator.h"

Accumulator::Accumulator() : motor((UINT32)PORT_ACC_VIC_1), servo(PORT_ACC_SERVO), frisbeeSwitch(PORT_ACC_SWITCH), state(SHOOTER_EMPTY){

}

Accumulator::~Accumulator() {

}

bool Accumulator:: start() {
    if(motor.Get() == 1) return false;
    motor.Set(1);
    return true;
}
void Accumulator:: shootVacated() {
    state = SHOOTER_EMPTY;
}

bool Accumulator:: kill() {
    if(motor.Get() == 0) return false;
    motor.Set(0);
    return true;
}

void Accumulator:: update() {
  switch(state) {
  case SHOOTER_EMPTY:
    if (frisbeeSwitch.IsPressed()){
      state=LOADING;
    }
    break;
  case LOADING:
    if (!frisbeeSwitch.IsPressed()){
      state=SHOOTER_LOADED;
    }
    break;
  case SHOOTER_LOADED:
    break;
  default:
    break;
  }
    //return false;
}

void Accumulator::setState(AccumulatorState nstate) {
  state = nstate;
}
