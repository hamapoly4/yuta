#include "StraRun.h"
#include <stdio.h>

using namespace ev3api;

StraRun::StraRun(eDire d, Control* gyrostrapd, Motor& leftmotor, Motor& rightmotor, eSpeed s)
	: dire(d), mGyroStraPD(gyrostrapd), Run(leftmotor, rightmotor, s)
{
	;
}

void StraRun::run()
{
	turn = mGyroStraPD->getTurn();
	
	switch (dire)
	{
		case FRONT:
			mLeftMotor.setPWM(pwm - turn);
			mRightMotor.setPWM(pwm + turn);
			break;
		case BEHIND:
			mLeftMotor.setPWM(-(pwm - turn));
			mRightMotor.setPWM(-(pwm + turn));
			break;
		default:
			break;
	}
	
}
