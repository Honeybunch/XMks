#include "Input.h"


Input::Input(short iT, char k, short sC, int mB, int mD, float mS)
{
	inputType		= iT;

	key				= k;
	specialCode		= sC;

	mouseButton		= mB;
	mouseDirection	= mD;
	mouseSpeed		= mS;
}

//because sometimes we want to initialize blank inputs
Input::Input()
{
	inputType		= 0;
	key				= 0;
	specialCode		= 0;
	mouseButton		= 0;
	mouseDirection	= 0;
	mouseSpeed		= 0;
}

Input::~Input(void)
{
}
