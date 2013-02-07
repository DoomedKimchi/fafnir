#ifndef NUMBERPID_H_
#define NUMBERPID_H_

#include "WPILib.h"

class NumberPID : public PIDSource, public PIDOutput {
private:
	double value;
public:
	NumberPID();
	double PIDGet();
	void PIDWrite(double input);
};
#endif /*NUMBERPID_H_*/