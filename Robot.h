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
  DriveTrain driveTrain;
  Accumulator accumulator;
  Shooter shooter;
  AxisCamera &camera;

  
public:
  Robot();
  void accumulate(); // take care of sensing?
  void shoot(); // just shoot, no aiming
  void aim(float yaw, float elevation); // angle to aim
  void aim(); // aim using the camera
  void climb();
};
#endif /* ROBOT_H */
