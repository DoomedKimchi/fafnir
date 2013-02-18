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
  shooter.shoot();
  accumulator.shootVacated();

}

void Robot::climb() {

}

ShifterMode Robot::getShifterMode() {
  return driveTrain.getShifterMode();
}

bool Robot::setShifterMode(ShifterMode mode) {
  return driveTrain.setShifterMode(mode);
}

ShifterPosition Robot::getShifterPosition() {
  return driveTrain.getShifterPosition();
}

bool Robot::setShifterPosition(ShifterPosition pos) {
  return driveTrain.setShifterPosition(pos);
}

void Robot::setSpeed(float s) {
  driveTrain.driveS(s);
}

void Robot::update() {
  driveTrain.update();
  accumulator.update();
  shooter.update();
}
 
