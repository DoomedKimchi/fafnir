#include "JoystickTest.h"

JoystickTest::JoystickTest(Robot *robot)
  :    speedStick(PORT_JS_SPEED)
  ,    turnStick(PORT_JS_TURN)
  ,    operatorStick(PORT_JS_OPERATOR) {
    shooting = false;
  this->robot = robot;
}

void JoystickTest::update() {
	printf("Joystick 1 (speedStick):\n");
	printf("X: %f\n", speedStick.GetX());
	printf("Y: %f\n", speedStick.GetY());
	printf("Trigger: %d\n", speedStick.GetTrigger());

	printf("Joystick 2 (turnStick):\n");
	printf("X: %f\n", turnStick.GetX());
	printf("Y: %f\n", turnStick.GetY());
	printf("Trigger: %d\n", turnStick.GetTrigger());

	printf("Joystick 3 (operatorStick):\n");
	printf("X: %f\n", operatorStick.GetX());
	printf("Y: %f\n", operatorStick.GetY());
	printf("Trigger: %d\n", operatorStick.GetTrigger());
}

