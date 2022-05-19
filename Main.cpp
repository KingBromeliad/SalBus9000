#include "SFML/Graphics.hpp"
#include <iostream>
#include "Solar_System.h"
#include "spaceship.h"
#include <cmath>
#include "GameInfo.h"
#include <vector>
using namespace sf;


int WinMain() {
	bool startBool = true;
	bool kill9 = false;
	while (true && !kill9) {
		GameInfo UI;
		std::vector<Solar_System>sys;
		sys.resize(1);
		bool isInPlanet = false;
		bool thrust = false;
		bool animation = false;
		int currentPlanet = 0;
		int counter = 0;
		Vector2f position;
		int windowx = 1080;
		int windowy = 1080;
		View view;
		view.setSize(windowx, windowy);
		view.setCenter(windowx / 2, windowy / 2);
		RenderWindow window(sf::VideoMode(windowx, windowy), "Non-Gravitar!");
		window.setView(view);
		window.setFramerateLimit(500);
		spaceship SalBus9000;

		
		
		
		while (window.isOpen() && !kill9)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			//while per intro
			while (startBool) {
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter) || Joystick::isButtonPressed(0, 7)) {
					startBool = false;
				}
				window.clear();
				UI.drawTransiction(window, view, 3);
				window.display();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))kill9 = true;

			//---------- Solar System view ---------\\

			if (!isInPlanet) {
				window.setView(view);
				for (int i = 0; i < sys[0].planets.size(); i++) {
					if (sys[0].planets[i].out_view.getGlobalBounds().intersects(SalBus9000.spaceshipImage.getGlobalBounds())) {
						isInPlanet = true;
						currentPlanet = i;
						view.setCenter(windowx / 2, windowy / 2);
						SalBus9000.spaceshipImage.setPosition(Vector2f(300, 50));
						SalBus9000.vecAcc = Vector2f(0.f, 0.f);
					}
				}

				//boundaries sistema solare
				
				if (SalBus9000.spaceshipImage.getPosition().x > windowx || SalBus9000.spaceshipImage.getPosition().x < 0) {
					SalBus9000.vecAcc.x = -SalBus9000.vecAcc.x;
				}
				if (SalBus9000.spaceshipImage.getPosition().y > windowy || SalBus9000.spaceshipImage.getPosition().y < 0) {
					SalBus9000.vecAcc.y = -SalBus9000.vecAcc.y;
				}
				

				//funzioni per il controllo della navicella
				SalBus9000.controlSpaceship();


				window.clear();

				//draw stars
				window.draw(sys[0].stars);
				
				// draw planets
				for (int i = 0; i < sys[0].planets.size(); i++) {
					window.draw(sys[0].planets[i].out_view);
				}

				//u die if u ran out of fuel
				if (SalBus9000.fuel <= 0) {
					UI.game_over = true;
					UI.drawTransiction(window, view, 4);
				}
				
				//----------------- Planet view----------------\\

			}
			else if (isInPlanet) {

				if (SalBus9000.spaceshipImage.getPosition().y < -10) {
					isInPlanet = false;
					view.setCenter(windowx / 2, windowy / 2);
					SalBus9000.spaceshipImage.setPosition(sys[0].planets[currentPlanet].out_view.getPosition().x + sys[0].planets[currentPlanet].out_view.getRadius(), sys[0].planets[currentPlanet].out_view.getPosition().y - 50);
					SalBus9000.vecAcc = Vector2f(0.f, 0.f);
					SalBus9000.bullets.resize(0);
				}
				//se vuoi la gravità non commentare questa linea...
				//SalBus9000.vecAcc.y += 0.0002;

				//movimento camera
				if (SalBus9000.spaceshipImage.getPosition().x > view.getCenter().x + 100) {
					if (view.getCenter().x < (sys[0].planets[currentPlanet].Vertex_n * 100) - (windowx / 2)) {
						view.move(Vector2f(SalBus9000.vecAcc.x, 0));
					}
				}
				else if (SalBus9000.spaceshipImage.getPosition().x < view.getCenter().x - 100) {
					if (view.getCenter().x > windowx / 2) {
						view.move(Vector2f(SalBus9000.vecAcc.x, 0));
					}
				}

				

				//boundaries pianeta
				if (SalBus9000.spaceshipImage.getPosition().x < 0 || SalBus9000.spaceshipImage.getPosition().x > sys[0].planets[currentPlanet].Vertex_n * 100) {
					SalBus9000.vecAcc.x = -SalBus9000.vecAcc.x;
				}

				window.setView(view);

				//if collider
				
				//collider bullet navicella con bunker
				for (int i = 0; i < SalBus9000.bullets.size(); i++) {
					for (int j = 0; j < sys[0].planets[currentPlanet].bunkers.size(); j++) {
						if (SalBus9000.bullets[i].bulletImage.getGlobalBounds().intersects(sys[0].planets[currentPlanet].bunkers[j].bunker_shape.getGlobalBounds())) {
							//animation 
							position = Vector2f(sys[0].planets[currentPlanet].bunkers[j].bunker_shape.getPosition());
							animation = true;
							counter = 0;
							sys[0].planets[currentPlanet].bunkers.erase(sys[0].planets[currentPlanet].bunkers.begin() + j);
							UI.Score += 50;
							SalBus9000.bullets.erase(SalBus9000.bullets.begin() + i);
						}
					}
				}

				

				//collider bullets navicella con terreno pianeta
				for (int j = 0; j < (sys[0].planets[currentPlanet].Vertex_n - 1); j++) {
					for (int i = 0; i < SalBus9000.bullets.size(); i++) {
						if (sys[0].planets[currentPlanet].Collision(SalBus9000.bullets[i].bulletImage.getPosition(), sys[0].planets[currentPlanet].terrain[j].position, sys[0].planets[currentPlanet].terrain[j + 1].position))
						{
							SalBus9000.bullets.erase(SalBus9000.bullets.begin() + i);
						}
					}
				}

				//collider navicella con terreno
				if (!SalBus9000.godmode) {
					for (int j = 0; j < (sys[0].planets[currentPlanet].Vertex_n - 1); j++) {
						if (sys[0].planets[currentPlanet].Collision(SalBus9000.spaceshipImage.getPosition(), sys[0].planets[currentPlanet].terrain[j].position, sys[0].planets[currentPlanet].terrain[j + 1].position)) {
							view.setCenter(windowx / 2, windowy / 2);
							SalBus9000.spaceshipImage.setPosition(Vector2f(310, 50));
							SalBus9000.vecAcc = Vector2f(0.f, 0.f);
								UI.Lives--;
						}
					}

					//collider navicella con bullet bunker
					for (int i = 0; i < sys[0].planets[currentPlanet].bunkers.size(); i++) {
						for (int j = 0; j < sys[0].planets[currentPlanet].bunkers[i].bullets.size(); j++) {
							if (sys[0].planets[currentPlanet].bunkers[i].bullets[j].bulletImage.getGlobalBounds().intersects(SalBus9000.spaceshipImage.getGlobalBounds())) {
								view.setCenter(windowx / 2, windowy / 2);
								SalBus9000.spaceshipImage.setPosition(Vector2f(windowx / 2, 50));
								SalBus9000.vecAcc = Vector2f(0.f, 0.f);
								UI.Lives--;
							}
						}
					}
				}

				//collider bullet bunker con il terreno
				for (int i = 0; i < sys[0].planets[currentPlanet].bunkers.size(); i++) {
					for (int j = 0; j < sys[0].planets[currentPlanet].bunkers[i].bullets.size(); j++) {
						for (int t = 0; t < sys[0].planets[currentPlanet].Vertex_n - 2; t++) {
							if (sys[0].planets[currentPlanet].Collision(sys[0].planets[currentPlanet].bunkers[i].bullets[j].bulletImage.getPosition(), sys[0].planets[currentPlanet].terrain[t].position, sys[0].planets[currentPlanet].terrain[t + 1].position)) {
								sys[0].planets[currentPlanet].bunkers[i].bullets.erase(sys[0].planets[currentPlanet].bunkers[i].bullets.begin() + j);
							}
						}
					}
				}
			


				//collider per prendere il fuel
				if (SalBus9000.fuelGrabber) {
					for (int i = 0; i < sys[0].planets[currentPlanet].fuels.size(); i++) {
						if (SalBus9000.fuelRay.getBounds().intersects(sys[0].planets[currentPlanet].fuels[i].fuel_shape.getGlobalBounds())) {
							SalBus9000.fuelUp(sys[0].planets[currentPlanet].fuels[i].fuel_type);
							sys[0].planets[currentPlanet].fuels.erase(sys[0].planets[currentPlanet].fuels.begin() + i);
						}
					}
					//collider forcefield per i proiettili dei bunker
					for (int i = 0; i < sys[0].planets[currentPlanet].bunkers.size(); i++) {
						for (int j = 0; j < sys[0].planets[currentPlanet].bunkers[i].bullets.size(); j++) {
							if (SalBus9000.forceField.getGlobalBounds().intersects(sys[0].planets[currentPlanet].bunkers[i].bullets[j].bulletImage.getGlobalBounds())) {
								sys[0].planets[currentPlanet].bunkers[i].bullets.erase(sys[0].planets[currentPlanet].bunkers[i].bullets.begin() + j);
							}
						}
					}
				}
				//funzioni per il controllo della navicella
				SalBus9000.controlSpaceship();
				SalBus9000.controlFuelRay();
				SalBus9000.shooting(windowy);

				//bunker fire solo se sono a una certa distaza dalla navicella
				for (int i = 0; i < sys[0].planets[currentPlanet].bunkers.size(); i++) {
					if (abs(SalBus9000.spaceshipImage.getPosition().x - sys[0].planets[currentPlanet].bunkers[i].bunker_shape.getPosition().x) < 800) {
						sys[0].planets[currentPlanet].bunkers[i].bunker_Fire(windowy);
					}
				}

				window.clear();

				//draw stars
				window.draw(sys[0].stars);
				//when u die
				UI.drawTransiction(window, view, 2);

				//draw proiettili pianeta
				for (int i = 0; i < SalBus9000.bullets.size(); i++) {
					window.draw(SalBus9000.bullets[i].bulletImage);
				}
				
				//draw fuel ray
				if (SalBus9000.fuelGrabber) {
					window.draw(SalBus9000.fuelRay);
					window.draw(SalBus9000.forceField);
				}

				//draw terreno del pianeta
				window.draw(sys[0].planets[currentPlanet].terrain);

				//draw proiettili dei bunker
				for (int i = 0; i < sys[0].planets[currentPlanet].bunkers.size(); i++) {
					for (int j = 0; j < sys[0].planets[currentPlanet].bunkers[i].bullets.size(); j++) {
						window.draw(sys[0].planets[currentPlanet].bunkers[i].bullets[j].bulletImage);
					}
				}
				//draw bunkers
				for (int i = 0; i < (sys[0].planets[currentPlanet].bunkers.size()); i++) {

					if (!sys[0].planets[currentPlanet].bunkers[i].is_destroyed) {
						window.draw(sys[0].planets[currentPlanet].bunkers[i].bunker_shape);
					}

				}
				//draw fuels
				for (int i = 0; i < sys[0].planets[currentPlanet].fuels.size(); i++) {
					window.draw(sys[0].planets[currentPlanet].fuels[i].fuel_shape);
				}

				if (animation) {
					sys[0].planets[currentPlanet].Explode(window, position, counter);
					counter++;
					if (counter >= 120) {
						animation = false;
					}
				}

				//u die if u ran out of fuel
				if (SalBus9000.fuel <= 0) {
					UI.game_over = true;
					UI.drawTransiction(window, view, 4);
				}

				//ditruzione pianeta
				if (sys[0].planets[currentPlanet].bunkers.size() == 0) {
					UI.drawTransiction(window, view, 0);
					UI.Score += 500;
					isInPlanet = false;
					SalBus9000.spaceshipImage.setPosition(sys[0].planets[currentPlanet].out_view.getPosition().x + sys[0].planets[currentPlanet].out_view.getRadius(), sys[0].planets[currentPlanet].out_view.getPosition().y - 50);
					sys[0].planets.erase(sys[0].planets.begin() + currentPlanet);
					view.setCenter(windowx / 2, windowy / 2);
					SalBus9000.vecAcc = Vector2f(0.f, 0.f);
					SalBus9000.bullets.resize(0);

					//prossimo sistema solare
					if (sys[0].planets.size() == 0) {
						UI.drawTransiction(window, view, 1);
						sys.erase(sys.begin());
						Solar_System sas;
						sys.push_back(sas);
						SalBus9000.spaceshipImage.setPosition(50, 50);
					}
				}


				
				//window.display();

			}

			//draw spaceship thrust
			if (SalBus9000.playerUp) {
				if (thrust) {
					window.draw(SalBus9000.thrust);
					thrust = false;
				}
				else {
					window.draw(SalBus9000.thrust2);
					thrust = true;
				}
			}
			//draw spaceship
			window.draw(SalBus9000.spaceshipImage);
			window.draw(SalBus9000.vertexImage);


			//draw UI
			UI.drawUi(window, view, SalBus9000.fuel, windowx);

			window.display();
		}
	}
	return 0;
}
