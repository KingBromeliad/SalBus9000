#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bunker.h"
#include "Fuel.h"
using namespace sf;

class Planet
{
public:
	int Vertex_n = 30;
	int Fuel_n = 100;
	CircleShape out_view;
	VertexArray terrain;
	VertexArray particles;
	std::vector<Bunker> bunkers;
	std::vector<Fuel> fuels;

	bool Collision(Vector2f p, Vector2f vert1, Vector2f vert2);
	void Explode(RenderWindow& window, Vector2f pos, int count);
	Planet();
	~Planet();
};