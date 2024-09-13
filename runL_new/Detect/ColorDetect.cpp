#include "ColorDetect.h"

using namespace ev3api;

ColorDetect::ColorDetect(const ColorSensor& colorsensor)
    : mColorSensor(colorsensor), mcolor(ELSE)
{
    ;
}

unsigned char ColorDetect::getColor()
{
	if (180 <= mhue && mhue <= 250)
	{
		if (mvalue <= 20)
		{
			mcolor = BLACK;
		}
	}
	
	if (211 <= mhue && mhue <= 213)
	{
		if (60 <= msaturation && msaturation <= 83)
		{
			mcolor = BLUE;
		}
	}
	
    return mcolor;
}

int ColorDetect::getV()
{
	return mvalue;
}

void ColorDetect::convHSV()
{
    setRGB();
	calcMax();
	calcMin();
	calcH();
	calcS();
	calcV();
}

void ColorDetect::setRGB()
{
    mColorSensor.getRawColor(mrgb);
}

void ColorDetect::calcMax()
{
    mmax = mrgb.r;
	if (mmax < mrgb.g)
	{
		mmax = mrgb.g;
	}
	
	if (mmax < mrgb.b)
	{
		mmax = mrgb.b;
	}
}

void ColorDetect::calcMin()
{
    if (mmax == mrgb.r)
	{
		mmin = mrgb.g;
		if (mmin > mrgb.b)
		{
			mmin = mrgb.b;
		}
	}
	else if (mmax == mrgb.g)
	{
		mmin = mrgb.b;
		if (mmin > mrgb.r)
		{
			mmin = mrgb.r;
		}
	}
	else if (mmax == mrgb.b)
	{
		mmin = mrgb.r;
		if (mmin > mrgb.g)
		{
			mmin = mrgb.g;
		}
	}
}

void ColorDetect::calcH()
{
	if (mmax == mrgb.r)
	{
		mhue = 60 * ((mrgb.g - mrgb.b) / (mmax - mmin));
	}
	else if (mmax == mrgb.g)
	{
		mhue = 60 * ((mrgb.b - mrgb.r) / (mmax - mmin)) + 120;
	}
	else if (mmax == mrgb.b)
	{
		mhue = 60 * ((mrgb.r - mrgb.g) / (mmax - mmin)) + 240;
	}
	else if (mrgb.r == mrgb.g && mrgb.g == mrgb.b)
	{
		mhue = 0;
	}
	
	if (mhue < 0)
	{
		mhue += 360;
	}
}

void ColorDetect::calcS()
{
	float f;
	f = (mmax - mmin) / mmax;
	msaturation = f * 100;
}

void ColorDetect::calcV()
{
	float f;
	f = mmax / 255;
	mvalue = f * 100;
}
