/*
 * Drivetrain class
 * It's the drive train, what do you think it does?
 * Are you seriously still reading this?
 */

DriveTrain::DriveTrain() {
  leftSol(PORT_DRIVE_SOL_1);
  rightSol(PORT_DRIVE_SOL_2);

  leftFrontEnc(PORT_DRIVE_ENC_1);
  leftBackEnc(PORT_DRIVE_ENC_2);
  rightFrontEnc(PORT_DRIVE_ENC_3);
  rightBackEnc(PORT_DRIVE_ENC_4);

  leftFrontVic(PORT_DRIVE_VIC_1);
  leftBackVic(PORT_DRIVE_VIC_2);
  rightFrontVic(PORT_DRIVE_VIC_3);
  rightBackVic(PORT_DRIVE_VIC_4);

  setMode(LOW_GEAR);
}

bool DriveTrain::engageHigh() {
  leftSol.set(SOL_DRIVE_HIGH);
  rightSol.set(SOL_DRIVE_HIGH);
}

bool DriveTrain::engageLow() {
  leftSol.set(SOL_DRIVE_LOW);
  rightSol.set(SOL_DRIVE_LOW);
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
    //set target speed
}

bool DriveTrain::driveDist(double d) {
    //set target distance
}

bool DriveTrain::driveTo(double d1, double d2) {
    //calculate polar coordinates (r, theta) then set values
}

bool DriveTrain::rotate(double d) {
    //set target angle
}

void DriveTrain::update() {
  if(mode == AUTO) {
    //automatic shifting code
    //and stuff
  }
  //check encoders
  //and do stuff with them
  //and stuff

  //Drive Speed
      //check dist since last tick
      //calc current speed
      //PID loop it up
  //Drive Dist
      //check target vs actual distance
      //PID loop
  //Turn
      //check current angle with gyro vs target angle
      //PID

  //ISSUES
      //angle and speed can be absolute, distance cannot (reliably)
}
