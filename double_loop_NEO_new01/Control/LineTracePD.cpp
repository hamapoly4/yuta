#include "LineTracePD.h"

LineTracePD::LineTracePD(HSVMonitor* hsvmonitor)
    : mHSVMonitor(hsvmonitor)
{
    ;
}

int LineTracePD::getTurn()
{
    calcTurn();
    return turn;
}

void LineTracePD::calcTurn()
{
    measured_value = mHSVMonitor->getV();
    calcP();
    calcD();
    turn = Pvalue + Dvalue;
}

void LineTracePD::calcP()
{
    diff = measured_value - THREATHOLD;
    Pvalue = diff * PGAIN;
}

void LineTracePD::calcD()
{
    Dvalue = (diff - old_diff) * DGAIN;
    old_diff = diff;
}
