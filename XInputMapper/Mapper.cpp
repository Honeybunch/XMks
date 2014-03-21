#include "Mapper.h"

Mapper::Mapper(int portNumber)
{
	robot = new Robot();
	gamepad = new XGamepad(portNumber);
	inputMap = new InputMap();
}

bool Mapper::loadMap(string file)
{
	ifstream fileStream(file);
	string fileContents;

	json_t* root;
	json_error_t error;

	//Read the file
	while(fileStream.good())
	{
		getline(fileStream, fileContents);
		fileContents += "\n";
	}
	fileStream.close();

	cout << fileContents << endl;

	//root = json_loads

	return true;
}

bool Mapper::writeMap(string file)
{
	//Manually serialize the map
	json_t* root;

	json_t* LTSense;
	json_t* RTSense;
	json_t* LSSense;
	json_t* RSSense;

	//Data that won't be stored in an array
	json_t* LTrigger;
	json_t* RTrigger;
	json_t* LSDown;
	json_t* LSRight; 
	json_t* LSLeft;
	json_t* LSUp;
	json_t* RSDown;
	json_t* RSRight; 
	json_t* RSLeft;
	json_t* RSUp;
	
	//The array of Buttons
	json_t* Buttons;

	//These will be used to fill the data of the actual inputs in the button array
	json_t* inputObject;

	json_t* inputType;
	json_t* key;
	json_t* specialCode;
	json_t* mouseButton;
	json_t* mouseDirection;
	json_t* mouseSpeed;

	root = json_object();

	Buttons = json_array();
	inputObject = json_object();

	LTrigger = json_object();
	RTrigger = json_object();

	LTSense = json_string(to_string(inputMap->LTSense).c_str());
	RTSense = json_string(to_string(inputMap->RTSense).c_str());
	LSSense = json_string(to_string(inputMap->LSSense).c_str());
	RSSense = json_string(to_string(inputMap->RSSense).c_str());

	//Buttons
	for(int i = 0; i < 14; i++)
	{
		inputType = json_integer(inputMap->Buttons[i]->inputType);
		key = json_integer(inputMap->Buttons[i]->key);
		specialCode = json_integer(inputMap->Buttons[i]->specialCode);
		mouseButton = json_integer(inputMap->Buttons[i]->mouseButton);
		mouseDirection = json_integer(inputMap->Buttons[i]->mouseDirection);
		mouseSpeed = json_string(to_string(inputMap->Buttons[i]->mouseSpeed).c_str());

		json_object_set(inputObject, "inputType", inputType);
		json_object_set(inputObject, "key", key);
		json_object_set(inputObject, "specialCode", specialCode);
		json_object_set(inputObject, "mouseButton", mouseButton);
		json_object_set(inputObject, "mouseDirection", mouseDirection);
		json_object_set(inputObject, "mouseSpeed", mouseSpeed);

		json_array_append_new(Buttons, inputObject);
	}

	//Triggers
	inputType = json_integer(inputMap->LTrigger->inputType);
	key = json_integer(inputMap->LTrigger->key);
	specialCode = json_integer(inputMap->LTrigger->specialCode);
	mouseButton = json_integer(inputMap->LTrigger->mouseButton);
	mouseDirection = json_integer(inputMap->LTrigger->mouseDirection);
	mouseSpeed = json_string(to_string(inputMap->LTrigger->mouseSpeed).c_str());

	json_object_set(LTrigger, "inputType", inputType);
	json_object_set(LTrigger, "key", key);
	json_object_set(LTrigger, "specialCode", specialCode);
	json_object_set(LTrigger, "mouseButton", mouseButton);
	json_object_set(LTrigger, "mouseDirection", mouseDirection);
	json_object_set(LTrigger, "mouseSpeed", mouseSpeed);

	json_array_append_new(Buttons, LTrigger);

	inputType = json_integer(inputMap->RTrigger->inputType);
	key = json_integer(inputMap->RTrigger->key);
	specialCode = json_integer(inputMap->RTrigger->specialCode);
	mouseButton = json_integer(inputMap->RTrigger->mouseButton);
	mouseDirection = json_integer(inputMap->RTrigger->mouseDirection);
	mouseSpeed = json_string(to_string(inputMap->RTrigger->mouseSpeed).c_str());

	json_object_set(RTrigger, "inputType", inputType);
	json_object_set(RTrigger, "key", key);
	json_object_set(RTrigger, "specialCode", specialCode);
	json_object_set(RTrigger, "mouseButton", mouseButton);
	json_object_set(RTrigger, "mouseDirection", mouseDirection);
	json_object_set(RTrigger, "mouseSpeed", mouseSpeed);

	json_array_append_new(Buttons, RTrigger);



	json_object_set(root, "LTSense", LTSense);
	json_object_set(root, "RTSense", RTSense);
	json_object_set(root, "LSSense", LSSense);
	json_object_set(root, "RSSense", RSSense);
	
	json_object_set(root, "Buttons", Buttons);

	json_object_set(root, "LTrigger", LTrigger);
	json_object_set(root, "RTrigger", RTrigger);

	//Dump to a file 
	char* jsonString = json_dumps(root, sizeof(root));

	ofstream stream;
	stream.open(file.c_str());
	stream << jsonString;
	stream.close();

	//Clear memory
	delete LTSense;
	delete RTSense;
	delete LSSense;
	delete RSSense;
	
	delete inputObject;

	return true;
}

