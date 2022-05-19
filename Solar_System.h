#pragma once
#include <SFML/Graphics.hpp>
#include "Planet.h"
using namespace std;

class Solar_System
{
public:
	VertexArray stars;
	vector<Planet> planets;

	Solar_System();
	~Solar_System();
};