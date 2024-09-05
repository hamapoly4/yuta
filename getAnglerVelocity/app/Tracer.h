#include "GyroSensor.h"

class Tracer {  // <1>
public:
  Tracer();
  void run();       // <2>

private:
  ev3api::GyroSensor mGyroSensor;
};
