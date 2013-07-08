#ifndef AUTONOMOUS_CONTROLLER_H
#define AUTONOMOUS_CONTROLLER_H

#include "Robot.h"

/*! \brief Controller for the autonomous period
 *
 * Controls the robot during the autonomous period of the competition
 * Currently, it only fires frisbees at targets */

class AutonomousController {
	private:
		/*! A pointer to the Robot fafnir */
		Robot *robot;
		AutonomousMode mode;

		void drive(float v = 0.7);
		void stop();

		Timer timer;

		/*! \brief Tells the robot to fire
		 * \return Whether firing was successful */
		bool fire();
		void dump(float time);

		bool targetAligned;
		bool targetReached;

	public:
		void update();
		void startTimer();
		/*! \brief Constructs an autonomous controller with a pointer to fafnir
		 * \param *fafnir A pointer to the Robot */
		AutonomousController(Robot *robot, AutonomousMode m);

		/*! \brief Destructor */
		virtual ~AutonomousController();
};

#endif /* AUTONOMOUS_CONTROLLER_H */
