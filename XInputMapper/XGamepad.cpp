#include "XGamepad.h"


XGamepad::XGamepad(int portNumber)
{		
	playerNumber = portNumber;
	GetController(portNumber);
}

bool XGamepad::GetController(int portNumber)
{
	//Keep trying to find a controller, and get it's ID
	controllerID = -1;

	ZeroMemory(&state, sizeof(XINPUT_STATE));

	if(XInputGetState(playerNumber -1,&state) == ERROR_SUCCESS)
	{
		std::cout << "Controller " << playerNumber <<" Detected" << std::endl;	
		controllerID = playerNumber -1;
		return true;
	}
	else
	{
		return false;
	}
}

//Refresh the controller input and store it in the variables of this class
void XGamepad::Refresh()
{
	//If the controller isn't connected, set the ID to -1 and start looking for it again
	if(XInputGetState(controllerID, &state) != ERROR_SUCCESS)
	{
			controllerID = -1;
			GetController(playerNumber);

	}

	//Check if every button is pressed
	
	//4 Letter buttons
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
		buttonsPressed[0] = 1;
	else
		buttonsPressed[0] = 0;
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0)
		buttonsPressed[1] = 1;
	else
		buttonsPressed[1] = 0;
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0)
		buttonsPressed[2] = 1;
	else
		buttonsPressed[2] = 0;
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0)
		buttonsPressed[3] = 1;
	else
		buttonsPressed[3] = 0;

	//Shoulder buttons
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0)
		buttonsPressed[4] = 1;
	else
		buttonsPressed[4] = 0;
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0)
		buttonsPressed[5] = 1;
	else
		buttonsPressed[5] = 0;

	//Back and Start
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0)
		buttonsPressed[6] = 1;
	else
		buttonsPressed[6] = 0;
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0)
		buttonsPressed[7] = 1;
	else
		buttonsPressed[7] = 0;

	//Stick Buttons
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0)
		buttonsPressed[8] = 1;
	else
		buttonsPressed[8] = 0;
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0)
		buttonsPressed[9] = 1;
	else
		buttonsPressed[9] = 0;

	//DPAD Directions
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0)
		buttonsPressed[10] = 1;
	else
		buttonsPressed[10] = 0;
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0)
		buttonsPressed[11] = 1;
	else
		buttonsPressed[11] = 0;
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0)
		buttonsPressed[12] = 1;
	else
		buttonsPressed[12] = 0;
	if((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0)
		buttonsPressed[13] = 1;
	else
		buttonsPressed[13] = 0;

	//Save Trigger values as percentages
	leftTrigger = (float) state.Gamepad.bLeftTrigger / 255;
	rightTrigger = (float) state.Gamepad.bRightTrigger / 255;

	//Save Thumbstick values as percentages
	leftStickX = max(-1, (float)state.Gamepad.sThumbLX / 32767);
	leftStickY = max(-1, (float)state.Gamepad.sThumbLY / 32767);

	rightStickX = max(-1, (float)state.Gamepad.sThumbRX / 32767);
	rightStickY = max(-1, (float)state.Gamepad.sThumbRY / 32767);
}

//Getters
DWORD* XGamepad::GetButtonsPressed()
{
	return buttonsPressed;
}
DWORD* XGamepad::GetButtonsReleased()
{
	return buttonsReleased;
}
float XGamepad::GetLeftTrigger()
{
	return leftTrigger;
}
float XGamepad::GetRightTrigger()
{
	return rightTrigger;
}
float XGamepad::GetLeftStickX()
{
	return leftStickX;
}
float XGamepad::GetLeftStickY()
{
	return leftStickY;
}
float XGamepad::GetRightStickX()
{
	return rightStickX;
}
float XGamepad::GetRightStickY()
{
	return rightStickY;
}

XGamepad::~XGamepad(void)
{
}
