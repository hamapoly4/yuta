#ifndef ___CLASS_RUNDISTDETECT
#define ___CLASS_RUNDISTDETECT

#include "CountMonitor.h"

class RunDistDetect {
public:
    RunDistDetect(const CountMonitor* countmonitor);
    float getRunDist();
    void measureRunDist();

private:
    static constexpr float ANGLE1DIST = 0.87266;

    const CountMonitor* mCountMonitor;

    int left_cnt;
    int right_cnt;
    float run_dist;
};

#endif // ___CLASS_RUNDISTDETECT
