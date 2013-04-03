#include "Dumper.h"

Dumper::Dumper()
	:
		motor1(PORT_DUMPER_VIC_1)
	,	motor2(PORT_DUMPER_VIC_2)
	,	motor3(PORT_DUMPER_VIC_3)
	,	motor4(PORT_DUMPER_VIC_4)
{
	// stuff
}

void Dumper::dump(float s) {
	printf("Dumper speed: %f\n", s);
	//motor1.Set(s);
	//motor2.Set(s);
	//motor3.Set(s);
	//motor4.Set(s);
	
	/* Note that I'm only using 4 victors
	 * because the practice robot only has 
	 * 4 victors for the DriveTrain.
	 * The actual dumper will only use 1 victor.
	 */
}

void Dumper::rotateS() {

}

void Dumper::update() {
	// Hardcoded values for testing
	motor1.Set(0.5);
	motor2.Set(0.5);
	motor3.Set(0.5);
	motor4.Set(0.5);
}
