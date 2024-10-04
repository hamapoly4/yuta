#include "DeviceManage.h"

using namespace ev3api;

DeviceManage::DeviceManage(Motor& leftmotor, Motor& rightmotor, Motor& leftmotorencoder,
                    Motor& rightmotorencoder, GyroSensor& gyrosensor)
    : mLeftMotor(leftmotor), mRightMotor(rightmotor), mLeftMotorEncoder(leftmotorencoder),
        mRightMotorEncoder(rightmotorencoder), mGyroSensor(gyrosensor), state(INITIAL)
{
    ;
}

DeviceManage::eState DeviceManage::getState() const
{
    return state;
}

void DeviceManage::reset()
{
    switch (state)
    {
        case INITIAL:
            exeInitial();
            break;
        case STOP_RUN:
            stopRun();
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
        default:
            break;
    }
}

void DeviceManage::exeInitial()
{
    int8_t j;
    for (j = 0; j < SIZE; j++)
    {
        angle_sampling[j] = 0;
    }
    i = 0;
    
    state = STOP_RUN;
    printf("exeInitail\n");
}


void DeviceManage::stopRun()
{
    mLeftMotor.stop();
    mRightMotor.stop();
    state = RESET_COUNT;
    printf("stopRun\n");
}

void DeviceManage::resetCount()
{
    mLeftMotorEncoder.setCount(0);
    mRightMotorEncoder.setCount(0);
    state = FIX_RESET_COUNT;
    printf("resetCount\n");
}

void DeviceManage::fixResetCount()
{
    left_count = mLeftMotorEncoder.getCount();
    right_count = mRightMotorEncoder.getCount();
    
    printf("left_count  : %d\n", left_count);
    printf("right_count : %d\n", right_count);

    if (left_count == 0 && right_count == 0)
    {
        state = RESET_ANGLE;
        printf("fixResetCount\n");
    }
    else
    {
        state = RESET_COUNT;
    }
}

void DeviceManage::resetAngle()
{
    mGyroSensor.reset();
    state = FIX_RESET_ANGLE;
    printf("resetAngle\n");
}

void DeviceManage::fixResetAngle()
{
    angle_sampling[i] = mGyroSensor.getAngle();

    if (angle_sampling[i] == 0)
    {
        i++;
    }
    else
    {
        i = 0;
        state = RESET_ANGLE;
    }
    
    if (i >= SIZE)
    {
        state = INITIAL;
    }
}
