#include "GameInfo.h"
#include <cstring>
#include "SFML/Graphics.hpp"
using namespace sf;


void GameInfo::drawUi(RenderWindow & window, View & view, int fuel, int windowx)
{
	if (Lives <= 0 || fuel < 0) game_over = true;

	if (Score >= nextship) {
		nextship += 1000;
		if (Lives < Max_lives) Lives++;
	}

	fuelText.setPosition(view.getCenter().x + windowx / 2 - 150, view.getCenter().y - windowx / 2 + 20);
	fuelTextD.setPosition(view.getCenter().x + windowx / 2 - 150, view.getCenter().y - windowx / 2 + 46);
	scoreText.setPosition(view.getCenter().x - 40, view.getCenter().y - windowx / 2);
	scoreTextD.setPosition(view.getCenter().x - 40, view.getCenter().y - windowx / 2 + 26);
	nextShipText.setPosition(view.getCenter().x - 45, view.getCenter().y - windowx / 2 + 52);
	nextShipTextD.setPosition(view.getCenter().x - 45, view.getCenter().y - windowx / 2 + 70);
	livesText.setPosition(view.getCenter().x - windowx / 2 + 100, view.getCenter().y - windowx / 2 + 20);

	fuelTextD.setString(std::to_string(fuel));
	scoreTextD.setString(std::to_string(Score));
	nextShipTextD.setString(std::to_string(nextship));

	window.draw(fuelText);
	window.draw(fuelTextD);
	window.draw(scoreText);
	window.draw(scoreTextD);
	window.draw(livesText);
	window.draw(nextShipText);
	window.draw(nextShipTextD);

	for (int i = 0; i < Lives; i++) {
		lives[i].setPosition(view.getCenter().x - windowx / 2 + 90 + i * 16, view.getCenter().y - windowx / 2 + 54);
		window.draw(lives[i]);
	}

}

GameInfo::GameInfo()
{
	game_over = false;
	Score = 0;
	Lives = 5;
	startValue = 0;
	for (int i = 0; i < Max_lives; i++) {
		CircleShape live;
		live.setPointCount(3);
		live.setRadius(6);
		live.setFillColor(Color::Transparent);
		live.setOutlineThickness(1.1);
		live.setOutlineColor(Color::Blue);
		lives.push_back(live);
	}

	font.loadFromFile("Vector Waves.ttf");
	textureIntro.loadFromFile("NON-GRAVITAR.png");
	textureIntro.setSmooth(true);
	intro.setTexture(textureIntro);
	intro.setPosition(0, 0);
	intro.scale(0.29, 0.29);

	fuelText.setFont(font);
	scoreText.setFont(font);
	fuelTextD.setFont(font);
	scoreTextD.setFont(font);
	nextShipText.setFont(font);
	nextShipTextD.setFont(font);
	livesText.setFont(font);
	
	fuelText.setCharacterSize(24);
	fuelTextD.setCharacterSize(24);
	scoreText.setCharacterSize(24);
	scoreTextD.setCharacterSize(24);
	nextShipText.setCharacterSize(18);
	nextShipTextD.setCharacterSize(18);
	livesText.setCharacterSize(24);

	fuelText.setFillColor(Color::Green);
	fuelTextD.setFillColor(Color::Blue);
	scoreText.setFillColor(Color::Green);
	scoreTextD.setFillColor(Color::Blue);
	nextShipText.setFillColor(Color::Green);
	nextShipTextD.setFillColor(Color::Blue);
	livesText.setFillColor(Color::Green);


	fuelText.setString("FUEL");
	scoreText.setString("SCORE");
	nextShipText.setString("NEXT SHIP");
	livesText.setString("LIVES");

	testoDistruzionePianeta.setFont(font);
	testoDistruzionePianeta.setCharacterSize(50);
	testoDistruzionePianeta.setFillColor(Color::Green);
	testoDistruzionePianeta.setString("PLANET CLEAR!");

	testoDistruzioneSys.setFont(font);
	testoDistruzioneSys.setCharacterSize(50);
	testoDistruzioneSys.setFillColor(Color::Green);
	testoDistruzioneSys.setString("SOLAR SYSTEM CLEAR!");

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(50);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setString("GAME OVER");

	
	pressEnterToRestart.setFont(font);
	pressEnterToRestart.setCharacterSize(30);
	pressEnterToRestart.setFillColor(Color::Green);
	pressEnterToRestart.setString("PRESS 'ENTER' TO RESTART");

	pressEnterToStart.setFont(font);
	pressEnterToStart.setCharacterSize(30);
	pressEnterToStart.setFillColor(Color::Green);
	pressEnterToStart.setString("PRESS 'ENTER' TO START");

	outOfFuel.setFont(font);
	outOfFuel.setCharacterSize(30);
	outOfFuel.setFillColor(Color::Red);
	outOfFuel.setString("OUT OF FUEL");

	credits.setFont(font);
	credits.setCharacterSize(30);
	credits.setFillColor(Color::Magenta);
	credits.setString("Credits: Enrico Sallei & Samuele Busi-2019");
}

