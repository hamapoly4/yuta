#include "Tracer.h" // <1>
#include <stdio.h>

Tracer::Tracer(Motor& leftwheel, Motor& rightwheel, RunDistDetect& rundistdetect, HSVconv& hsvconv):
  leftWheel(leftwheel), rightWheel(rightwheel),
  mRunDistDetect(rundistdetect), mHSVconv(hsvconv) { // <2>
}

bool Tracer::run() {
  
  const float Kp = 0.1;
  const float Ki = 0.005;
  const float Kd = 3;
  const int target = 40;
  
  const int dist_target = 2800;
  const float KP = 0.0125;
  
  int dist = 0;
  int PWM = 0;
  
  static int old_diff = 0;
  int diff = 0;
  static int sum = 0;
  static unsigned char i;
  int D_value = 0;
  int I_value = 0;
  int P_value = 0;
  int turn = 0;
  
  const unsigned char edge = 1;
  
  int value;
  
  mHSVconv.calcHSV();
  value = mHSVconv.getV();

  // P control
  diff = value - target;
  P_value = Kp * diff;
  
  // I control
  sum += diff;
  I_value = Ki * sum;
  i++;
  if (i >= 20)
  {
    i = 0;
    sum  = 0;
  }
  
  // D control
  D_value = (diff - old_diff) * Kd;
  
  // control sum
  turn = P_value + I_value + D_value;
  
  dist = mRunDistDetect.getRunDist();
  if (dist >= dist_target)
  {
    return true;
  }
  
  PWM = pwm + KP * (dist_target - dist);

  // RasPike run!!
  if (edge == 0)  // right edge
  {
    leftWheel.setPWM(PWM - turn);
    rightWheel.setPWM(PWM + turn);
  }
  else if (edge == 1) // left edge
  {
    leftWheel.setPWM(PWM + turn);
    rightWheel.setPWM(PWM - turn);
  }
  
  old_diff = diff;
  
  return false;
}

void Tracer::terminate() {
  leftWheel.stop();  // <1>
  rightWheel.stop();
}
