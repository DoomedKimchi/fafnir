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
  int getAutonomousMode();
  //Joystick already has methods for these
  int getStickX(); // can we pass the joystick inside?
  int getStickY();

  void update();
};

#endif /* DRIVER_STATION_H */
