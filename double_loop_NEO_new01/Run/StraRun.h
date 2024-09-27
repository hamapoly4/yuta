#ifndef ___CLASS_STRARUN
#define ___CLASS_STRARUN	// インクルードカード

#include "Run.h"
#include "GyroStraPD.h"
#include "Motor.h"

class StraRun : public Run {
public:
	StraRun(GyroStraPD* gyrostrapd, ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, eSpeed s);
	void run();

private:
	GyroStraPD* mGyroStraPD;
};

#endif // ___CLASS_STRARUN
