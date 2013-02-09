#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"
#include "Constants.h"
#include "NumberPID.h"

class Shooter {
private:
   Encoder elevationEncoder;
   Encoder speedEncoder;
   
   Victor motor1; //this is the first motor that spins the wheel to propel the frisbee
   Victor motor2; // this is the second motor that spins the wheel to propel the frisbee
   Victor motor3; //this is the third motor that spins the wheel to propel the frisbee  
   Victor motorElevation; //this is the third motor that will elevate the shooting mechanism of the robot. 
   
   PIDController elevationController;
   
   Solenoid sol1;
   Solenoid sol2;

   void setSpinSpeed(float sp);

public:
   Shooter();
   void setElevation(float angle); // set elevation 
   NumberPID elevationError; // elevation error, ie if target = 60 and elevation = 45, error = 15
   NumberPID outputFiller; // pointless object that PIDController needs, hence 'filler'
   float elevationTarget; // goal elevation, ie 60 degrees
   float motorPower; // how much to set the victor (PWM)
   void shoot();
   void update();
};

#endif /* SHOOTER_H */
