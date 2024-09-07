#include "Scenario.h"
#include <stdio.h>

using namespace ev3api;

Scenario::Scenario(Scene* scene[], Motor& leftmotor, Motor& rightmotor,
					 	Motor& leftmotorencoder, Motor& rightmotorencoder,
							GyroSensor& resetgyro, ColorDetect* colordetect)
	: mscene_no(TOP), mscene_switch_flag(false), mscenario_fin_flag(false), reset_flag(true),
	  mLeftMotor(leftmotor), mRightMotor(rightmotor),
	  mLeftMotorEncoder(leftmotorencoder), mRightMotorEncoder(rightmotorencoder),
	  mResetGyro(resetgyro), mColorDetect(colordetect)
{
	unsigned char i;
	for (i = 0; i < 13; i++)
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
}

void Scenario::switch_scene()
{
	int angle;
	if (reset_flag == true)
	{
		reset_device();
		reset_flag = false;
	}
	else
	{
		angle = mResetGyro.getAngle();
		printf("angle : %d\n", angle);
		if (angle == 0)
		{
			mscene_no++;
			mscene_switch_flag = false;
		}
		reset_flag = true;
	}
	

	if (mscene_no > LAST)
	{
		mscenario_fin_flag = true;
	}
}

void Scenario::reset_device()
{
	mLeftMotor.stop();
	mRightMotor.stop();

	mLeftMotorEncoder.setCount(0);
	mRightMotorEncoder.setCount(0);
	mResetGyro.reset();
	
	printf("reset device!!\n\n");
}

bool Scenario::finish()
{
	return mscenario_fin_flag;
}
