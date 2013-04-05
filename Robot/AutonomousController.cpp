#include "AutonomousController.h"
#include "Robot.h"

AutonomousController::AutonomousController(Robot *robot, AutonomousMode m) {
  this->robot = robot;
  mode = m;
  targetAligned = 0;
  targetReached = 0;

  timer.Start();
}

AutonomousController::~AutonomousController() {
  
}

void AutonomousController::driveStraight() {
  printf("Driving straight\n");
  robot->setSpeed(-0.7);
  robot->rotateSpeed(0.0);
  Wait(1);
}

void AutonomousController::driveRight() {
  robot->rotateSpeed(0.2);
  Wait(1);
}

void AutonomousController::driveLeft() {
  robot->rotateSpeed(-0.2);
  Wait(1);
}

void AutonomousController::rotateRight() {
  robot->rotateSpeed(0.5);
  Wait(1);
}

void AutonomousController::rotateLeft() {
  robot->rotateSpeed(-0.5);
  Wait(1);
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

}

void AutonomousController::driveBlindly() {
  printf("Driving blindly!\n");
  printf("%lu", timer.Get());
  if (timer.Get() < 1.0) {
     robot->setSpeed(-0.8);
  }
  else {
    robot->rotateSpeed(0.8);
  }
}

void AutonomousController::update(int bearing) {
	if (bearing > 5)
		driveRight();
}
