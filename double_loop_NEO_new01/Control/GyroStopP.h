#ifndef ___CLASS_GYROSTOPP
#define ___CLASS_GYROSTOPP

#include "AngleMonitor.h"

class GyroStopP : public Control {
public:
    GyroStopP(AngleMonitor* anglemonitor);
    int getTurn();
    void calcTurn();
    void calcP();

private:
    AngleMonitor* mAngleMonitor;

    static const float PGAIN = 0.17;
    static const int threathold[] = {
		1, 35, 10, 20,
	};

	static int8_t size;

	int8_t cnt;
};

#endif // ___CLASS_GYROSTOPP