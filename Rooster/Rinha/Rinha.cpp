
#include <iostream>
#define SFML_STATIC

#include <opencv2/core/core.hpp>

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <SFML/Network.hpp>
#include <vector>
#include <cmath>


using namespace std;
using namespace sf;

#define FRAMERATE_LIMIT 60
#define G 9.81
#define PI 3.1415926563

const int SCREEN_WIDTH = VideoMode::getDesktopMode().width;
const int SCREEN_HEIGHT = VideoMode::getDesktopMode().height;

#include "jogador_de_video.h"
#include "entradas.h"
#include "Elementos.h"
#include "Galo.h"
#include "GaloSniper.h"
using namespace Rooster;
#include "Briga.h"
#include "fregues.h"
#include "cardapio.h"





int main() {

	//Enter go out of the video
	//playVideo("intro.mp4");
	
	int option = 2;

	try {
		//connectToServer("192.169.0.0", 59000);
	}
	catch (const char* e) {
		cout << e << endl;
	}
	
	RenderWindow* window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TBRB",Style::Fullscreen);
	window->setFramerateLimit(FRAMERATE_LIMIT);



	Rooster::HitBox hb;
	Texture t;
	t.loadFromFile("sprites/galoSniper.png");

	Sniper galo = Sniper(hb, 20, 20, 20, Rooster::state::STOPPED, t,true);
	Sniper galo2 = Sniper(hb, 20, 20, 20, Rooster::state::STOPPED, t,false);

	Texture mapa;
	RectangleShape fundo(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	mapa.loadFromFile("sprites/shopping.png");

	fundo.setPosition(0, 0);
	fundo.setTexture(&mapa);

	//socket.setBlocking(false);

	while (window->isOpen())
	{
		
		switch (option)
		{
		case UMJOGADORES:
			singlePlayer(window,galo,galo2,option,fundo);
			break;
		case MENU_PRINCIPAL:
			menuPrincipal(window,option);
			break;
		default:
			break;
		}

		
	}
	return 0;
}
