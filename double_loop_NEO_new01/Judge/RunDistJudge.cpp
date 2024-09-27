#include "RunDistJudge.h"
#include <stdio.h>

constexpr float target_dist[7] = {
	300, 100, 800, 100, 400, 100, 300,
};

int8_t RunDistJudge::size = 0;

RunDistJudge::RunDistJudge(RunDistDetect* rundistdetect)
	: mRunDistDetect(rundistdetect)
{
	cnt = size++;
}

bool RunDistJudge::judge()
{
	current_dist = mRunDistDetect->getRunDist();

	if (current_dist >= target_dist[cnt])
	{
		printf("%fmm走った！！\n", current_dist);
		return true;
	}

	return false;
}
