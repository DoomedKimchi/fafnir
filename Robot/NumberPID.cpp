#include "NumberPID.h"

NumberPID::NumberPID() {
	value = 0;
}
void NumberPID::PIDWrite(double input) {
	value = input;
}
double NumberPID::PIDGet() {
	return value;
}
