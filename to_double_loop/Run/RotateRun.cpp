#include "RotateRun.h"
#include <stdio.h>

using namespace ev3api;

RotateRun::RotateRun(eRota r, Control* gyrostopp, Motor& leftmotor, Motor& rightmotor, eSpeed s)
	: rota(r), mGyroStopP(gyrostopp), Run(leftmotor, rightmotor, s)
{
	;
}

void RotateRun::run()
{
	turn = mGyroStopP->getTurn();
	switch (rota)
	{
		case LEFT:
			mLeftMotor.setPWM(-(pwm + turn));
			mRightMotor.setPWM(+(pwm + turn));
			break;
		case RIGHT:
			mLeftMotor.setPWM(+(pwm + turn));
			mRightMotor.setPWM(-(pwm + turn));
			printf("rigth rotate!!\n");
			break;
		default:
			break;
	}
}
