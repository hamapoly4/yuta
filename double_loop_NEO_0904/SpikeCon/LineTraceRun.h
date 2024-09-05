#ifndef ___CLASS_LINETRACERUN
#define ___CLASS_LINETRACERUN	// インクルードカード

#include "abstract_run.h"
#include "Motor.h"
#include "PDcon.h"

class LineTraceRun : public Run {
private:
	static const int PWM = 45;

	PDcon* mPDconColor;
	ev3api::Motor& mLeftMotor;
	ev3api::Motor& mRightMotor;

	enum eEdge { LEFT, RIGHT, };

	int mturn;
	unsigned char medge;

public:
	LineTraceRun(unsigned char edge, ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, PDcon* pdconcolor);
	void run();
};

#endif // ___CLASS_LINETRACERUN
