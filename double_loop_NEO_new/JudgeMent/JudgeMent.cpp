#include "JudgeMent.h"

using namespace ev3api;

GyroSensor JudgeMent::mGyroSensor(PORT_4);
Motor JudgeMent::LeftMotorEncoder(PORT_C);
Motor JudgeMent::RightMotorEncoder(PORT_B);

JudgeMent::JudgeMent()
{
    ;
}

JudgeMent::~JudgeMent()
{
    mGyroSensor.reset();
    LeftMotorEncoder.setCount(0);
    RightMotorEncoder.setCount(0);
}