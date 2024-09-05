#include "Scene.h"
#include <stdio.h>

unsigned char Scene::mscene_no = 0;

Scene::Scene(Run* run, JudgeMent* judgement)
	: mRun(run), mJudgeMent(judgement)
{
	mcurrent_scene_no = mscene_no++;
}

void Scene::run()
{
	mRun[mcurrent_scene_no]->run();
}

bool Scene::fin_judge()
{
	return mJudgeMent[mcurrent_scene_no]->judge();
}
