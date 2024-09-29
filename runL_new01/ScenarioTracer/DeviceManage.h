#ifndef ___CLASS_DEVICEMANAGE
#define ___CLASS_DEVICEMANAGE

#include "Motor.h"
#include "GyroSensor.h"

class DeviceManage {
public:
    enum eState { INITIAL, STOP_RUN, FIX_STOP_RUN, RESET_COUNT, FIX_RESET_COUNT,  RESET_ANGLE, FIX_RESET_ANGLE, };

    DeviceManage(ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, ev3api::Motor& leftmotorencoder,
                    ev3api::Motor& rightmotorencoder, ev3api::GyroSensor& gyrosensor);

    eState getState() const;
    void reset();
    void exeInitial();
    void stopRun();
    void fixStopRun();
    void resetCount();
    void fixResetCount();
    void resetAngle();
    void fixResetAngle();

private:
    ev3api::Motor& mLeftMotor;
    ev3api::Motor& mRightMotor;
    ev3api::Motor& mLeftMotorEncoder;
    ev3api::Motor& mRightMotorEncoder;
    ev3api::GyroSensor& mGyroSensor;

    eState state;

    int32_t left_count;
    int32_t old_left_count;

    int32_t right_count;
    int32_t old_right_count;

    int16_t angle;
};

#endif // ___CLASS_MANAGE