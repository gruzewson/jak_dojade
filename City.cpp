#include "City.h"

City::City()
{
	this->name = "";
	this->x = 0;
	this->y = 0;
}

City::City(String name, int x, int y, int index)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->index = index;
}

City::~City()
{
}
