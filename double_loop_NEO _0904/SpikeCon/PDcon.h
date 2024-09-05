#ifndef ___CLASS_PDCON
#define ___CLASS_PDCON	// インクルードカード

#include "GyroSensor.h"
#include "ColorDetect.h"

class PDcon {
private:

    enum eRun { STRAIGHT, LINETRACE, };

    ev3api::GyroSensor& mGyroSensor;
    ColorDetect* mColorDetect;

    int mthreathold;
    int mdiff;
    int mold_diff;
    float mPgain;
    float mDgain;
    int mP_value;
    int mD_value;
    int mturn;
    unsigned char mRunmethod;

public:
    PDcon(unsigned char runmethod, ev3api::GyroSensor& gyrosensor, ColorDetect* colordetect);
    int getTurn();
    void calcTurn();
    void calcP();
    void calcD();
};

#endif // ___CLASS_PDCON
