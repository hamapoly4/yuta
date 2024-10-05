/*--------------------------------------------
 *	FILE NAME : abstract_run
 *	FILE TYPE : Header File
 *	AUTHOR    : Yuta Kondo
 * 	SUMMARY   : Abstract Class &
 *		    Sub Class
 *--------------------------------------------*/

#ifndef ___CLASS_RUN
#define ___CLASS_RUN	// インクルードカード

#include "Motor.h"

class Run {
public:
	enum eSpeed { LOW, MID, MID_HIGH, HIGH, HIGH_SUPER, };

	virtual void run() = 0;	// 純粋仮想関数

protected:
	ev3api::Motor& mLeftMotor;
	ev3api::Motor& mRightMotor;

	eSpeed speed;
	int8_t turn;
	int8_t pwm;
	Run(ev3api::Motor& leftmotor, ev3api::Motor& rightmotor, eSpeed s);
};

#endif // ___CLASS_RUN
