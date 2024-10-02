#include "LineTraceRun.h"
#include <stdio.h>

using namespace ev3api;

LineTraceRun::LineTraceRun(eEdge e, Control* linetracepid, Motor& leftmotor, Motor& rightmotor, eSpeed s)
	: edge(e), mLineTracePID(linetracepid), Run(leftmotor, rightmotor, s)
{
	;
}

void LineTraceRun::run()
{
	turn = mLineTracePID->getTurn();
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
		default:
			break;
	}
}
