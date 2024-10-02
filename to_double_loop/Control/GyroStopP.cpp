#include "GyroStopP.h"
#include <stdio.h>

const int GyroStopP::threathold[5] = {
    1, -30, -10, 10, 25,
};

int8_t GyroStopP::size = 0;

GyroStopP::GyroStopP(AngleMonitor* anglemonitor)
    : mAngleMonitor(anglemonitor), Control()
{
    cnt = size++;
}

int GyroStopP::getTurn()
{
    calcTurn();
    return turn;
}

void GyroStopP::calcTurn()
{
    measured_value = mAngleMonitor->getAngle();
    calcP();
    turn = Pvalue;
}

void GyroStopP::calcP()
{
    diff = threathold[cnt] - measured_value;
    if (threathold[cnt] < 0)
    {
        diff = -diff;
    }
    printf("diff : %d", diff);

    Pvalue = diff * PGAIN;
}
