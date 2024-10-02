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

	inline static constexpr float target_dist[6] = {
		300, 100, 300, 150, 200, 160,
	};

	static int8_t size;

	int8_t cnt;

	float current_dist;
};

#endif // ___CLASS_RUNDISTJUDGE
