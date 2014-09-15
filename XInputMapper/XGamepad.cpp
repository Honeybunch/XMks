#include "XGamepad.h"


XGamepad::XGamepad(int portNumber)
{		
	playerNumber = portNumber;
	isConnected = false;

	//Setup some base values
	for(int i =0; i < 14; i++)
		buttonsPressed[i] =0;

	leftStickX = 0;
	leftStickY = 0;

	rightStickX = 0;
	rightStickY = 0;

	leftTrigger = 0;
	rightTrigger = 0;
}

void XGamepad::Open(int portNumber)
{
	int numJoysticks = SDL_NumJoysticks();

	//Keep trying to find a controller, and get it's ID
	std::cout << "Controller Count: " << numJoysticks << std::endl;

	if (numJoysticks <= 0)
	{
		std::cout << "No Controllers Found" << std::endl;
		return;
	}

	int portID = portNumber - 1;

	//Check if the controller at the given port is compatible and open it
	if(SDL_IsGameController(portID))
	{
		controller = SDL_GameControllerOpen(portID);

		std::cout << "Found controller at port " << portNumber << " named: " << SDL_GameControllerNameForIndex(portID) << std::endl;
	}
	else
	{
		std::cout << "Could not open controller " <<playerNumber <<": " << SDL_GetError() << std::endl;
		return;
	}

	isConnected = true;

	printf("Controller %i is mapped as \"%s\".\n", portNumber, SDL_GameControllerMapping(controller));
}

void XGamepad::Close()
{
	if(isConnected)
	{
		isConnected = false;
		SDL_GameControllerClose(controller);
	}
}

//Refresh the controller input and store it in the variables of this class
void XGamepad::Refresh(const SDL_Event& event, const SDL_Event& previousEvent)
{
	//If the controller isn't connected, set the ID to -1 and start looking for it again
	if(!isConnected)
	{
			controllerID = -1;
			Open(playerNumber);
	}

	//Check and update inputs
	switch(event.type)
	{

	case SDL_CONTROLLERAXISMOTION:
		{
			int axis = event.jaxis.axis;
			int value = event.jaxis.value;
			float percentValue = value/32768.0f; // The value we want from -1 to 1

			std::cout << percentValue << std::endl;

			switch(value){
			case 0:
				leftStickY = percentValue;
				 break;
			case 1:
				leftStickX = percentValue;
				break;
			case 2:
				rightStickY = percentValue;
				break;
			case 3:
				rightStickX = percentValue;
				break;
			case 4:
				leftTrigger = percentValue;
				break;
			case 5: 
				rightTrigger = percentValue;
				break;
			}

			break;
		}
	case SDL_CONTROLLERBUTTONDOWN:
		{
			int buttonIndex = event.cbutton.button;

			std::cout << "Button " <<buttonIndex<< " Down!" << std::endl;

			buttonsPressed[buttonIndex] = 1;
			break;
		}
	case SDL_CONTROLLERBUTTONUP:
		{
			int buttonIndex = event.jbutton.button;

			//Only record a button up event if the button was down last cycle
			if (previousEvent.type == SDL_CONTROLLERBUTTONDOWN && previousEvent.cbutton.button == buttonIndex)
			{
				std::cout << "Button " <<buttonIndex<< " Up!" << std::endl;

				buttonsPressed[buttonIndex] = 0;
			}
			break;
		}
	default:
		{
			break;
		}
	}

	/*
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
	*/
}

//Getters
DWORD* XGamepad::GetButtonsPressed()
{
	return buttonsPressed;
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
	Close();

	delete controller;
}
