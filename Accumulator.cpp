#include "Accumulator.h" 

Accumulator::Accumulator()
    :    motor((UINT32)PORT_ACC_VIC_1) {

}

bool Accumulator:: start() {
    return false;
}

bool Accumulator:: kill() {
    return false;
}

bool Accumulator:: update(bool accumulate) {
    return false;
}



