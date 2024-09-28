#include "ColorJudge.h"
#include <stdio.h>

const ColorDetect::eColor ColorJudge::target_color[6] = {
	ColorDetect::BLACK, ColorDetect::BLUE,
	ColorDetect::BLACK, ColorDetect::BLUE,
	ColorDetect::BLACK, ColorDetect::BLUE,
};

int8_t ColorJudge::size = 0;

ColorJudge::ColorJudge(ColorDetect* colordetect)
	: mColorDetect(colordetect)
{
	cnt = size++;
}

bool ColorJudge::judge()
{
	printf("Color judge!!\n");
	current_color = mColorDetect->getColor(target_color[cnt]);

	if (current_color == target_color[cnt])
	{
		return true;
	}

	return false;
}
