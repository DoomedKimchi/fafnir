#include "Robot.h"

Robot::Robot() {
  camera = AxisCamera::GetInstance();
  compressor(COMPRESSOR_SPIKE_PORT, PRESSURE_CUTOFF_PORT);
  compressor.Start(); 
}

void Robot::aim(int yaw, int elevation) {

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
