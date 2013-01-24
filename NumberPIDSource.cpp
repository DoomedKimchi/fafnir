#include "NumberPIDSource.h"

NumberPIDSource::NumberPIDSource() {
	value = 0;
}
void PIDWrite(double input) {
	value = input;
}
void PIDGet() {
	return value;
}