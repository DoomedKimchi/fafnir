#include "DriveTrain.h"

DriveTrain::DriveTrain() 
  :  leftSol(PORT_DRIVE_SOL_1)
  ,  rightSol(PORT_DRIVE_SOL_2)

  ,  leftEnc((UINT32)PORT_DRIVE_ENC_1_A, (UINT32)PORT_DRIVE_ENC_1_B)
  ,  rightEnc((UINT32)PORT_DRIVE_ENC_2_A, (UINT32)PORT_DRIVE_ENC_2_B)

  ,  leftFrontVic(PORT_DRIVE_VIC_1)
  ,  leftBackVic(PORT_DRIVE_VIC_2)
  ,  rightFrontVic(PORT_DRIVE_VIC_3)
  ,  rightBackVic(PORT_DRIVE_VIC_4) 

  ,  gyro((UINT32)PORT_DRIVE_GYRO)
  ,  distanceController(3.0f,0.0f,-1.0f,&distanceInput,&outputContainer)
  ,  distanceInput()
  ,  outputContainer()
  ,  speedController(3.0f,0.0f,-1.0f,&speedInput,&outputContainer)
  ,  speedInput() {

    setShifterMode(AUTO);
  setShifterPosition(LOW_GEAR);
  leftEnc.SetDistancePerPulse(DRIVE_ENC_FEET_PER_PULSE);
  rightEnc.SetDistancePerPulse(DRIVE_ENC_FEET_PER_PULSE);
  leftEnc.Start();
  rightEnc.Start();
}

bool DriveTrain::engageHigh() {
  leftSol.Set(SOL_DRIVE_HIGH);
  rightSol.Set(SOL_DRIVE_HIGH);
  return true;
}

bool DriveTrain::engageLow() {
  leftSol.Set(SOL_DRIVE_LOW);
  rightSol.Set(SOL_DRIVE_LOW);
  return true;
}

bool DriveTrain::setShifterMode(ShifterMode m) {
  mode = m;
  return true;
}

ShifterMode DriveTrain::getShifterMode() {
  return mode;
}

bool DriveTrain::setShifterPosition(ShifterPosition p) {
  if(p == HIGH_GEAR) {
    engageHigh();
  }
  engageLow();
  return true;
}

ShifterPosition DriveTrain::getShifterPosition() {
  if(!leftSol.Get()) {
    return HIGH_GEAR;
  }
  return LOW_GEAR;
}

//driveDist and driveTo mostly for auto
bool DriveTrain::driveD(double d) { // tolerence is currently .01
  //set target distance  
  targetDist = d;
  leftEnc.Reset();
  leftEnc.Start();
  rightEnc.Reset();
  rightEnc.Start();

  return false;
}

bool DriveTrain::driveS(double s) {
  //set target speed
  targetSpeed = s;
  return true;
  // PID control may not actually be optimal for speed, we'll need to do real testing
  // acceleration NEEDS to be the output (90% sure)
  // we can't output motor power because as currentSpeed reaches setSpeed, then motor power will go to zero
  // acceleration needs to be added to motorpower every time unit (tick)
  // We shouldn't use I (Konstant) unless there is slipping (not sure about this)
}

bool DriveTrain::driveTo(Complex target) {
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
    return true;
}

bool DriveTrain::rotateA(double a) {
    targetAngle = a;
    return true;
  //set target angle
}

bool DriveTrain::rotateS(double s) {
    targetRotSpeed = s;
    return true;
    //this method may never get used in this form
  //set target speed
}

float DriveTrain::getSpeed() {
    return (leftEnc.GetRate() + rightEnc.GetRate())/2.0;
}

void DriveTrain::setSpeed(float s) {
  // make motors turn, -2^15 < s < 2^15
}

void DriveTrain::update() {
  if(mode == AUTO) {
      if (getSpeed() > GEAR_UPSHIFT_CUTOFF) {
	  engageHigh();
      }
      else if (getSpeed() < GEAR_DOWNSHIFT_CUTOFF) {
	  engageLow();
      }
  }

  /* dist PID */
  float progress = leftEnc.GetDistance(); // what about turning?

  distanceInput.PIDWrite(targetDist - progress); // progree
  if (distanceInput.PIDGet() <= .01) {
    targetSpeed = 0; // within tolerence
  }
  else {
      targetSpeed = distanceController.Get();
  }

  //check encoders
  //and do stuff with them
  //and stuff
  leftFrontVic.Set(targetSpeed+targetRotSpeed);
  leftBackVic.Set(targetSpeed+targetRotSpeed);
  rightFrontVic.Set(targetSpeed-targetRotSpeed);
  rightBackVic.Set(targetSpeed-targetRotSpeed);

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
