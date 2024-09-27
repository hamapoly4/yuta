#ifndef ___CLASS_SCENE
#define ___CLASS_SCENE

#include "Run.h"	// ���ۃN���X�̃w�b�_�i���s�j
#include "RotateRun.h"		//
#include "StraRun.h"		//
#include "LineTraceRun.h"	// �h���N���X

#include "Judge.h"				// ���ۃN���X�̃w�b�_�i����j
#include "RotateAngleJudge.h"	//
#include "RunDistJudge.h"		//
#include "ColorJudge.h"			// �h���N���X

class Scene {
private:
	static int8_t scene_no;

	Run* mRun;
	Judge* mJudge;

	unsigned char current_scene_no;

public:
	Scene(Run* run, Judge* judge);
	void run();
	bool judge();
};

#endif // ___CLASS_SCENE
