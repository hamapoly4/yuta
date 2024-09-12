#ifndef ___CLASS_RUNDISTJUDGEMENT
#define ___CLASS_RUNDISTJUDGEMENT

#include "JudgeMent.h"
#include "RunDistDetect.h"

class RunDistJudgeMent : public JudgeMent {
private:
	RunDistDetect *mRunDistDetect;

	float mtarget_dist;
	float mcurrent_dist;
	
public:
	RunDistJudgeMent(float target_dist, RunDistDetect* rundistdetect);
	bool judge();
};

#endif // ___CLASS_RUNDISTJUDGEMENT