#include "LineTraceRun.h"
#include <stdio.h>

using namespace ev3api;

LineTraceRun::LineTraceRun(unsigned char edge, Motor& leftmotor, Motor& rightmotor, PDcon* pdconcolor)
	: medge(edge), mLeftMotor(leftmotor), mRightMotor(rightmotor), mPDconColor(pdconcolor), Run(PWM)
{
	;
}

void LineTraceRun::run()
{
	mturn = mPDconColor->getTurn();
	if (medge == RIGHT)
	{
		mLeftMotor.setPWM(mfix_pwm - mturn);
		mRightMotor.setPWM(mfix_pwm + mturn);
	}
	else if (medge == LEFT)
	{
		mLeftMotor.setPWM(mfix_pwm + mturn);
		mRightMotor.setPWM(mfix_pwm - mturn);
	}
	//printf("LineTrace Run!!\n");
	//printf("pwm is %d\n", mfix_pwm);

}
