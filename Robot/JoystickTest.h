#ifndef JOYSTICK_TEST_H
#define JOYSTICK_TEST_H

#include <WPILib.h>
#include "Constants.h"
#include "Robot.h"

/*! \brief Test the joysticks for debugging purposes
 *
 *
 * The robot uses Halo drive; one joystick controls the speed of the robot, another its turning, and a final joystick performs functions such as aiming and firing.
 */

class JoystickTest {
	private:
		/* joysticks */
		Joystick speedStick;
		Joystick turnStick;
		Joystick operatorStick;

		Robot *robot;

		bool buttShifterMode;
		bool shooting;
		float gain;

	public:
		JoystickTest(Robot *robot);

		void update();
};

#endif /* JOYSTICK_TEST */
