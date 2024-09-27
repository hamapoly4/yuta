#include "DeviceManage.h"

using namespace ev3api;

DeviceManage::DeviceManage(Motor& leftmotor, Motor& rightmotor, Motor& leftmotorencoder,
                    Motor& rightmotorencoder, GyroSensor& gyrosensor)
    : mLeftMotor(leftmotor), mRightMotor(rightmotor), mLeftMotorEncoder(leftmotorencoder),
        mRightMotorEncoder(rightmotorencoder), mGyroSensor(gyrosensor), state(INITIAL)
{
    ;
}

eState Device::getState() const
{
    return state;
}

void Device::reset()
{
    switch (state)
    {
        case INITIAL:
            exeInitial();
            break;
        case STOP_RUN:
            stopRun();
            break;
        case FIX_STOP_RUN:
            fixStopRun();
            break;
        case RESET_COUNT:
            resetCount();
            break;
        case FIX_RESET_COUNT:
            fixResetCount();
            break;
        case RESET_ANGLE:
            resetAngle();
            break;
        case FIX_RESET_ANGLE:
            fixResetAngle();
            break;
    }
}

void Device::exeInitial()
{
    old_left_count = 0;
    old_right_count = 0;
    old_angle = 0;
    state = STOP_RUN;
}


void Device::stopRun()
{
    mLeftMotor.stop();
    mRightMotor.stop();
    state = FIX_STOP_RUN
}

void Device::fixStopRun()
{
    left_count = mLeftMotorEncoder.getCount();
    right_count = mRightMotorEncoder.getCount();

    if (old_left_count == left_count && old_right_count == right_count)
    {
        state = RESET_COUNT;
    }

    old_left_count = left_count;
    old_right_count = right_count;
}

void Device::resetCount()
{
    mLeftMotorEncoder.setCount(0);
    mRightMotorEncoder.setCount(0);
    state = FIX_RESET_COUNT;
}

void Device::fixResetCount()
{
    left_count = mLeftMotorEncoder.getCount();
    right_count = mRightMotorEncoder.getCount();

    if (left_count == 0 && right_count == 0)
    {
        state = RESET_ANGLE;
    }
}

void Device::resetAngle()
{
    mGyroSensor.reset();
    state = FIX_RESET_ANGLE;
}

void Device::fixResetAngle()
{
    angle = mGyroSensor.getAngle():
    if (angle == 0)
    {
        state = INITIAL;
    }
}
