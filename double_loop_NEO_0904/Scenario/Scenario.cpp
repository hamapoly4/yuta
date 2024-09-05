#include "Scenario.h"
#include <stdio.h>

using namespace ev3api;

Scenario::Scenario(Scene* scene[], Motor& leftmotor, Motor& rightmotor,
					 	Motor& leftmotorencoder, Motor& rightmotorencoder,
							GyroSensor& judgegyro, GyroSensor& strarungyro, ColorDetect* colordetect)
	: mscene_no(TOP), mscene_switch_flag(false), mscenario_fin_flag(false),
	  mLeftMotor(leftmotor), mRightMotor(rightmotor),
	  mLeftMotorEncoder(leftmotorencoder), mRightMotorEncoder(rightmotorencoder),
	  mJudgeGyro(judgegyro), mStraRunGyro(strarungyro), mColorDetect(colordetect)
{
	unsigned char i;
	for (i = 0; i < 13; i++)
	{
		mScene[i] = scene[i];
	}
}

void Scenario::run()
{
	switch (mscene_no)
	{
		case  2:
		case  3:
		case  6:
		case  7:
		case 10:
			mColorDetect->convHSV();
			break;
		default:
			break;
	}
	
	mScene[mscene_no]->run();
	mscene_switch_flag = mScene[mscene_no]->fin_judge();

	if (mscene_switch_flag == true)
	{
		switch_scene();
	}
}

void Scenario::switch_scene()
{
	reset_device();

	if (mscene_no >= LAST)
	{
		mscenario_fin_flag = true;
	}
	else
	{
		mscene_no++;
		mscene_switch_flag = false;
	}
}

void Scenario::reset_device()
{
	mLeftMotor.stop();
	mRightMotor.stop();

	mLeftMotorEncoder.setCount(0);
	mRightMotorEncoder.setCount(0);
	mJudgeGyro.reset();
	mStraRunGyro.reset();
}

bool Scenario::finish()
{
	return mscenario_fin_flag;
}
