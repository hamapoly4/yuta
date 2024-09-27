#include "LineTraceRun.h"
#include <stdio.h>

using namespace ev3api;

LineTraceRun::LineTraceRun(eEdge e, Control* linetracepd, Motor& leftmotor, Motor& rightmotor, eSpeed s)
	: edge(e), mLineTracePD(linetracepd), Run(leftmotor, rightmotor, s)
{
	;
}

void LineTraceRun::run()
{
	turn = mLineTracePD->getTurn();
	switch (edge)
	{
		case LEFT:
			mLeftMotor.setPWM(pwm + turn);
			mRightMotor.setPWM(pwm - turn);
			break;
		case RIGHT:
			mLeftMotor.setPWM(pwm - turn);
			mRightMotor.setPWM(pwm + turn);
			break;
	}
}
