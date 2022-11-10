
enum mode {
	SINGLE,
	LAN,
	LOCAL
};

int mode = SINGLE;

#include <functional>
#include "importados.h"


void menuSong(int * option, RenderWindow * window) {

	SoundBuffer buffer;
	buffer.loadFromFile("sounds\\freefires.ogg");
	Sound s(buffer);
	s.setLoop(true);

	bool play = false;


	while (window->isOpen()) {

		int a = *option;

		bool e = a == MENU_PRINCIPAL || a == GAMEMODE || a == MULTI_MODE || a == CONFIG || a == MULTI || a == MINIGAME;

		if (e && !play) {
			s.play();
			play = true;
		}
		else 
		{
			if (!e && play) {
				play = false;
				s.stop();
			}
		}
	}


}
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


	RenderWindow* window = new RenderWindow(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TBRB", SCREEN_WIDTH == 1280 ? Style::Default : Style::Fullscreen);

	// Carregando texturas pra particulas
	Rooster::partTextures.init();

	basicFont.loadFromFile("fonts/whitrabt.ttf");

	int option = MENU_PRINCIPAL;



	bool motaouhenrique = true;


	/* M�SICA: A MULHER QUANDO QUER NAMORAR
	* CANTOR: RAIMUNDO SOLDADO
	A MUI�, QUANDO ELA QUER NAMORAR
	ELA FICA ESQUENTANDO QUE NEM UM MOTOR DE PARTIDA
	E LOGO A GENTE TOCA NA CHAVE
	ELA FICA PEGUANDO A PRIMEIRA E A R�
	DA PRIMEIRA E A R� ELA VAI PARA A REDU��O
	VAI PARA A TERCEIRA E A QUARTA APAIXONADA
	E FICA ESQUENTANDO QUE NEM UM MOTOR DE PARTIDA
	E LOGO A GENTE TOCA NA CHAVE ELA FICA PEGANDO
	ELA FICA PEGANDO A PRIMEIRA E A R� APAIXONADA
	APAIXONADA COM O CORA��O BATENDO
	ELA FICA PEGANDO A PRIMEIRA E A R�
	DA PRIMEIRA E A R� ELA VAI PARA A REDU��O
	VAI PARA A TERCEIRA E A QUARTA APAIXONADA
	E FICA ESQUENTANDO QUE NEM UM MOTOR DE PARTIDA
	E LOGO A GENTE TOCA NA CHAVE ELA FICA PEGANDO
	ELA FICA PEGANDO A PRIMEIRA E A R� APAIXONADA
	APAIXONADA COM O CORA��O BATENDO
	COM OS OLHOS DERRAMADOS DE AMOR
	A MUIER, QUANDO ELA QUER NAMORAR
	ELA FICA ESQUENTANDO QUE NEM UM MOTOR DE PARTIDAM
	E LOGO A GENTE TOCA NA CHAVE
	ELA FICA PEGANDO A PRIMEIRA E A R�
	DA PRIMEIRA E A R� ELA VAI PARA A REDU��O
	VAI PARA A TERCEIRA E A QUARTA APAIXONADA
	E FICA ESQUENTANDO QUE NEM UM MOTOR
	QUE NEM UM MOTOR DE PARTIDA A TODO MOMENTO
	A TODO MOMENTO ELA FICA ESQUENTANO
	QUE NEM UM MOTOR DE PARTIDA
	E LOGO A GENTE TOCA NA CHAVE ELA FICA PEGANDO
	A PRIMEIRA E A R�
	A PRIMEIRA R� APAIXONADA
	COM O CORA��O BATENDO E OS OLHOS DERRAMANDO DE AMOR
	[MUSICA]
	OH...
	[POSSIVEL ERRO DO CANTOR]
	A MUIER, QUANDO ELA QUER NAMORAR
	ELA FICA ESQUENTANDO QUE NEM UM MOTOR DE PARTIDA
	E LOGO A GENTE TOCA NA CHAVE
	ELA FICA PEGANDO A PRIMEIRA E A R�
	DA PRIMEIRA E A R� ELA VAI PARA A REDU��O
	VAI PARA A TERCEIRA E A QUARTA APAIXONADA
	E FICA PEGANDO E ESQUENTANDO
	ESQUENTANDO QUE NEM UM MOTOR DE PARTIDA
	[MUSICA FINALIZANDO]
	*/

	window->clear(Color::Black);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(FRAMERATE_LIMIT);
	window->setMouseCursorGrabbed(true);
	Image icon;
	icon.loadFromFile("icons/galo5.png");
	window->setIcon(100, 100, icon.getPixelsPtr());


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

	Texture background_t;
	RectangleShape background(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	background.setPosition(0, 0);
	background_t.loadFromFile("sprites/background_menu.png");
	background.setTexture(&background_t);

	window->setMouseCursorVisible(true);
	window->setMouseCursorGrabbed(false);

	TcpSocket* socket = new TcpSocket();
	TcpListener* listener = new TcpListener();

	Texture* __mapa = NULL;
	sf::Thread t(std::bind(&menuSong, &option, window));
	t.launch();
	int __map = -1;
	while (window->isOpen())
	{
		switch (option)
		{

		case UMJOGADORES:
			singlePlayer(window,*galo,*galo2,option,fundo);
			delete galo;
			delete galo2;
			__mapa = NULL;

			selector->reset();
			break;
		case ISPATOTIME:
			miniGame1->patinho(*window, option);
			break;
		case SELECTION:
			
			selector->show(window,option,&galo,&galo2);
			break;
		case VERSUS:
			
			
			if (mode == SINGLE) {
				option = UMJOGADORES;
				versus(*window, *galo, *galo2, fundo, __map);
			}
			else if (mode == LAN) {

				if (isHost) {
					galo2->facingRight = false;
					galo->facingRight = true;
				}
				else {
					galo2->facingRight = true;
					galo->facingRight = false;
				}

				if (isHost)
					versus(*window, *galo, *galo2, fundo, __map);
				else
					versus(*window, *galo2, *galo, fundo, __map);

				option = DOISJODADOR;
			}
			else if (mode == LOCAL) {
				versus(*window, *galo, *galo2, fundo, __map);
				option = UMJOGADORES;
			}
			
			break;


		case INTRO: {
			option = introducao(window);
			break;
		}
		case BOTAPRAARROCHAR:
			pianoTiles(window);
			break;
		case DOISJODADOR:
			lan(window, *galo, *galo2, option, fundo, socket);
			selector->reset();
			option = MULTI_MODE;
			break;
		case MAPA_FALIDO_E_ACHE_RUIM_WALTER:
			
			if (mode == LAN) {
				__mapa = selecionarMapa(window, socket, __map);
			}
			else
				__mapa = selecionarMapa(window, __map);
			if (__mapa == NULL) {
				option = SELECTION;
			}
			else {
				fundo.setTexture(__mapa);
				option = VERSUS;
			}

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
