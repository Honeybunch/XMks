#include "InputMap.h"

InputMap::InputMap(void)
{
	LTSense = .5f;
	RTSense = .5f;
	LSSense = .5f;
	RSSense = .5f;

	A =			new Input(0, 'q', 0,0,0,0);
	B =			new Input();
	X =			new Input();
	Y =			new Input();
	LShoulder = new Input(1, 0, VK_SPACE,0,0,0);
	RShoulder = new Input(0, 'e', 0,0,0,0);
	Back =		new Input(1, 0, VK_ESCAPE, 0,0,0);
	Start =		new Input(1, 0, VK_RETURN, 0,0,0);
	LStick =	new Input();
	RStick =	new Input();
	DDown =		new Input(0, 's', 0,0,0,0);
	DRight =	new Input(0, 'd', 0,0,0,0);
	DLeft =		new Input(0, 'a', 0,0,0,0);
	DUp =		new Input(0, 'w', 0,0,0,0);
	LTrigger =	new Input();
	RTrigger =	new Input();
	LSDown =	new Input();
	LSRight =	new Input();
	LSLeft =	new Input();
	LSUp =		new Input();
	RSDown =	new Input(1, 0, VK_DOWN,0,0,0);
	RSRight =	new Input(1, 0, VK_RIGHT,0,0,0);
	RSLeft =	new Input(1, 0, VK_LEFT,0,0,0);
	RSUp =		new Input(1, 0, VK_UP,0,0,0);

	Buttons[0] = A;		
	Buttons[1] = B;		
	Buttons[2] = X;
	Buttons[3] = Y;	
	Buttons[4] = LShoulder;
	Buttons[5] = RShoulder;
	Buttons[6] = Back;
	Buttons[7] = Start;
	Buttons[8] = LStick;
	Buttons[9] = RStick;
	Buttons[10] = DDown;
	Buttons[11] = DRight;
	Buttons[12] = DLeft;
	Buttons[13] = DUp;

	//Populate inputs
	inputs["A"]				= A;
	inputs["B"]				= B;
	inputs["X"]				= X;
	inputs["Y"]				= Y;
	inputs["LShoulder"]		= LShoulder;
	inputs["RShoulder"]		= RShoulder;
	inputs["Back"]			= Back;
	inputs["Start"]			= Start;
	inputs["LStick"]		= LStick;
	inputs["RStick"]		= RStick;
	inputs["DDown"]			= DDown;
	inputs["DRight"]		= DRight;
	inputs["DLeft"]			= DLeft;
	inputs["DUp"]			= DUp;
	inputs["LTrigger"]		= LTrigger;
	inputs["RTrigger"]		= RTrigger;
	inputs["LSDown"]		= LSDown;
	inputs["LSRight"]		= LSRight;
	inputs["LSLeft"]		= LSLeft;
	inputs["LSUp"]			= LSUp;
	inputs["RSDown"]		= RSDown;
	inputs["RSRight"]		= RSRight;
	inputs["RSLeft"]		= RSLeft;
	inputs["RSUp"]			= RSUp;
}


InputMap::~InputMap(void)
{
	
	delete A;
	delete B;
	delete X;
	delete Y;
	delete LShoulder;
	delete RShoulder;
	delete Back;
	delete Start;
	delete LStick;
	delete RStick;
	delete DDown;
	delete DRight;
	delete DLeft;
	delete DUp;
	delete LTrigger;
	delete RTrigger;
	delete LSDown;
	delete LSRight;
	delete LSLeft;
	delete LSUp;
	delete RSDown;
	delete RSRight;
	delete RSLeft;
	delete RSUp;
}
