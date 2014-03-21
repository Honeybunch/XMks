#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "jansson.h"
#include "jansson_config.h"

#include "InputMap.h"
#include "XGamepad.h"
#include "Robot.h"

using namespace std;

class Mapper
{
public:
	Mapper(int portNumber);

	bool loadMap(string file);
	bool writeMap(string file);

	void runMap();

	~Mapper(void);

private:
	Robot* robot;
	XGamepad* gamepad;
	InputMap* inputMap;
};

