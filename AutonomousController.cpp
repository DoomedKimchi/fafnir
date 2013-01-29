#include "AutonomousController.h"
#include "Robot.h"

AutonomousController::AutonomousController(Robot *robot) {
  fafnir = robot;
}

AutonomousController::~AutonomousController() {
  
}

bool AutonomousController::fire() {
  fafnir->aim();
  fafnir->shoot();
}
