#ifndef ___CLASS_LINETRACERUN
#define ___CLASS_LINETRACERUN	// インクルードカード

#include "Run.h"
#include "Control.h"
#include "Motor.h"

class LineTraceRun : public Run {
public:
	enum eEdge { LEFT, RIGHT, };

	LineTraceRun(eEdge e, Control* linetracepd, ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, eSpeed s);
	void run();

private:
	Control* mLineTracePD;
	eEdge edge;
};

#endif // ___CLASS_LINETRACERUN
