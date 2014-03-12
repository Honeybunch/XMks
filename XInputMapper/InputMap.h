#ifndef INPUTMAP_H
#define INPUTMAP_H

#include <Windows.h>
#include "Input.h"

class InputMap
{

public:
	InputMap(void);

	//Sensitivities to map
	float LTSense;
	float RTSense;
	float LSSense;
	float RSSense;

	//Input keys to map
	Input* A;
	Input* B;
	Input* X;
	Input* Y;
	Input* LShoulder;
	Input* RShoulder;
	Input* Back;
	Input* Start;
	Input* LStick;
	Input* RStick;
	Input* DDown;
	Input* DRight;
	Input* DLeft;
	Input* DUp;
	Input* LTrigger;
	Input* RTrigger;
	Input* LSDown;
	Input* LSRight;
	Input* LSLeft;
	Input* LSUp;
	Input* RSDown;
	Input* RSRight;
	Input* RSLeft;
	Input* RSUp;

	//Array of buttons
	Input* Buttons[14];

	~InputMap(void);

private:
	
};

#endif
