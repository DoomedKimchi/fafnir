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


void AutonomousController::startTimer() {

}

void AutonomousController::driveStraight(float t = 1) {
  printf("Driving straight\n");
  robot->setSpeed(-0.7);
  robot->rotateSpeed(0.0);
  Wait(t);
}

void AutonomousController::driveRight(float t = 1) {
  robot->rotateSpeed(0.2);
  Wait(t);
}

void AutonomousController::driveLeft(float t = 1) {
  robot->rotateSpeed(-0.2);
  Wait(t);
}

void AutonomousController::rotateRight(float t = 1) {
  robot->rotateSpeed(0.5);
  Wait(t);
}

void AutonomousController::rotateLeft(float t = 1) {
  robot->rotateSpeed(-0.5);
  Wait(t);
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
<<<<<<< HEAD
/*	targetAligned = 1;
  if(targetAligned)
    driveStraight();
  //Wait(1);
  if (targetReached)
    dump(); */
/*  if (timer.Get() < 1.0) {
     robot->setSpeed(-1.0);
=======
  /*	targetAligned = 1;
	if(targetAligned)
	driveStraight();
	//Wait(1);
	if (targetReached)
	dump(); */
  printf("%lu", timer.Get());
  if (timer.Get() < 1.0) {
    robot->setSpeed(-0.8);
>>>>>>> 1bbaded16b1e1124e2234feb5e6c5e9486cb49cd
  }
  else {
      robot->rotateSpeed(1.0);
      }*/
}
