#ifndef ___CLASS_LINETRACERUN
#define ___CLASS_LINETRACERUN	// インクルードカード

#include "abstract_run.h"
#include "Motor.h"
#include "PIDcon.h"

class LineTraceRun : public Run {
private:
	PIDcon* mPIDcon;
	ev3api::Motor& mLeftMotor;
	ev3api::Motor& mRightMotor;
	enum eEdge { LEFT, RIGHT, };
	enum eSpeed { LOW, HIGH, };

	int mpwm;
	int mturn;
	unsigned char medge;
	unsigned char mspeed;

public:
	LineTraceRun(unsigned char edge, unsigned char speed,
		ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, PIDcon* pidcon);
	void run();
};

#endif // ___CLASS_LINETRACERUN
