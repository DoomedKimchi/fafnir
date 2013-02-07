#include "Robot.h"

Robot::Robot() 
    :  /*camera (AxisCamera::GetInstance()) 
	 ,  */compressor(PORT_PRESSURE_CUTOFF, PORT_COMPRESSOR_SPIKE) {
  compressor.Start();
}

void Robot::aim(float yaw, float elevation) {

}

void Robot::aim() {

}

void Robot::shoot() {
	
}

void Robot::climb() {

}

void Robot::update() {
    driveTrain.update();
    accumulator.update(true);
    shooter.update();
}
