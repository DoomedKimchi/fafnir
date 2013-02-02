#include "HumanController.h"

HumanController::HumanController()
    :    speedStick(PORT_JS_SPEED)
    ,    turnStick(PORT_JS_TURN)
    ,    operatorStick(PORT_JS_OPERATOR) {

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

  /* forced gear shifting modes */
  if(turnStick.GetRawButton(JS_TURN_MANMODE_TOGGLE)) {
    // if auto
      // engage manual
    
    // if high gear
      // engage low gear
    // if low gear
      // engage high gear
  }
  else if(turnStick.GetRawButton(JS_TURN_MANMODE_LOW)) {
    // engage low gear
  }
  else if(turnStick.GetRawButton(JS_TURN_MANMODE_HIGH)) {
    // engage high gear
  }
}
