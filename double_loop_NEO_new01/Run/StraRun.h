#ifndef ___CLASS_STRARUN
#define ___CLASS_STRARUN	// インクルードカード

#include "Run.h"
#include "Control.h"
#include "Motor.h"

class StraRun : public Run {
public:
	StraRun(Control* gyrostrapd, ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, eSpeed s);
	void run();

private:
	Control* mGyroStraPD;
};

#endif // ___CLASS_STRARUN
