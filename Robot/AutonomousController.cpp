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

void AutonomousController::runDefault() {
  robot->aim();

  robot->shoot();
  robot->shoot();
  robot->shoot();
}

void AutonomousController::update() {

}
