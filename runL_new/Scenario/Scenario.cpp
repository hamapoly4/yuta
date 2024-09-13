#include "Scenario.h"
#include <stdio.h>

using namespace ev3api;

Scenario::Scenario(Scene* scene[], Motor& leftmotor, Motor& rightmotor,
					 	Motor& leftmotorencoder, Motor& rightmotorencoder,
							Motor& resetleft, Motor& resetright, ColorDetect* colordetect)
	: mscene_no(TOP), mscene_switch_flag(false), mscenario_fin_flag(false),
	  mLeftMotor(leftmotor), mRightMotor(rightmotor),
	  mLeftMotorEncoder(leftmotorencoder), mRightMotorEncoder(rightmotorencoder),
	  mResetLeft(resetleft), mResetRight(resetright), mColorDetect(colordetect)
{
	unsigned char i;
	for (i = 0; i < SIZE; i++)
	{
		mScene[i] = scene[i];
	}
}

void Scenario::run()
{
	if (mscene_switch_flag == true)
	{
		switch_scene();
		return;
	}
	
	mColorDetect->convHSV();
	
	mScene[mscene_no]->run();
	mscene_switch_flag = mScene[mscene_no]->fin_judge();
}

void Scenario::switch_scene()
{
	reset_device();
	mscene_no++;
	mscene_switch_flag = false;	

	if (mscene_no > LAST)
	{
		mscenario_fin_flag = true;
	}
}

void Scenario::reset_device()
{
	mResetLeft.reset();
	mResetRight.reset();
	
	printf("reset device!!\n\n");
}

bool Scenario::finish()
{
	return mscenario_fin_flag;
}
