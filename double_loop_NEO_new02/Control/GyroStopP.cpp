#include "GyroStopP.h"

const int GyroStopP::threathold[4] = {
	1, -35, -10, 20,
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
    Pvalue = diff * PGAIN;
}
