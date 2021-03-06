#include <WPILib.h>
#include "Robot.h"
#include "AutonomousController.h"
#include "HumanController.h"
#include "JoystickTest.h"

class Fafnir : public IterativeRobot {
	private:
		HumanController humanController;
		JoystickTest joystickTest;
		AutonomousMode mode;
		AutonomousController autoController;
		Robot robot;
	public:
		Fafnir();

		/* Only these methods are supported by the IterativeRobot class in WPILib
		   See: http://www.virtualroadside.com/WPILib/class_iterative_robot.html/
		   as well as the WPILib source.
		*/
		void RobotInit();
		// Disabled is simply another mode like Teleop and Autonomous, and has an Init and a Periodic function
		void DisabledInit();
		void AutonomousInit();
		void TeleopInit();
		void TestInit();

		void DisabledPeriodic();
		void AutonomousPeriodic();
		void TeleopPeriodic();
		void TestPeriodic();
};

Fafnir::Fafnir() :
	humanController(&robot),
	joystickTest(&robot),
	mode(DEFAULT),
	autoController(&robot, mode),
	robot()
{
}

void Fafnir::RobotInit() {
	printf("Robot initializing\n");
	// Check motors/sensors
	// Ping the RPi
}

void Fafnir::DisabledInit() {
	printf("Entering disabled mode\n");
	// Spin down all motors
	// Halt network communications
	// Deconstruct robot classes?
}

void Fafnir::AutonomousInit() {
	printf("Starting Autonomous mode\n");
	autoController.startTimer();
}

void Fafnir::TeleopInit() {
	printf("Starting Teleop mode\n");
	//robot.startCompressor();
}

void Fafnir::TestInit() {
	printf("Starting Test mode\n");
}

void Fafnir::DisabledPeriodic() {
	// Flash the fancy lights and stuff
}

void Fafnir::AutonomousPeriodic() {
	autoController.update();
	robot.update();
}

void Fafnir::TeleopPeriodic() {
	humanController.update();
	robot.update();
}

void Fafnir::TestPeriodic() {
	//joystickTest.update(); //uncomment this line to test joysticks
}

START_ROBOT_CLASS(Fafnir);
