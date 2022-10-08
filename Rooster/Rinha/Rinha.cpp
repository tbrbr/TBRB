
#include <iostream>
#define SFML_STATIC

#include <opencv2/core/core.hpp>
#include "jogador_de_video.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <cmath>


using namespace std;
using namespace sf;

#define FRAMERATE_LIMIT 60
#define G 9.81
#define PI 3.1415926563

#include "entradas.h"
#include "Elementos.h"
#include "Galo.h"
#include "GaloSniper.h"
#include "fregues.h"

using namespace Rooster;




void _inline singlePlayer(RenderWindow * window, Event& e, Galo& galo,int &option) {


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		galo.setState(Rooster::state::RUNNING);
		galo.facingRight = true;
		galo.animRun();

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		galo.setState(Rooster::state::RUNNING);
		galo.facingRight = false;
		galo.animRun();

	}
	else
	{
		galo.setState(Rooster::state::STOPPED);
		galo.setHspeed(0);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		galo.animJump();
	}

	galo.update();

	window->clear();
	RectangleShape fundo(Vector2f(1280, 720));
	fundo.setPosition(0, 0);
	fundo.setFillColor(Color(100, 100, 100));

	window->draw(fundo);
	galo.show(*window);
	window->display();

}


int main() {

	//Enter sai do video
	playVideo("intro.mp4");
	
	int option = 0;

	try {
		connectToServer("192.169.0.0", 59000);
	}
	catch (const char* e) {
		cout << e << endl;
	}

	RenderWindow* window = new RenderWindow(VideoMode(1280, 720), "TBRB");
	window->setFramerateLimit(FRAMERATE_LIMIT);

	Rooster::HitBox hb;
	Texture t;
	t.loadFromFile("sprites/galoSniper.png");


	Sniper galo = Sniper(hb, 20, 20, 20, Rooster::state::STOPPED, t);
	Sniper galo2 = Sniper(hb, 20, 20, 20, Rooster::state::STOPPED, t);

	socket.setBlocking(false);

	while (window->isOpen())
	{
		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window->close();
			}
		}
		switch (option)
		{
		case UMJOGADORES:
			singlePlayer(window, e, galo, option);

		default:
			break;
		}
		window->setPosition(Vector2i(20, 20));
		
	}
	return 0;
}
