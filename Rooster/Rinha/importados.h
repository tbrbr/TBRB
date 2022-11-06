#ifndef VITOR_IMPORTS
#define VITOR_IMPORTS

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

#define porfavorseformexernissodeixe0depoisissotravameupctodosejaeducadoprasersinceroissoeumpedidodesocorroeudesistodetrabalharcommota 1

//va se arrombar nao
#if  porfavorseformexernissodeixe0depoisissotravameupctodosejaeducadoprasersinceroissoeumpedidodesocorroeudesistodetrabalharcommota
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

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



#include "entradas.h"

using namespace Rooster;

#include "pause_menu.h"
#include "Briga.h"
#include "muitosjogadores.h"
#include "server_connect.h"
#include "cardapio.h"
#include "menu_inicial.h"
#include "selecao_de_mapa_falida.h"

#endif