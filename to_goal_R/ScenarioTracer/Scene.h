#ifndef ___CLASS_SCENE
#define ___CLASS_SCENE

#include "Run.h"
#include "Judge.h"

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
