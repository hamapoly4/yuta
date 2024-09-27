﻿#include "Scenario.h"
#include <stdio.h>

using namespace ev3api;

Scenario::Scenario(Scene* scene[])
	: state(INITIAL)
{
	int8_t i;
	for (i = 0; i < SIZE; i++)
	{
		mScene[i] = scene[i];
	}
}

eState Scenario::getState()
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
	}
}

void Scenario::exeInitial()
{
	scene_no = 0;
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

	if (scene_no > SIZE)
	{
		state = INITIAL;
	}
	else
	{
		state = EXE_SCENE;
	}
}
