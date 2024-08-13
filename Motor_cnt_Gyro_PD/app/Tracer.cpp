#include "Tracer.h" // <1>
#include <stdio.h>

Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), gyroSensor(PORT_4), sonarSensor(PORT_3) { // <2>
  }

void Tracer::angle_reset()
{
  gyroSensor.reset();
}

void Tracer::run() {
  static unsigned char flag = false;
  int16_t dist;
  dist = sonarSensor.getDistance();
  
  if (-1 < dist && dist < 5)
  {
    flag = true;
    return;
  }
  
  if (flag == false)
  {
    return;
  }
  
  
  int turn;
  int angle;
  
  /* Motor PID value */
  int left_cnt = 0;
  int right_cnt = 0;
  int cnt_diff = 0;
  
  angle = gyroSensor.getAngle();
  //printf("angle : %d\n", angle);
  
  left_cnt = leftWheel.getCount();
  right_cnt = rightWheel.getCount();
  cnt_diff = left_cnt - right_cnt ;
  
  turn = PDcalc(angle) + PDcalc(cnt_diff);
  
  printf("turn : %d\n", turn);
  // RasPike run!!
  leftWheel.setPWM(pwm - turn);
  rightWheel.setPWM(pwm + turn);
}

int Tracer::PDcalc(int mvalue)
{
  const float Kp = 1.5;
  const float Kd = 3;
  const int target = 0;
  
  static int old_diff = 0;
  
  int diff = 0;
  
  int D_value = 0;
  int P_value = 0;
  int turn = 0;
  
  // P control
  diff = mvalue - target;
  P_value = Kp * diff;
  
  // D control
  D_value = (diff - old_diff) * Kd;
  
  // control sum
  turn = P_value + D_value;
  
  old_diff = diff;
  
  return turn;
}

void Tracer::terminate() {
  leftWheel.stop();  // <1>
  rightWheel.stop();
}
