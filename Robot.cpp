#include "Robot.h"

Robot::Robot() 
  :  compressor(PORT_COMPRESSOR_SPIKE, PORT_PRESSURE_CUTOFF) {
  camera = AxisCamera::GetInstance();
  compressor.Start();
}

void Robot::aim(float yaw, float elevation) {

}

void Robot::aim(RGBImage image) {

}

void Robot::shoot() {
	
}

void Robot::climb() {

}

void Robot::update() {
    driveTrain.update();
    accumulator.update();
    shooter.update();
}
