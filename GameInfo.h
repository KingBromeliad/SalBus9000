#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
using namespace sf;
class GameInfo
{
public:
	int Score = 0;
	int Lives = 5;
	int const Max_lives = 10;
	int nextship = 1000;
	bool game_over;
	std::vector<CircleShape> lives;

	Font font;

	Text fuelText;
	Text fuelTextD;
	Text scoreText;
	Text scoreTextD;
	Text livesText;
	Text nextShipText;
	Text nextShipTextD;
	Text testoDistruzionePianeta;
	Text testoDistruzioneSys;
	Text gameOverText;
	Text pressEnterToRestart;
	Text pressEnterToStart;
	Text outOfFuel;
	Text credits;
	Texture textureIntro;
	Sprite intro;
	int startValue;

	void drawUi(RenderWindow &window, View &view, int fuel, int windowx);
	void drawTransiction(RenderWindow &window, View &view, int n);
	GameInfo();
	~GameInfo();
};