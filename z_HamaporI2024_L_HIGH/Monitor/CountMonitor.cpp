#include "CountMonitor.h"

using namespace ev3api;

CountMonitor::CountMonitor(const Motor& leftmotorencoder, const Motor& rightmotorencoder)
    : mLeftMotorEncoder(leftmotorencoder), mRightMotorEncoder(rightmotorencoder)
{
    ;
}

void CountMonitor::Measure()
{
    left_count = mLeftMotorEncoder.getCount();
    right_count = mRightMotorEncoder.getCount();
}

int32_t CountMonitor::getLeftCount() const
{
    return left_count;
}

int32_t CountMonitor::getRightCount() const
{
    return right_count;
}
