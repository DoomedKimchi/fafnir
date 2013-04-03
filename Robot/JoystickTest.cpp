#include "JoystickTest.h"

JoystickTest::JoystickTest(Robot *robot)
  :    speedStick(PORT_JS_SPEED)
  ,    turnStick(PORT_JS_TURN)
  ,    operatorStick(PORT_JS_OPERATOR) {
    shooting = false;
  this->robot = robot;
}

void JoystickTest::update() {
  //printf("Joystick 1 (speedStick):\n");
	if ((speedStick.GetX() >= 0.2) || (speedStick.GetX() <= -0.2))
    printf("1X: %f\n", speedStick.GetX());
	if ((speedStick.GetY() >= 0.2) || (speedStick.GetY() <= -0.2))
		printf("1Y: %f\n", speedStick.GetY());
	if (speedStick.GetTrigger() != 0.0)
		printf("1Trigger: %d\n", speedStick.GetTrigger());

	//printf("Joystick 2 (turnStick):\n");
	if ((turnStick.GetY() >= 0.2) || (turnStick.GetY() <= -0.2))
		printf("2X: %f\n", turnStick.GetX());
	if ((turnStick.GetY() >= 0.2) || (turnStick.GetY() <= -0.2))
		printf("2Y: %f\n", turnStick.GetY());
	if (turnStick.GetTrigger() != 0.0)
		printf("2Trigger: %d\n", turnStick.GetTrigger());

	//printf("Joystick 3 (operatorStick):\n");
	if ((operatorStick.GetX() >= 0.2) || (operatorStick.GetX() <= -0.2))
		printf("3X: %f\n", operatorStick.GetX());
	if ((operatorStick.GetY() >= 0.2) || (operatorStick.GetY() <= -0.2))
		printf("3Y: %f\n", operatorStick.GetY());
	if (operatorStick.GetTrigger() != 0.0)
		printf("3Trigger: %d\n", operatorStick.GetTrigger());
}

