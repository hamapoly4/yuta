#include "Tracer.h" // <1>
#include <stdio.h>

Tracer::Tracer(Motor& leftwheel, Motor& rightwheel, RunDistDetect& rundistdetect, HSVconv& hsvconv):
  leftWheel(leftwheel), rightWheel(rightwheel),
  mRunDistDetect(rundistdetect), mHSVconv(hsvconv) { // <2>
}

bool Tracer::run() {
  static int pwm = 35;
  
  static int cnt1 = 0;
  static int cnt2 = 0;
  
  static bool flag = false;
  static float Kp = 0.5;
  static float Ki = 0;
  static float Kd = 2;
  const int target = 40;
  
  static int dist_target = 2700;
  static int dist_target2 = 50;
  
  int dist = 0;
  
  static int old_diff = 0;
  int diff = 0;
  static int sum = 0;
  static unsigned char i;
  int D_value = 0;
  int I_value = 0;
  int P_value = 0;
  int turn = 0;
  
  const unsigned char edge = 1;
  
  static bool fin_flag = false;
  
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
  if (flag == false)
  {
    if (dist >= dist_target2)
    {
      flag = true;
      pwm = 70;
      Kp = 0.1;
      Ki = 0.005;
      Kd = 3;
      cnt1++;
      if (cnt1 == 2)
      {
        dist_target = 1700;
      }
      else if (cnt1 == 3)
      {
        dist_target = 550;
      }
      else if (cnt1 == 4)
      {
        printf("Morita Hikaru!!\n\n");
        fin_flag = true;
      }
      deviceReset();
      return false;
    }
  }
  
  if (flag == true)
  {
    if (dist >= dist_target)
    {
      flag = false;
      pwm = 35;
      dist_target2 = 400;
      Kp = 0.5;
      Ki = 0;
      Kd = 2;
      cnt2++;
      if (cnt2 == 4)
      {
        dist_target2 = 50;
      }
      deviceReset();
      return false;
    }
  }
  
  if (fin_flag == true)
  {
    return true;
  }

  // RasPike run!!
  if (edge == 0)  // right edge
  {
    leftWheel.setPWM(pwm - turn);
    rightWheel.setPWM(pwm + turn);
  }
  else if (edge == 1) // left edge
  {
    leftWheel.setPWM(pwm + turn);
    rightWheel.setPWM(pwm - turn);
  }
  
  old_diff = diff;
  
  return false;
}

void Tracer::terminate() {
  leftWheel.stop();  // <1>
  rightWheel.stop();
}

void Tracer::deviceReset()
{
  leftWheel.reset();
  rightWheel.reset();
}
