#include "Robot.h"


Robot::Robot(void)
{
}

void Robot::MouseDown(int button)
{
	DWORD flag;

	switch(button)
	{
	case 0:
		flag = MOUSEEVENTF_LEFTDOWN;
		break;
	case 1:
		flag = MOUSEEVENTF_RIGHTDOWN;
		break;
	case 2:
		flag = MOUSEEVENTF_MIDDLEDOWN;
		break;
	default:
		return;
		break;
	}

	INPUT* input = new INPUT;

	input->type = INPUT_MOUSE;
	input->mi.mouseData = 0;
	input->mi.dwFlags = flag;
	input->mi.time = 0;
	input->mi.dwExtraInfo = 0;
	SendInput(1, input, sizeof(INPUT));

	delete(input);
}

void Robot::MouseUp(int button)
{
	DWORD flag;

	switch(button)
	{
	case 0:
		flag = MOUSEEVENTF_LEFTUP;
		break;
	case 1:
		flag = MOUSEEVENTF_RIGHTUP;
		break;
		flag = MOUSEEVENTF_MIDDLEUP;
		break;
	default:
		return;
		break;
	}

	INPUT* input = new INPUT;

	input->type = INPUT_MOUSE;
	input->mi.mouseData = 0;
	input->mi.dwFlags = flag;
	input->mi.time = 0;
	input->mi.dwExtraInfo = 0;
	SendInput(1, input, sizeof(INPUT));

	delete(input);
}


/*
	0 = up
	1 = right
	2 = down
	3 = left
*/
void Robot::MouseMovement(int direction, float amount)
{
	float dx = 0;
	float dy = 0;

	switch(direction)
	{
	case 0:
		dy =-amount;
		break;
	case 1:
		dx = amount;
		break;
	case 2:
		dy = amount;
		break;
	case 3:
		dx = -amount;
		break;
	default:
		return;
		break;
	}

	INPUT* input = new INPUT;

	input->type = INPUT_MOUSE;

	input->mi.mouseData = 0;
	input->mi.dwFlags = MOUSEEVENTF_MOVE;
	input->mi.dx = dx;
	input->mi.dy = dy;
	input->mi.time = 0;
	input->mi.dwExtraInfo = 0;

	SendInput(1, input, sizeof(INPUT));

	delete input;
}

void Robot::KeyDown(char key)
{
	INPUT* input = new INPUT;

	const short keyChar = VkKeyScan(key);
	const UINT mappedKey = MapVirtualKey(LOBYTE(keyChar),0);

	//Press down key
	input->type = INPUT_KEYBOARD;
	input->ki.dwFlags = KEYEVENTF_SCANCODE;
	input->ki.wScan = mappedKey;
	SendInput(1, input, sizeof(INPUT));

	delete input;
}

void Robot::KeyUp(char key)
{
	INPUT* input = new INPUT;

	const short keyChar = VkKeyScan(key);
	const UINT mappedKey = MapVirtualKey(LOBYTE(keyChar),0);

	//Set key up
	input->type = INPUT_KEYBOARD;
	input->ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	input->ki.wScan = mappedKey;
	SendInput(1, input, sizeof(INPUT));

	delete input;
}

void Robot::SpecialDown(short VKCode)
{
	INPUT* input = new INPUT;

	//Press down key
	input->type = INPUT_KEYBOARD;
	input->ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	input->ki.wVk = VKCode;
	SendInput(1, input, sizeof(INPUT));

	delete input;
}

void Robot::SpecialUp(short VKCode)
{
	INPUT* input = new INPUT;

	//Set key up
	input->type = INPUT_KEYBOARD;
	input->ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
	input->ki.wVk = VKCode;
	SendInput(1, input, sizeof(INPUT));

	delete input;
}


Robot::~Robot(void)
{
}
