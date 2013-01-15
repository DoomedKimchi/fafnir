#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

/*
 * Drivetrain class
 * It's the drive train, what do you think it does?
 * Are you seriously still reading this?
 */

class DriveTrain {
private:
  bool low_gear;
  bool automatic;
  Encoder enc_left_front;
  Encoder enc_left_back;
  Encoder enc_right_front;
  Encoder enc_right_back;

public:
  void drive(int); //straight forward or straight backward
  void drive(int,int); //control speeds of left/right
  void drive(int,int,int,int) //control each motor
  void rotate(int, int); //parameters: rotate angle, rotate speed

  bool getGear();
  void setGear(bool);

  void startAuto();
  void endAuto();
  void isAuto();
  void periodicAuto();
};

#endif /* DRIVE_TRAIN_H *?
