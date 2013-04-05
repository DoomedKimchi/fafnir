#include "Robot.h"

Robot::Robot() 
    :   
/*camera (AxisCamera::GetInstance()) 
	 ,  */compressor(PORT_PRESSURE_CUTOFF, PORT_COMPRESSOR_SPIKE) {
	message = (char *)malloc(sizeof(char)*BUFFSIZE);
	messageStatus = 0;
    //printf("allocated compressor relay port on spike %d\n and cutoff at %d\n", PORT_COMPRESSOR_SPIKE, PORT_PRESSURE_CUTOFF);
}

void Robot::aim(float yaw, float elevation) {

}

void Robot::startCompressor() {
    compressor.Start();
    printf("compressor started\n");
}

void Robot::aim() {

}

void Robot::shoot() {
  shooter.shoot();
  //accumulator.shootVacated();
}

void Robot::dump(float s) {
	dumper.dump(s);
}

void Robot::autoDump() {
	dumper.autoDump();
}

void Robot::elevationSpeed(float s) {
    shooter.elevationSpeed(s);
}

void Robot::climb() {

}

void Robot::receiveMessage(char *msg) {
  //*message = *msg;
  messageStatus = 1;
}

ShifterMode Robot::getShifterMode() {
  return driveTrain.getShifterMode();
}

bool Robot::setShifterMode(ShifterMode mode) {
  return driveTrain.setShifterMode(mode);
}

ShifterPosition Robot::getShifterPosition() {
  return driveTrain.getShifterPosition();
}

bool Robot::setShifterPosition(ShifterPosition pos) {
  return driveTrain.setShifterPosition(pos);
}

ShooterState Robot::getShooterState() {
  //return shooter.getState();
  return LOADED;
}

void Robot::setSpeed(float s) {
  driveTrain.driveS(s);
}

void Robot::rotateSpeed(float s) {

    driveTrain.rotateS(s);
}

void Robot::setAccumulatorSpeed(float s){
}

bool Robot::autoAccumulate(){
}

void Robot::update() {
  //if(message != NULL) {
	if(0) {
    printf("Message from pi:\n");
    printf("%s\n", message);
  }
	if (messageStatus)
		printf("Message success!");
  //printf("setting drive speed to 0.5\n");
  //driveTrain.driveS(0.5);
  driveTrain.update(); //update has to be after setting the speed
  //accumulator.update();
  //shooter.update();
  dumper.update();
}

void Robot::shootVacated() {
}

void Robot::setAccumulatorState(AccumulatorState nstate) {
}


 
