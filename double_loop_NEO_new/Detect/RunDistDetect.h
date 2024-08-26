#ifndef ___CLASS_RUNDISTDETECT
#define ___CLASS_RUNDISTDETECT

#include "Motor.h"

class RunDistDetect {
private:
    const float mANGLE1DIST = 0.87266;

    const ev3api::Motor& LeftMotorEncoder;
    const ev3api::Motor& RightMotorEncoder;

    enum eTire { RIGHT, LEFT, BOTH, };

    int mleft_cnt;
    int mright_cnt;
    int mold_left_cnt;
    int mold_right_cnt;
    float mleft_sum;
    float mright_sum;
    float mrun_dist;
    unsigned char mtire;

public:
    RunDistDetect(const ev3api::Motor& leftmotorencoder, const ev3api::Motor& rightmotorencoder, unsigned char tire);
    ~RunDistDetect();
    float getRunDist();
    void measureRunDist();
};

#endif // ___CLASS_RUNDISTDETECT