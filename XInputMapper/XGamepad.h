#ifndef XGAMEPAD_H
#define XGAMEPAD_H

#include <iostream>
#include <windows.h>
#include <XInput.h>
#include <math.h>

class XGamepad
{
public:
	XGamepad(int portNumber);

	void Refresh();

	DWORD* GetButtonsPressed();
	DWORD* GetButtonsReleased();

	float GetLeftTrigger();
	float GetRightTrigger();

	float GetLeftStickX();
	float GetLeftStickY();

	float GetRightStickX();
	float GetRightStickY();

	~XGamepad(void);

private:
	int controllerID;
	int playerNumber;
	XINPUT_STATE state;

	DWORD buttonsPressed[14];
	DWORD buttonsReleased[14];

	float leftTrigger;
	float rightTrigger;

	float leftStickX;
	float leftStickY;

	float rightStickX;
	float rightStickY;

	bool GetController(int portNumber);

};

#endif
