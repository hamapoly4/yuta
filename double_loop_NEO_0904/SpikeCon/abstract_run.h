/*--------------------------------------------
 *	FILE NAME : abstract_run
 *	FILE TYPE : Header File
 *	AUTHOR    : Yuta Kondo
 * 	SUMMARY   : Abstract Class &
 *		    Sub Class
 *--------------------------------------------*/

#ifndef ___ABSTRACT_CLASS
#define ___ABSTRACT_CLASS	// インクルードカード

class Run {
protected:
	int mfix_pwm;	// 既定のPWM値
	Run(int pwm);	// コンストラクタ
public:
	virtual void run() = 0;	// 純粋仮想関数
};

#endif // ___ABSTRACT_CLASS
