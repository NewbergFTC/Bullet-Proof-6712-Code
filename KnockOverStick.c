#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     HTIRS2,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     rf,            tmotorTetrix, openLoop, driveLeft, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rb,            tmotorTetrix, openLoop, driveLeft)
#pragma config(Motor,  mtr_S1_C2_1,     lf,            tmotorTetrix, openLoop, reversed, driveRight)
#pragma config(Motor,  mtr_S1_C2_2,     lb,            tmotorTetrix, openLoop, driveRight, encoder)
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
//Stick facing parking zone
void Zone1(){
	writeDebugStreamLine("Start Zone1 Routine----------------------------------------------------------");
	GoForward(12,-20);
	turn(LEFT,(DEGREES_70),100);
	GoForward(32,-100);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Stick facing diagonal to zone
void Zone2(){
	writeDebugStreamLine("Start Zone2 Routine----------------------------------------------------------");
	turn(LEFT,DEGREES_15,100);
	GoForward(27,-20);
	turn(RIGHT,DEGREES_80,-100);
	GoForward(25,-100);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Stick facing ramp
void Zone3(){
	writeDebugStreamLine("Start Zone3 Routine----------------------------------------------------------");
	GoForward(18,20);
	turn(LEFT,DEGREES_20,100);
	GoForward(48,-100);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
task main(){
	waitForStart();
	initializeRobot();
	IrSetup();

//Gets five ir readings at six inch intervals
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GoForward(6,-20);
	wait1Msec(250);
	IrReading1 = ReadIR();
	GoForward(6,-20);
	wait1Msec(250);
	IrReading2 = ReadIR();
	GoForward(6,-20);
	wait1Msec(250);
	IrReading3 = ReadIR();
	GoForward(6,-20);
	wait1Msec(250);
	IrReading4 = ReadIR();
	GoForward(6,-20);
	wait1Msec(250);
	IrReading5 = ReadIR();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	stickAtZone = (((IrReading3 == 3) && (IrReading4 == 3)) ||    // Two of readings 3,4, and 5 equal 3 and the first reading does not equal 3
	((IrReading3 == 3) && (IrReading5 == 3)) ||
	((IrReading4 == 3) && (IrReading5 == 3))) &&
	(IrReading1 != 3);
	stickAtRamp = (((IrReading1 == 3) && (IrReading2 == 3)) ||    // Two of readings 1, 2, and 3 equal 3 and the fifth reading does not equal 3
	((IrReading1 == 3) && (IrReading3 == 3)) ||
	((IrReading2 == 3) && (IrReading3 == 3))) &&
	(IrReading5 != 3);
	writeDebugStreamLine("IR Readings = %i, %i, %i, %i, %i",IrReading1, IrReading2,IrReading3, IrReading4,IrReading5);
	writeDebugStreamLine("stickAtRamp = %i, stickAtZone = %i",stickAtRamp,stickAtZone);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (stickAtZone){
		Zone1();          //Stick facing parking zone
		stopAllTasks();
	}
	if (stickAtRamp){
		Zone3();          //Stick facing ramp
		stopAllTasks();
	}
	else{
		Zone2();          //Stick diagonal to parking zone
		stopAllTasks();
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
