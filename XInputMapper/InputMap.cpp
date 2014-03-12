#include "InputMap.h"


InputMap::InputMap(void)
{
	LTSense = .5f;
	RTSense = .5f;
	LSSense = .15f;
	RSSense = .15f;

	A =			new Input(specialKey, '0', VK_SPACE, 0,0,0);
	B =			new Input(specialKey, '0', VK_SHIFT, 0,0,0);
	X =			new Input(specialKey, '0', VK_CONTROL, 0,0,0);
	Y =			new Input(specialKey, '0', VK_TAB, 0,0,0);
	LShoulder = new Input(key, 'q', 0,0,0,0);
	RShoulder = new Input(key, 'e', 0,0,0,0);
	LTrigger =	new Input(mousePress, '0', 0,1,0,0);
	RTrigger =	new Input(mousePress, '0', 0,0,0,0);
	LSDown =	new Input(key, 's', 0,0,0,0);
	LSRight =	new Input(key, 'd', 0,0,0,0);
	LSLeft =	new Input(key, 'a', 0,0,0,0);
	LSUp =		new Input(key, 'w', 0,0,0,0);
	RSDown =	new Input(mouseMovement, '0', 0,0,0, 10);
	RSRight =	new Input(mouseMovement, '0', 0,0,3,-10);
	RSLeft =	new Input(mouseMovement, '0', 0,0,1, 10);
	RSUp =		new Input(mouseMovement, '0', 0,0,2,-10);

	Buttons[0] = A;		
	Buttons[1] = B;		
	Buttons[2] = X;
	Buttons[3] = Y;	
	Buttons[4] = LShoulder;
	Buttons[5] = RShoulder;
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

	delete Buttons;
}