void Mapper::runMap()
{
	DWORD* buttonsPressed;
	DWORD buttonsPreviouslyPressed[14];

	float previousLTValue = 0;
	float previousRTValue = 0;

	while(true)
	{
		gamepad->Refresh();

		buttonsPressed = gamepad->GetButtonsPressed();

		float leftStickX = gamepad->GetLeftStickX();
		float leftStickY = gamepad->GetLeftStickY();
		
		float rightStickX = gamepad->GetRightStickX();
		float rightStickY = gamepad->GetRightStickY();

		float leftTrigger = gamepad->GetLeftTrigger();
		float rightTrigger = gamepad->GetRightTrigger();

		
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
				if(inputMap->Buttons[i]->inputType == specialKey)
					robot->SpecialDown(inputMap->Buttons[i]->specialCode);
				else if(inputMap->Buttons[i]->inputType == mousePress)
					robot->MouseDown(inputMap->Buttons[i]->mouseButton);
				else if(inputMap->Buttons[i]->inputType == mouseMovement)
					robot->MouseMovement(inputMap->Buttons[i]->mouseDirection, inputMap->Buttons[i]->mouseSpeed);
				else
				{
					robot->KeyDown(inputMap->Buttons[i]->key);
				}
			}
			else if(buttonsPreviouslyPressed != 0 && buttonsPressed[i] == 0 && buttonsPreviouslyPressed[i] == 1)
			{
				if(inputMap->Buttons[i]->inputType == specialKey)
					robot->SpecialUp(inputMap->Buttons[i]->specialCode);
				else if(inputMap->Buttons[i]->inputType == mousePress)
					robot->MouseUp(inputMap->Buttons[i]->mouseButton);
				else
					robot->KeyUp(inputMap->Buttons[i]->key);
			}
			
		}

		//Handle Triggers
		if(leftTrigger > inputMap->LTSense && previousLTValue < inputMap->LTSense)
		{
			if(inputMap->LTrigger->inputType == specialKey)
				robot->SpecialDown(inputMap->LTrigger->specialCode);
			else if(inputMap->LTrigger->inputType == mousePress)
				robot->MouseDown(inputMap->LTrigger->mouseButton);
			else if(inputMap->LTrigger->inputType == mouseMovement)
				robot->MouseMovement(inputMap->LTrigger->mouseDirection, inputMap->LTrigger->mouseSpeed);
			else
				robot->KeyDown(inputMap->LTrigger->key);
		}
		else if(leftTrigger < inputMap->LTSense && previousLTValue > inputMap->LTSense)
		{
			if(inputMap->LTrigger->inputType == specialKey)
				robot->SpecialUp(inputMap->LTrigger->specialCode);
			else if(inputMap->LTrigger->inputType == mousePress)
				robot->MouseUp(inputMap->LTrigger->mouseButton);
			else
				robot->KeyUp(inputMap->LTrigger->key);
		}

		if(rightTrigger > inputMap->RTSense && previousRTValue < inputMap->RTSense)
		{
			if(inputMap->RTrigger->inputType == specialKey)
				robot->SpecialDown(inputMap->RTrigger->specialCode);
			else if(inputMap->RTrigger->inputType == mousePress)
				robot->MouseDown(inputMap->RTrigger->mouseButton);
			else if(inputMap->RTrigger->inputType == mouseMovement)
				robot->MouseMovement(inputMap->RTrigger->mouseDirection, inputMap->RTrigger->mouseSpeed);
			else
				robot->KeyDown(inputMap->RTrigger->key);
		}
		else if(rightTrigger < inputMap->RTSense && previousRTValue > inputMap->RTSense)
		{
			if(inputMap->RTrigger->inputType == specialKey)
				robot->SpecialUp(inputMap->RTrigger->specialCode);
			else if(inputMap->RTrigger->inputType == mousePress)
				robot->MouseUp(inputMap->RTrigger->mouseButton);
			else
				robot->KeyUp(inputMap->RTrigger->key);
		}

		//Handle Left Stick mapping
		if(leftStickX > inputMap->LSSense)
		{
			if(inputMap->LSRight->inputType == specialKey)
			{
				robot->SpecialDown(inputMap->LSRight->specialCode);
			}
			else if(inputMap->LSRight->inputType == mousePress)
			{
				robot->MouseDown(inputMap->LSRight->mouseButton);
				robot->MouseUp(inputMap->LSRight->mouseButton);
			}
			else if(inputMap->LSRight->inputType == mouseMovement)
			{
				robot->MouseMovement(inputMap->LSRight->mouseDirection, inputMap->LSRight->mouseSpeed * leftStickX);
			}
			else
			{
				robot->KeyDown(inputMap->LSRight->key);
				robot->KeyUp(inputMap->LSLeft->key);
			}
		}
		else if(leftStickX < -inputMap->LSSense)
		{
			if(inputMap->LSLeft->inputType == specialKey)
			{
				robot->SpecialDown(inputMap->LSLeft->specialCode);
			}
			else if(inputMap->LSLeft->inputType == mousePress)
			{
				robot->MouseDown(inputMap->LSLeft->mouseButton);
				robot->MouseUp(inputMap->LSLeft->mouseButton);
			}
			else if(inputMap->LSLeft->inputType == mouseMovement)
			{
				robot->MouseMovement(inputMap->LSLeft->mouseDirection, inputMap->LSLeft->mouseSpeed * rightStickX);
			}
			else
			{
				robot->KeyDown(inputMap->LSLeft->key);
				robot->KeyUp(inputMap->LSRight->key);
			}
		}
		else
		{
			if(inputMap->LSLeft->inputType == key)
				robot->KeyUp(inputMap->LSLeft->key);
			if(inputMap->LSRight->inputType == key)
				robot->KeyUp(inputMap->LSRight->key);
		}

		if(leftStickY > inputMap->LSSense)
		{
			if(inputMap->LSUp->inputType == specialKey)
			{
				robot->SpecialDown(inputMap->LSUp->specialCode);
			}
			else if(inputMap->LSUp->inputType == mousePress)
			{
				robot->MouseDown(inputMap->LSUp->mouseButton);
				robot->MouseUp(inputMap->LSUp->mouseButton);
			}
			else if(inputMap->LSUp->inputType == mouseMovement)
			{
				robot->MouseMovement(inputMap->LSUp->mouseDirection, inputMap->LSUp->mouseSpeed * leftStickY);
			}
			else
			{
				robot->KeyDown(inputMap->LSUp->key);
				robot->KeyUp(inputMap->LSDown->key);
			}
		}
		else if(leftStickY < -inputMap->LSSense)
		{
			if(inputMap->LSDown->inputType == specialKey)
			{
				robot->SpecialDown(inputMap->LSDown->specialCode);
			}
			else if(inputMap->LSDown->inputType == mousePress)
			{
				robot->MouseDown(inputMap->LSDown->mouseButton);
				robot->MouseUp(inputMap->LSDown->mouseButton);
			}
			else if(inputMap->LSDown->inputType == mouseMovement)
			{
				robot->MouseMovement(inputMap->LSDown->mouseDirection, inputMap->LSDown->mouseSpeed * leftStickY);
			}
			else
			{
				robot->KeyDown(inputMap->LSDown->key);
				robot->KeyUp(inputMap->LSUp->key);
			}
		}
		else
		{
			if(inputMap->LSUp->inputType == key)
				robot->KeyUp(inputMap->LSUp->key);
			if(inputMap->LSDown->inputType == key)
				robot->KeyUp(inputMap->LSDown->key);
		}

		//Handle Right Stick mapping
		if(rightStickX > inputMap->RSSense)
		{
			if(inputMap->RSRight->inputType == specialKey)
			{
				robot->SpecialDown(inputMap->RSRight->specialCode);
			}
			else if(inputMap->RSRight->inputType == mousePress)
			{
				robot->MouseDown(inputMap->RSRight->mouseButton);
				robot->MouseUp(inputMap->RSRight->mouseButton);
			}
			else if(inputMap->RSRight->inputType == mouseMovement)
			{
				robot->MouseMovement(inputMap->RSRight->mouseDirection, inputMap->RSRight->mouseSpeed * rightStickX);
			}
			else
			{
				robot->KeyDown(inputMap->RSRight->key);
				robot->KeyUp(inputMap->RSLeft->key);
			}
		}
		else if(rightStickX < -inputMap->RSSense)
		{
			if(inputMap->RSLeft->inputType == specialKey)
			{
				robot->SpecialDown(inputMap->RSLeft->specialCode);
			}
			else if(inputMap->RSLeft->inputType == mousePress)
			{
				robot->MouseDown(inputMap->RSLeft->mouseButton);
				robot->MouseUp(inputMap->RSLeft->mouseButton);
			}
			else if(inputMap->RSLeft->inputType == mouseMovement)
			{
				robot->MouseMovement(inputMap->RSLeft->mouseDirection, inputMap->RSLeft->mouseSpeed * rightStickX);
			}
			else
			{
				robot->KeyDown(inputMap->RSLeft->key);
				robot->KeyUp(inputMap->RSRight->key);
			}
		}
		else
		{
			if(inputMap->RSLeft->inputType == key)
				robot->KeyUp(inputMap->RSLeft->key);
			if(inputMap->RSRight->inputType == key)
				robot->KeyUp(inputMap->RSRight->key);
		}

		if(rightStickY > inputMap->RSSense)
		{
			if(inputMap->RSUp->inputType == specialKey)
			{
				robot->SpecialDown(inputMap->RSUp->specialCode);
			}
			else if(inputMap->RSUp->inputType == mousePress)
			{
				robot->MouseDown(inputMap->RSUp->mouseButton);
				robot->MouseUp(inputMap->RSUp->mouseButton);
			}
			else if(inputMap->RSUp->inputType == mouseMovement)
			{
				robot->MouseMovement(inputMap->RSUp->mouseDirection, inputMap->RSUp->mouseSpeed * rightStickY);
			}
			else
			{
				robot->KeyDown(inputMap->RSUp->key);
				robot->KeyUp(inputMap->RSDown->key);
			}
		}
		else if(rightStickY < -inputMap->RSSense)
		{
			if(inputMap->RSDown->inputType == specialKey)
			{
				robot->SpecialDown(inputMap->RSDown->specialCode);
			}
			else if(inputMap->RSDown->inputType == mousePress)
			{
				robot->MouseDown(inputMap->RSDown->mouseButton);
				robot->MouseUp(inputMap->RSDown->mouseButton);
			}
			else if(inputMap->RSDown->inputType == mouseMovement)
			{
				robot->MouseMovement(inputMap->RSDown->mouseDirection, inputMap->RSDown->mouseSpeed * rightStickY);
			}
			else
			{
				robot->KeyDown(inputMap->RSDown->key);
				robot->KeyUp(inputMap->RSUp->key);
			}
		}
		else
		{
			if(inputMap->RSUp->inputType == key)
				robot->KeyUp(inputMap->RSUp->key);
			if(inputMap->RSDown->inputType == key)
				robot->KeyUp(inputMap->RSDown->key);
		}

		//Set previously pressed input to the input of this frame 
		for(int i = 0; i < 14; i++)
			buttonsPreviouslyPressed[i] = buttonsPressed[i];
		//Set previous trigger values
		previousLTValue = leftTrigger;
		previousRTValue = rightTrigger;

		//system("cls");
	}
}

Mapper::~Mapper(void)
{
	delete robot;
	delete gamepad;
	delete inputMap;
}
