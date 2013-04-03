#include "HumanController.h"

HumanController::HumanController(Robot *robot)
  :    speedStick(PORT_JS_SPEED)
  ,    turnStick(PORT_JS_TURN)
  ,    operatorStick(PORT_JS_OPERATOR) {
    shooting = false;
  this->robot = robot;
}

AutonomousMode HumanController::getAutonomousMode() {
  return DEFAULT;
}


void HumanController::update() {
  //check current state of joysticks
  //calculate what to do based on joysticks and robot state (e.g. drive speed for certain gear)
  //gear ranges should look something like:
  //low gear: 0 ft/sec – 5.5 ft/sec
  //high gear: 5 ft/sec – max speed (probably 16 ft/sec)

  /* begin drive forward/backward */
  //printf("joystick y: %f\t",  speedStick.GetY());
  //printf("joystick x: %f\n",  turnStick.GetX());
  robot->setSpeed(speedStick.GetY());
  robot->rotateSpeed(turnStick.GetX());
  /* end drive forward/backward */
  // printf("%f\n", speedStick.GetX());
  robot->elevationSpeed(operatorStick.GetY());
  /* begin Gearshifter changing */
  if(turnStick.GetRawButton(JS_TURN_MODE_TOGGLE)) {
    if(!buttShifterMode) {
      if(robot->getShifterMode() == AUTO) {
	robot->setShifterMode(MANUAL);
      }
      else {
	robot->setShifterMode(AUTO);
      }
    }
  }
  else if(turnStick.GetRawButton(JS_TURN_POSITION_LOW)) {
    robot->setShifterPosition(LOW_GEAR);
  }
  else if(turnStick.GetRawButton(JS_TURN_POSITION_HIGH)) {
    robot->setShifterPosition(HIGH_GEAR);
  }
  buttShifterMode = turnStick.GetRawButton(JS_TURN_MODE_TOGGLE);
  /* end Gearshifter changing */

  //printf("Trigger state: %d\n", operatorStick.GetTrigger());
  /* begin operator commands */
  if(operatorStick.GetTrigger()) {
    printf("Trigger depressed; let's shoot a frisbee!\n");
    robot->shoot();
  }
  shooting = operatorStick.GetTrigger();
  
  gain = operatorStick.GetTrigger();

  
  /* end operator commands */ 

  // Dumper
  //printf("opstick y: %f\n", operatorStick.GetY());
  robot->dump(operatorStick.GetY());
}
