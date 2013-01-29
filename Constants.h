#ifndef CONSTANTS_H
#define CONSTANTS_H

/*! \brief Contains all constants */

/*! Speed cutoffs for shifting gears */
#define GEAR_UPSHIFT_CUTOFF 6.0
#define GEAR_DOWNSHIFT_CUTOFF 4.0

/*! First solenoid drive port */
#define PORT_DRIVE_SOL_1 0
/*! Second solenoid drive port */
#define PORT_DRIVE_SOL_2 0

/*! Accumulator Victor port */
#define PORT_ACC_VIC_1 0

/*! First encoder drive port */
#define PORT_DRIVE_ENC_1_A 0
#define PORT_DRIVE_ENC_1_B 0
/*! Second encoder drive port */
#define PORT_DRIVE_ENC_2_A 0
#define PORT_DRIVE_ENC_2_B 0

/*! Gyro port for drive train */
#define PORT_DRIVE_GYRO 0

/*! First drive train Victor port */
#define PORT_DRIVE_VIC_1 0
/*! Second drive train Victor port */
#define PORT_DRIVE_VIC_2 0
/*! Third drive train Victor port */
#define PORT_DRIVE_VIC_3 0
/*! Fourth drive train Victor port */
#define PORT_DRIVE_VIC_4 0

/*! First motor port */
#define PORT_PWM_1 0
/*! Second motor port */
#define PORT_PWM_2 0

/*! First joystick port */
#define PORT_JOYSTICK_SPEED 0
/*! Second joystick port */
#define PORT_JOYSTICK_TURN 0
/*! Third joystick port */
#define PORT_JOYSTICK_OPERATOR 0

/*! Speed joystick trigger id */
#define BUTT_JOYSTICK_SPEED_TRIGGER 0
/*! Speed joystick button 2 id */
#define BUTT_JOYSTICK_SPEED_2 1
/*! Speed joystick button 3 id */
#define BUTT_JOYSTICK_SPEED_3 2
/*! Speed joystick button 4 id */
#define BUTT_JOYSTICK_SPEED_4 3
/*! Speed joystick button 5 id */
#define BUTT_JOYSTICK_SPEED_5 4
/*! Speed joystick button 6 id */
#define BUTT_JOYSTICK_SPEED_6 5
/*! Speed joystick button 7 id */
#define BUTT_JOYSTICK_SPEED_7 6
/*! Speed joystick button 2 id */
#define BUTT_JOYSTICK_SPEED_8 7
/*! Speed joystick button 2 id */
#define BUTT_JOYSTICK_SPEED_9 8
/*! Speed joystick button 2 id */
#define BUTT_JOYSTICK_SPEED_10 9
/*! Speed joystick button 2 id */
#define BUTT_JOYSTICK_SPEED_11 10
/*! Speed joystick x-axis id */
#define AXIS_JOYSTICK_SPEED_X 0
/*! Speed joystick y-axis id */
#define AXIS_JOYSTICK_SPEED_Y 1
/*! Speed joystick z-axis id */
#define AXIS_JOYSTICK_SPEED_Z 2

/*! Turn joystick trigger id */
#define BUTT_JOYSTICK_TURN_TRIGGER 0
/*! Turn joystick button 2 id */
#define BUTT_JOYSTICK_TURN_2 1
/*! Turn joystick button 3 id */
#define BUTT_JOYSTICK_TURN_3 2
/*! Turn joystick button 4 id */
#define BUTT_JOYSTICK_TURN_4 3
/*! Turn joystick button 5 id */
#define BUTT_JOYSTICK_TURN_5 4
/*! Turn joystick button 6 id */
#define BUTT_JOYSTICK_TURN_6 5
/*! Turn joystick button 7 id */
#define BUTT_JOYSTICK_TURN_7 6
/*! Turn joystick button 2 id */
#define BUTT_JOYSTICK_TURN_8 7
/*! Turn joystick button 2 id */
#define BUTT_JOYSTICK_TURN_9 8
/*! Turn joystick button 2 id */
#define BUTT_JOYSTICK_TURN_10 9
/*! Turn joystick button 2 id */
#define BUTT_JOYSTICK_TURN_11 10
/*! Turn joystick x-axis id */
#define AXIS_JOYSTICK_TURN_X 0
/*! Turn joystick y-axis id */
#define AXIS_JOYSTICK_TURN_Y 1
/*! Turn joystick z-axis id */
#define AXIS_JOYSTICK_TURN_Z 2

/*! Operator joystick trigger id */
#define BUTT_JOYSTICK_OPERATOR_TRIGGER 0
/*! Operator joystick button 2 id */
#define BUTT_JOYSTICK_OPERATOR_2 1
/*! Operator joystick button 3 id */
#define BUTT_JOYSTICK_OPERATOR_3 2
/*! Operator joystick button 4 id */
#define BUTT_JOYSTICK_OPERATOR_4 3
/*! Operator joystick button 5 id */
#define BUTT_JOYSTICK_OPERATOR_5 4
/*! Operator joystick button 6 id */
#define BUTT_JOYSTICK_OPERATOR_6 5
/*! Operator joystick button 7 id */
#define BUTT_JOYSTICK_OPERATOR_7 6
/*! Operator joystick button 2 id */
#define BUTT_JOYSTICK_OPERATOR_8 7
/*! Operator joystick button 2 id */
#define BUTT_JOYSTICK_OPERATOR_9 8
/*! Operator joystick button 2 id */
#define BUTT_JOYSTICK_OPERATOR_10 9
/*! Operator joystick button 2 id */
#define BUTT_JOYSTICK_OPERATOR_11 10
/*! Operator joystick x-axis id */
#define AXIS_JOYSTICK_OPERATOR_X 0
/*! Operator joystick y-axis id */
#define AXIS_JOYSTICK_OPERATOR_Y 1
/*! Operator joystick z-axis id */
#define AXIS_JOYSTICK_OPERATOR_Z 2

/*! Solenoid high drive */
#define SOL_DRIVE_HIGH false
/*! Solenide low drive */
#define SOL_DRIVE_LOW true

/*! Shifter upper cutoff */
#define SHIFT_CUTOFF_UP 5.5
/*! Shifter lower cutoff */
#define SHIFT_CUTOFF_DOWN 4.5

/*! Compressor spike port */
#define PORT_COMPRESSOR_SPIKE 0
/*! Pressure cutoff port */
#define PORT_PRESSURE_CUTOFF 0

/*! Different gear modes for the drive train */
enum ShifterMode { LOW_GEAR, HIGH_GEAR, AUTO };

/*! Types of autonomous modes */
enum AutonomousMode { DEFAULT, ALTERNATE_1, ALTERNATE_2 };

#endif /* CONSTANTS_H */

