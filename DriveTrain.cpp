/*
 * Drivetrain class
 * It's the drive train, what do you think it does?
 * Are you seriously still reading this?
 */

DriveTrain::DriveTrain() {
  leftSol(PORT_SOL_LEFT);
  rightSol(PORT_SOL_RIGHT);

  leftFrontEnc(PORT_ENC_1);
  leftBackEnc(PORT_ENC_2);
  rightFrontEnc(PORT_ENC_3);
  rightBackEnc(PORT_ENC_4);

  leftFrontVic(PORT_VIC_1);
  leftBackVic(PORT_VIC_2);
  rightFrontVic(PORT_VIC_3);
  rightBackVic(PORT_VIC_4);

  setMode(LOW_GEAR);
}

bool DriveTrain::engageHigh() {
  leftSol.set(HIGH_GEAR);
  rightSol.set(HIGH_GEAR);
}

bool DriveTrain::engageLow() {
  leftSol.set(LOW_GEAR);
  rightSol.set(LOW_GEAR);
}

bool DriveTrain::setMode(ShifterMode s) {
  switch (s) {
  case HIGH_GEAR: 
    engageHigh();
    mode = HIGH_GEAR;
    break;
  case LOW_GEAR:
    engageLow();
    mode = LOW_GEAR;
    break;
  case AUTO:
    mode = AUTO;
    break;
  default:
    break;
  }
}

ShifterMode DriveTrain::getMode() {
  return mode;
}

bool DriveTrain::driveSpd(double d) {
  
}

bool DriveTrain::driveDist(double d) {

}

bool DriveTrain::driveTo(double d1, double d2) {

}

bool DriveTrain::rotate(double d) {

}

void DriveTrain::update() {
  if(mode == AUTO) {
    //automatic shifting code
    //and stuff
  }
}
