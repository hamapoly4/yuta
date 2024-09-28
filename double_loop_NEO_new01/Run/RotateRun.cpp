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
	int PWM;
	turn = mGyroStopP->getTurn();
	printf("turn : %d\n", turn);
	printf("pwm  : %d\n", pwm);
	PWM = pwm + turn;
	printf("PWM : %d\n", PWM);
		
	switch (rota)
	{
		case LEFT:
			mLeftMotor.setPWM(-PWM);
			mRightMotor.setPWM(+PWM);
			break;
		case RIGHT:
			mLeftMotor.setPWM(+PWM);
			mRightMotor.setPWM(-PWM);
			printf("rigth rotate!!\n");
			break;
		default:
			break;
	}
}
