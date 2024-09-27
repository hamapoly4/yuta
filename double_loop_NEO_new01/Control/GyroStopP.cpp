#include "GyroStopP.h"

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
    diff = measured_value - threathold[cnt];
    Pvalue = diff * PGAIN;
}
