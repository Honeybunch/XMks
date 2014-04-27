#include "main.h"

int main(int argc, char* argv[])
{	
	bool running = true;

	//We will be using the Joystick subsystem of SDL, but we kind of have to init everything
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL Failed to initialize: " << SDL_GetError();
		return -1;
	}

	SDL_SetHint("SDL_JOYSTICK_ALLOW_BACKGROUND_EVENTS", "1"); 

	Mapper* mapperOne = new Mapper(1);

	while(running)
	{
		cout << "Commmands: " << endl;
		cout << "load - Load a Map" << endl;
		cout << "start - Start Map" << endl;
		cout << "stop - End Map" << endl;
		cout << "edit - Edit Current Map" << endl;
		cout << "write - Write Current Map to a File" << endl;
		cout << "exit - Exit Program" << endl;

		string input;
		getline(cin, input);

		if(input == "load")
		{
			cout << "Enter the filename (.map): " << endl;

			string file;
			getline(cin, file);

			if(mapperOne->loadMap("res/" + file))
				cout << file << " was loaded!" << endl;
			else 
				cout << "The file " << file << " could not be found" << endl;
				
		}
		else if(input == "start")
		{
			mapperOne->runMap();
		}
		else if(input == "stop")
		{
			mapperOne->stopMap();
		}
		else if(input == "edit")
		{
			system("cls");
			cout << "What would you like to edit?" << endl;
			cout << "Buttons: A, B, DDown, Back, LStick, LShoulder etc." << endl;
			cout << "Sticks: LSUp, RSDown, etc" << endl;
			cout << "Triggers: LTrigger, RTrigger" << endl;
			cout << "Sensetivites: Left Stick, Right Trigger, etc" << endl << endl;

			string inputName = "";
			getline(cin, inputName);

			if(mapperOne->getMap()->inputs[inputName])
			{
				system("cls");
				cout << "What would you like to map " << inputName << " to?" << endl;
				cout << "0 - basic key" << endl;
				cout << "1 - special key (left, escape, etc)" << endl;
				cout << "2 - mouse press" << endl;
				cout << "3 - mouse movement" << endl << endl;
				
				int type = -1;

				//only take numeric input
				bool valid = false;
				while(!valid)
				{
					cin >> type;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');

					if((type >=0 && type <= 3))
						valid = true;
					else
						cout << "sorry, that's not a valid type" << endl;
				}

				//Depending on the type of input, create a new input object
				Input* newInput = new Input();

				if(type == 0)
				{
					
				}
				else if(type == 1)
				{
				
				}
				else if(type == 2)
				{
				
				}
				else if(type == 3)
				{
				
				}

				//Set the new input
				mapperOne->getMap()->inputs[inputName] = newInput;

				cout << "Input Mapped" << endl;
			}
			else
			{
				cout << "Sorry, there's no input by that name" << endl;
			}
		}
		else if(input == "exit")
		{
			running = false;
		}
	}

	delete mapperOne;

	return 0;
}