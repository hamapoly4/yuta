#include "LineTracePID.h"

LineTracePID::LineTracePID(HSVMonitor* hsvmonitor, int8_t t, float p, float i, float d)
    : mHSVMonitor(hsvmonitor), threathold(t), p(pgain), i(igain), dgain(d)
{
    ;
}

int LineTracePID::getTurn()
{
    calcTurn();
    return turn;
}

void LineTracePID::calcTurn()
{
    measured_value = mHSVMonitor->getV();
    calcP();
    calcI();
    calcD();
    turn = Pvalue +  Ivalue + Dvalue;
}

void LineTracePID::calcP()
{
    diff = measured_value - threathold;
    Pvalue = diff * pgain;
}

void LineTracePID::calcI()
{
    sum += diff;
    Ivalue = sum * igain;

    i++;
    if (i >= 10)
    {
        i = 0;
        sum = 0;
    }
}

void LineTracePID::calcD()
{
    Dvalue = (diff - old_diff) * dgain;
    old_diff = diff;
}
