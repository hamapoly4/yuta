#ifndef ___CLASS_ROTATEANGLEJUDGE
#define ___CLASS_ROTATEANGLEJUDGE

#include "Judge.h"
#include "AngleMonitor.h"

class RotateAngleJudge : public Judge {
public:
	enum eRota { LEFT, RIGHT, };

	RotateAngleJudge(eRota r, AngleMonitor* anglemonitor);
	bool judge();

private:
	AngleMonitor* mAngleMonitor;

	static const int target_angle[5];

	static int8_t size;

	int8_t cnt;

	int current_angle;
	eRota rota;
};

#endif // ___CLASS_ROTATEANGLEJUDGE
