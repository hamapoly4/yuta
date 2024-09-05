#include "PDcon.h"

using namespace ev3api;

PDcon::PDcon(unsigned char runmethod, ev3api::GyroSensor& gyrosensor, ColorDetect* colordetect)
    : mRunmethod(runmethod), mGyroSensor(gyrosensor), mColorDetect(colordetect)
{
    if (mRunmethod == STRAIGHT)
    {
        mthreathold = 0;
        mPgain = 1.5;
        mDgain = 3;
    }
    else if (mRunmethod == LINETRACE)
    {
        mthreathold = 70;
        mPgain = 0.50;
        mDgain = 2;
    }
}

int PDcon::getTurn()
{    
    calcTurn();
    return mturn;
}

void PDcon::calcTurn()
{
    calcP();
    calcD();
    mturn = mP_value + mD_value;
}

void PDcon::calcP()
{
    if (mRunmethod == STRAIGHT)
    {
        mdiff = mGyroSensor.getAngle() - mthreathold;
    }
    else if (mRunmethod == LINETRACE)
    {
        mdiff = mColorDetect->getV() - mthreathold;
    }

    mP_value = mdiff * mPgain;
}

void PDcon::calcD()
{
    mD_value = (mdiff - mold_diff) * mDgain;
    mold_diff = mdiff;
}
