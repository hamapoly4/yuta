#ifndef ___CLASS_LINETRACERUN
#define ___CLASS_LINETRACERUN	// インクルードカード

#include "Run.h"
#include "LineTracePD.h"
#include "Motor.h"

class LineTraceRun : public Run {
public:
	enum eEdge { LEFT, RIGHT, };

	LineTraceRun(eEdge e, LineTracePD* linetracepd, ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, eSpeed s);
	void run();

private:
	LineTracePD* mLineTracePD;
	eEdge edge;
};

#endif // ___CLASS_LINETRACERUN
