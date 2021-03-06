#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
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
void ScoreInTube(){
	writeDebugStreamLine("Start ScoreInTube Routine ");
	GoForward(86,-20);             //Moves robot off of ramp in front of tube.
	GoForward(7,-10);              // Moves robot to tube, overshooting it
	TubeLatch(LATCH_DOWN);         //Latches onto tube
	sweeperInitialize();           //Knocks down the sweepers, so slides can lift
	lift(60,LIFT_MOTOR_SPEED);     //Lifts linear slides up to designated height
	ScoreBallInTube(DOOR_OPEN);    //Opens servo door, scoring balls
	wait1Msec(1500);
	ScoreBallInTube(DOOR_CLOSED);  //Closes Servo Door
	GoForward(0.5,20);             //Ensures that door servo does not get stuck on tube
	lift(58,-LIFT_MOTOR_SPEED);    //Lowers Linear Slides
	//SwingTurn(SWING_TURN_LEFT,DEGREES_90,100);
	//SwingTurn(SWING_TURN_RIGHT,DEGREES_90,-100);
	//GoForward(85,50);
	//TubeLatch(LATCH_UP);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
task main(){
	waitForStart();
	initializeRobot();
	ScoreInTube();
}
