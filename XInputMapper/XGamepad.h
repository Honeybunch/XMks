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

	void Refresh(const SDL_Event& event, const SDL_Event& previousEvent);

	DWORD* GetButtonsPressed();

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
	
	SDL_GameController* controller;
	bool isConnected;

	DWORD buttonsPressed[14];

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
