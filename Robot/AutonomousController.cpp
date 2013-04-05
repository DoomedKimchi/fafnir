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
  timer.Start();
}

void AutonomousController::drive(float v) {
  printf("Driving at %f\n", v);
  robot->setSpeed(-v);
  robot->rotateSpeed(0.0);
}

void AutonomousController::stop() {
  drive(0);
  robot->rotateSpeed(0);
}

bool AutonomousController::fire() {
  robot->aim();
  robot->shoot();

  return true;
}

void AutonomousController::dump(float time) {
  if(time < DUMP_TIME) robot->dump();
  else if(time < DUMP_TIME + DUMP_PAUSE_TIME) robot->stopDump();
  else robot->unDump();
}

void AutonomousController::runDefault() {

}

void AutonomousController::update() {
  /*if(timer.Get() < 1.0) {
    setSpeed();
  }
  else if(timer.Get() < 1.0 + TOT_DUMP_TIME * 3) {
    stop();
    dump((timer.Get() - 1.0) % TOT_DUMP_TIME);
  } else {
    robot->stopDump();
    }*/
}
