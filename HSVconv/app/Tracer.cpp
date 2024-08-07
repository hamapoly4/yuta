#include "Tracer.h" // <1>
#include <stdio.h>

Tracer::Tracer(HSVconv& hsvconv):
  leftWheel(PORT_C), rightWheel(PORT_B), gyroSensor(PORT_4), mHSVconv(hsvconv) { // <2>
}

void Tracer::terminate() {
  leftWheel.stop();  // <1>
  rightWheel.stop();
}

void Tracer::run() {
  mHSVconv.calcHSV();
  
  printf("Red        : %d\n", mHSVconv.getR());
  printf("Green      : %d\n", mHSVconv.getG());
  printf("Blue       : %d\n", mHSVconv.getB());
  printf("\n");
  printf("Hue        : %d\n", mHSVconv.getH());
  printf("Saturation : %d\n", mHSVconv.getS());
  printf("Value      : %d\n", mHSVconv.getV());
  printf("\n");
  printf("MAX        : %f\n", mHSVconv.getMAX());
  printf("MIN        : %f\n", mHSVconv.getMIN());
  printf("\n");
  printf("\n");
}
