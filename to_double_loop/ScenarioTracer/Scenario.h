#ifndef ___CLASS_SCENARIO
#define ___CLASS_SCENARIO

#include "Scene.h"

class Scenario {
public:
	enum eState { INITIAL, EXE_SCENE, SWITCH_SCENE, FINISH };

	static const int8_t ALL_SIZE = 24;
	static const int8_t LAP_SIZE = 7;
	static const int8_t DOUBLE_SIZE = 17;

	Scenario(Scene* scene[], int8_t t, int8_t l);
	eState getState();
	void execute();
	void exeInitial();
	void exeScene();
	void switchScene();

private:
	Scene* mScene[ALL_SIZE];

	int8_t top;
	int8_t last;

	int8_t scene_no;

	eState state;
};

#endif // ___CLASS_SCENARIO
