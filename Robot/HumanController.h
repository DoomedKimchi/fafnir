#ifndef HUMAN_CONTROLLER_H
#define HUMAN_CONTROLLER_H

#include <WPILib.h>
#include "Constants.h"
#include "Robot.h"

/*! \brief Takes human control during the operator period
 *
 * Operates the robot while the field is in teleop mode, as well as determ
ining which sequence of autonomous commands the autonomous mode should execute.
 * 
 * The robot uses Halo drive; one joystick controls the speed of the robot, another its turning, and a final joystick performs functions such as aiming and firing.
 */

class HumanController {
 private:
  /* joysticks */
  Joystick speedStick;
  Joystick turnStick; 
  Joystick operatorStick;

  Robot *robot;

  bool buttShifterMode;
  bool shooting;
  int gain;
  
 public:
  AutonomousMode getAutonomousMode();
  HumanController(Robot *robot);

  void update();
};

#endif /* HUMAN_CONTROLLER_H */
