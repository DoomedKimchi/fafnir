#include "Accumulator.h" 

Accumulator::Accumulator()
    :    motor((UINT32)PORT_ACC_VIC_1) {

}

Accumulator::~Accumulator() {
    
}

bool Accumulator:: start() {
    if(motor.Get() == 1) return false;
    motor.Set(1);
    return true;
}
void Accumulator:: shootVacated() {
  frisbeePresent = false;
}

bool Accumulator:: kill() {
    if(motor.Get() == 0) return false;
    motor.Set(0);
    return true;
}

bool Accumulator:: update(bool accumulate) {
    return false;
}



