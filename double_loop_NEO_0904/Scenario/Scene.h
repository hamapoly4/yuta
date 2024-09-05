#ifndef ___CLASS_SCENE
#define ___CLASS_SCENE

#include "abstract_run.h"	// 抽象クラスのヘッダ（走行）
#include "RotateRun.h"		//
#include "StraRun.h"		//
#include "LineTraceRun.h"	// 派生クラス

#include "JudgeMent.h"				// 抽象クラスのヘッダ（判定）
#include "RotateAngleJudgeMent.h"	//
#include "RunDistJudgeMent.h"		//
#include "ColorJudgeMent.h"			// 派生クラス

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
