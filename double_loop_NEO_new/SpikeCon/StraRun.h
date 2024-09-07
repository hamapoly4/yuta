#ifndef ___CLASS_STRARUN
#define ___CLASS_STRARUN	// インクルードカード

#include "abstract_run.h"
#include "PDcon.h"
#include "Motor.h"

class StraRun : public Run {
private:
	static const int PWM = 35;

	ev3api::Motor& mLeftMotor;
	ev3api::Motor& mRightMotor;
	PDcon* mPDconGyro;

	int mturn;

public:
	StraRun(ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, PDcon* pdcongyro);
	void run();
};

#endif // ___CLASS_STRARUN
