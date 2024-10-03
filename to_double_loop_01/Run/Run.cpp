#include "Run.h"

using namespace ev3api;

Run::Run(Motor& leftmotor, Motor& rightmotor, eSpeed s)
    : mLeftMotor(leftmotor), mRightMotor(rightmotor), speed(s)
{
    switch (speed)
    {
        case LOW:
            pwm = 35;
            break;
        case MID:
            pwm = 45;
            break;
        case HIGH:
            pwm = 70;
            break;
        default:
            break;
    }
}