#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     HTIRS2,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     rf,            tmotorTetrix, openLoop, driveLeft)
#pragma config(Motor,  mtr_S1_C1_2,     rb,            tmotorTetrix, openLoop, driveLeft)
#pragma config(Motor,  mtr_S1_C2_1,     lf,            tmotorTetrix, openLoop, driveRight)
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
task main(){
	waitForStart();
	initializeRobotTeleop();                                       // Starts the robot in the preferred starting position.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (true){
		getJoystickSettings (joystick);
		leftmotorpower  = joystick.joy1_y1*powerratio;                 //Tethers joystick values to motor power
		rightmotorpower = joystick.joy1_y2*powerratio;                  //Tethers joystick values to motor power
		motor [lf] = leftmotorpower;                                      //Main drive control for robot
		motor [lb] = leftmotorpower;                                      //Main drive control for robot
		motor [rf] = rightmotorpower;                                     //Main drive control for robot
		motor [rb] = rightmotorpower;                                     //Main drive control for robot
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (joy1Btn(7) && (powerratio > .5) && (complete == false)){        //Adjusts drive power
			powerratio = powerratio - .25;
			complete = true;
		}
		else if (joy1Btn(8) && (powerratio < 1) && (complete == true)){     //Adjusts drive power
			powerratio = powerratio + .25;
			complete = false;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (joy2Btn(5)) {                                                   //Acivates latching servo
			servo [latch] = LATCH_DOWN;
		}
		if (joy2Btn(6)){                                                    //Deactivates latching servo
			servo [latch] = LATCH_UP;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (joy1Btn(5)){                                                    //Opens servo door
			servo[door] = DOOR_OPEN;
			servo[door] = DOOR_OPEN;
		}
		if(joy1Btn(6)){                                                     //Closes servo door
			servo[door] = DOOR_CLOSED;
			servo[door] = DOOR_CLOSED;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		sweeperpower = joy2Btn(7)? SWEEPER_ON : 0;                          //Activates sweeper
		motor[fl] = sweeperpower;
		motor[fr] = sweeperpower;
		if(joy2Btn(8)){                                                     //Activates sweeper in reverse
			motor[fl] = -SWEEPER_ON;
			motor[fr] = -SWEEPER_ON;
			SweeperStopTime = CurrentTime + 500;
		}
		if(CurrentTime > SweeperStopTime){                                  //Deactivates reverse sweeper
			motor[fl] = 0;
			motor[fr] = 0;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		LiftSpeedLimit =  (((nMotorEncoder[ur] < (LIFT_120_HEIGHT - 1900))) && joy2Btn(4) ||    //Activates lift
		((nMotorEncoder[ur] > 2000) && joy2Btn(2)))? 1:
		//(((nMotorEncoder[ur] < (LIFT_120_HEIGHT -  15))) && joy2Btn(4) ||
		(joy2Btn(4) ||
		(joy2Btn(2)))? 0.3 : 0;
		writeDebugStreamLine("LiftSpeedLimit = %f, Right Lift Encoder Value = %i",LiftSpeedLimit,nMotorEncoder[ur]);
		liftmotor = joy2Btn(4)? LIFT_MOTOR_SPEED*LiftSpeedLimit :                                //Activates lift
		joy2Btn(2)? -LIFT_MOTOR_SPEED*LiftSpeedLimit : 0;
		writeDebugStreamLine("liftmotor = %f",liftmotor);
		motor[ur] = liftmotor;
		motor[ul] = liftmotor;
		writeDebugStreamLine("Right Lift Encoder Value = %f",nMotorEncoder[ur]);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CurrentTime = CurrentTime + 10;
	//wait1Msec(10);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}