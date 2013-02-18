#include "AutonomousController.h"
#include "Robot.h"

AutonomousController::AutonomousController(Robot *robot, AutonomousMode m) {
  fafnir = robot;
  mode = m;

}

AutonomousController::~AutonomousController() {
  
}

bool AutonomousController::fire() {
  fafnir->aim();
  fafnir->shoot();
}

void AutonomousController::update() {

}
