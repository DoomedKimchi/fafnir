#include <WPILib.h>
#include "Robot.h"
#include "AutonomousController.h"
#include "HumanController.h"
#include "JoystickTest.h"

class Fafnir : public IterativeRobot {
private:
    HumanController humanController;
    AutonomousController autoController;
    JoystickTest joystickTest;
    Robot robot;
    AutonomousMode mode;
public:
    Fafnir();
    void AutonomousInit();
    void TeleopInit();
    void TestInit();

    void AutonomousPeriodic();
    void TeleopPeriodic();
    void TestPeriodic();

    void AutonomousDisabled();
    void TeleopDisabled();
    void TestDisabled();
};

Fafnir::Fafnir() 
    :    humanController(&robot) 
	,	 joystickTest(&robot)
    ,    autoController(&robot, mode)
    ,    robot() {

}

void Fafnir::AutonomousInit() {
    printf("AutoInit\n");
    autoController.startTimer();
}

void Fafnir::AutonomousPeriodic() {
    autoController.update();
    robot.update();
}

void Fafnir::AutonomousDisabled() {
    //delete autonomousController;
}

void Fafnir::TeleopInit() {
    robot.startCompressor();

    robot.setTeleop(true);
    //driveStation(&robot);
    //robot.shoot(); //Commented because we don't want the robot to shoot before the trigger is pressed
	//robot.setSpeed(0.5);
}

void Fafnir::TeleopPeriodic() {
    //float speed;
    humanController.update();
    //printf("Teleop Periodic called\n");
    robot.update();
}

void Fafnir::TeleopDisabled() {
    //delete driveStation();
}

void Fafnir::TestInit() {
	
}

void Fafnir::TestPeriodic() {
	joystickTest.update(); //uncomment this line to test joysticks
}

void Fafnir::TestDisabled() {
    
}

START_ROBOT_CLASS(Fafnir);

