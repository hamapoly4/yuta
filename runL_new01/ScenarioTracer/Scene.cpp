﻿#include "Scene.h"

Scene::Scene(Run* run, Judge* judge)
	: mRun(run), mJudge(judge)
{
	;
}

void Scene::run()
{
	mRun->run();
}

bool Scene::judge()
{
	printf("Scene judge!!\n");
	return mJudge->judge();
}
