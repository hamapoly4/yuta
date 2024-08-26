#include "RotateAngleJudgeMent.h"
#include <stdio.h>

using namespace ev3api;

RotateAngleJudgeMent::RotateAngleJudgeMent(unsigned char rota, int target_angle)
	: mrota(rota), mtarget_angle(target_angle)
{
	;
}

RotateAngleJudgeMent::~RotateAngleJudgeMent()
{
	;
}

bool RotateAngleJudgeMent::judge()
{
	mcurrent_angle = mGyroSensor.getAngle();

	if (mrota == RIGHT)
	{
		printf("右旋回角度：%d度\n", mcurrent_angle);
		if (mcurrent_angle >= mtarget_angle)
		{
			return true;
		}
	}
	else if (mrota == LEFT)
	{
		printf("左旋回角度：%d度\n", mcurrent_angle);
		if (mcurrent_angle <= mtarget_angle)
		{
			return true;
		}
	}

	return false;
}
