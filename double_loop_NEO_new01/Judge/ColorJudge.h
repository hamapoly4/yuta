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

	static const Detect::eColor target_color[] = {
		BLACK, BLUE, BLACK, BLUE, BLACK, BLUE,
	};

	static int8_t size;

	int8_t cnt;

	Detect::eColor current_color;
};

#endif // ___CLASS_COLORJUDGE