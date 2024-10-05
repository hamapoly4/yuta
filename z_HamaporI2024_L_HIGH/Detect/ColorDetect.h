#ifndef ___CLASS_COLORDETECT
#define ___CLASS_COLORDETECT

#include "HSVMonitor.h"

class ColorDetect {
public:
    enum eColor { BLACK, BLUE, ELSE, };

    ColorDetect(HSVMonitor* hsvmonitor);
    eColor getColor(eColor target_color);
    void getBlack();
    void getBlue();

private:
    HSVMonitor* mHSVMonitor;

    eColor color;
    int hue;
    int saturation;
    int value;
};

#endif // ___CLASS_COLORDETECT