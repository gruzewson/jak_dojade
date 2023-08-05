#pragma once
#include "String.h"
#include "Vector.h"
#include "Pair.h"
class City
{
public:
	String name;
	bool checked = false;
	int index;
	int x, y;
	Vector<MyPair<City*, int>> neighbours;
	City();
	City(String name, int x, int y, int index);
	~City();
};

