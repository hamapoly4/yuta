#ifndef ___CLASS_LINE_TRACE_PID
#define ___CLASS_LINE_TRACE_PID

#include "Control.h"
#include "HSVMonitor.h"

class LowLineTracePID : public Control {
public:
    LowLineTracePID(HSVMonitor* HSVMonitor, int8_t t, float p, float i, float d);
    int getTurn();
    void calcTurn();
    void calcP();
    void calcI();
    void calcD();

private:
    HSVMonitor* mHSVMonitor;

    int8_t threathold;
    float pgain;
    float igain;
    float dgain;
};

#endif // ___CLASS_LINE_TRACE_PID
