#include "StraRun.h"
#include <stdio.h>

using namespace ev3api;

StraRun::StraRun(Control* gyrostrapd, Motor& leftmotor, Motor& rightmotor, eSpeed s)
	: mGyroStraPD(gyrostrapd), Run(leftmotor, rightmotor, s)
{
	;
}

void StraRun::run()
{
	turn = mGyroStraPD->getTurn();
	mLeftMotor.setPWM(pwm - turn);
	mRightMotor.setPWM(pwm + turn);
}