void GameInfo::drawTransiction(RenderWindow& window, View& view, int n) {//n seleziona il tipo di transizione/schermata
	int value = 0;
	if (n == 0) { //distruzione pianeta
		for (int i = 0; i < 500; i++) {
			testoDistruzionePianeta.setPosition(view.getCenter().x - 150, view.getCenter().y - 50);
			window.clear();
			window.draw(testoDistruzionePianeta);
			window.display();
		}
	}else if(n == 1){ //distruzione sistema solare
		for (int i = 0; i < 1000; i++) {
			testoDistruzioneSys.setPosition(testoDistruzionePianeta.getPosition().x - 80, testoDistruzionePianeta.getPosition().y);
			window.clear();
			window.draw(testoDistruzioneSys);
			window.display();
		}
	}
	else if (n == 2) { //game over normale
		while (game_over) {
			gameOverText.setPosition(view.getCenter().x - 120, view.getCenter().y - 200);
			if (Keyboard::isKeyPressed(Keyboard::Enter) || Joystick::isButtonPressed(0, 7)) {
				window.close();
				game_over = false;
			}
			pressEnterToRestart.setPosition(view.getCenter().x - 160, view.getCenter().y + 30);
			window.clear();
			window.draw(gameOverText);
			value++;
			if (value < 250) {
				window.draw(pressEnterToRestart);
			}
			if (value == 500) {
				value = 0;
			}
			window.display();
		}
	}
	else if (n == 3) {//intro screen
		window.draw(intro);
		pressEnterToStart.setPosition(view.getCenter().x - 150, view.getCenter().y + 200);
		credits.setPosition(view.getCenter().x - 280, view.getCenter().y + 260);
		window.draw(credits);
		startValue++;
		if (startValue < 250) {
			window.draw(pressEnterToStart);
		}if (startValue == 500) {
			startValue = 0;
		}
	}
	else if (n == 4) {
		while (game_over) { // game over out of fuel
			gameOverText.setPosition(view.getCenter().x - 120, view.getCenter().y - 200);
			outOfFuel.setPosition(gameOverText.getPosition().x + 50, gameOverText.getPosition().y + 70);
			if (Keyboard::isKeyPressed(Keyboard::Enter) || Joystick::isButtonPressed(0, 7)) {
				window.close();
				game_over = false;
			}
			pressEnterToRestart.setPosition(view.getCenter().x - 160, view.getCenter().y);
			window.clear();
			window.draw(gameOverText);
			window.draw(outOfFuel);
			value++;
			if (value < 250) {
				window.draw(pressEnterToRestart);
			}
			if (value == 500) {
				value = 0;
			}
			window.display();
		}
	}
}

GameInfo::~GameInfo()
{
}