#ifndef ___CLASS_COUNTMONITOR
#define ___CLASS_COUNTMONITOR

#include "Motor.h"

class CountMonitor {
public:
    CountMonitor(const ev3api::Motor& leftmotorencoder, const ev3api::Motor& rightmotorencoder);
    void Measure();
    int32_t getLeftCount() const;
    int32_t getRightCount() const;

private:
    const ev3api::Motor& mLeftMotorEncoder;
    const ev3api::Motor& mRightMotorEncoder;

    int32_t left_count;
    int32_t right_count;
};

#endif // ___CLASS_COUNTMONITOR