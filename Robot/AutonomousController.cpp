#include "AutonomousController.h"
#include "Robot.h"

AutonomousController::AutonomousController(Robot *robot, AutonomousMode m) {
  this->robot = robot;
  mode = m;

}

AutonomousController::~AutonomousController() {
  
}

bool AutonomousController::fire() {
  fafnir->aim();
  fafnir->shoot();

  return true;
}

void AutonomousController::runDefault() {
  robot.aim();

  fafnir->shoot();
  fafnir->shoot();
  fafnir->shoot();
}

void AutonomousController::update() {

}
