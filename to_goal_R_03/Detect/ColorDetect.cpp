#include "ColorDetect.h"
#include <stdio.h>

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
		case RED:
			getRed();
			break;
		case BLUE:
			getBlue();
			break;
		default:
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

void ColorDetect::getRed()
{
	if (338 <= hue && hue <= 352)
	{
		color = RED;
		printf("color is RED!!\n");
	}
}

void ColorDetect::getBlue()
{
	if (208 <= hue && hue <= 213)
	{
		if (37 <= saturation && saturation <= 83)
		{
			color = BLUE;
		}
	}
}
