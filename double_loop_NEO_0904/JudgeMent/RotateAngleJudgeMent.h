#ifndef ___CLASS_ROTATEANGLEJUDGEMENT
#define ___CLASS_ROTATEANGLEJUDGEMENT

#include "JudgeMent.h"
#include "GyroSensor.h"

class RotateAngleJudgeMent : public JudgeMent {
private:

	enum eRota { LEFT, RIGHT, };

	ev3api::GyroSensor& mGyroSensor;
	
	int mtarget_angle;
	int mcurrent_angle;
	unsigned char mrota;

public:
	RotateAngleJudgeMent(unsigned char rota, int target_angle, ev3api::GyroSensor& gyrosensor);
	bool judge();
};

#endif // ___CLASS_ROTATEANGLEJUDGEMENT
