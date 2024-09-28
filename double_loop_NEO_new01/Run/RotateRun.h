#ifndef ___CLASS_ROTATERUN
#define ___CLASS_ROTATERUN	// インクルードカード

#include "Run.h"
#include "Control.h"
#include "GyroStopP.h"
#include "Motor.h"

class RotateRun : public Run {
public:
	enum eRota { LEFT, RIGHT, };

	RotateRun(eRota r, Control* gyrostopp, ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, eSpeed s = LOW);

	void run();

private:
	Control* mGyroStopP;

	eRota rota;
};

#endif // ___CLASS_ROTATERUN
