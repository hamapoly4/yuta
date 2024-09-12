#ifndef ___CLASS_SCENE
#define ___CLASS_SCENE

#include "abstract_run.h"
#include "JudgeMent.h"

class Scene {
private:
	static unsigned char mscene_no;

	Run* mRun;
	JudgeMent* mJudgeMent;

	unsigned char mcurrent_scene_no;

public:
	Scene(Run* run, JudgeMent* judgement);
	void run();
	bool fin_judge();
};

#endif // ___CLASS_SCENE
