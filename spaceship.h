#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include "Bullet.h"

using namespace sf;

class spaceship {
public:
	Vector2f vecVel;
	Vector2f vecAcc;
	float maxSpeed;
	bool playerUp, playerLeft, playerRight, fuelGrabber, shoot;
	bool godmode;
	int shootTimer, shootTimerMax;
	float fuel;
	Bullet bullet;
	std::vector<Bullet>bullets;
	CircleShape spaceshipImage;
	CircleShape vertexImage;
	CircleShape thrust;
	CircleShape thrust2;
	VertexArray fuelRay;
	CircleShape forceField;

	spaceship();
	~spaceship();
	void controlSpaceship();
	void controlFuelRay();
	void shooting(float windowy);
	void fuelUp(int type);

};

