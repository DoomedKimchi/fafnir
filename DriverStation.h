#ifndef DRIVER_STATION_H
#define DRIVER_STATION_H

#include "WPILib.h"

class DriverStation {
private:
	Joystick leftStick;
	Joystick rightStick;
	// buttons and things
public:
  void update();
  int getAutoType(); // we can set different autonomous starting places or procedures
  int getStickX(Joystick stick); // pass in which joystick to get
  int getStickY(Joystick stick); // pass in which joystick to get
};

#endif /* DRIVER_STATION_H */
