#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Solenoid port numbering */
#define PORT_DRIVE_SOL_1 0
#define PORT_DRIVE_SOL_2 0

/* Encoder port numbering */
#define PORT_DRIVE_ENC_1 0
#define PORT_DRIVE_ENC_2 0
#define PORT_DRIVE_ENC_3 0
#define PORT_DRIVE_ENC_4 0

/* DriveTrain Victor port numbering */
#define PORT_DRIVE_VIC_1 0
#define PORT_DRIVE_VIC_2 0
#define PORT_DRIVE_VIC_3 0
#define PORT_DRIVE_VIC_4 0

/* Joystick port numbering */
#define PORT_JOYSTICK_SPEED 0
#define PORT_JOYSTICK_TURN 0
#define PORT_JOYSTICK_OPERATOR 0

/* Speed joystick button and axis numbering */
#define BUTT_JOYSTICK_SPEED_TRIGGER 0
#define BUTT_JOYSTICK_SPEED_2 1
#define BUTT_JOYSTICK_SPEED_3 2
#define BUTT_JOYSTICK_SPEED_4 3
#define BUTT_JOYSTICK_SPEED_5 4
#define BUTT_JOYSTICK_SPEED_6 5
#define BUTT_JOYSTICK_SPEED_7 6
#define BUTT_JOYSTICK_SPEED_8 7
#define BUTT_JOYSTICK_SPEED_9 8
#define BUTT_JOYSTICK_SPEED_10 9
#define BUTT_JOYSTICK_SPEED_11 10

/* Turn joystick button and axis numbering */
#define BUTT_JOYSTICK_TURN_TRIGGER 0
#define BUTT_JOYSTICK_TURN_2 1
#define BUTT_JOYSTICK_TURN_3 2
#define BUTT_JOYSTICK_TURN_4 3
#define BUTT_JOYSTICK_TURN_5 4
#define BUTT_JOYSTICK_TURN_6 5
#define BUTT_JOYSTICK_TURN_7 6
#define BUTT_JOYSTICK_TURN_8 7
#define BUTT_JOYSTICK_TURN_9 8
#define BUTT_JOYSTICK_TURN_10 9
#define BUTT_JOYSTICK_TURN_11 10

/* Operator joystick button and axis numbering */
#define BUTT_JOYSTICK_OPERATOR_TRIGGER 0
#define BUTT_JOYSTICK_OPERATOR_2 1
#define BUTT_JOYSTICK_OPERATOR_3 2
#define BUTT_JOYSTICK_OPERATOR_4 3
#define BUTT_JOYSTICK_OPERATOR_5 4
#define BUTT_JOYSTICK_OPERATOR_6 5
#define BUTT_JOYSTICK_OPERATOR_7 6
#define BUTT_JOYSTICK_OPERATOR_8 7
#define BUTT_JOYSTICK_OPERATOR_9 8
#define BUTT_JOYSTICK_OPERATOR_10 9
#define BUTT_JOYSTICK_OPERATOR_11 10

/* Solenoid definitions */
#define SOL_DRIVE_HIGH false
#define SOL_DRIVE_LOW true

enum ShifterMode { LOW_GEAR, HIGH_GEAR, AUTO };
enum AutonomousMode { DEFAULT, ALTERNATE_1, ALTERNATE_2 };

#endif /* CONSTANTS_H */

