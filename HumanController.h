#ifndef DRIVE_CONTROLLER_H
#define DRIVE_CONTROLLER_H

#include "WPILib.h"
#include "Constants.h"

/*! \brief Takes human control during the operator period
 *
 * Operates the robot while the field is in teleop mode, as well as determining which sequence of autonomous commands the autonomous mode should execute.
 * 
 * The robot uses Halo drive; one joystick controls the speed of the robot, another its turning, and a final joystick performs functions such as aiming and firing.
 */

class DriveController {
 private:
  /*! Speed joystick */
  Joystick speedStick;

  /*! Turn joystick */
  Joystick turnStick; 

  /*! Operator joystick */
  Joystick operatorStick;

 public:
  /*! \brief Method constantly called by Robot */
  bool update();
};

#endif /* DRIVE_CONTROLLER_H */
