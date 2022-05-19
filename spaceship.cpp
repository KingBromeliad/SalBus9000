#include "spaceship.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace sf;


spaceship::spaceship() {
	vecAcc = Vector2f(0.f, 0.f);
	maxSpeed = 0.8;
	fuel = 5000;
	shootTimer = 0;
	shootTimerMax = 50;
	playerUp = false;
	playerLeft = false;
	playerRight = false;
	fuelGrabber = false;
	shoot = false;
	godmode = false;
	//spaceship image
	spaceshipImage.setPointCount(3);
	spaceshipImage.setRadius(10.f);
	spaceshipImage.setOutlineThickness(2.f);
	spaceshipImage.setOutlineColor(Color::Magenta);
	spaceshipImage.setFillColor(Color::Black);
	spaceshipImage.setOrigin(spaceshipImage.getPosition().x + 10, spaceshipImage.getPosition().y + 10);
	spaceshipImage.setPosition(50, 50);
	vertexImage.setPointCount(3);
	vertexImage.setOutlineThickness(3.f);
	vertexImage.setOutlineColor(Color::Blue);
	vertexImage.setFillColor(Color::Blue);
	vertexImage.setRadius(5.f);
	vertexImage.setOrigin(spaceshipImage.getOrigin().x - 5, spaceshipImage.getOrigin().y);
	//thrust image
	thrust.setPointCount(3);
	thrust.setFillColor(Color(255, 117, 20));
	thrust.setRadius(3.f);
	thrust.setOrigin(spaceshipImage.getOrigin().x - 6.5, spaceshipImage.getOrigin().y + 1.5);
	thrust2.setPointCount(3);
	thrust2.setFillColor(Color::Red);
	thrust2.setRadius(6.f);
	thrust2.setOrigin(spaceshipImage.getOrigin().x - 3.5, spaceshipImage.getOrigin().y + 6);
	//fuel ray
	fuelRay.setPrimitiveType(Lines);
	fuelRay.resize(4);
	for (int i = 0; i < 4; i++) {
		fuelRay[i].color = Color::Yellow;
	}
	//force field
	forceField.setOutlineThickness(1);
	forceField.setFillColor(Color::Transparent);
	forceField.setOutlineColor(Color::Red);
	forceField.setRadius(25.f);
	//bullet
	bullet.bulletImage.setFillColor(Color::Yellow);
	bullet.bulletImage.setRadius(2.f);

}


spaceship::~spaceship() {

}


void spaceship::controlSpaceship() {
	
	float Xaxis = Joystick::getAxisPosition(0, Joystick::X);
	//float Yaxis = Joystick::getAxisPosition(0, Joystick::Y);
	//vecVel = Vector2f(Xaxis / 100, Yaxis / 100);
	
	if (Keyboard::isKeyPressed(Keyboard::W) || Joystick::isButtonPressed(0, 4)) {
		playerUp = true;
	}
	else {
		playerUp = false;
	}
	
	if (Keyboard::isKeyPressed(Keyboard::D) || Xaxis > 50) {
		playerRight = true;
	}
	else {
		playerRight = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) || Xaxis < -50) {
		playerLeft = true;
	}
	else {
		playerLeft = false;
	}
	
	if (playerRight) {
		spaceshipImage.setRotation(spaceshipImage.getRotation() + 0.5);
	}
	if (playerLeft) {
		spaceshipImage.setRotation(spaceshipImage.getRotation() - 0.5);
	}
	vecVel = Vector2f((sin(spaceshipImage.getRotation() / 57.2957)) * 0.5, (-cos(spaceshipImage.getRotation() / 57.2957)) * 0.5);
	
	if (playerUp) {
		vecAcc.x += vecVel.x * 0.002;
		vecAcc.y += vecVel.y * 0.002;		if (vecAcc.x > maxSpeed)vecAcc.x = maxSpeed;
		if (vecAcc.y > maxSpeed)vecAcc.y = maxSpeed;
		if (vecAcc.x < -maxSpeed)vecAcc.x = -maxSpeed;
		if (vecAcc.y < -maxSpeed)vecAcc.y = -maxSpeed;
		fuel -= 0.1;
	}
	spaceshipImage.move(vecAcc);
	vertexImage.setPosition(spaceshipImage.getPosition());
	vertexImage.setRotation(spaceshipImage.getRotation());
	thrust.setPosition(spaceshipImage.getPosition());
	thrust.setRotation(spaceshipImage.getRotation() + 180);
	thrust2.setPosition(spaceshipImage.getPosition());
	thrust2.setRotation(spaceshipImage.getRotation() + 180);
}

void spaceship::controlFuelRay() {
	
	float Yaxis;
	Yaxis = Joystick::getAxisPosition(0, Joystick::Y);

	if (Keyboard::isKeyPressed(Keyboard::S) || Yaxis > 50) {
		fuelGrabber = true;
	}
	else {
		fuelGrabber = false;
	}
	
	if (fuelGrabber) {
		fuelRay[0].position = Vector2f(spaceshipImage.getPosition().x - 15, spaceshipImage.getPosition().y + 40);
		fuelRay[1].position = Vector2f(spaceshipImage.getPosition().x - 5, spaceshipImage.getPosition().y + 5);
		fuelRay[2].position = Vector2f(spaceshipImage.getPosition().x + 5, spaceshipImage.getPosition().y + 5);
		fuelRay[3].position = Vector2f(spaceshipImage.getPosition().x + 15, spaceshipImage.getPosition().y + 40);
		if (vecAcc.x > 0) {
			vecAcc.x -= 0.001;
		}
		else if (vecAcc.x < 0) {
			vecAcc.x += 0.001;
		}
		if (vecAcc.y > 0) {
			vecAcc.y -= 0.001;
		}
		else if (vecAcc.y < 0) {
			vecAcc.y += 0.001;
		}
		forceField.setPosition(spaceshipImage.getPosition().x - 25, spaceshipImage.getPosition().y - 25);
	}
}


void spaceship::shooting(float windowy) {
	if ((playerUp && Keyboard::isKeyPressed(Keyboard::K)) || Joystick::isButtonPressed(0, 5)) {
		shoot = true;
	}
	else {
		shoot = false;
	}
	
	if (shootTimer < shootTimerMax) {
		shootTimer++;
	}
	if (shoot && shootTimer >= shootTimerMax && bullets.size() < 2) {
		bullet.bulletImage.setPosition(Vector2f(spaceshipImage.getPosition()));
		bullet.vecVel = Vector2f(vecVel.x * 2, vecVel.y * 2);
		bullets.push_back(Bullet(bullet));
		shootTimer = 0;
	}
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].bulletImage.move(bullets[i].vecVel);
		bullets[i].bulletDistance++;
		if (bullets[i].bulletDistance > 200) {
			bullets.erase(bullets.begin() + i);
		}
	}
}

void spaceship::fuelUp(int type) {
	if (type < 2) {
		fuel += 2000;
	}
	else {
		fuel += 5000;
	}
}
