#include "LineTraceRun.h"
#include <stdio.h>

using namespace ev3api;

LineTraceRun::LineTraceRun(unsigned char edge, unsigned char speed,
	Motor& leftmotor, Motor& rightmotor, PIDcon* pidcon)
	: medge(edge), mspeed(speed), mLeftMotor(leftmotor), mRightMotor(rightmotor), mPIDcon(pidcon)
{
	if (mspeed == LOW)
	{
		mpwm = 35;
	}
	else if (mspeed == HIGH)
	{
		mpwm = 70;
	}
}

void LineTraceRun::run()
{
	mturn = mPIDcon->getTurn();
	if (medge == RIGHT)
	{
		mLeftMotor.setPWM(mpwm - mturn);
		mRightMotor.setPWM(mpwm + mturn);
	}
	else if (medge == LEFT)
	{
		mLeftMotor.setPWM(mpwm + mturn);
		mRightMotor.setPWM(mpwm - mturn);
	}
	//printf("LineTrace Run!!\n");
	//printf("pwm is %d\n", mfix_pwm);

}
