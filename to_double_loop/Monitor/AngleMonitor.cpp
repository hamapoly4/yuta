#include "AngleMonitor.h"

using namespace ev3api;

AngleMonitor::AngleMonitor(GyroSensor& gyrosensor)
    : mGyroSensor(gyrosensor)
{
    ;
}

void AngleMonitor::Measure()
{
    angle = mGyroSensor.getAngle();
}

int AngleMonitor::getAngle() const
{
    return angle;
}
