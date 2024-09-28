#include "ColorDetect.h"

ColorDetect::ColorDetect(HSVMonitor* hsvmonitor)
    : mHSVMonitor(hsvmonitor)
{
    ;
}

ColorDetect::eColor ColorDetect::getColor(eColor target_color)
{
	color = ELSE;

	hue = mHSVMonitor->getH();
	saturation = mHSVMonitor->getS();
	value = mHSVMonitor->getV();

	switch (target_color)
	{
		case BLACK:
			getBlack();
			break;
		case BLUE:
			getBlue();
			break;
	}
	
    return color;
}

void ColorDetect::getBlack()
{
	if (180 <= hue && hue <= 250)
	{
		if (value <= 20)
		{
			color = BLACK;
		}
	}
}

void ColorDetect::getBlue()
{
	if (211 <= hue && hue <= 213)
	{
		if (60 <= saturation && saturation <= 83)
		{
			color = BLUE;
		}
	}
}
