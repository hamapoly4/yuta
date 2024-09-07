#ifndef ___CLASS_SCENE
#define ___CLASS_SCENE

#include "abstract_run.h"	// ���ۃN���X�̃w�b�_�i���s�j
#include "RotateRun.h"		//
#include "StraRun.h"		//
#include "LineTraceRun.h"	// �h���N���X

#include "JudgeMent.h"				// ���ۃN���X�̃w�b�_�i����j
#include "RotateAngleJudgeMent.h"	//
#include "RunDistJudgeMent.h"		//
#include "ColorJudgeMent.h"			// �h���N���X

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
