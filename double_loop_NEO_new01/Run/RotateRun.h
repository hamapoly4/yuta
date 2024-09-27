#ifndef ___CLASS_ROTATERUN
#define ___CLASS_ROTATERUN	// インクルードカード

#include "Run.h"
#include "GyroStopP.h"
#include "Motor.h"

class RotateRun : public Run {
public:
	enum eRota { LEFT, RIGHT, };

	RotateRun(eRota r, GyroStopP* gyrostopp, ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, eSpeed s = LOW);

	void run();

private:
	GyroStopP* mGyroStopP;

	eRota rota;
};

#endif // ___CLASS_ROTATERUN
