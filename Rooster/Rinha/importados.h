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

// Versao Exemplo:  1.102356
#define GAMEVERSION 1.100043

#define FRAMERATE_LIMIT 60
#pragma warning(disable : 4996)
#define println(x) (std::cout << x << std::endl)

using namespace std;
using namespace sf;

//const int SCREEN_WIDTH =  VideoMode::getDesktopMode().width;
//const int SCREEN_HEIGHT = VideoMode::getDesktopMode().height;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

#define SHOWDEBUG false
#define GODMODE false


#include "GlobalInfo.h"


Font basicFont;

#include "varios_idiomas.h"
#include "efeitos_fodas.h"

#include "Math2.h"
#include "MathSfml.h"

#include "entradas.h"

Rooster::input mainInput;

#include "GUI.h";

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


using namespace Rooster;

#include "Mapeamento2.h"
#include "Shop.h"
#include "pause_menu.h"// pq eu ja esperava isso?kkkkkkkkkkkkkkkkkkkkkk perai rapid�o, vou mudar um neg�cio aq no codigo
#include "brain.h"
#include "Briga.h"
#include "muitosjogadores.h"
#include "server_connect.h"
#include "cardapio.h"
#include "menu_inicial.h"
#include "selecao_de_mapa_falida.h"
#include "versus.h"



#endif