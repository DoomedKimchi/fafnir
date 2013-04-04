#include "AutonomousController.h"
#include "Robot.h"

AutonomousController::AutonomousController(Robot *robot, AutonomousMode m) {
  this->robot = robot;
  mode = m;

}

AutonomousController::~AutonomousController() {
  
}

void AutonomousController::driveStraight() {

}

void AutonomousController::driveRight() {

}

void AutonomousController::driveLeft() {

}

void AutonomousController::rotateRight() {

}

void AutonomousController::rotateLeft() {

}

bool AutonomousController::fire() {
  robot->aim();
  robot->shoot();

  return true;
}

void AutonomousController::dump() {
	robot->autoDump();
}

void AutonomousController::runDefault() {
  robot->aim();

  robot->shoot();
  robot->shoot();
  robot->shoot();
}

void AutonomousController::update() {

}
