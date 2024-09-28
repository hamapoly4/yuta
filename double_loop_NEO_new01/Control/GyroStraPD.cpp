#include "GyroStraPD.h"

GyroStraPD::GyroStraPD(AngleMonitor* anglemonitor)
    : mAngleMonitor(anglemonitor), Control()
{
    ;
}

int GyroStraPD::getTurn()
{
    calcTurn();
    return turn;
}

void GyroStraPD::calcTurn()
{
    measured_value = mAngleMonitor->getAngle();
    calcP();
    calcD();
    turn = Pvalue + Dvalue;
}

void GyroStraPD::calcP()
{
    diff = measured_value - THREATHOLD;
    Pvalue = diff * PGAIN;
}

void GyroStraPD::calcD()
{
    Dvalue = (diff - old_diff) * DGAIN;
    old_diff = diff;
}
