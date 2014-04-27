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
	//Keep trying to find a controller, and get it's ID
	std::cout << "Controller Count: " << SDL_NumJoysticks() << std::endl;

	joy = SDL_JoystickOpen(portNumber -1);

	if(joy)
	{
		std::cout << "Found controller at port " << portNumber << " named: " << SDL_GameControllerNameForIndex(portNumber -1) << std::endl; 
	}
	else
	{
		std::cout << "Could not open controller " <<playerNumber <<": " << SDL_GetError() << std::endl;
		return;
	}

	isConnected = true;

	 printf("Joystick has %d axes, %d hats, %d balls, and %d buttons\n",
           SDL_JoystickNumAxes(joy), SDL_JoystickNumHats(joy),
           SDL_JoystickNumBalls(joy), SDL_JoystickNumButtons(joy));

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
		SDL_JoystickClose(joy);
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

	case SDL_JOYAXISMOTION:
		{
			int axis = event.jaxis.axis;
			int value = event.jaxis.value;
			float percentValue = value/32767; // The value we want from -1 to 1

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
	case SDL_JOYBUTTONDOWN:
		{
			int buttonIndex = event.jbutton.button;

			std::cout << "Button " <<buttonIndex<< " Down!" << std::endl;

			buttonsPressed[buttonIndex] = 1;
			break;
		}
	case SDL_JOYBUTTONUP:
		{
			int buttonIndex = event.jbutton.button;

			//Only record a button up event if the button was down last cycle
			if(previousEvent.type == SDL_JOYBUTTONDOWN && previousEvent.jbutton.button == buttonIndex)
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

	delete joy;
	delete haptic;
}
