#include "WPILib.h"
#include "Robot.h"
#include "AutonomousController.h"
#include "HumanController.h"

class Fafnir : public IterativeRobot {
private:
    HumanController humanController;
    AutonomousController autoController;
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
    ,    autoController(&robot, mode)
    ,    robot() {

}

void Fafnir::AutonomousInit() {
    printf("AutoInit\n");
}

void Fafnir::AutonomousPeriodic() {
    autoController.update();
    robot.update();
}

void Fafnir::AutonomousDisabled() {
    //delete autonomousController;
}

void Fafnir::TeleopInit() {
    //driveStation(&robot);
	//robot.setSpeed(0.5);
}

void Fafnir::TeleopPeriodic() {
    //humanController.update();
    robot.update();
}

void Fafnir::TeleopDisabled() {
    //delete driveStation();
}

void Fafnir::TestInit() {
	
}

void Fafnir::TestPeriodic() {
    
}

void Fafnir::TestDisabled() {
    
}

START_ROBOT_CLASS(Fafnir);

