#include <SFML/Graphics.hpp>
#include <math.h> 
#include <random>
#include <ctime>
#include <vector>
#include "Planet.h"
#include "Bunker.h"
#include "Fuel.h"
using namespace sf;


Planet::Planet()
{
	terrain.resize(Vertex_n);

	particles.setPrimitiveType(Points);
	particles.resize(40);
	for (int i = 0; i < particles.getVertexCount(); i++) {
		particles[i].color = Color::Red;
	}

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> random(0, 100);
	std::uniform_int_distribution<std::mt19937::result_type> random1(0, 200);

	int randomT;
	srand((unsigned)time(0));

	terrain.setPrimitiveType(LinesStrip);
	terrain.resize(Vertex_n);

	for (int i = 0; i < Vertex_n; i++) {
		terrain[i].position = Vector2f(i * 100 + random(rng), 400 + random1(rng));
		terrain[i].color = Color::Magenta;
	}
	terrain[0].position = Vector2f(0.f, 500.f);
	terrain[Vertex_n - 1].position = Vector2f(Vertex_n * 100, 500.f);

	//bunker shid;

	Vector2f vert1;
	Vector2f vert2;
	float rotation;


	for (int i = 1; i < (Vertex_n - 1); i++)
	{
		randomT = (rand() % 7) + 0;

		if ((i % 5 == 0) || (randomT == 4)) {
			vert1 = terrain[i].position;
			vert2 = terrain[i + 1].position;

			Bunker bunker;
			bunker.bunker_shape.setOrigin(bunker.bunker_shape.getSize().x / 2, 0);
			bunker.bunker_center = Vector2f(bunker.bunker_shape.getOrigin().x, bunker.bunker_shape.getOrigin().y + bunker.bunker_shape.getSize().y / 2);
			bunker.bunker_shape.setPosition(Vector2f(((vert2.x + vert1.x) / 2), ((vert2.y + vert1.y) / 2)));
			rotation = asin((vert1.y - vert2.y) / (sqrt(pow((vert2.x - vert1.x), 2) + pow((vert2.y - vert1.y), 2))));
			bunker.bunker_center = Vector2f(bunker.bunker_shape.getPosition().x, bunker.bunker_shape.getPosition().y + bunker.bunker_shape.getSize().y / 2);

			bunker.bunker_center.x = (bunker.bunker_center.x - bunker.bunker_shape.getPosition().x) * cos(3.141592654 - rotation) - (bunker.bunker_center.y - bunker.bunker_shape.getPosition().y) * sin(3.141592654 - rotation) + bunker.bunker_shape.getPosition().x;
			bunker.bunker_center.y = (bunker.bunker_center.x - bunker.bunker_shape.getPosition().x) * sin(3.141592654 - rotation) + (bunker.bunker_center.y - bunker.bunker_shape.getPosition().y) * cos(3.141592654 - rotation) + bunker.bunker_shape.getPosition().y;


			bunker.velocity = Vector2f((-(vert1.y - vert2.y) / (sqrt(pow((vert2.x - vert1.x), 2) + pow((vert2.y - vert1.y), 2)))), ((vert1.x - vert2.x) / (sqrt(pow((vert2.x - vert1.x), 2) + pow((vert2.y - vert1.y), 2)))));
			bunker.velocityL = Vector2f(((vert1.x - vert2.x) / (sqrt(pow((vert2.x - vert1.x), 2) + pow((vert2.y - vert1.y), 2)))), ((vert1.y - vert2.y) / (sqrt(pow((vert2.x - vert1.x), 2) + pow((vert2.y - vert1.y), 2)))));
			rotation = rotation * (57.29577); //radiant to degree conversion by: value * (180 / pi)
			bunker.bunker_shape.setRotation(-rotation + 180);



			bunkers.push_back(bunker);
		}
		else if (i % 6 == 0) {
			vert1 = terrain[i].position;
			vert2 = terrain[i + 1].position;

			Fuel fuel;

			fuel.fuel_shape.setPosition(Vector2f(((vert2.x + vert1.x) / 2), ((vert2.y + vert1.y) / 2)));
			rotation = asin((vert1.y - vert2.y) / (sqrt(pow((vert2.x - vert1.x), 2) + pow((vert2.y - vert1.y), 2))));
			rotation = rotation * (57.29577); //radiant to degree conversion by: value * (180 / pi)
			fuel.fuel_shape.setRotation(-rotation);

			fuels.push_back(fuel);
		}
	}
}

bool Planet::Collision(Vector2f p, Vector2f vert1, Vector2f vert2) {
	float miny;
	if (vert1.y >= vert2.y) miny = vert1.y;
	else miny = vert2.y;
	if ((((((p.x - vert1.x) / (vert2.x - vert1.x)) - ((p.y - vert1.y) / (vert2.y - vert1.y))) < 0.1 && (((p.x - vert1.x) / (vert2.x - vert1.x)) - ((p.y - vert1.y) / (vert2.y - vert1.y))) > -0.1) || (p.y > miny)) && p.x <= vert2.x && p.x >= vert1.x)
		return true;
	else return false;
}

void Planet::Explode(RenderWindow& window, Vector2f pos, int count)
{
	int randomT;
	srand((unsigned)time(0));
	randomT = (rand() % 7) + 0;

	std::default_random_engine rng;
	std::uniform_real_distribution<double> random(-10.0, 25.0);

	for (int i = 0; i < (particles.getVertexCount() - 5); i += 6) {
		particles[i + 0].position = Vector2f(pos.x + count / 7 + random(rng), pos.y - count / 5 - random(rng));
		particles[i + 1].position = Vector2f(pos.x - count / 7 - random(rng), pos.y - count / 5 - random(rng));
		particles[i + 2].position = Vector2f(pos.x + count / 7 + random(rng), pos.y - count / 70 - random(rng));
		particles[i + 3].position = Vector2f(pos.x - count / 7 - random(rng), pos.y - count / 70 - random(rng));
		particles[i + 4].position = Vector2f(pos.x + count / 60 + random(rng), pos.y - count / 10 - random(rng));
		particles[i + 5].position = Vector2f(pos.x - count / 60 - random(rng), pos.y - count / 10 - random(rng));
		particles[i + 6].position = Vector2f(pos.x, pos.y - count / 2 - random(rng) / 10);

		randomT = (rand() % 3) + 0;
		if (count > 80 && randomT > 1) particles[i].color = Color::Black;

	}

	window.draw(particles);

}

Planet::~Planet()
{
}