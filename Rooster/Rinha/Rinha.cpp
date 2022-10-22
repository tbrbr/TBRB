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

#include <fstream>

#define FRAMERATE_LIMIT 60

#define println(x) (std::cout << x << std::endl)

using namespace std;
using namespace sf;

const int SCREEN_WIDTH = VideoMode::getDesktopMode().width;
const int SCREEN_HEIGHT = VideoMode::getDesktopMode().height;

bool keyboardState[sf::Keyboard::KeyCount][3];


#include "Patinho/Patinho.h"
#include "Patinho/jogoDoPatinho.h"
#include "TilesDoArrocha.h"


#include "Math2.h"

//#include "jogador_de_video.h"
#include "entradas.h"
#include "Elementos.h"
#include "Galo.h"
#include "GaloSniper.h"
#include "galoKalsa.h"
#include "GaloBruxo.h"

using namespace Rooster;

#include "Briga.h"
#include "fregues.h"
#include "cardapio.h"

int main() {


	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		keyboardState[i][0] = false;
		keyboardState[i][1] = false;
		keyboardState[i][2] = false;
	}
	
	int option = 2;

	try {
		//connectToServer("192.169.0.0", 59000);
	}
	catch (const char* e) {
		cout << e << endl;
	}
	
	RenderWindow* window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TBRB",Style::Fullscreen);

	window->clear(Color::Black);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(FRAMERATE_LIMIT);
	


	
	
	Galo *galo = new Sniper( 20, 20, 20, Rooster::state::STOPPED,true);
    Galo *galo2 = new Sniper(20, 20, 20, Rooster::state::STOPPED, false);

	Pato *miniGame1 = new Pato((*window));
	
	Texture mapa;
	RectangleShape fundo(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	mapa.loadFromFile("sprites/shopping.png");

	fundo.setPosition(0, 0);
	fundo.setTexture(&mapa);

	//socket.setBlocking(false);

	//fazendo um ponteiro pra menu pra dar free depois
	MenuPrincipal* menuprincipal = new MenuPrincipal();
	SelectionSinglePlayer* selector = new SelectionSinglePlayer();
	pianoYamaha piano;
	

	while (window->isOpen())
	{
		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
			bool keyState = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
			if (!keyboardState[i][0] && keyState) {
				keyboardState[i][1] = true;
			}
			else {
				keyboardState[i][1] = false;
			}

			if (keyboardState[i][0] && !keyState) {
				keyboardState[i][2] = true;
			}
			else {
				keyboardState[i][2] = false;
			}

			keyboardState[i][0] = keyState;

		}
	
		//piano.draw(*window);
		
		switch (option)
		{
		case UMJOGADORES:
			singlePlayer(window,*galo,*galo2,option,fundo);
			break;
		case MENU_PRINCIPAL:
			menuprincipal->ShowMenu(window,option);
			break;
		case ISPATOTIME:
			miniGame1->patinho(*window, option);
			break;
		case SELECTION:
			selector->show(window,option,galo,galo2);
			break;
		default:
			break;
		}
		
		
	}
	return 0;
}
