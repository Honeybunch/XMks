#include "Mapper.h"

Mapper::Mapper(int portNumber)
{
	robot = new Robot();
	gamepad = new XGamepad(portNumber);
	inputMap = new InputMap();

	running = false;
}

bool Mapper::loadMap(string file)
{
	if(running)
	{
		cout << "Mapper is running!" << endl;
		return false;
	}

	ifstream fileStream;
	string fileContents;

	json_t* root;
	json_error_t error;

	//These will be parsed to floats before adding to the input map
	char* LTSense;
	char* RTSense;
	char* LSSense;
	char* RSSense;

	//Objects to parse seperately 
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
	
	json_t* Buttons;
	json_t* currentButton;

	//Temp values to unpack to
	int inputType;
	int key;
	char* mouseSpeed;
	int specialCode;
	int mouseButton;
	int mouseDirection;

	//Have jansson load the file into a jansson object that we can attempt to parse
	root = json_load_file(file.c_str(), JSON_DECODE_ANY, &error);

	//Check for errors
	if(!root)
	{
		cout << "Error on line " << error.line << ": " << error.text << endl;
		return false;
	}

	//Get objects / arrays from root
	LTrigger = json_object_get(root, "LTrigger");
	RTrigger = json_object_get(root, "RTrigger");
	LSDown   = json_object_get(root, "LSDown");
	LSRight  = json_object_get(root, "LSRight");
	LSLeft   = json_object_get(root, "LSLeft");
	LSUp     = json_object_get(root, "LSUp");
	RSDown   = json_object_get(root, "RSDown");
	RSRight  = json_object_get(root, "RSRight");
	RSLeft   = json_object_get(root, "RSLeft");
	RSUp     = json_object_get(root, "RSUp");

	Buttons = json_object_get(root, "Buttons");

	//Unpack simple values
	json_unpack(root, "{s:s, s:s, s:s, s:s}",
		"LTSense", &LTSense,
		"RTSense", &RTSense,
		"LSSense", &LSSense,
		"RSSense", &RSSense);

	//Unpack buttons array
	for(int i=0 ; i< 14; i++){
		currentButton = json_array_get(Buttons, i);

		json_unpack(currentButton, "{s:i, s:i, s:s, s:i s:i, s:i}",
			"inputType", &inputType,
			"key", &key,
			"mouseSpeed", &mouseSpeed,
			"specialCode", &specialCode,
			"mouseButton", &mouseButton,
			"mouseDirection", &mouseDirection);
		inputMap->Buttons[i]->inputType = inputType;
		inputMap->Buttons[i]->key = (char)key;
		inputMap->Buttons[i]->mouseSpeed = (float)atof(mouseSpeed);
		inputMap->Buttons[i]->specialCode = specialCode;
		inputMap->Buttons[i]->mouseButton = mouseButton;
		inputMap->Buttons[i]->mouseDirection = mouseDirection;
	}


	//Unpack objects and set values into input map

	//Left Trigger
	json_unpack(LTrigger, "{s:i, s:i, s:s, s:i s:i, s:i}",
		"inputType", &inputType,
		"key", &key,
		"mouseSpeed", &mouseSpeed,
		"specialCode", &specialCode,
		"mouseButton", &mouseButton,
		"mouseDirection", &mouseDirection);
	inputMap->LTrigger->inputType = inputType;
	inputMap->LTrigger->key = (char)key;
	inputMap->LTrigger->mouseSpeed = (float)atof(mouseSpeed);
	inputMap->LTrigger->specialCode = specialCode;
	inputMap->LTrigger->mouseButton = mouseButton;
	inputMap->LTrigger->mouseDirection = mouseDirection;

	//Right Trigger
	json_unpack(RTrigger, "{s:i, s:i, s:s, s:i s:i, s:i}",
		"inputType", &inputType,
		"key", &key,
		"mouseSpeed", &mouseSpeed,
		"specialCode", &specialCode,
		"mouseButton", &mouseButton,
		"mouseDirection", &mouseDirection);
	inputMap->RTrigger->inputType = inputType;
	inputMap->RTrigger->key = (char)key;
	inputMap->RTrigger->mouseSpeed = (float)atof(mouseSpeed);
	inputMap->RTrigger->specialCode = specialCode;
	inputMap->RTrigger->mouseButton = mouseButton;
	inputMap->RTrigger->mouseDirection = mouseDirection;

	//Left Stick Down
	json_unpack(LSDown, "{s:i, s:i, s:s, s:i s:i, s:i}",
		"inputType", &inputType,
		"key", &key,
		"mouseSpeed", &mouseSpeed,
		"specialCode", &specialCode,
		"mouseButton", &mouseButton,
		"mouseDirection", &mouseDirection);
	inputMap->LSDown->inputType = inputType;
	inputMap->LSDown->key = (char)key;
	inputMap->LSDown->mouseSpeed = (float)atof(mouseSpeed);
	inputMap->LSDown->specialCode = specialCode;
	inputMap->LSDown->mouseButton = mouseButton;
	inputMap->LSDown->mouseDirection = mouseDirection;

	//Left Stick Right
	json_unpack(LSRight, "{s:i, s:i, s:s, s:i s:i, s:i}",
		"inputType", &inputType,
		"key", &key,
		"mouseSpeed", &mouseSpeed,
		"specialCode", &specialCode,
		"mouseButton", &mouseButton,
		"mouseDirection", &mouseDirection);
	inputMap->LSRight->inputType = inputType;
	inputMap->LSRight->key = (char)key;
	inputMap->LSRight->mouseSpeed = (float)atof(mouseSpeed);
	inputMap->LSRight->specialCode = specialCode;
	inputMap->LSRight->mouseButton = mouseButton;
	inputMap->LSRight->mouseDirection = mouseDirection;

	//Left Stick Left
	json_unpack(LSLeft, "{s:i, s:i, s:s, s:i s:i, s:i}",
		"inputType", &inputType,
		"key", &key,
		"mouseSpeed", &mouseSpeed,
		"specialCode", &specialCode,
		"mouseButton", &mouseButton,
		"mouseDirection", &mouseDirection);
	inputMap->LSLeft->inputType = inputType;
	inputMap->LSLeft->key = (char)key;
	inputMap->LSLeft->mouseSpeed = (float)atof(mouseSpeed);
	inputMap->LSLeft->specialCode = specialCode;
	inputMap->LSLeft->mouseButton = mouseButton;
	inputMap->LSLeft->mouseDirection = mouseDirection;

	//Left Stick Up
	json_unpack(LSUp, "{s:i, s:i, s:s, s:i s:i, s:i}",
		"inputType", &inputType,
		"key", &key,
		"mouseSpeed", &mouseSpeed,
		"specialCode", &specialCode,
		"mouseButton", &mouseButton,
		"mouseDirection", &mouseDirection);
	inputMap->LSUp->inputType = inputType;
	inputMap->LSUp->key = (char)key;
	inputMap->LSUp->mouseSpeed = (float)atof(mouseSpeed);
	inputMap->LSUp->specialCode = specialCode;
	inputMap->LSUp->mouseButton = mouseButton;
	inputMap->LSUp->mouseDirection = mouseDirection;

	//Right Stick Down
	json_unpack(RSDown, "{s:i, s:i, s:s, s:i s:i, s:i}",
		"inputType", &inputType,
		"key", &key,
		"mouseSpeed", &mouseSpeed,
		"specialCode", &specialCode,
		"mouseButton", &mouseButton,
		"mouseDirection", &mouseDirection);
	inputMap->RSDown->inputType = inputType;
	inputMap->RSDown->key = (char)key;
	inputMap->RSDown->mouseSpeed = (float)atof(mouseSpeed);
	inputMap->RSDown->specialCode = specialCode;
	inputMap->RSDown->mouseButton = mouseButton;
	inputMap->RSDown->mouseDirection = mouseDirection;

	//Right Stick Right
	json_unpack(RSRight, "{s:i, s:i, s:s, s:i s:i, s:i}",
		"inputType", &inputType,
		"key", &key,
		"mouseSpeed", &mouseSpeed,
		"specialCode", &specialCode,
		"mouseButton", &mouseButton,
		"mouseDirection", &mouseDirection);
	inputMap->RSRight->inputType = inputType;
	inputMap->RSRight->key = (char)key;
	inputMap->RSRight->mouseSpeed = (float)atof(mouseSpeed);
	inputMap->RSRight->specialCode = specialCode;
	inputMap->RSRight->mouseButton = mouseButton;
	inputMap->RSRight->mouseDirection = mouseDirection;

	//Right Stick Left
	json_unpack(RSLeft, "{s:i, s:i, s:s, s:i s:i, s:i}",
		"inputType", &inputType,
		"key", &key,
		"mouseSpeed", &mouseSpeed,
		"specialCode", &specialCode,
		"mouseButton", &mouseButton,
		"mouseDirection", &mouseDirection);
	inputMap->RSLeft->inputType = inputType;
	inputMap->RSLeft->key = (char)key;
	inputMap->RSLeft->mouseSpeed = (float)atof(mouseSpeed);
	inputMap->RSLeft->specialCode = specialCode;
	inputMap->RSLeft->mouseButton = mouseButton;
	inputMap->RSLeft->mouseDirection = mouseDirection;

	//Right Stick Up
	json_unpack(RSUp, "{s:i, s:i, s:s, s:i s:i, s:i}",
		"inputType", &inputType,
		"key", &key,
		"mouseSpeed", &mouseSpeed,
		"specialCode", &specialCode,
		"mouseButton", &mouseButton,
		"mouseDirection", &mouseDirection);
	inputMap->RSUp->inputType = inputType;
	inputMap->RSUp->key = (char)key;
	inputMap->RSUp->mouseSpeed = (float)atof(mouseSpeed);
	inputMap->RSUp->specialCode = specialCode;
	inputMap->RSUp->mouseButton = mouseButton;
	inputMap->RSUp->mouseDirection = mouseDirection;

	//Clear memory
	delete root;

	delete LTSense;
	delete RTSense;
	delete LSSense;
	delete RSSense;

	delete LTrigger;
	delete RTrigger;
	delete LSDown;
	delete LSRight; 
	delete LSLeft;
	delete LSUp;
	delete RSDown;
	delete RSRight; 
	delete RSLeft;
	delete RSUp;
	
	delete Buttons;
	delete currentButton;

	delete mouseSpeed;

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

	//Buttons
	Buttons = json_array();
	inputObject = json_object();

	//Triggers
	LTrigger = json_object();
	RTrigger = json_object();

	//Sticks
	LSDown = json_object();
	LSRight = json_object();
	LSLeft = json_object();
	LSUp = json_object();
	RSDown = json_object();
	RSRight = json_object();
	RSLeft = json_object();
	RSUp = json_object();

	//Sensetivities
	LTSense = json_string(to_string(inputMap->LTSense).c_str());
	RTSense = json_string(to_string(inputMap->RTSense).c_str());
	LSSense = json_string(to_string(inputMap->LSSense).c_str());
	RSSense = json_string(to_string(inputMap->RSSense).c_str());

	/*
		Buttons
	*/
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

		json_array_append(Buttons, inputObject);

		inputObject = json_object(); //reset the object; without this, only the last button will be added 14 times
	}

	/*
		Left Trigger
	*/
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

	/*
		Right Trigger
	*/

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

	/*
		Left Stick
	*/
	inputType = json_integer(inputMap->LSDown->inputType);
	key = json_integer(inputMap->LSDown->key);
	specialCode = json_integer(inputMap->LSDown->specialCode);
	mouseButton = json_integer(inputMap->LSDown->mouseButton);
	mouseDirection = json_integer(inputMap->LSDown->mouseDirection);
	mouseSpeed = json_string(to_string(inputMap->LSDown->mouseSpeed).c_str());

	json_object_set(LSDown, "inputType", inputType);
	json_object_set(LSDown, "key", key);
	json_object_set(LSDown, "specialCode", specialCode);
	json_object_set(LSDown, "mouseButton", mouseButton);
	json_object_set(LSDown, "mouseDirection", mouseDirection);
	json_object_set(LSDown, "mouseSpeed", mouseSpeed);

	inputType = json_integer(inputMap->LSRight->inputType);
	key = json_integer(inputMap->LSRight->key);
	specialCode = json_integer(inputMap->LSRight->specialCode);
	mouseButton = json_integer(inputMap->LSRight->mouseButton);
	mouseDirection = json_integer(inputMap->LSRight->mouseDirection);
	mouseSpeed = json_string(to_string(inputMap->LSRight->mouseSpeed).c_str());

	json_object_set(LSRight, "inputType", inputType);
	json_object_set(LSRight, "key", key);
	json_object_set(LSRight, "specialCode", specialCode);
	json_object_set(LSRight, "mouseButton", mouseButton);
	json_object_set(LSRight, "mouseDirection", mouseDirection);
	json_object_set(LSRight, "mouseSpeed", mouseSpeed);

	inputType = json_integer(inputMap->LSLeft->inputType);
	key = json_integer(inputMap->LSLeft->key);
	specialCode = json_integer(inputMap->LSLeft->specialCode);
	mouseButton = json_integer(inputMap->LSLeft->mouseButton);
	mouseDirection = json_integer(inputMap->LSLeft->mouseDirection);
	mouseSpeed = json_string(to_string(inputMap->LSLeft->mouseSpeed).c_str());

	json_object_set(LSLeft, "inputType", inputType);
	json_object_set(LSLeft, "key", key);
	json_object_set(LSLeft, "specialCode", specialCode);
	json_object_set(LSLeft, "mouseButton", mouseButton);
	json_object_set(LSLeft, "mouseDirection", mouseDirection);
	json_object_set(LSLeft, "mouseSpeed", mouseSpeed);

	inputType = json_integer(inputMap->LSUp->inputType);
	key = json_integer(inputMap->LSUp->key);
	specialCode = json_integer(inputMap->LSUp->specialCode);
	mouseButton = json_integer(inputMap->LSUp->mouseButton);
	mouseDirection = json_integer(inputMap->LSUp->mouseDirection);
	mouseSpeed = json_string(to_string(inputMap->LSUp->mouseSpeed).c_str());

	json_object_set(LSUp, "inputType", inputType);
	json_object_set(LSUp, "key", key);
	json_object_set(LSUp, "specialCode", specialCode);
	json_object_set(LSUp, "mouseButton", mouseButton);
	json_object_set(LSUp, "mouseDirection", mouseDirection);
	json_object_set(LSUp, "mouseSpeed", mouseSpeed);

	/*
		Right Stick
	*/
	inputType = json_integer(inputMap->RSDown->inputType);
	key = json_integer(inputMap->RSDown->key);
	specialCode = json_integer(inputMap->RSDown->specialCode);
	mouseButton = json_integer(inputMap->RSDown->mouseButton);
	mouseDirection = json_integer(inputMap->RSDown->mouseDirection);
	mouseSpeed = json_string(to_string(inputMap->RSDown->mouseSpeed).c_str());

	json_object_set(RSDown, "inputType", inputType);
	json_object_set(RSDown, "key", key);
	json_object_set(RSDown, "specialCode", specialCode);
	json_object_set(RSDown, "mouseButton", mouseButton);
	json_object_set(RSDown, "mouseDirection", mouseDirection);
	json_object_set(RSDown, "mouseSpeed", mouseSpeed);

	inputType = json_integer(inputMap->RSRight->inputType);
	key = json_integer(inputMap->RSRight->key);
	specialCode = json_integer(inputMap->RSRight->specialCode);
	mouseButton = json_integer(inputMap->RSRight->mouseButton);
	mouseDirection = json_integer(inputMap->RSRight->mouseDirection);
	mouseSpeed = json_string(to_string(inputMap->RSRight->mouseSpeed).c_str());

	json_object_set(RSRight, "inputType", inputType);
	json_object_set(RSRight, "key", key);
	json_object_set(RSRight, "specialCode", specialCode);
	json_object_set(RSRight, "mouseButton", mouseButton);
	json_object_set(RSRight, "mouseDirection", mouseDirection);
	json_object_set(RSRight, "mouseSpeed", mouseSpeed);

	inputType = json_integer(inputMap->RSLeft->inputType);
	key = json_integer(inputMap->RSLeft->key);
	specialCode = json_integer(inputMap->RSLeft->specialCode);
	mouseButton = json_integer(inputMap->RSLeft->mouseButton);
	mouseDirection = json_integer(inputMap->RSLeft->mouseDirection);
	mouseSpeed = json_string(to_string(inputMap->RSLeft->mouseSpeed).c_str());

	json_object_set(RSLeft, "inputType", inputType);
	json_object_set(RSLeft, "key", key);
	json_object_set(RSLeft, "specialCode", specialCode);
	json_object_set(RSLeft, "mouseButton", mouseButton);
	json_object_set(RSLeft, "mouseDirection", mouseDirection);
	json_object_set(RSLeft, "mouseSpeed", mouseSpeed);

	inputType = json_integer(inputMap->RSUp->inputType);
	key = json_integer(inputMap->RSUp->key);
	specialCode = json_integer(inputMap->RSUp->specialCode);
	mouseButton = json_integer(inputMap->RSUp->mouseButton);
	mouseDirection = json_integer(inputMap->RSUp->mouseDirection);
	mouseSpeed = json_string(to_string(inputMap->RSUp->mouseSpeed).c_str());

	json_object_set(RSUp, "inputType", inputType);
	json_object_set(RSUp, "key", key);
	json_object_set(RSUp, "specialCode", specialCode);
	json_object_set(RSUp, "mouseButton", mouseButton);
	json_object_set(RSUp, "mouseDirection", mouseDirection);
	json_object_set(RSUp, "mouseSpeed", mouseSpeed);

	//Attach all the objects to the root
	json_object_set(root, "LTSense", LTSense);
	json_object_set(root, "RTSense", RTSense);
	json_object_set(root, "LSSense", LSSense);
	json_object_set(root, "RSSense", RSSense);
	
	json_object_set(root, "Buttons", Buttons);

	json_object_set(root, "LTrigger", LTrigger);
	json_object_set(root, "RTrigger", RTrigger);

	json_object_set(root, "LSDown", LSDown);
	json_object_set(root, "LSRight", LSRight);
	json_object_set(root, "LSLeft", LSLeft);
	json_object_set(root, "LSUp", LSUp);

	json_object_set(root, "RSDown", RSDown);
	json_object_set(root, "RSRight", RSRight);
	json_object_set(root, "RSLeft", RSLeft);
	json_object_set(root, "RSUp", RSUp);

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
	delete LSDown;
	delete LSRight; 
	delete LSLeft;
	delete LSUp;
	delete RSDown;
	delete RSRight; 
	delete RSLeft;
	delete RSUp;
	
	delete inputObject;

	delete inputType;
	delete key;
	delete specialCode;
	delete mouseButton;
	delete mouseDirection;
	delete mouseSpeed;

	return true;
}

