#ifndef NUMBERPIDSOURCE_H_
#define NUMBERPIDSOURCE_H_

#include "WPILib.h"

class NumberPIDSource : public PIDSource {
private:
	float value;
public:
	void PIDWrite(float output);
}