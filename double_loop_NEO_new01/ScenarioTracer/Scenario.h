#ifndef ___CLASS_SCENARIO
#define ___CLASS_SCENARIO

#include "Scene.h"

class Scenario {
public:
	enum eState { INITIAL, EXE_SCENE, SWITCH_SCENE };
	static const int8_t SIZE = 17;

	Scenario(Scene* scene[]);
	eState getState();
	void execute();
	void exeInitial();
	void exeScene();
	void switchScene();

private:
	Scene* mScene[SIZE];

	int8_t scene_no;

	eState state;
};

#endif // ___CLASS_SCENARIO
