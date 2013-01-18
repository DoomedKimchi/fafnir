#ifndef ROBOT_H
#define ROBOT_H

#include "WPILib.h"
#include "Constants.h"
#include "Accumulator.h"
#include "AutonomousController.h"
#include "DriverStation.h"
#include "Shooter.h"

class Robot {
private:
   DriverStation driverStation;
   Shooter shooter;
   AutonomousController autonomousController;
   Accumulator accumulator;
   AxisCamera &camera;
public:
   Robot();
   void drive(float speed); //drive forward at speed
   void drive(float speed, float speed); // left, right motor set speeds
   void drive(float speed, float curvature); // drive at speed and curvature
   void accumulate(); // take care of sensing?
   void shoot(); // just shoot, no aiming
   void aim(float yaw, float elevation); // angle to aim
   void aim(); // aim using the camera
   void climb();
};
#endif /* ROBOT_H */
