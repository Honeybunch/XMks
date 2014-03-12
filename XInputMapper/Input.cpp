#include "Input.h"


Input::Input(short iT, char k, short sC, int mB, int mD, float mS)
{
	inputType = iT;

	key = k;
	specialCode = sC;

	mouseButton = mB;
	mouseDirection = mD;
	mouseSpeed = mS;
}


Input::~Input(void)
{
}
