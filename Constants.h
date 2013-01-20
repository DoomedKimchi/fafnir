#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Solenoid port numbering */
#define PORT_DRIVE_SOL_1 1
#define PORT_DRIVE_SOL_2 2

/* Encoder port numbering */
#define PORT_DRIVE_ENC_1 3
#define PORT_DRIVE_ENC_2 4
#define PORT_DRIVE_ENC_3 5
#define PORT_DRIVE_ENC_4 6

/* DriveTrain Victor port numbering */
#define PORT_DRIVE_VIC_1 7
#define PORT_DRIVE_VIC_2 8
#define PORT_DRIVE_VIC_3 9
#define PORT_DRIVE_VIC_4 10

/* Joystick port numbering */
#define PORT_JOYSTICK_SPEED 11
#define PORT_JOYSTICK_TURN 12
#define PORT_JOYSTICK_OPERATOR 13

#define SOL_HIGH false
#define SOL_LOW true

enum ShifterModes { LOW_GEAR, HIGH_GEAR, AUTO };

#endif /* CONSTANTS_H */

