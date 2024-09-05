#include "RotateRun.h"
#include <stdio.h>

using namespace ev3api;

RotateRun::RotateRun(unsigned char rota, Motor& leftmotor, Motor& rightmotor)
	: mrota(rota), mLeftMotor(leftmotor), mRightMotor(rightmotor), Run(PWM)
{
	;
}

void RotateRun::run()
{
	if (mrota == RIGHT)
	{
		mLeftMotor.setPWM(+mfix_pwm);
		mRightMotor.setPWM(-mfix_pwm);
	}
	else if (mrota == LEFT)
	{
		mLeftMotor.setPWM(-mfix_pwm);
		mRightMotor.setPWM(+mfix_pwm);
	}
	//printf("Rotation Run!!\n");
	//printf("pwm is %d\n", mfix_pwm);
}
