#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Encoder feet per pulse */
#define DRIVE_ENC_FEET_PER_PULSE 0.0
#define SHOOTER_ENC_FEET_PER_PULSE 0.0
#define SHOOTER_DEG_PER_PULSE 0.0

/* Speed cutoffs for shifting gears */
#define GEAR_UPSHIFT_CUTOFF 6.0
#define GEAR_DOWNSHIFT_CUTOFF 4.0

/* Solenoid drive ports */
#define PORT_DRIVE_SOL_1 0
#define PORT_DRIVE_SOL_2 0

/* Solenoid shooter ports */
#define PORT_SHOOTER_SOL_1 0
#define PORT_SHOOTER_SOL_2 0
#define PORT_SHOOTER_SOL_SHOOT 2
#define PORT_SHOOTER_SOL_REC 1

#define PORT_ACC_SWITCH 0

/* Accumulator Victor port */
#define PORT_ACC_VIC_1 0

/* Accumulator Servo Angles */
#define SERVO_ANGLE_UP 90
#define SERVO_ANGLE_DOWN 0

/* Accumulator Servo Port */
#define PORT_ACC_SERVO 0

/* Encoder drive pots */
#define PORT_DRIVE_ENC_1_A 0
#define PORT_DRIVE_ENC_1_B 0
#define PORT_DRIVE_ENC_2_A 0
#define PORT_DRIVE_ENC_2_B 0

/* Gyro port for drive train */
#define PORT_DRIVE_GYRO 1

/* Drive train Victor ports */
#define PORT_DRIVE_VIC_1 5
#define PORT_DRIVE_VIC_2 10
#define PORT_DRIVE_VIC_3 2
#define PORT_DRIVE_VIC_4 1

/* Motor ports */
#define PORT_PWM_1 0
#define PORT_PWM_2 0

/* Joystick ports */
#define PORT_JS_SPEED 1
#define PORT_JS_TURN 2
#define PORT_JS_OPERATOR 3

/* Speed joystick button and axis IDs */
#define JS_SPEED_TRIGGER 0
#define JS_SPEED_2 1
#define JS_SPEED_3 2
#define JS_SPEED_4 3
#define JS_SPEED_5 4
#define JS_SPEED_6 5
#define JS_SPEED_7 6
#define JS_SPEED_8 7
#define JS_SPEED_9 8
#define JS_SPEED_10 9
#define JS_SPEED_11 10
#define JS_SPEED_X 0
#define JS_SPEED_Y 1
#define JS_SPEED_Z 2

/* Turn joystick button and axis IDs */
#define JS_TURN_TRIGGER 0
#define JS_TURN_MODE_TOGGLE 1
#define JS_TURN_POSITION_LOW 2
#define JS_TURN_4 3
#define JS_TURN_POSITION_HIGH 4
#define JS_TURN_6 5
#define JS_TURN_7 6
#define JS_TURN_8 7
#define JS_TURN_9 8
#define JS_TURN_10 9
#define JS_TURN_11 10
#define JS_TURN_X 0
#define JS_TURN_Y 1
#define JS_TURN_Z 2

/* Operator joystick button and axis IDs */
#define JS_OPERATOR_TRIGGER 0 //This is now obsolete because we are using GetTrigger instead of GetRawButton
#define JS_OPERATOR_2 1
#define JS_OPERATOR_3 2
#define JS_OPERATOR_4 3
#define JS_OPERATOR_5 4
#define JS_OPERATOR_6 5
#define JS_OPERATOR_7 6
#define JS_OPERATOR_8 7
#define JS_OPERATOR_9 8
#define JS_OPERATOR_10 9
#define JS_OPERATOR_11 10
#define JS_OPERATOR_X 0
#define JS_OPERATOR_Y 1
#define JS_OPERATOR_GAIN 2

/* Solenoid drive modes */
#define SOL_DRIVE_HIGH false
#define SOL_DRIVE_LOW true

/* Shifter cutoffs */
#define SHIFT_CUTOFF_UP 5.5
#define SHIFT_CUTOFF_DOWN 4.5

/* Compressor spike port */
#define PORT_COMPRESSOR_SPIKE 3

/* Pressure cutoff port */
#define PORT_PRESSURE_CUTOFF 3

/* Shooter encoder ports */
#define PORT_SHOOTER_ENC_1_A 0
#define PORT_SHOOTER_ENC_1_B 0

#define PORT_SHOOTER_ENC_2_A 0
#define PORT_SHOOTER_ENC_2_B 0

/* Shooter victor ports */
/* There are only 4 speed controllers
 * on the testing robot, so I re-used
 * the left-side victors from the
 * Drive Train.
 */
//#define PORT_SHOOTER_VIC_1 4
#define PORT_SHOOTER_VIC_1 5
//#define PORT_SHOOTER_VIC_2 9
#define PORT_SHOOTER_VIC_2 10
#define PORT_SHOOTER_VIC_ELEVATION 8

/* Shooter timing constants */
#define SHOOT_PRIMING_WAIT 5.0
#define SHOOT_SHOOTING_WAIT 5.0
#define SHOOT_RECOVERING_WAIT 5.0
#define SHOOT_SPINUP_WAIT 5.0

/* Shooter minimum speed to shoot */
#define SHOOT_SPEED 0.0

/* Types of gear modes for the drive train */
enum ShifterMode { MANUAL, AUTO };

enum ShifterPosition { LOW_GEAR, HIGH_GEAR };

/* Types of autonomous modes */
enum AutonomousMode { DEFAULT, ALTERNATE_1, ALTERNATE_2 };

enum ShooterState { LOADED, PRIMED, SHOOTING, RECOVERING, EMPTY, AIMING };

enum AccumulatorState { SHOOTER_EMPTY, SHOOTER_LOADED, LOADING };

enum DriveState { DRIVE_DISTANCE, DRIVE_SPEED };

#endif /* CONSTANTS_H */

