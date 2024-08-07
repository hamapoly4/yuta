#include "Motor.h"       // <1>
#include "GyroSensor.h" // <2>
#include "SonarSensor.h"

using namespace ev3api;  // <4>

class Tracer {  // <1>
public:
  Tracer();
  void angle_reset();
  bool run();       // <2>
  void terminate();

private:
  Motor leftWheel;
  Motor rightWheel;
  GyroSensor gyroSensor; // <3>
  SonarSensor sonarSensor;
#ifndef MAKE_RASPIKE
  const int8_t pwm = (Motor::PWM_MAX) / 6;
#else
  const int8_t pwm = 60;
#endif

};
