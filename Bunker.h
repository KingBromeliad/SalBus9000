#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include "Bullet.h"

using namespace sf;

class Bunker
{
public:
	RectangleShape bunker_shape;
	bool is_destroyed = false;
	int shootTimer;
	int shootTimerMax;
	int value;
	int type;
	Bullet bullet;
	std::vector<Bullet>bullets;
	Vector2f velocity;
	Vector2f velocityL;
	Vector2f bunker_center;


	void bunker_Fire(float windowy);
	Bunker();
	~Bunker();
};
