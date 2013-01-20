#include "WPILib.h"
#include "Robot.h"
#include "AutonomousController.h"
#include "DriverController.h"

class Fafnir : public IterativeRobot {
private:
    DriverStation driveStation;
    AutonomousController autoController;
    Robot robot;
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

Fafnir::Fafnir() {
    robot()
}

void Fafnir::AutonomousInit() {
    autoController(&robot);
}

void Fafnir::AutonomousPeriodic() {
    autoController.update();
}

void Fafnir::AutonomousDisabled() {
    delete autonomousController;
}

void Fafnir::TeleopInit() {
    driveStation(&robot);
}

void Fafnir::TeleopPeriodic() {
    driveStation.update();
}

void Fafnir::TeleopDisabled() {
    delete driveStation();
}

void Fafnir::TestInit() {
	
}

void Fafnir::TestPeriodic() {
    
}

void Fafnir::TestDisabled() {
    
}

START_ROBOT_CLASS(Fafnir);

