#include "Shooter.h"

Shooter::Shooter() :
	//elevationEncoder((UINT32)PORT_SHOOTER_ENC_1_A, (UINT32)PORT_SHOOTER_ENC_1_B)
	//,    speedEncoder((UINT32)PORT_SHOOTER_ENC_2_A, (UINT32)PORT_SHOOTER_ENC_2_B)
	motor1(PORT_SHOOTER_VIC_1),
	motor2(PORT_SHOOTER_VIC_2),
	motorElevation(PORT_SHOOTER_VIC_ELEVATION),
	//    ,    sol1(PORT_SHOOTER_SOL_1)
	//    ,    sol2(PORT_SHOOTER_SOL_2)
	solShoot(PORT_SHOOTER_SOL_SHOOT),
	solRecover(PORT_SHOOTER_SOL_REC)
	//,    elevationController(3.0f, 0.0f, -1.0f, &elevationError, &outputFiller) { // 3,0,-1 are pid constants
{
	state = LOADED;
	shootRequested = 0;
	//setElevation(30.0); // constructor that will set the elevation as 30 (default)

	//elevationEncoder.SetDistancePerPulse(SHOOTER_DEG_PER_PULSE);
	//speedEncoder.SetDistancePerPulse(SHOOTER_ENC_FEET_PER_PULSE);

	//motorPower = 0;
	//elevationError.PIDWrite(0.0);

}

void Shooter::elevationSpeed(float speed) {
	elevSpeed = speed;
}

//Shooter:: Shooter(elevationY) {
//  setElevation(elevationY); // a constructor that will take an argument that will set the elevation of the shooter
//}
void Shooter::setElevation(float f) {
	// sets target elevation
	elevationTarget = f;
}

void Shooter::setSpinSpeed(float sp) {
	printf("SpinSpeed set to: %f", sp);
	motor1.Set(sp);
	motor2.Set(sp);
}

void Shooter::shoot() {
	shootRequested = 1;
	printf("A shot has been requested by the operator\n");
	//float sp = 0.2;
	//motor1.Set(sp);
	//motor2.Set(sp);
	//    state = SHOOTING;
}

void Shooter::manualShoot(float sp) {
	targetSpeed = sp;
}

void Shooter::update() {
	//setSpinSpeed(1.0);
	motorElevation.Set(elevSpeed);

	/*
	setSpinSpeed(0.0);
	if (shootRequested) {
		//setSpinSpeed(1.0); // is 100 a reasonable value?
		// push frisbee into shooter
		printf("Shots requested: %d\n", shootRequested);
		//printf("shoot requested... spinning up\n");
		//sol1.Set(true);
		//sol2.Set(true);
		//shootTimer.Start();
		shootRequested = 0;
		shootTimer.Start();
		//solShoot.Set(false);
		//solRecover.Set(true);
		setSpinSpeed(SHOOT_SPEED);
		state = PRIMED;
	}
	*/

	/* Manual shooter control */
	setSpinSpeed(targetSpeed);

	/*switch(state) {
	  case LOADED:
	  setSpinSpeed(0.0);
	  if (shootRequested) {
	  //setSpinSpeed(1.0); // is 100 a reasonable value?
	  // push frisbee into shooter
	  printf("shoot requested... spinning up\n");
	  //sol1.Set(true);
	  //sol2.Set(true);
	  //shootTimer.Start();
	  //shootRequested--;
	  shootRequested = 0;
	  shootTimer.Start();
	  solShoot.Set(false);
	  solRecover.Set(true);
	  setSpinSpeed(-0.5);
	  state = PRIMED;
	  }

	  break;
	  case AIMING:
	  //	elevationError.PIDWrite(elevationEncoder.GetDistance() - elevationTarget);
	  // note that just because we updated the error doesn't mean the output
	  // changed b/c the PID loop updates in its own loop
	  //motorPower = elevationController.Get();
	  //motorElevation.Set(motorPower); //not sure what the write set pwoer method is
	  break;
	  case PRIMED:
	  setSpinSpeed(-0.5);
	  printf("primed... waiting to shoot %.3f\n", SHOOT_SPINUP_WAIT-shootTimer.Get());
	  if (shootTimer.HasPeriodPassed(SHOOT_SPINUP_WAIT)) {
	  //if (speedEncoder.GetRate() < SHOOT_SPEED) {
	  solShoot.Set(true);
	  //solRecover.Set(false);
	  shootTimer.Reset();
	  //}
	  printf("spun up! shooting...\n");
	  state = SHOOTING;
	  }
	  break;
	  case SHOOTING:
	  setSpinSpeed(-0.5);
	  if (shootTimer.HasPeriodPassed(SHOOT_SHOOTING_WAIT)) {
	  //sol1.Set(false);
	  //sol2.Set(false);
	  solShoot.Set(true);
	  solRecover.Set(false);
	  shootTimer.Reset();
	  state = RECOVERING;
	  }
	  break;
	  case RECOVERING:
	  setSpinSpeed(0.0);
	  if (shootTimer.HasPeriodPassed(SHOOT_RECOVERING_WAIT)) {
	  state = LOADED;
	  shootTimer.Reset();
	  shootTimer.Stop();
	  }
	  break;
	  case EMPTY:
	  break;
	  default:
	  break;
	  }*/
}

ShooterState Shooter::getState() {
	return state;
}
