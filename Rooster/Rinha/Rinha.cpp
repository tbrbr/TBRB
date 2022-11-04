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

#define VA_SE_FODER_WALTER_ARROMBADO_FDP_URUBU_AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA 1
//va se arrombar nao
#if  VA_SE_FODER_WALTER_ARROMBADO_FDP_URUBU_AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
#else
const int SCREEN_WIDTH = VideoMode::getDesktopMode().width;
const int SCREEN_HEIGHT = VideoMode::getDesktopMode().height;
#endif

#define SHOWDEBUG true

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
#include "server_connect.h"
#include "cardapio.h"
#include "menu_inicial.h"
#include "selecao_de_mapa_falida.h"


int main() {

	/*
	cout << IpAddress::getLocalAddress();
>>>>>>> d3cbbbba0f164096bb2fcd72d6e8adf79221dd15
	cout << "Server?";
	cin >> ishost;
	*/
	//mota va tomar no seu cu por favor.
	LANGUAGE::Lang lang = LANGUAGE::ENGLISH;
	{
		FILE* file = fopen("lang/start_lang.ini", "r");
		if (file != NULL) {
			if(fscanf(file, "%d", (int *) & lang))
				fclose(file);
		}
	}

	LANG.startAllTexts(lang);




	int option = MULTI_MODE;
	
	
#if 1
	RenderWindow* window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TBRB",Style::Default);
#else
	RenderWindow* window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TBRB", Style::Fullscreen);
#endif

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
	struct GaloStats pesteSt;
	struct GaloStats botaSt;

	sniperSt = { 100, 10, 15, 9, 5 , 15 };
	kalsaSt = { 100, 12, 12, 10, 6 , 20 };
	bruxoSt = { 60, 15, 12, 9, 5   , 20 };
	pesteSt = { 120, 12, 10, 11, 6 , 12 };
	botaSt = { 80, 13, 10, 12, 4   , 20 };


	Galo* galo = NULL;
	Galo* galo2 = NULL;


	Pato *miniGame1 = new Pato((*window));

	RectangleShape fundo;

	fundo.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	SelectionSinglePlayer* selector = new SelectionSinglePlayer();


	MapSelector* mapSelector = new MapSelector();
	Texture background_t;
	RectangleShape background(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	background.setPosition(0, 0);
	background_t.loadFromFile("sprites/background_menu.png");
	background.setTexture(&background_t);


	fundo.setTexture(mapSelector->getTexture());

	window->setMouseCursorVisible(true);
	window->setMouseCursorGrabbed(false);

	TcpSocket* socket = new TcpSocket();
	TcpListener* listener = new TcpListener();

	while (window->isOpen())
	{
		
		switch (option)
		{
		case UMJOGADORES:
			if (!galo) {
				return 1;
			}

			fundo.setTexture(mapSelector->getSelectedMap());

			singlePlayer(window,*galo,*galo2,option,fundo);
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
		
			multiPlayer(window, *galo, *galo2, option, fundo, socket);
			option = MULTI_MODE;
			break;
		case MAPA_FALIDO_E_ACHE_RUIM_WALTER:
			mapSelector->draw(window, option, true);
			break;
		case JOIN:
			option = join(window, background, socket);
			break;

		case CREATE:
			option = create(window, background, socket, listener);
			break;

		case MULTI: 
			option = muitoJogadores(window, background);
			break;
		case MULTI_MODE:
			option = multoJogadoresMode(window, background);
			break;

		case MENU_PRINCIPAL:
			option = MenuPrincipal(window, background);
			break;

		case GAMEMODE:
			option = selecionarModo(window, background);
			break;
		case CONFIG:
			option = configScreen(window, background);
			break;

		case MINIGAME:
			option = minigame(window, background);
			break;
		case MULTI_SELECT:
			option = selector->show(window, &galo, &galo2, socket);
		default:
			break;
		}
		
		
		
	}
	return 0;
}
