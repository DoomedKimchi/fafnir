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

  ,  gyro((UINT32)PORT_DRIVE_GYRO) {

  setMode(LOW_GEAR);
  leftEnc.SetDistancePerPulse(DRIVE_ENC_FEET_PER_PULSE);
  rightEnc.SetDistancePerPulse(DRIVE_ENC_FEET_PER_PULSE);
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

void DriveTrain::setShifterMode(ShifterMode m) {
  mode = m;
}

ShifterMode DriveTrain::getShifterMode() {
  return mode;
}

void DriveTrain::setShifterPosition(ShifterPosition p) {
  if(p == HIGH_GEAR) {
    engageHigh();
  }
  engageLow();
}

ShifterPosition DriveTrain::getShifterPosition() {
  if(!leftSol.Get()) {
    return HIGH_GEAR;
  }
  return LOW_GEAR;
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
    return true;
}

bool DriveTrain::driveS(double s) {
  //set target speed
  if (s > GEAR_UPSHIFT_CUTOFF) {
    engageHigh();
    
    return true;
  }
  else if (s < GEAR_DOWNSHIFT_CUTOFF) {
      engageLow();
  }
  targetSpeed = s;
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

void DriveTrain::update() {
  if(mode == AUTO) {
      if (getSpeed() > GEAR_UPSHIFT_CUTOFF) {
	  engageHigh();
      }
      else if (getSpeed() < GEAR_DOWNSHIFT_CUTOFF) {
	  engageLow();
      }
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

float DriveTrain::getSpeed() {
    return (leftEnc.GetRate() + rightEnc.GetRate())/2.0;
}
