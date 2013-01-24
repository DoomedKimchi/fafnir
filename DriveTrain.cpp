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

//driveDist and driveTo mostly for auto
bool DriveTrain::driveD(double d) {
  //set target distance  
  /* pseudo code
  *error = d - currentPosition
  PC_Dist.calculate()
  self.driveS(*output)
  
  // for drivetrain.h
  PIDController PC_Dist;
  
  // for constructor
  PC_Dist(1,0,.05,*error,*output,.05) // not sure if can give floats to the PIDController, constants need tuning (lots!)
  */
}

bool DriveTrain::driveS(double s) {
  //set target speed
  if (s > gearCutoff) {
    engageHigh();
    
    return true;
  }
  engageLow();
  
  return true;
  // Don't delete this unless you want to be a douche (but move it around as much as you want to)
  // Ok people, this is how we use a PID controller to set the speed! (by Nathan)
  // PID control may not actually be optimal for speed, we'll need to do real testing
  // Here goes
  // PID: Input : currentSpeed - setSpeed, Output : acceleration
  // acceleration NEEDS to be the output (90% sure)
  // we can't output motor power because as currentSpeed reaches setSpeed, then motor power will go to zero
  // acceleration needs to be added to motorpower every time unit (tick)
  // We shouldn't use I (Konstant) unless there is slipping (not sure about this)
  
  // for gears:
  // we need to find the ratios and multiply the ratio by motor power
  // thats all
  
  // I don't like /* and */
  
  /* pseudo code!
  // we may need to create a subclass of PIDSource just to hold a number (called outputNumberClass)
  // I'm not sure how to create a PID controller without a PIDSource class
  
  // for drivetrain.h
  PIDController PC_speed;
  
  // for constructor
  PC_speed(1,0,.05,encoderLeft, victorLeft, outputNumberClass, .05) // constructor is in the form (Kp,Ki,Kd,source,output,period)
  // getting the right constants and ratios could take a lot of time and not be worth it
  
  // this needs to be called every tick
  power = power + outPutNumberClass.value()
  Victor.setPower(power)
  
  */
  
}

bool DriveTrain::driveTo(double r, double theta) {
  //calculate polar coordinates (r, theta) then set values
  
  // Nathan's notes:
  // Steering_value = component_perpendicular_to_forward ( vector_to_target ).normalize.multiply(steering speed)
  // steering speed is important, should probably PID that
  // if you don't normalize and mult the value, then its basically a P controller
  
  //Craig W. Reynolds steering algorithm (expanded to seek behavior) take a look at a simple boids program to further understand
  //boids written by me! http://openprocessing.org/sketch/67395
  
  /* void seek(PVector target) {
    PVector desired = PVector.sub(target,location);
    desired.normalize();
    desired.mult(maxspeed);
    PVector steer = PVector.sub(desired,velocity);

    // Limit the magnitude of the steering force.
    steer.limit(maxforce);

    applyForce(steer);
  }
  */
  
  // HOWEVER, this method most likely won't work because we can't accuratrly keep track of our current position
  // we may just have to turn to the angle and drive forward
  // the craigs reynold thing is for a moving seek target (so its like a feedback controller)
}

bool DriveTrain::rotateD(double d) {
  //set target angle
}

bool DriveTrain::rotateS(double s) {
  //set target speed
}

void DriveTrain::update() {
  if(mode == AUTO) {
    //automatic shifting code
    //and stuff
  }
  //check encoders
  //and do stuff with them
  //and stuff
  
  //Drive Speed/Ang Speed
      //check dist since last tick
      //calc current speed
      //scale on a per wheel basis based on turn speed
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
