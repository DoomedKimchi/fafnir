#include "NumberPIDSource.h"

NumberPIDSource::NumberPIDSource() {
	value = 0;
}
void NumberPIDSource::PIDWrite(double input) {
	value = input;
}
double NumberPIDSource::PIDGet() {
	return value;
}
