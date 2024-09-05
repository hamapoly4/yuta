#include "RotateAngleJudgeMent.h"
#include <stdio.h>

using namespace ev3api;

RotateAngleJudgeMent::RotateAngleJudgeMent(unsigned char rota, int target_angle, GyroSensor& gyrosensor)
	: mrota(rota), mtarget_angle(target_angle), mGyroSensor(gyrosensor)
{
	;
}

bool RotateAngleJudgeMent::judge()
{
	mcurrent_angle = mGyroSensor.getAngle();
	
	if (mcurrent_angle >= (mtarget_angle + 10))
	{
		printf("mcurrent_angle is over mtarget_angle!!\n");
		printf("So return!!\n");
		return false;
	}

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
