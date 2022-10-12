#include <iostream>

#define SFML_STATIC

#include <opencv2/core/core.hpp>
#include "efeitos_fodas.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <SFML/Network.hpp>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

const int SCREEN_WIDTH = VideoMode::getDesktopMode().width;
const int SCREEN_HEIGHT = VideoMode::getDesktopMode().height;

#include "Patinho/Patinho.h"
#include "Patinho/jogoDoPatinho.h"
#include "TilesDoArrocha.h"

#define FRAMERATE_LIMIT 60
#define G 9.81
#define PI 3.1415926563

//#include "jogador_de_video.h"
#include "entradas.h"
#include "Elementos.h"
#include "Galo.h"
#include "GaloSniper.h"

using namespace Rooster;

#include "Briga.h"
#include "fregues.h"
#include "cardapio.h"

int main() {
	
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

	Pato *miniGame1 = new Pato((*window));

	Texture mapa;
	RectangleShape fundo(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	mapa.loadFromFile("sprites/shopping.png");

	fundo.setPosition(0, 0);
	fundo.setTexture(&mapa);

	//socket.setBlocking(false);

	/*fazendo um ponteiro pra menu pra dar free depois*/
	MenuPrincipal* menuprincipal = new MenuPrincipal();

	pianoYamaha piano;


	while (window->isOpen())
	{

		//piano.draw(*window);

		
		switch (option)
		{
		case UMJOGADORES:
			singlePlayer(window,galo,galo2,option,fundo);
			break;
		case MENU_PRINCIPAL:
			menuprincipal->ShowMenu(window,option);
			break;
		case ISPATOTIME:
			miniGame1->patinho(*window);

		default:
			break;
		}
	}
	return 0;
}
