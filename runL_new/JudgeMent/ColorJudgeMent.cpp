#include "ColorJudgeMent.h"
#include <stdio.h>

ColorJudgeMent::ColorJudgeMent(unsigned char target_color, ColorDetect* colordetect)
	: mtarget_color(target_color), mColorDetect(colordetect)
{
	;
}

bool ColorJudgeMent::judge()
{
	mcurrent_color = mColorDetect->getColor();

	if (mcurrent_color == mtarget_color)
	{
		return true;
	}

	return false;
}
