#include "PIDcon.h"

PIDcon::PIDcon(unsigned char speed, ColorDetect* colordetect)
    : mspeed(speed), mColorDetect(colordetect), msum(0), mi(0)
{
    if (mspeed == LOW)
    {
        mPgain = 0.5;
        mIgain = 0.005;
        mDgain = 2;
    }
    else if (mspeed == HIGH)
    {
        mPgain = 0.1;
        mIgain = 0.005;
        mDgain = 3;
    }
}

int PIDcon::getTurn()
{    
    calcTurn();
    return mturn;
}

void PIDcon::calcTurn()
{
    getDiff();
    calcP();
    calcI();
    calcD();
    mturn = mP_value + mI_value + mD_value;
}

void PIDcon::getDiff()
{
    mdiff = mColorDetect->getV() - mthreathold;
}

void PIDcon::calcP()
{
    mP_value = mdiff * mPgain;
}

void PIDcon::calcI()
{
    msum += mdiff;
    mI_value = msum * mIgain;

    mi++;
    if (mi >= 10)
    {
        mi = 0;
        msum = 0;
    }
}

void PIDcon::calcD()
{
    mD_value = (mdiff - mold_diff) * mDgain;
    mold_diff = mdiff;
}
