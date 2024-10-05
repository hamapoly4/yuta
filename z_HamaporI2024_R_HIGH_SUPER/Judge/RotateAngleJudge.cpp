#include "RotateAngleJudge.h"
#include <stdio.h>

using namespace ev3api;

const int RotateAngleJudge::target_angle[7] = {
	-1, 30, 12, -10, -25, -72, 63,
};

int8_t RotateAngleJudge::size = 0;

RotateAngleJudge::RotateAngleJudge(eRota r, AngleMonitor* anglemonitor)
	: rota(r), mAngleMonitor(anglemonitor)
{
	cnt = size++;
}

bool RotateAngleJudge::judge()
{
	printf("RotateAngleJudge judge\n");
	current_angle = mAngleMonitor->getAngle();

	if (rota == LEFT)
	{
		printf("左旋回角度：%d度\n", current_angle);
		if (current_angle <= target_angle[cnt])
		{
			return true;
		}
	}
	else if (rota == RIGHT)
	{
		printf("右旋回角度：%d度\n", current_angle);
		if (current_angle >= target_angle[cnt])
		{
			return true;
		}
	}

	return false;
}
