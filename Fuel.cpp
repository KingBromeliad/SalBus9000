#include "Fuel.h"
#include <SFML/Graphics.hpp>
#include <random>
using namespace std;



Fuel::Fuel()
{

	fuel_shape.setSize(Vector2f(8, 8));
	fuel_shape.setFillColor(Color::Transparent);
	fuel_shape.setOutlineThickness(2.6);
	fuel_shape.setOutlineColor(Color::Blue);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> random(0, 2);
	fuel_type = random(rng);
	if (fuel_type < 2) {
		fuel_shape.setOutlineColor(Color::Red);
	}

}


Fuel::~Fuel()
{
}
