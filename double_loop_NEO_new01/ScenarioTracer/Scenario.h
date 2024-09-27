#ifndef ___CLASS_SCENARIO
#define ___CLASS_SCENARIO

#include "Scene.h"

class Scenario {
private:
	static const int8_t SIZE = 17;

	enum eState { INITIAL, EXE_SCENE, SWITCH_SCENE };

	Scene* mScene[SIZE];

	int8_t scene_no;

public:
	Scenario(Scene* scene[]);
	eState getState();
	void execute();
	void exeInitial();
	void exeScene();
	void switchScene();
};

#endif // ___CLASS_SCENARIO
