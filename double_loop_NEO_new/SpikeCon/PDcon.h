#ifndef ___CLASS_PDCON
#define ___CLASS_PDCON	// インクルードカード

#include "GyroSensor.h"
#include "ColorSensor.h"

class PDcon {
private:
    const ev3api::GyroSensor PDgyro;
    static ev3api::ColorSensor PDcolor;

    enum eRun { STRAIGHT, LINETRACE, };

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
    PDcon(const ev3api::GyroSensor pdgyro = 0, unsigned char runmethod, int threathold, float Pgain, float Dgain);
    ~PDcon();
    int getTurn();
    void calcTurn();
    void calcP();
    void calcD();
};

#endif // ___CLASS_PDCON