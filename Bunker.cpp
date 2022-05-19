#include "Bunker.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include "Planet.h"
#include <cmath>;
#include <iostream>
#include <random>


Bunker::Bunker()
{
	bunker_shape.setSize(Vector2f(20, 20));
	bullet.bulletImage.setRadius(2.f);
	bullet.bulletImage.setFillColor(Color::Red);
	shootTimerMax = 400;
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> randomType(0, 1);
	type = randomType(rng);
	if (type == 0) {
		bunker_shape.setFillColor(Color::Blue);
	}
	else {
		bunker_shape.setFillColor(Color(240, 128, 128));
	}
}
void Bunker::bunker_Fire(float windowy) {

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> random(0, 2);
	std::uniform_int_distribution<std::mt19937::result_type> random1(0, 1);
	if (shootTimer < shootTimerMax) {
		shootTimer++;
	}
	if (type == 0) {
		value = random(rng);
		if(shootTimer >= shootTimerMax){
			bullet.bulletImage.setPosition(bunker_center);
			if (value == 0) {
				bullet.vecVel = Vector2f(velocity + velocityL);
			}
			else if (value == 1) {
				bullet.vecVel = velocity;
			}
			else if (value == 2) {
				bullet.vecVel = Vector2f(velocity - velocityL);
			}
			bullets.push_back(Bullet(bullet));
			shootTimer = 0;
		}
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].bulletImage.move(bullets[i].vecVel.x * 0.4, bullets[i].vecVel.y * 0.4);
			bullets[i].bulletDistance++;
			if (bullets[i].bulletImage.getPosition().y < 0 || bullets[i].bulletImage.getPosition().y > windowy || bullets[i].bulletDistance >= 600) {
				bullets.erase(bullets.begin() + i);
			}
		}
	}
	else {
		value = random1(rng);
	 if (shootTimer >= shootTimerMax) {
			bullet.bulletImage.setPosition(bunker_center);
			if (value == 0) {
				bullet.vecVel = Vector2f(velocity + velocityL);
			}
			else {
				bullet.vecVel = Vector2f(velocity - velocityL);
			}
			bullets.push_back(Bullet(bullet));
			shootTimer = 0;
		}
		
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i].bulletImage.move(bullets[i].vecVel.x * 0.4, bullets[i].vecVel.y * 0.4);
			bullets[i].bulletDistance++;
			if (bullets[i].bulletImage.getPosition().y < 0 || bullets[i].bulletImage.getPosition().y > windowy || bullets[i].bulletDistance >= 600) {
				bullets.erase(bullets.begin() + i);
			}
		}
	}
}


Bunker::~Bunker()
{
}
