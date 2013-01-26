
DriveController::DriveController()
    :    speedStick(PORT_JOYSTICK_SPEED)
    ,    turnStick(PORT_JOYSTICK_TURN)
    ,    operatorStick(PORT_JOYSTICK_OPERATOR) {

}

AutonomousMode DriveController::getAutonomousMode() {

}

int DriveController::getStickX() {

}

int DriveController::getStickY() {

}

void DriveController::update() {
    //check current state of joysticks
    //calculate what to do based on joysticks and robot state (e.g. drive speed for certain gear)
    //gear ranges should look something like:
        //low gear: 0 ft/sec – 5.5 ft/sec
        //high gear: 5 ft/sec – max speed (probably 16 ft/sec)
}
