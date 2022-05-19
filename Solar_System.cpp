#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "Solar_System.h"
#include "Planet.h"
using namespace sf;

Solar_System::Solar_System()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> random(100, 550);
	std::uniform_int_distribution<std::mt19937::result_type> random1(0, 20);
	std::uniform_int_distribution<std::mt19937::result_type> randoms(0, 5000);
	std::uniform_int_distribution<std::mt19937::result_type> random1s(0, 620);

	stars.resize(500);
	stars.setPrimitiveType(Points);
	for (int i = 0; i < 500; i++) {
		stars[i].position = Vector2f(randoms(rng), random1s(rng));
	}

	for (int i = 0; i < 5; i++) {
		Planet planet;
		planet.out_view.setPosition((i + 1) * 102, random(rng));
		planet.out_view.setRadius(random1(rng) + 15);
		planet.out_view.setFillColor(Color(random1(rng) * 10, random1(rng) * 5, random1(rng) * 11));
		planet.out_view.setOutlineThickness(random1(rng));
		planet.out_view.setOutlineColor(Color(i * 50, random1(rng) * 3, 100));

		planets.push_back(planet);
	}
}

Solar_System::~Solar_System() {

}