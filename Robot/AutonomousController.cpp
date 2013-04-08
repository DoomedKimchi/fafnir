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

void AutonomousController::drive(float speed, float turnSpeed) {
  printf("Driving at %f\n", speed);
  printf("Turning at %f\n", turnSpeed);
  robot->setSpeed(-speed);
  robot->rotateSpeed(turnSpeed);
}

void AutonomousController::stop() {
  //drive(0);
  robot->rotateSpeed(0);
}

bool AutonomousController::fire() {
  robot->aim();
  robot->shoot();

  return true;
}

/*void AutonomousController::dump(float time) {
  if(time < DUMP_TIME) robot->dump();
  else if(time < DUMP_TIME + DUMP_PAUSE_TIME) robot->stopDump();
  else robot->unDump();
  }*/

void AutonomousController::driveBlindly() {
  printf("Driving blindly!\n");
  /*if(timer.Get() < 1.0) {
    setSpeed();
>>>>>>> 5cd53ba6ea3a3d3d2cc19be7218fe331c2cc2ad3
  }
  else if(timer.Get() < 1.0 + TOT_DUMP_TIME * 3) {
    stop();
    dump((timer.Get() - 1.0) % TOT_DUMP_TIME);
  } else {
    robot->stopDump();
  }
  */
}

void AutonomousController::update(int bearing) {
	if (bearing == 3) { // target is aligned so drive straight
		printf("Driving straight\n");
		drive(AUTO_SPEED, 0.0);
	}
	else if (bearing == 1) // target on left so turn left
		drive(AUTO_SPEED, -AUTO_TURN_SPEED);
	else if (bearing == 2) // target on right so turn right
		drive(AUTO_SPEED, AUTO_TURN_SPEED);
	else if (bearing == 0) { 
		drive(0, AUTO_TURN_SPEED); // no target found so turn instead 
	}
}
