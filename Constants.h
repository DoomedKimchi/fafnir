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

/* Solenoid definitions */
#define SOL_DRIVE_HIGH false
#define SOL_DRIVE_LOW true

enum ShifterMode { LOW_GEAR, HIGH_GEAR, AUTO };
enum AutonomousMode { DEFAULT, ALTERNATE_1, ALTERNATE_2 };

#endif /* CONSTANTS_H */

