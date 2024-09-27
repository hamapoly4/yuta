#ifndef ___CLASS_LINETRACEPI
#define ___CLASS_LINETRACEPD

#include "HSVMonitor.h"

class LineTracePD : public Control {
private:
    HSVMonitor* mHSVMonitor;

    static const int THREATHOLD = 70;
    static const float PGAIN = 0.5;
    static const float DGAIN = 2;

public:
    LineTracePD(HSVMonitor* HSVMonitor);
    int getTurn();
    void calcTurn();
    void calcP();
    void calcD();
};

#endif // ___CLASS_LINETRACEPD
