#include "HSVMonitor.h"

using namespace ev3api;

HSVMonitor::HSVMonitor(const ColorSensor& colorsensor)
    : mColorSensor(colorsensor)
{
    ;
}

void HSVMonitor::convHSV()
{
    setRGB();
	calcMax();
	calcMin();
	calcH();
	calcS();
	calcV();
}

void HSVMonitor::setRGB()
{
    mColorSensor.getRawColor(rgb);
}

void HSVMonitor::calcMax()
{
    max = rgb.r;
	if (max < rgb.g)
	{
		max = rgb.g;
	}
	
	if (max < rgb.b)
	{
		max = rgb.b;
	}
}

void HSVMonitor::calcMin()
{
    if (max == rgb.r)
	{
		min = rgb.g;
		if (min > rgb.b)
		{
			min = rgb.b;
		}
	}
	else if (max == rgb.g)
	{
		min = rgb.b;
		if (min > rgb.r)
		{
			min = rgb.r;
		}
	}
	else if (max == rgb.b)
	{
		min = rgb.r;
		if (min > rgb.g)
		{
			min = rgb.g;
		}
	}
}

void HSVMonitor::calcH()
{
	if (max == rgb.r)
	{
		hue = 60 * ((rgb.g - rgb.b) / (max - min));
	}
	else if (max == rgb.g)
	{
		hue = 60 * ((rgb.b - rgb.r) / (max - min)) + 120;
	}
	else if (max == rgb.b)
	{
		hue = 60 * ((rgb.r - rgb.g) / (max - min)) + 240;
	}
	else if (rgb.r == rgb.g && rgb.g == rgb.b)
	{
		hue = 0;
	}
	
	if (hue < 0)
	{
		hue += 360;
	}
}

void HSVMonitor::calcS()
{
	float f;
	f = (max - min) / max;
	saturation = f * 100;
}

void HSVMonitor::calcV()
{
	float f;
	f = max / 255;
	value = f * 100;
}

int HSVMonitor::getH() const
{
    return hue;
}

int HSVMonitor::getS() const
{
    return saturation;
}

int HSVMonitor::getV() const
{
	return value;
}
