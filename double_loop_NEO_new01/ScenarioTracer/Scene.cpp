#include "Scene.h"

int8_t Scene::scene_no = 0;

Scene::Scene(Run* run, Judge* judge)
	: mRun(run), mJudge(judge)
{
	current_scene_no = scene_no++;
}

void Scene::run()
{
	mRun->run();
}

bool Scene::judge()
{
	return mJudge->judge();
}
