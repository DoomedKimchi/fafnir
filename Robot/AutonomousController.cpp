#include "AutonomousController.h"
#include "Robot.h"

AutonomousController::AutonomousController(Robot *robot, AutonomousMode m) {
  this->robot = robot;
  mode = m;
  targetAligned = 0;
  targetReached = 0;
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
	driveStraight();
	dump();
}

void AutonomousController::update() {
/*	targetAligned = 1;
  if(targetAligned)
    driveStraight();
  //Wait(1);
  if (targetReached)
    dump(); */
  robot->rotateSpeed(0.5);
}