InputMap* Mapper::getMap()
{
	return inputMap;
}

void Mapper::runMap()
{
	if(!running)
	{
		running = true;
		mapThread = new thread(&Mapper::mapController, this);		
	}
	else
	{
		cout << "Map is already running" << endl;
	}
}

void Mapper::stopMap()
{
	if(running)
	{
		running = false;
	}
	else
	{
		cout << "Map is not running" << endl;
	}
}

//This is the function that will run in the thread
void Mapper::mapController()
{
	DWORD* buttonsPressed; //Possible memory leak if this is never delete...
	DWORD buttonsPreviouslyPressed[14];

	float previousLTValue = 0;
	float previousRTValue = 0;

	SDL_Event event;

	while(running)
	{
		SDL_PollEvent(&event);
		gamepad->Refresh(event);

		buttonsPressed = gamepad->GetButtonsPressed();

		float leftStickX = gamepad->GetLeftStickX();
		float leftStickY = gamepad->GetLeftStickY();
		
		float rightStickX = gamepad->GetRightStickX();
		float rightStickY = gamepad->GetRightStickY();

		float leftTrigger = gamepad->GetLeftTrigger();
		float rightTrigger = gamepad->GetRightTrigger();

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
					robot->KeyDown(inputMap->Buttons[i]->key);
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

			if(inputMap->RSLeft->inputType == specialKey)
				robot->SpecialUp(inputMap->RSLeft->specialCode);
			if(inputMap->RSRight->inputType == specialKey)
				robot->SpecialUp(inputMap->RSRight->specialCode);
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

			if(inputMap->RSUp->inputType == specialKey)
				robot->SpecialUp(inputMap->RSUp->specialCode);
			if(inputMap->RSDown->inputType == specialKey)
				robot->SpecialUp(inputMap->RSDown->specialCode);
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
