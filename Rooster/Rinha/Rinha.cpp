#include <iostream>

#define SFML_STATIC




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

#define ISMOTADESKTOP 0

#if  ISMOTADESKTOP
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;
#else
const int SCREEN_WIDTH = VideoMode::getDesktopMode().width;
const int SCREEN_HEIGHT = VideoMode::getDesktopMode().height;
#endif

#define SHOWDEBUG false

#include "varios_idiomas.h"
#include "efeitos_fodas.h"


#include "Math2.h"
#include "entradas.h"

Rooster::input mainInput;

LANGUAGE LANG;


#include "Sangue.h"
Rooster::ParticleSystem mainPartSystem;

#include "fregues.h"
#include "introducoes.h"
#include "checador_de_posicao.h"

#include "Elementos.h"
#include "Galo.h"
#include "GaloSniper.h"
#include "galoKalsa.h"
#include "GaloBruxo.h"
#include "galoPeste.h"
#include "galoBota.h"

#include "Patinho/Patinho.h"
#include "Patinho/jogoDoPatinho.h"
#include "TilesDoArrocha.h"




//#include "jogador_de_video.h"





#include "entradas.h"

using namespace Rooster;

#include "Briga.h"
#include "muitosjogadores.h"

#include "cardapio.h"
#include "menu_inicial.h"
#include "selecao_de_mapa_falida.h"


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


	int option = MENU_PRINCIPAL;
	option = BOTAPRAARROCHAR;
	
	
	
	RenderWindow* window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TBRB",Style::Fullscreen);

	window->clear(Color::Black);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(FRAMERATE_LIMIT);
	window->setMouseCursorGrabbed(true);


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
	Galo* galo2 = new Sniper(sniperSt, Rooster::state::STOPPED, true);

	println("Carregarou");


	Pato *miniGame1 = new Pato((*window));

	RectangleShape fundo;
	fundo.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	SelectionSinglePlayer* selector = new SelectionSinglePlayer();
	MapSelector* mapSelector = new MapSelector();

	window->setMouseCursorVisible(true);
	window->setMouseCursorGrabbed(false);

	while (window->isOpen())
	{
		
		switch (option)
		{
		case UMJOGADORES:
			if (!galo) {
				return 1;
			}

			fundo.setTexture(mapSelector->getSelectedMap());

			println("singleplay");

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
			multiPlayer(window, *galo, galo2, option, fundo);
			break;
		case MAPA_FALIDO_E_ACHE_RUIM_WALTER:
			mapSelector->draw(window, option, true);
			break;
		default:
			break;
		}
		
		
		
	}
	return 0;
}
