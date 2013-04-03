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
	// only print the speed if its absolute value is greater than 0.1
	if((s >= 0.1) || (s <= -0.1))
	  printf("Dumper speed: %f\n", s);
	motor1.Set(s);
	motor2.Set(s);
	motor3.Set(s);
	motor4.Set(s);
	
	/* Note that I'm only using 4 victors
	 * because the practice robot only has 
	 * 4 victors for the DriveTrain.
	 * The actual dumper will only use 1 victor,
	 * so comment out or remove the rest.
	 */
}

void Dumper::autoDump(float s, double t) {
	printf("\nAutomatically dumping\n");
	// Note that the variables "s" and "t" have to be calibrated to the correct values.
	s = DUMP_SPEED;
	t = DUMP_TIME;

	//printf("stopping motor\n");
  //dump(0); // stop motor first
	//printf("waiting for 1 seconds\n");
  //Wait(1); // wait for a second
	printf("start dump\n");
	dump(s); // start dump
	printf("waiting for %f seconds\n", t);
  Wait(t); // pause execution of method (the motors keep turning)
	dump(0);
	Wait(DUMP_PAUSE_TIME);
	s = UNDUMP_SPEED;
	t = UNDUMP_TIME;
	printf("move dumper back\n");
  dump(-s); // return dumper to original position
	printf("waiting for %f seconds\n", t);
  Wait(t);
	printf("stopping motor\n");
  dump(0);

	printf("Dump complete\n");
}

void Dumper::rotateS() {

}

void Dumper::update() {
	// Hardcoded values for testing, remove/comment out once they work
	//motor1.Set(0.5);
	//motor2.Set(0.5);
	//motor3.Set(0.5);
	//motor4.Set(0.5);
}
