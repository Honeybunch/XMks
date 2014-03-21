#include "main.h"

int main()
{	
	std::cout << "Please Connect a Controller" << std::endl;

	Mapper* mapperOne = new Mapper(1);

	mapperOne->writeMap("res/test.map");

	delete mapperOne;

	return 0;
}