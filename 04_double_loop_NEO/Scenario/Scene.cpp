#include "Scene.h"
#include <stdio.h>

Scene::Scene(unsigned char scene_no)
	: mcurrent_scene_no(scene_no)
{
	// 各シーンに応じた走行オブジェクトを確保
	switch (mcurrent_scene_no)
	{
		case  0:
		case  3:
		case  5:
		case 13:
		case 15:
			mRun[mcurrent_scene_no] = new RotateRun(RIGHT);
			break;
		case  1:
		case  6:
		case 11:
			mRun[mcurrent_scene_no] = new StraRun;
			break;
		case  2:
		case  7:
		case 12:
		case 14:
			mRun[mcurrent_scene_no] = new LineSearchRun;
			break;
		case  4:
			mRun[mcurrent_scene_no] = new LineTraceRun(RIGHT);
			break;
		case  8:
		case 10:
			mRun[mcurrent_scene_no] = new RotateRun(LEFT);
			break;
		case  9:
			mRun[mcurrent_scene_no] = new LineTraceRun(LEFT);
			break;
		default:
			break;
	}

	// 各シーンに応じた判定オブジェクトを確保
	switch (mcurrent_scene_no)
	{
		case  0:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 13);
			break;
		case  1:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 500);
			break;
		case  2:
		case  7:
		case 14:
			mJudgeMent[mcurrent_scene_no] = new ColorJudgeMent(BLACK);
			break;
		case  3:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 30);
			break;
		case  4:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(RIGHT, 650);
			break;
		case  5:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 16);
			break;
		case  6:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 800);
			break;
		case  8:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -30);
			break;
		case  9:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(LEFT, 1200);
			break;
		case 10:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(LEFT, -27);
			break;
		case 11:
			mJudgeMent[mcurrent_scene_no] = new RunDistJudgeMent(BOTH, 1200);
			break;
		case 12:
			mJudgeMent[mcurrent_scene_no] = new ColorJudgeMent(BLUE);
			break;
		case 13:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 15);
			break;
		case 15:
			mJudgeMent[mcurrent_scene_no] = new RotateAngleJudgeMent(RIGHT, 15);
			break;
		default:
			break;
	}
}

Scene::~Scene()
{
	delete mRun[mcurrent_scene_no];
	delete mJudgeMent[mcurrent_scene_no];

	printf("シーン番号：%d シーンオブジェクトの解放！！\n\n", mcurrent_scene_no + 1);
}

void Scene::run()
{
	mRun[mcurrent_scene_no]->run();
}

bool Scene::fin_judge()
{
	return mJudgeMent[mcurrent_scene_no]->judge();
}
