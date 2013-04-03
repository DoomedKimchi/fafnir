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

void Dumper::autoDump(float s, double t) {
	printf("Automatically dumping\n");
	// Note that the variables "s" and "t" have to be calibrated to the correct values.
	s = 0.2; // temporarily hard-coded, remove when defined elsewhere
	t = 2;  // temporarily hard-coded, remove when defined elsewhere

	dump(s); // start dump
  Wait(t); // pause execution of method (the motors keep turning)
  dump(0); // stop dump
  Wait(1); // wait for a second
  dump(-s); // return dumper to original position
  Wait(t);
  dump(0);

	printf("Dump complete\n");
}

void Dumper::rotateS() {

}

void Dumper::update() {
	// Hardcoded values for testing, remove/comment out once they work
	motor1.Set(0.5);
	motor2.Set(0.5);
	motor3.Set(0.5);
	motor4.Set(0.5);
}
