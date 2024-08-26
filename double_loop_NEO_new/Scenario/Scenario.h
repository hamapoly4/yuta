#ifndef ___CLASS_SCENARIO
#define ___CLASS_SCENARIO

#include "Scene.h"

class Scenario {
private:
	static const unsigned char TOP = 0;
	static const unsigned char LAST = 15;

	Scene* mScene[16];
	unsigned char mscene_no;
	bool mscene_switch_flag;
	bool mscenario_fin_flag;

public:
	Scenario();
	~Scenario();
	void run();
	void switch_scene();
	bool finish();
};

#endif // ___CLASS_SCENARIO