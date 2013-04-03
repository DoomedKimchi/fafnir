#ifndef DUMPER_H
#define DUMPER_H

#include <WPILib.h>
#include "Constants.h"
#include "NumberPID.h"
#include "LinearVictor.h"

class Dumper {
	private:
		LinearVictor motor1;
		LinearVictor motor2;
		LinearVictor motor3;
		LinearVictor motor4;

	public:
		Dumper();
		void dump(float s);
		void autoDump(float s, double t);
		void rotateS();
		void update();
};

#endif /* DUMPER_H */
