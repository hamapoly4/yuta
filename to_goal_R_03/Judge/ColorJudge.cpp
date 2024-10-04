#include "ColorJudge.h"
#include <stdio.h>

const ColorDetect::eColor ColorJudge::target_color[12] = {
	ColorDetect::BLUE,
	ColorDetect::BLACK, ColorDetect::BLUE,
	ColorDetect::BLACK, ColorDetect::BLUE,
	ColorDetect::BLACK, ColorDetect::BLUE,
	ColorDetect::BLUE,
	ColorDetect::BLUE, ColorDetect::RED,
	ColorDetect::RED, ColorDetect::RED,
};

int8_t ColorJudge::size = 0;

ColorJudge::ColorJudge(ColorDetect* colordetect)
	: mColorDetect(colordetect)
{
	cnt = size++;
}

bool ColorJudge::judge()
{
	current_color = mColorDetect->getColor(target_color[cnt]);

	if (current_color == target_color[cnt])
	{
		return true;
	}

	return false;
}
