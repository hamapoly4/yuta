#ifndef ___CLASS_COLORJUDGE
#define ___CLASS_COLORJUDGE

#include "Judge.h"
#include "ColorDetect.h"

class ColorJudge : public Judge {
public:
	ColorJudge(ColorDetect* colordetect);
	bool judge();

private:
	ColorDetect *mColorDetect;

	static const ColorDetect::eColor target_color[10];

	static int8_t size;

	int8_t cnt;

	ColorDetect::eColor current_color;
};

#endif // ___CLASS_COLORJUDGE
