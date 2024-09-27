#ifndef ___CLASS_LINESEARCHRUN
#define ___CLASS_LINESEARCHRUN

#include "Run.h"
#include "Motor.h"

class LineSearchRun : public Run {
public:
    LineSearchRun(ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, eSpeed s = LOW);
    void run();
};

#endif // ___CLASS_LINESEARCHRUN