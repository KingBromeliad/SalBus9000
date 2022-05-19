#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Fuel
{
public:
	RectangleShape fuel_shape;
	int fuel_type;

	Fuel();
	~Fuel();
};

