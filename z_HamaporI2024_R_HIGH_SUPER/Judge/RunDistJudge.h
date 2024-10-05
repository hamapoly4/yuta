#ifndef ___CLASS_RUNDISTJUDGE
#define ___CLASS_RUNDISTJUDGE

#include "Judge.h"
#include "RunDistDetect.h"

class RunDistJudge : public Judge {
public:
	RunDistJudge(RunDistDetect* rundistdetect);
	bool judge();

private:
	RunDistDetect *mRunDistDetect;

	inline static constexpr float target_dist[17] = {
		80, 2700, 500, 1550, 550, 550,
		300, 100, 350, 150, 400, 160, 200,
		200, 100, 1900, 250,
	};

	static int8_t size;

	int8_t cnt;

	float current_dist;
};

#endif // ___CLASS_RUNDISTJUDGE
