#include "Scenario.h"
#include <stdio.h>

using namespace ev3api;

Scenario::Scenario(Scene* scene[], int8_t t, int8_t l)
	: state(INITIAL), top(t), last(l)
{
	int8_t i;
	for (i = 0; i < ALL_SIZE; i++)
	{
		mScene[i] = scene[i];
	}
}

Scenario::eState Scenario::getState()
{
	return state;
}

void Scenario::execute()
{
	switch (state)
	{
		case INITIAL:
			exeInitial();
			break;
		case EXE_SCENE:
			exeScene();
			break;
		case SWITCH_SCENE:
			switchScene();
			break;
		default:
			break;
	}
}

void Scenario::exeInitial()
{
	scene_no = top;
	state = EXE_SCENE;
}

void Scenario::exeScene()
{
	mScene[scene_no]->run();

	if (mScene[scene_no]->judge() == true)
	{
		state = SWITCH_SCENE;
	}
}

void Scenario::switchScene()
{
	scene_no++;

	if (scene_no > last)
	{
		state = FINISH;
	}
	else
	{
		state = EXE_SCENE;
	}
}
