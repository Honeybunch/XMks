#ifndef INPUT_H
#define INPUT_H

enum INPUTTYPE
{
	key,
	specialKey, 
	mousePress,
	mouseMovement
};

class Input
{
public:
	Input(short inputType, char k, short sC, int mB, int mD, float mS);
	Input();

	/*
		0 = key
		1 = specialKey
		2 = mousePress
		3 = mouseMovement
	*/
	short inputType;

	char key;
	short specialCode;
	int mouseButton;
	int mouseDirection;
	float mouseSpeed;

	~Input(void);
};

#endif