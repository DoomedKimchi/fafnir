#ifndef NUMBERPIDSOURCE_H_
#define NUMBERPIDSOURCE_H_

#include "WPILib.h"

class NumberPIDSource : public PIDSource {
private:
	double value;
public:
	NumberPIDSource();
	double PIDGet();
	void PIDWrite(double input);
};
#endif /*NUMBERPIDSOURCE_H_*/
