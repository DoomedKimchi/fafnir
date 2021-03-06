#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include <WPILib.h>
#include "Constants.h"
#include "LimitSwitch.h"

/*! \brief Controls frisbee accumulation
 *
 * This is the part of the robot responsible for picking up Frisbees and getting them into the robot. In its most basic form, it consists of one motor that will run a series of rollers and belts that will intake the discs.
 * Depending on feasibility, this will also feature an arm to flip upside down Frisbees before they go into the robot. */

class Accumulator {
	private:
		/*! The state of the Accumulator */
		AccumulatorState state;
		/*! The motor that controls the accumulator */
		Victor motor;
		//pneumatic arm for flipping
		//beam sensor for frisbee?
		LimitSwitch frisbeeSwitch;
		Servo servo;

		bool accumulating;

		bool shooting;

	public:
		/*!\brief Start the motor
		 * \pre The motor is not running
		 * \return Whether the motor has been started */
		bool start();

		/*! \brief Kill the motor
		 * \pre The motor is running
		 * \return Whether the motor has been stopped */
		bool kill();

		bool autoAccumulate();

		/*!\brief The method that is continually called by Robot
		 * \param accumulate Whether autoAccumulate() should be called
		 * \return Whether update succeeded */
		void update();
		void shootVacated();

		void setState(AccumulatorState nstate);
		/*! \brief Constructor */
		Accumulator();

		/*! \brief Destructor */
		virtual ~Accumulator();
};

#endif /* ACCUMULATOR_H */
