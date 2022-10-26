#include <iostream>

#define SFML_STATIC

#include "varios_idiomas.h"
#include "efeitos_fodas.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <SFML/Network.hpp>
#include <vector>
#include <random>
#include <cmath>

#include <fstream>

#define FRAMERATE_LIMIT 60
#pragma warning(disable : 4996)
#define println(x) (std::cout << x << std::endl)

using namespace std;
using namespace sf;


const int SCREEN_WIDTH = VideoMode::getDesktopMode().width;
const int SCREEN_HEIGHT = VideoMode::getDesktopMode().height;

bool keyboardState[sf::Keyboard::KeyCount][3];

LANGUAGE LANG;

#include "fregues.h"
#include "introducoes.h"
#include "checador_de_posicao.h"

#include "Patinho/Patinho.h"
#include "Patinho/jogoDoPatinho.h"
#include "TilesDoArrocha.h"


#include "Math2.h"

//#include "jogador_de_video.h"


#include "Sangue.h"
Rooster::ParticleSystem mainPartSystem;


#include "entradas.h"
#include "Elementos.h"
#include "Galo.h"
#include "GaloSniper.h"
#include "galoKalsa.h"
#include "GaloBruxo.h"
#include "galoPeste.h"
using namespace Rooster;

#include "Briga.h"
#include "muitosjogadores.h"

#include "cardapio.h"
#include "menu_inicial.h"


int main() {

	LANGUAGE::Lang lang = LANGUAGE::ENGLISH;
	{
		FILE* file = fopen("lang/start_lang.ini", "r");
		if (file != NULL) {
			if(fscanf(file, "%d", (int *) & lang))
				fclose(file);
		}
	}

	LANG.startAllTexts(lang);

	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		keyboardState[i][0] = false;
		keyboardState[i][1] = false;
		keyboardState[i][2] = false;
	}
	
	int option = INTRO;

	
	RenderWindow* window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TBRB",Style::Fullscreen);

	window->clear(Color::Black);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(FRAMERATE_LIMIT);
	window->setMouseCursorGrabbed(false);
	Cursor cursor;
	Image c;
	c.loadFromFile("sprites/cursor_teste.png");

	cursor.loadFromPixels(c.getPixelsPtr(), Vector2u(c.getSize().x, c.getSize().y), Vector2u(0, 0));
	window->setMouseCursor(cursor);

	struct GaloStats sniperSt;
	struct GaloStats kalsaSt;
	struct GaloStats bruxoSt;

	sniperSt = { 100, 10, 10, 10, 5 };
	kalsaSt = { 100, 10, 10, 10, 5 };
	bruxoSt = { 60, 10, 10, 10, 5 };

	Galo* galo = new Sniper(sniperSt, Rooster::state::STOPPED, true);
	Galo* galo2 = NULL;


	Pato *miniGame1 = new Pato((*window));
	
	Texture mapa;
	RectangleShape fundo(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	mapa.loadFromFile("sprites/ceasa.png");

	fundo.setPosition(0, 0);
	fundo.setTexture(&mapa);

	//socket.setBlocking(false);

	SelectionSinglePlayer* selector = new SelectionSinglePlayer();
	

	

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
	
		cout << IpAddress::getLocalAddress();
		
		switch (option)
		{
		case UMJOGADORES:
			if (!galo) {
				return 1;
			}
			singlePlayer(window,*galo,*galo2,option,fundo);
			break;
		case MENU_PRINCIPAL:
			option = MenuPrincipal(window);
			break;
		case ISPATOTIME:
			miniGame1->patinho(*window, option);
			break;
		case SELECTION:
			selector->show(window,option,&galo,&galo2);
			break;
		case INTRO: {
			option = introducao(window);

			break;
		}
		case BOTAPRAARROCHAR:
			pianoTiles(window);
			break;
		case DOISJODADOR:
			if (!galo) {
				return 1;
			}
			multiPlayer(window, *galo, &galo2, option, fundo);
			break;
			
		default:
			break;
		}
		
		
		
	}
	return 0;
}
