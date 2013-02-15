#include "Accumulator.h" 

Accumulator::Accumulator() : motor((UINT32)PORT_ACC_VIC_1), servo(PORT_ACC_SERVO), frisbeeSwitch(PORT_ACC_SWITCH){
  this.state = AccumulatorState.EMPTY;
}

virtual Accumulator::~Accumulator() {
    
}

private bool Accumulator:: start() {
    if(motor.Get() == 1) return false;
    motor.Set(1);
    return true;
}
private void Accumulator:: shootVacated() {
  frisbeePresent = false;
}

private bool Accumulator:: kill() {
    if(motor.Get() == 0) return false;
    motor.Set(0);
    return true;
}

private bool Accumulator:: update(bool accumulate) {
  switch(state) {
  case EMPTY:
    break; 
  case LOADING:
    break; 
  case LOADED:
    break; 
  default:
    break;
  }
    return false;
}

public setState(AccumulatorState state) {
  this.state = state;
}
