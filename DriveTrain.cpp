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

ShifterMode DriveTrain::getMode() {
  return mode;
}

bool DriveTrain::setMode(ShifterMode s) {
  if(s == HIGH_GEAR) {
    engageHigh();
    mode = HIGH_GEAR;
  }
  else if (s == LOW_GEAR) {
    engageLow();
    mode = LOW_GEAR;
  }
  else if (s == AUTO) {
    mode = AUTO;
  }
}

void DriveTrain::update() {
  if(mode == AUTO) {
    //automatic shifting code
    //and stuff
  }
}
