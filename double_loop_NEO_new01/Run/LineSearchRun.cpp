#include "LineSearchRun.h"

using namespace ev3api;

LineSearchRun::LineSearchRun(Motor& leftmotor, Motor& rightmotor, eSpeed s)
    : Run(leftmotor, rightmotor, s)
{
    ;
}

void LineSearchRun::run()
{
    mLeftMotor.setPWM(pwm);
	mRightMotor.setPWM(pwm);
}
