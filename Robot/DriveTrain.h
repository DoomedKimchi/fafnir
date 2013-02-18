#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include <complex>
#include "Constants.h"
#include "WPILib.h"
#include "NumberPID.h"

/*! \brief Controls the robot's movement
 *
 * All driving commands on the robot, for both moving from one location to another, should take place through the DriveTrain. It will handle all movement events for the robot, apart from internal systems.
 * The gearing system will also be part of the drive train, so there will be four motors to drive the robot (two for each side) and two pneumatic arms to switch gears. */

class DriveTrain {
private:
	DriveState state;

  /* Current gear mode */
  ShifterMode mode;
  
  /* Solenoids */
  Solenoid leftSol;
  Solenoid rightSol;

  /* Encoders */  
  Encoder leftEnc;
  Encoder rightEnc;
  
  /* Speed controllers */
  Victor leftFrontVic;
  Victor leftBackVic;
  Victor rightFrontVic;
  Victor rightBackVic;

  /*! The robot's gyrometer */
  Gyro gyro;

  NumberPID distanceInput;
  NumberPID distanceOutput;
  PIDController distanceController;

  NumberPID speedInput;
  NumberPID speedOutput;
  // use outputcontainer as container
  PIDController speedController;
  
  NumberPID rotOutput;
  PIDController rotationController;

  int speed;
  int rotSpeed;

  float targetSpeed;
  float targetDist;
  Complex targetPoint;
  float targetAngle;
  float targetRotSpeed;

  bool engageHigh();
  bool engageLow();

public:
  DriveTrain();
  /*! Drive a distance
   * \remark This will override the target speed and target point; if target speed or point is set, this will unset it
   * \param dist The distance to drive
   * \return Whether setting target was successful */
  bool driveD(double dist);
  /*! Drive at a speed
   * \remark This will override the target distance and target point; if target distance or point is set, this will unset it
   * \param spd The speed at which to drive
   * \return Whether setting target was successful */
  bool driveS(double spd);
  /*! Drive to a point relative to the robot
   * \remark This will override the target distance and target speed; if target distance or speed is set, this will unset it
   * \param target The target to drive to, relative to the robot's current location
   * \return Whether setting target was successful */
  bool driveTo(Complex target);
  
  /*! Rotate an angle
   * \remark This will override the target rotational speed; if target rotational speed is set, this will unset it
   * \param angle The angle to turn
   * \return Whether setting target was successful */
  bool rotateA(double angle);
  /*! Rotate at a speed
   * \remark This will override the target angle; if target angle is set, this will unset it
   * \param rotSpd The speed at which to rotate
   * \return Whether setting target was successful */
  bool rotateS(double rotSpd);
  
  /*! Get the current shifter mode
   * \return the current mode of the shifter */
  ShifterMode getShifterMode();
  /*! Set the shifter mode
   * \param mode The new mode for the shifter
   * \return Whether setting the mode was successful */
  bool setShifterMode(ShifterMode m);
  ShifterPosition getShifterPosition();
  bool setShifterPosition(ShifterPosition p);

  float getSpeed();
  void setSpeed(float s);

  /*! Method that is constantly called by Robot */
  void update();
};

#endif /* DRIVE_TRAIN_H */
