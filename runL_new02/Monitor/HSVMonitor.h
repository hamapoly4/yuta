#ifndef ___CLASS_HSVMONITOR
#define ___CLASS_HSVMONITOR

#include "ColorSensor.h"

class HSVMonitor {
private:
    const ev3api::ColorSensor& mColorSensor;

    rgb_raw_t rgb;
    float max;
    float min;
    int hue;
    int saturation;
    int value;

public:
    HSVMonitor(const ev3api::ColorSensor& colorsensor);
    void convHSV();
    void setRGB();
    void calcMax();
    void calcMin();
    void calcH();
    void calcS();
    void calcV();
    int getH() const;
    int getS() const;
    int getV() const;
};

#endif // ___CLASS_HSVMONITOR