#include "RunDistDetect.h"

RunDistDetect::RunDistDetect(const CountMonitor* countmonitor)
    : mCountMonitor(countmonitor)
{
    ;
}

float RunDistDetect::getRunDist()
{    
    measureRunDist();
    return run_dist;
}

void RunDistDetect::measureRunDist()
{
    left_cnt = mCountMonitor->getLeftCount();
    right_cnt = mCountMonitor->getRightCount();

    run_dist = (left_cnt + right_cnt) * ANGLE1DIST / 2.0;
}
