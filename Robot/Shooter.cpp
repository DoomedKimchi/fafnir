#include "Shooter.h"

Shooter::Shooter() 
    :    elevationEncoder((UINT32)PORT_SHOOTER_ENC_1_A, (UINT32)PORT_SHOOTER_ENC_1_B) 
    ,    motor1(PORT_SHOOTER_VIC_1)
    ,    motor2(PORT_SHOOTER_VIC_2)
    ,    motor3(PORT_SHOOTER_VIC_3)
    ,    motorElevation(PORT_SHOOTER_VIC_ELEVATION) {
    setElevation(30.0); // constructor that will set the elevation as 30 (default)
}

//Shooter:: Shooter(elevationY) {
//  setElevation(elevationY); // a constructor that will take an argument that will set the elevation of the shooter
//}
void Shooter::setElevation(float f) {
  //need code from WPILib to set the elevation of the shooter
} 

void Shooter::update() {
    
}
