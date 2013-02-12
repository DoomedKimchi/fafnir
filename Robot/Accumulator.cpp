#include "Accumulator.h" 

Accumulator::Accumulator() : motor((UINT32)PORT_ACC_VIC_1) {
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
    return false;
}

public setState(AccumulatorState state) {
  this.state = state;
}
