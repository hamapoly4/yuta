#include "RunDistDetect.h"

using namespace ev3api;

RunDistDetect::RunDistDetect(const Motor& leftmotorencoder, const Motor& rightmotorencoder)
    : mLeftMotorEncoder(leftmotorencoder), mRightMotorEncoder(rightmotorencoder),
      mold_left_cnt(0), mold_right_cnt(0), mleft_sum(0), mright_sum(0)
{
    ;
}

float RunDistDetect::getRunDist()
{    
    measureRunDist();
    return mrun_dist;
}

void RunDistDetect::measureRunDist()
{
    mright_cnt = mRightMotorEncoder.getCount();
    mleft_cnt = mLeftMotorEncoder.getCount();

    mright_sum += mright_cnt - mold_right_cnt;
    mleft_sum += mleft_cnt - mold_left_cnt;

    mrun_dist = (mright_sum + mleft_sum) * mANGLE1DIST / 2.0;

    mold_right_cnt = mright_cnt;
    mold_left_cnt = mleft_cnt;
}
