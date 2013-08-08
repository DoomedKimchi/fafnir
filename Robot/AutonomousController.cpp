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

void AutonomousController::update() {
}
