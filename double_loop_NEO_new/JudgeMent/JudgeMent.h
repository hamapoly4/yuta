#ifndef ___CLASS_JUDGEMENT
#define ___CLASS_JUDGEMENT

#include "GyroSensor.h"
#include "Motor.h"

class JudgeMent {
protected:
	static ev3api::GyroSensor mGyroSensor;
	static ev3api::Motor LeftMotorEncoder;
	static ev3api::Motor RightMotorEncoder;
	JudgeMent();
public:
	virtual ~JudgeMent() = 0;
	virtual bool judge() = 0;
};

#endif // ___CLASS_JUDGE