#ifndef ___CLASS_GYROSTRA
#define ___CLASS_GYROSTRA

#include "Control.h"
#include "AngleMonitor.h"

class GyroStraPD : public Control {
private:
    AngleMonitor* mAngleMonitor;

    static const int THREATHOLD = 0;
    static constexpr float PGAIN = 1.5;
    static constexpr float DGAIN = 3;

public:
    GyroStraPD(AngleMonitor* anglemonitor);
    int getTurn();
    void calcTurn();
    void calcP();
    void calcD();
};

#endif // ___CLASS_GYROSTRA
