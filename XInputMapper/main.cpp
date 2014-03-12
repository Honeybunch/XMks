#include "main.h"

int main()
{	
	std::cout << "Please Connect a Controller" << std::endl;

	Robot* robot = new Robot();
	XGamepad* padOne = new XGamepad(1);
	InputMap* padOneMap = new InputMap();
	
	DWORD* buttonsPressed;
	DWORD buttonsPreviouslyPressed[14];

	float previousLTValue = 0;
	float previousRTValue = 0;

	while(true)
	{
		padOne->Refresh();

		buttonsPressed = padOne->GetButtonsPressed();

		float leftStickX = padOne->GetLeftStickX();
		float leftStickY = padOne->GetLeftStickY();
		
		float rightStickX = padOne->GetRightStickX();
		float rightStickY = padOne->GetRightStickY();

		float leftTrigger = padOne->GetLeftTrigger();
		float rightTrigger = padOne->GetRightTrigger();

		
		/*
		//Digital Input
		std::cout << "A:\t\t "				<< buttonsPressed[0] << " - " << buttonsPreviouslyPressed[0] << std::endl;
		std::cout << "B:\t\t "				<< buttonsPressed[1] << " - " << buttonsPreviouslyPressed[1] << std::endl;
		std::cout << "X:\t\t "				<< buttonsPressed[2] << " - " << buttonsPreviouslyPressed[2] << std::endl;
		std::cout << "Y:\t\t "				<< buttonsPressed[3] << " - " << buttonsPreviouslyPressed[3] << std::endl;
		std::cout << "LShoulder:\t "		<< buttonsPressed[4] << " - " << buttonsPreviouslyPressed[4] << std::endl;
		std::cout << "RShoulder:\t "		<< buttonsPressed[5] << " - " << buttonsPreviouslyPressed[5] << std::endl;
		std::cout << "Back:\t\t "			<< buttonsPressed[6] << " - " << buttonsPreviouslyPressed[6] << std::endl;
		std::cout << "Start:\t\t "			<< buttonsPressed[7] << " - " << buttonsPreviouslyPressed[7] << std::endl;
		std::cout << "LStick:\t\t "			<< buttonsPressed[8] << " - " << buttonsPreviouslyPressed[8] << std::endl;
		std::cout << "RStick:\t\t "			<< buttonsPressed[9] << " - " << buttonsPreviouslyPressed[9] << std::endl;
		std::cout << "DPAD Down:\t "		<< buttonsPressed[10] << " - " << buttonsPreviouslyPressed[10] << std::endl;
		std::cout << "DPAD Right:\t "		<< buttonsPressed[11] << " - " << buttonsPreviouslyPressed[11] << std::endl;
		std::cout << "DPAD Left:\t "		<< buttonsPressed[12] << " - " << buttonsPreviouslyPressed[12] << std::endl;
		std::cout << "DPAD UP:\t "			<< buttonsPressed[13] << " - " << buttonsPreviouslyPressed[13] << std::endl;

		//Analog Input
		std::cout << "Left Trigger:\t "		<< leftTrigger << std::endl;
		std::cout << "Right Trigger:\t "	<< rightTrigger << std::endl;
		std::cout << "Left Stick X:\t "		<< leftStickX << std::endl;
		std::cout << "Left Stick Y:\t "		<< leftStickY << std::endl;
		std::cout << "Right Stick X:\t "	<< rightStickX << std::endl;
		std::cout << "Right Stick Y:\t "	<< rightStickY << std::endl;
		*/

		Sleep(10);

		//Handle Button Presses
		for(int i =0; i < 14; i++){
			if(buttonsPressed[i] == 1 && buttonsPreviouslyPressed[i] != 1)
			{
				if(padOneMap->Buttons[i]->inputType == specialKey)
					robot->SpecialDown(padOneMap->Buttons[i]->specialCode);
				else if(padOneMap->Buttons[i]->inputType == mousePress)
					robot->MouseDown(padOneMap->Buttons[i]->mouseButton);
				else if(padOneMap->Buttons[i]->inputType == mouseMovement)
					robot->MouseMovement(padOneMap->Buttons[i]->mouseDirection, padOneMap->Buttons[i]->mouseSpeed);
				else
				{
					robot->KeyDown(padOneMap->Buttons[i]->key);
				}
			}
			else if(buttonsPreviouslyPressed != 0 && buttonsPressed[i] == 0 && buttonsPreviouslyPressed[i] == 1)
			{
				if(padOneMap->Buttons[i]->inputType == specialKey)
					robot->SpecialUp(padOneMap->Buttons[i]->specialCode);
				else if(padOneMap->Buttons[i]->inputType == mousePress)
					robot->MouseUp(padOneMap->Buttons[i]->mouseButton);
				else
					robot->KeyUp(padOneMap->Buttons[i]->key);
			}
			
		}

		//Handle Triggers
		if(leftTrigger > padOneMap->LTSense && previousLTValue < padOneMap->LTSense)
		{
			if(padOneMap->LTrigger->inputType == specialKey)
				robot->SpecialDown(padOneMap->LTrigger->specialCode);
			else if(padOneMap->LTrigger->inputType == mousePress)
				robot->MouseDown(padOneMap->LTrigger->mouseButton);
			else if(padOneMap->LTrigger->inputType == mouseMovement)
				robot->MouseMovement(padOneMap->LTrigger->mouseDirection, padOneMap->LTrigger->mouseSpeed);
			else
				robot->KeyDown(padOneMap->LTrigger->key);
		}
		else if(leftTrigger < padOneMap->LTSense && previousLTValue > padOneMap->LTSense)
		{
			if(padOneMap->LTrigger->inputType == specialKey)
				robot->SpecialUp(padOneMap->LTrigger->specialCode);
			else if(padOneMap->LTrigger->inputType == mousePress)
				robot->MouseUp(padOneMap->LTrigger->mouseButton);
			else
				robot->KeyUp(padOneMap->LTrigger->key);
		}

		if(rightTrigger > padOneMap->RTSense && previousRTValue < padOneMap->RTSense)
		{
			if(padOneMap->RTrigger->inputType == specialKey)
				robot->SpecialDown(padOneMap->RTrigger->specialCode);
			else if(padOneMap->RTrigger->inputType == mousePress)
				robot->MouseDown(padOneMap->RTrigger->mouseButton);
			else if(padOneMap->RTrigger->inputType == mouseMovement)
				robot->MouseMovement(padOneMap->RTrigger->mouseDirection, padOneMap->RTrigger->mouseSpeed);
			else
				robot->KeyDown(padOneMap->RTrigger->key);
		}
		else if(rightTrigger < padOneMap->RTSense && previousRTValue > padOneMap->RTSense)
		{
			if(padOneMap->RTrigger->inputType == specialKey)
				robot->SpecialUp(padOneMap->RTrigger->specialCode);
			else if(padOneMap->RTrigger->inputType == mousePress)
				robot->MouseUp(padOneMap->RTrigger->mouseButton);
			else
				robot->KeyUp(padOneMap->RTrigger->key);
		}

		//Handle Stick mapping
		if(rightStickX > padOneMap->RSSense)
		{
			if(padOneMap->RSRight->inputType == specialKey)
			{
				robot->SpecialDown(padOneMap->RSRight->specialCode);
			}
			else if(padOneMap->RSRight->inputType == mousePress)
			{
				robot->MouseDown(padOneMap->RSRight->mouseButton);
				robot->MouseUp(padOneMap->RSRight->mouseButton);
			}
			else if(padOneMap->RSRight->inputType == mouseMovement)
			{
				robot->MouseMovement(padOneMap->RSRight->mouseDirection, padOneMap->RSRight->mouseSpeed * rightStickX);
			}
			else
			{
				robot->KeyDown(padOneMap->RSRight->key);
			}
		}
		else if(rightStickX < -padOneMap->RSSense)
		{
			if(padOneMap->RSLeft->inputType == specialKey)
			{
				robot->SpecialDown(padOneMap->RSLeft->specialCode);
			}
			else if(padOneMap->RSLeft->inputType == mousePress)
			{
				robot->MouseDown(padOneMap->RSLeft->mouseButton);
				robot->MouseUp(padOneMap->RSLeft->mouseButton);
			}
			else if(padOneMap->RSLeft->inputType == mouseMovement)
			{
				robot->MouseMovement(padOneMap->RSLeft->mouseDirection, padOneMap->RSLeft->mouseSpeed * rightStickX);
			}
			else
			{
				robot->KeyDown(padOneMap->RSLeft->key);
			}
		}
		if(rightStickY > padOneMap->RSSense)
		{
			if(padOneMap->RSUp->inputType == specialKey)
			{
				robot->SpecialDown(padOneMap->RSUp->specialCode);
			}
			else if(padOneMap->RSUp->inputType == mousePress)
			{
				robot->MouseDown(padOneMap->RSUp->mouseButton);
				robot->MouseUp(padOneMap->RSUp->mouseButton);
			}
			else if(padOneMap->RSUp->inputType == mouseMovement)
			{
				robot->MouseMovement(padOneMap->RSUp->mouseDirection, padOneMap->RSUp->mouseSpeed * rightStickY);
			}
			else
			{
				robot->KeyDown(padOneMap->RSUp->key);
			}
		}
		else if(rightStickY < -padOneMap->RSSense)
		{
			if(padOneMap->RSDown->inputType == specialKey)
			{
				robot->SpecialDown(padOneMap->RSDown->specialCode);
			}
			else if(padOneMap->RSDown->inputType == mousePress)
			{
				robot->MouseDown(padOneMap->RSDown->mouseButton);
				robot->MouseUp(padOneMap->RSDown->mouseButton);
			}
			else if(padOneMap->RSDown->inputType == mouseMovement)
			{
				robot->MouseMovement(padOneMap->RSDown->mouseDirection, padOneMap->RSDown->mouseSpeed * rightStickY);
			}
			else
			{
				robot->KeyDown(padOneMap->RSDown->key);
			}
		}

		//Set previously pressed input to the input of this frame 
		for(int i = 0; i < 14; i++)
			buttonsPreviouslyPressed[i] = buttonsPressed[i];
		//Set previous trigger values
		previousLTValue = leftTrigger;
		previousRTValue = rightTrigger;

		//system("cls");
	}


	delete robot;
	delete padOne;

	return 0;
}