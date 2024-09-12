#ifndef ___CLASS_PIDcon
#define ___CLASS_PIDcon	// インクルードカード

#include "ColorDetect.h"

class PIDcon {
private:

    enum eSpeed { LOW, HIGH, };

    ColorDetect* mColorDetect;

    static const int mthreathold = 40;
    int mdiff;

    float mPgain;
    int mP_value;

    float mIgain;
    int msum;
    int mi;
    int mI_value;

    float mDgain;
    int mold_diff;
    int mD_value;

    int mturn;
    unsigned char mspeed;

public:
    PIDcon(unsigned char speed, ColorDetect* colordetect);
    int getTurn();
    void calcTurn();
    void getDiff();
    void calcP();
    void calcI();
    void calcD();
};

#endif // ___CLASS_PIDcon
