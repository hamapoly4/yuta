#include "RunDistJudge.h"
#include <stdio.h>

int8_t RunDistJudge::size = 0;

RunDistJudge::RunDistJudge(RunDistDetect* rundistdetect)
	: mRunDistDetect(rundistdetect)
{
	cnt = size++;
}

bool RunDistJudge::judge()
{
	current_dist = mRunDistDetect->getRunDist();
	
	if (current_dist < 0)
	{
		current_dist = -current_dist;
	}

	if (current_dist >= target_dist[cnt])
	{
		printf("%fmm走った！！\n", current_dist);
		return true;
	}

	return false;
}
