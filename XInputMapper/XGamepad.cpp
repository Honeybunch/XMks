#include "XGamepad.h"


XGamepad::XGamepad(int portNumber)
{		
	playerNumber = portNumber;
	isConnected = false;
}

void XGamepad::Open(int portNumber)
{
	//Keep trying to find a controller, and get it's ID
	std::cout << "Controller Count: " << SDL_NumJoysticks() << std::endl;

	if(SDL_IsGameController(portNumber - 1))
	{
		std::cout << "Found controller at port " << portNumber << " named: " << SDL_GameControllerNameForIndex(portNumber -1) << std::endl; 
		gamepad = SDL_GameControllerOpen(portNumber - 1);
	}
	else
	{
		std::cout << "Could not open controller " <<playerNumber <<": " << SDL_GetError() << std::endl;
		return;
	}

	SDL_Joystick* joy = SDL_GameControllerGetJoystick(gamepad);
	joystickID = SDL_JoystickInstanceID(joy);

	isConnected = true;

	//If they joystick has haptic controller
	if(SDL_JoystickIsHaptic(joy))
	{
		haptic = SDL_HapticOpenFromJoystick(joy);
		std::cout << "Haptic Effects: " << SDL_HapticNumEffects(haptic) << std::endl;
		std::cout << "Haptic Query: " << SDL_HapticQuery(haptic) << std::endl;
		if(SDL_HapticRumbleSupported(haptic))
		{
			//If we have haptic rumble support, lets initiate it
			if(SDL_HapticRumbleInit(haptic) != 0)
			{
				std::cout << "Haptic Rumble Init: " << SDL_GetError() << std::endl;
				SDL_HapticClose(haptic);
				haptic = 0;
			}
		}
		else
		{
			SDL_HapticClose(haptic);
			haptic = 0;
		}
	}
	else
	{
		std::cout << "No haptics :(" << std::endl;
	}
}

void XGamepad::Close()
{
	if(isConnected)
	{
		isConnected = false;
		if(haptic)
		{
			SDL_HapticClose(haptic);
			haptic = 0;
		}
		SDL_GameControllerClose(gamepad);
		gamepad = 0;
	}
}

//Refresh the controller input and store it in the variables of this class
void XGamepad::Refresh(const SDL_Event& event)
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
	case SDL_JOYAXISMOTION:
		{
			std::cout << "Axis Motion!" << std::endl;
			break;
		}
	case SDL_JOYBUTTONDOWN:
		{
			Uint8 buttonIndex = event.jbutton.button;

			std::cout << "Button Down!" << std::endl;

			buttonsPressed[buttonIndex] = 1;
			break;
		}
	case SDL_JOYBUTTONUP:
		{
			Uint8 buttonIndex = event.jbutton.button;

			std::cout << "Button Up!" << std::endl;

			buttonsPressed[buttonIndex] = 0;
			break;
		}
	/*
	case SDL_CONTROLLERDEVICEADDED:
		{
			Open(playerNumber);
			break;
		}
	case SDL_CONTROLLERDEVICEREMOVED:
		{
			Close();
			break;
		}
		*/
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
	Close();

	delete gamepad;
	delete haptic;
}
