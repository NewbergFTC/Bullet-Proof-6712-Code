#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     HTIRS2,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     rf,            tmotorTetrix, openLoop, driveLeft, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rb,            tmotorTetrix, openLoop, driveLeft)
#pragma config(Motor,  mtr_S1_C2_1,     lf,            tmotorTetrix, openLoop, driveRight, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     lb,            tmotorTetrix, openLoop, driveRight)
#pragma config(Motor,  mtr_S2_C1_1,     fl,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     fr,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     ul,            tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     ur,            tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S3_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_2,    latch,                tServoStandard)
#pragma config(Servo,  srvo_S3_C1_3,    door,                 tServoStandard)
#pragma config(Servo,  srvo_S3_C1_4,    leftlight,            tServoStandard)
#pragma config(Servo,  srvo_S3_C1_5,    rightlight,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "Bullet-Proof-Subroutines.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
task main()
{
	while (true)
	{
		TButtons nBtn;
		nBtn = nNxtButtonPressed;
		if(nBtn == kLeftButton){
			motor[ul] = 50;
			motor[ur] = 50;
			wait1Msec(1);
		}
		else if(nBtn == kRightButton){
			motor[ul] = -50;
			motor[ur] = -50;
			wait1Msec(1);
		}
		else{
			motor[ul] = 0;
			motor[ur] = 0;
		}
	}
}