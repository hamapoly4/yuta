#ifndef ___CLASS_ROTATERUN
#define ___CLASS_ROTATERUN	// インクルードカード

#include "abstract_run.h"
#include "Motor.h"

class RotateRun : public Run {
private:
	enum Rota { LEFT, RIGHT, };

	static const int PWM = 55;

	ev3api::Motor& mLeftMotor;
	ev3api::Motor& mRightMotor;

	unsigned char mrota;

public:
	RotateRun(unsigned char rota, ev3api::Motor& leftmotor, ev3api::Motor& rightmotor);

	void run();
};

#endif // ___CLASS_ROTATERUN
