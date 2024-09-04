#include "Tracer.h" // <1>
#include <stdio.h>

Tracer::Tracer(HSVconv& hsvconv):
  leftWheel(PORT_C), rightWheel(PORT_B), mHSVconv(hsvconv) { // <2>
}

bool Tracer::run() {
  
  const float Kp = 0.5;
  const float Kd = 2;
  const int target = 70;
  static int old_diff = 0;
  int diff = 0;
  int D_value = 0;
  int P_value = 0;
  int turn = 0;
  
  static bool blue_flag = true;    // for blue detect
  static bool black_flag = false;  // for black detect
  static unsigned char edge = 1;
  static bool fin_flag = false;
  
  int hue;
  int saturation;
  int value;
  
  mHSVconv.calcHSV();
  hue = mHSVconv.getH();
  saturation = mHSVconv.getS();
  value = mHSVconv.getV();
  
  //printf("h : %d\n", hue);
  //printf("s : %d\n", saturation);
  //printf("v : %d\n\n", value);

  if (blue_flag == true)
  {
    if (180 <= hue && hue <= 250)
    {
      if (60 <= saturation && saturation <= 87)
      {
        if (29 <= value && value <= 40)
        {
          blue_flag = false;
          black_flag = true;
          printf("blue detect!!\n\n");
          fin_flag = true;
        }
      }
    }
  }
  
  if (black_flag == true)
  {
    if (180 <= hue && hue <= 250)
    {
      if (value <= 20)
      {
        edge = 0;
        black_flag = false;
        printf("black detect!!\n");
        printf("change edge!!\n\n");
      }
    }
  }
  
  if (fin_flag == true)
  {
    return true;
  }

  // P control
  diff = value - target;
  P_value = Kp * diff;
  
  // D control
  D_value = (diff - old_diff) * Kd;
  
  // control sum
  turn = P_value + D_value;

  // RasPike run!!
  if (edge == 0)  // right edge
  {
    if (blue_flag == false)
    {
      printf("blue through hey!!\n\n");
    }
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
