#ifndef ___CLASS_SCENE
#define ___CLASS_SCENE

#include "Run.h"
#include "LineSearchRun.h"
#include "LineTraceRun.h"
#include "RotateRun.h"
#include "StraRun.h"

#include "Judge.h"
#include "RotateAngleJudge.h"
#include "RunDistJudge.h"
#include "ColorJudge.h"

class Scene {
public:
	Scene(Run* run, Judge* judge);
	void run();
	bool judge();

private:
	Run* mRun;
	Judge* mJudge;
};

#endif // ___CLASS_SCENE
