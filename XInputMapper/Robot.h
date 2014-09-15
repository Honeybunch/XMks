#ifndef ROBOT_H
#define ROBOT_H

#include <windows.h>

class Robot
{
public:
	Robot(void);

	//Mouse Functions
	void MouseDown(int button);
	void MouseUp(int button);

	void MouseMovement(int direction, float amount);

	//Keyboard functions
	void KeyDown(char key);
	void KeyUp(char key);
	void SpecialDown(short VKCode);
	void SpecialUp(short VKCode);

	~Robot(void);
};

#endif

