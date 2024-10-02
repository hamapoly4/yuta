#ifndef ___CLASS_ANGLEMONITOR
#define ___CLASS_ANGLEMONITOR

#include "GyroSensor.h"

class AngleMonitor {
private:
    ev3api::GyroSensor& mGyroSensor;

    int angle;

public:
    AngleMonitor(ev3api::GyroSensor& gyrosensor);
    void Measure();
    int getAngle() const;
};

#endif // ___CLASS_ANGLEMONITOR
