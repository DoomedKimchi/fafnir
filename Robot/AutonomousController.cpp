#include "AutonomousController.h"
#include "Robot.h"

AutonomousController::AutonomousController(Robot *robot, AutonomousMode m) {
  this->robot = robot;
  mode = m;

}

AutonomousController::~AutonomousController() {
  
}

bool AutonomousController::fire() {
  robot->aim();
  robot->shoot();

  return true;
}

void AutonomousController::dump() {
  /* We could also move this code to Dumper.cpp into a method like autoDump
   * and just call that from here, so we could also use it in teleop.
   * Note that the variables "s" and "t" have to be calibrated to the correct values.
   */
  float s = 0.2; // speed at which to run the dumper
  double t = 2; // how long to run the dumper
  robot->dump(s); // start dump
  Wait(t); // pause execution of method (the motors keep turning)
  robot->dump(0); // stop dump
  Wait(1); // wait for a second
  robot->dump(-s); // return dumper to original position
  Wait(t);
  robot->dump(0);
}

void AutonomousController::runDefault() {
  robot->aim();

  robot->shoot();
  robot->shoot();
  robot->shoot();
}

void AutonomousController::update() {

}
