#ifndef XGAMEPAD_H
#define XGAMEPAD_H

#include <iostream>
#include <windows.h>
#include <SDL.h>
#include <math.h>

class XGamepad
{
public:
	XGamepad(int portNumber);

	void Refresh(const SDL_Event& event);

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
	
	SDL_GameController* gamepad;
	SDL_Haptic* haptic;
	SDL_JoystickID joystickID;
	bool isConnected;

	DWORD buttonsPressed[14];
	DWORD buttonsReleased[14];

	float leftTrigger;
	float rightTrigger;

	float leftStickX;
	float leftStickY;

	float rightStickX;
	float rightStickY;

	void Open(int portNumber);
	void Close();

};

#endif
