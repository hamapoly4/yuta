#include "Tracer.h" // <1>
#include <stdio.h>

Tracer::Tracer(HSVconv& hsvconv):
  leftWheel(PORT_C), rightWheel(PORT_B), gyroSensor(PORT_4),
  sonarSensor(PORT_3), colorSensor(PORT_2), mHSVconv(hsvconv) { // <2>
}

void Tracer::run() {
  static unsigned char old_scene = 0;
  
  if (old_scene != scene)
  {
    leftWheel.setCount(0);
    rightWheel.setCount(0);
    gyroSensor.reset();
    
    old_scene = scene;
  }
  
  switch (scene)
  {
    case 1:
        rotate(13);
        break;
    case 2:
        stra_run();
        break;
    case 3:
        rotate(30);
        break;
    case 4:
        linetrace();
        break;
    case 5:
        rotate(16);
        break;
    case 6:
        stra_run();
        break;
    case 7:
        rotate(-30);
        break;
    case 8:
        linetrace();
        break;
    case 9:
        rotate(-27);
        break;
    case 10:
        stra_run();
        break;
    default:
        wup_tsk(MAIN_TASK);
        break;
  }
}

void Tracer::rotate(signed char ideal)
{
  static unsigned char flag = false;
  int16_t dist;
  int angle;
  
  dist = sonarSensor.getDistance();
  if (-1 < dist && dist < 5)
  {
    printf("RasPike Start!!\n");
    flag = true;
    return;
  }
  
  if (flag == false)
  {
    return;
  }

  if (scene == 7 || scene == 9)
  {
    angle = gyroSensor.getAngle();
    if (angle <= ideal)
    {
      printf("RasPike Rotate %d degree(Measured Value)\n", angle);
      
      scene++;
    }
  }
  else
  {
    angle = gyroSensor.getAngle();
    if (angle >= ideal)
    {
      printf("RasPike Rotate %d degree(Measured Value)\n", angle);
      
      scene++;
    }
  }
  
  if (scene == 7 || scene == 9)
  {
    leftWheel.setPWM(-pwm);
    rightWheel.setPWM(pwm);
  }
  else
  {
    leftWheel.setPWM(pwm);
    rightWheel.setPWM(-pwm);
  }
  // RasPike run!!
}

void Tracer::stra_run()
{
  const float Kp = 1.5;
  const float Kd = 3;
  const int target = 0;
  static int old_diff = 0;
  int diff = 0;
  int D_value = 0;
  int P_value = 0;
  int turn = 0;
  
  int angle;
  
  int stra_pwm = pwm - 5;
  
  int s;
  int v;

  // P control
  angle = gyroSensor.getAngle();
  diff = angle - target;
  P_value = Kp * diff;
  
  // D control
  D_value = (diff - old_diff) * Kd;
  
  // control sum
  turn = P_value + D_value;

  mHSVconv.calcHSV();
  if (scene == 10)
  {
    printf("gyroAngle : %d\n", angle);
    s = mHSVconv.getS();
    if (60 <= s && s <= 87)
    {
      v = mHSVconv.getV();
      if (29 <= v && v <= 40)
      {
        printf("h : %d\n", mHSVconv.getH());
        printf("s : %d\n", s);
        printf("v : %d\n", v);
        
        scene++;
      }
    }
  }
  else
  {
    s = mHSVconv.getS();
    if (s <= 25)
    {
      v = mHSVconv.getV();
      if (v < 10)
      {
        printf("h : %d\n", mHSVconv.getH());
        printf("s : %d\n", s);
        printf("v : %d\n", v);

        scene++;
      }
    }
  }
    
  // RasPike run!!
  leftWheel.setPWM(stra_pwm - turn);
  rightWheel.setPWM(stra_pwm + turn);
  printf("turn : %d\n", turn);

  old_diff = diff;
}

void Tracer::linetrace()
{
  const float Kp = 0.50;
  const float Kd = 2;
  const int target = 69;
  static int old_diff = 0;
  int diff = 0;
  int D_value = 0;
  int P_value = 0;
  int turn = 0;
  
  const float dist_1cnt = 0.87266;
  int left_cnt = 0;
  int right_cnt = 0;
  static int old_left_cnt = 0;
  static int old_right_cnt = 0;
  static float left_cnt_sum = 0;
  static float right_cnt_sum = 0;
  int run_dist = 0;
  
  int linetrace_pwm = pwm - 5;

  // P control
  diff = colorSensor.getBrightness() - target;
  P_value = Kp * diff;
  
  // D control
  D_value = (diff - old_diff) * Kd;
  
  // control sum
  turn = P_value + D_value;
  
  // RasPike run!!
  if (scene == 4)
  {
    leftWheel.setPWM(linetrace_pwm - turn);
    rightWheel.setPWM(linetrace_pwm + turn);
    
    right_cnt = rightWheel.getCount();
    right_cnt_sum += right_cnt - old_right_cnt;
    
    run_dist = right_cnt_sum * dist_1cnt;
    if (run_dist >= 700)
    {
      printf("distance is over 600mm!!\n");
      printf("right_cnt : %d\n", right_cnt);
      
      scene++;
    }
    old_right_cnt = right_cnt;
  }
  else if (scene == 8)
  {
    leftWheel.setPWM(linetrace_pwm + turn);
    rightWheel.setPWM(linetrace_pwm - turn);
    
    left_cnt = leftWheel.getCount();
    left_cnt_sum += left_cnt - old_left_cnt;
    
    run_dist = left_cnt_sum * dist_1cnt;
    if (run_dist >= 1200)
    {
      printf("distance is over 1200mm!!\n");
      printf("left_cnt : %d\n", left_cnt);
      
      scene++;
    }
    old_left_cnt = left_cnt;
  }
  
  old_diff = diff;
}

void Tracer::terminate() {
  leftWheel.stop();  // <1>
  rightWheel.stop();
}
