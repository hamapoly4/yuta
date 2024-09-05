#include "StraRun.h"
#include <stdio.h>

using namespace ev3api;

StraRun::StraRun(Motor& leftmotor, Motor& rightmotor, PDcon* pdcongyro)
	: mLeftMotor(leftmotor), mRightMotor(rightmotor), mPDconGyro(pdcongyro), Run(PWM)
{
	;
}

void StraRun::run()
{
	mturn = mPDconGyro->getTurn();
	mLeftMotor.setPWM(mfix_pwm - mturn);
	mRightMotor.setPWM(mfix_pwm + mturn);
	
	//printf("Straight Run!!\n");
	//printf("pwm is %d\n", mfix_pwm);
}
