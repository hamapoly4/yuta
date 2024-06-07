#include "app.h"
#include "util.h"

#include "Motor.h"
#include "ColorSensor"
#include "Clock.h"

using namespace ev3api;

class Tracer {  // <1>
public:
  Tracer();
  void run();       // <2>
  void init();
  void terminate();

private:
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor; // <3>
  const int8_t mThreshold = 22;  // <4>
#ifndef MAKE_RASPIKE
  const int8_t pwm = (Motor::PWM_MAX) / 6;
#else
  const int8_t pwm = 60;
#endif

 float calc_prop_value();
};
/////////////////////////////////////////////
Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_3) { // <2>
  }

void Tracer::init() {
  init_f("Tracer");
}

void Tracer::terminate() {
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}


  float Tracer::calc_prop_value(){
  const float Kp = 0.8;
  const int target = 35;
  const int bias = 5;

    int diff = colorSensor.getBrightness() - target;
    return (Kp * diff + bias);
  }

void Tracer::run() {
  msg_f("runnning...", 1);
  float turn = calc_prop_value();
  int pwm_l = pwm - turn;
  int pwm_r = pwm + turn;
  leftWheel.setPWM(pwm_l);
  rightWheel.setPWM(pwm_r);
}

Tracer tracer;  // <4>
Clock clock;    // <5>

void tracer_task(intptr_t exinf) { // <1>
  tracer.run(); // <2>
  ext_tsk();
}

void main_task(intptr_t unused) { // <1>
  const uint32_t duration = 100*1000; // <2>

  tracer.init(); // <3>
  sta_cyc(TRACER_CYC); // <4>
  
  while (!ev3_button_is_pressed(LEFT_BUTTON)) { // <1>
      clock.sleep(duration);   // <2>
  }

  stp_cyc(TRACER_CYC); // <3>
  tracer.terminate(); // <4>
  ext_tsk(); // <5>
}
