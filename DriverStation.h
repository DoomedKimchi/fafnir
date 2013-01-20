#ifndef DRIVER_STATION_H
#define DRIVER_STATION_H

#include "WPILib.h"

class DriverStation {
private:
   Joystick speedStick;
   Joystick turnStick; 
   Joystick operatorStick;

   AutonomousMode mode;
public:
  int getAutoType(); // we can set different autonomous starting places or procedures
  int getStickX(); // can we pass the joystick inside?
  int getStickY();

  void update();
};

#endif /* DRIVER_STATION_H */
