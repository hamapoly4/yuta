#ifndef ___CLASS_LINETRACEPD
#define ___CLASS_LINETRACEPD

#include "Control.h"
#include "HSVMonitor.h"

class LineTracePD : public Control {
private:
    HSVMonitor* mHSVMonitor;

    static const int THREATHOLD = 70;
    static constexpr float PGAIN = 0.5;
    static constexpr float DGAIN = 2;

public:
    LineTracePD(HSVMonitor* HSVMonitor);
    int getTurn();
    void calcTurn();
    void calcP();
    void calcD();
};

#endif // ___CLASS_LINETRACEPD
