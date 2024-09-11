#include "Motor.h"       // <1>
#include "ev3api.h"
#include "RunDistDetect.h"
#include "HSVconv.h"

using namespace ev3api;  // <4>

class Tracer {  // <1>
public:
  Tracer(Motor& leftwheel, Motor& rightwheel, RunDistDetect& rundistdetect, HSVconv& hsvconv);
  bool run();       // <2>
  void terminate();

private:
  Motor& leftWheel;
  Motor& rightWheel;
  RunDistDetect& mRunDistDetect;
  HSVconv& mHSVconv;
  const int8_t mThreshold = 20;  // <4>
  const int pwm = 35;

  rgb_raw_t rgb;
};
