#ifndef ___CLASS_GYROSTOPP
#define ___CLASS_GYROSTOPP

#include "Control.h"
#include "AngleMonitor.h"

class GyroStopP : public Control {
public:
    GyroStopP(AngleMonitor* anglemonitor);
    int getTurn();
    void calcTurn();
    void calcP();

private:
    AngleMonitor* mAngleMonitor;

    static constexpr float PGAIN = 0.1;
    static const int threathold[7];

	static int8_t size;

	int8_t cnt;
};

#endif // ___CLASS_GYROSTOPP
