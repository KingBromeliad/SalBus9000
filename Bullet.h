#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Bullet
{
public:
	CircleShape bulletImage;
	Vector2f vecVel;
	int bulletDistance;

	Bullet();
	~Bullet();
};

