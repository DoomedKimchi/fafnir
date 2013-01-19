/*
 * Drivetrain class
 * It's the drive train, what do you think it does?
 * Are you seriously still reading this?
 */

DriveTrain::DriveTrain {
  
}

bool DriveTrain::engageHigh() {
  if(gear == HIGH_GEAR) {
    return false;
  }
  gear = HIGH_GEAR;
  return true;
}

bool DriveTrain::engageLow() {
  if(gear == LOW_GEAR) {
    return false;
  }
  if(
  return true;
}

bool DriveTrain::periodicAuto() {

}

bool DriveTrain::driveSpd(double d) {

}

bool DriveTrain::driveDist(double d) {

}

bool DriveTrain::driveTo(double d1, double d2) {

}

bool DriveTrain::rotateSpd(double d) {

}

bool DriveTrain::rotateDist(double d) {

}

ShifterMode DriveTrain::getGear() {

}

bool DriveTrain::setGear(ShifterMode s) {

}

DriveTrain::update() {

}
