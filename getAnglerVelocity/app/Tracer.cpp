#include "Tracer.h" // <1>
#include <stdio.h>

Tracer::Tracer()
  : mGyroSensor(PORT_4)
{
  ;
}

void Tracer::run()
{
  static int angle = 0;
  int raw;

  raw = mGyroSensor.getAnglerVelocity();
  angle += raw;

  printf("angle : %f\n", angle);
}
