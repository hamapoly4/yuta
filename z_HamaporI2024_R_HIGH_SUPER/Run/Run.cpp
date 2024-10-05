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
        case MID_HIGH:
            pwm = 52;
            break;
        case HIGH:
            pwm = 70;
            break;
        case HIGH_SUPER:
            pwm = 80;
        default:
            break;
    }
}
