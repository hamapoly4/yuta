#include "Motor.h"       // <1>
#include "GyroSensor.h"
#include "SonarSensor.h"
#include "ColorSensor.h"
#include "ev3api.h"
#include "HSVconv.h"

using namespace ev3api;  // <4>

class Tracer {  // <1>
public:
  Tracer(HSVconv& hsvconv);
  void run();       // <2>
  void rotate(signed char ideal);
  void stra_run();
  void terminate();
  void linetrace();

private:
  Motor leftWheel;
  Motor rightWheel;
  GyroSensor gyroSensor; // <3>
  SonarSensor sonarSensor;
  ColorSensor colorSensor;
  HSVconv& mHSVconv;
  
  unsigned char scene = 1;
  const int8_t mThreshold = 20;  // <4>
#ifndef MAKE_RASPIKE
  const int8_t pwm = (Motor::PWM_MAX) / 6;
#else
  const int8_t pwm = 45;
#endif

  rgb_raw_t rgb;
};
