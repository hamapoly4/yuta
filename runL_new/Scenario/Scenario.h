#ifndef ___CLASS_SCENARIO
#define ___CLASS_SCENARIO

#define SIZE 7

#include "Scene.h"
#include "Motor.h"
#include "ColorDetect.h"

class Scenario {
private:
	static const unsigned char TOP = 0;
	static const unsigned char LAST = 6;

	Scene* mScene[SIZE];
	ev3api::Motor&		 mLeftMotor;
	ev3api::Motor&		 mRightMotor;
	ev3api::Motor&       mLeftMotorEncoder;
	ev3api::Motor&       mRightMotorEncoder;
	ev3api::Motor&       mResetLeft;
	ev3api::Motor&       mResetRight;
	ColorDetect*		 mColorDetect;

	unsigned char mscene_no;
	bool mscene_switch_flag;
	bool mscenario_fin_flag;

public:
	Scenario(Scene* scene[], ev3api::Motor& leftmotor, ev3api::Motor& rightmotor,
				ev3api::Motor& leftmotorencoder, ev3api::Motor& rightmotorencoder,
					ev3api::Motor& resetleft, ev3api::Motor& resetright, ColorDetect* colordetect);
	void run();
	void switch_scene();
	void reset_device();
	bool finish();
};

#endif // ___CLASS_SCENARIO
