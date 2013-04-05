#include <WPILib.h>
#include "Robot.h"
#include "AutonomousController.h"
#include "HumanController.h"
#include "JoystickTest.h"
#include "server.h"

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

    // These 3 methods are not recognized by WPILib
    void AutonomousDisabled(); // the disable functions are not being called
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
    printf("Starting server\n");
    server_init(&robot);
    printf("Server is listening\n");
    server_begin_listening();
}

void Fafnir::AutonomousPeriodic() {
    autoController.update();
    //robot.update();
}

void Fafnir::AutonomousDisabled() {
    //delete autonomousController;
	printf("disabling autonomous\n");
	server_close();
}

void Fafnir::TeleopInit() {
    //robot.startCompressor();
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
    printf("Starting server\n");
    server_init(&robot);
    printf("Server is listening\n");
    server_begin_listening();
}

void Fafnir::TestPeriodic() {
	//joystickTest.update(); //uncomment this line to test joysticks
}

void Fafnir::TestDisabled() {
    
}

START_ROBOT_CLASS(Fafnir);

