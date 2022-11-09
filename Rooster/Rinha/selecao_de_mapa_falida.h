#ifndef RECLAME_MAIS_DESSA_SELECAO_WALTER_CORNO
#define RECLAME_MAIS_DESSA_SELECAO_WALTER_CORNO

#include "versus.h"

struct Mapa {

	string nome;
	string file;
	string finalfile;

};

void updateCircle(CircleShape * circles, RenderWindow * window) {

	for (int i = 0; i < 4; i++)
	{
		circles[i].setRadius(window->getSize().y / 50);
		circles[i].setFillColor(Color::Red);
		circles[i].setOutlineColor(Color::Transparent);
	}

	circles[0].setPosition(window->getSize().x * 0.16, window->getSize().y * 0.2380);
	circles[1].setPosition(window->getSize().x * 0.26, window->getSize().y * 0.253);
	circles[2].setPosition(window->getSize().x * 0.345, window->getSize().y * 0.33);
	circles[3].setPosition(window->getSize().x * 0.235, window->getSize().y * 0.49);


	circles[0].setOutlineThickness(circles[0].getRadius() * 3);
	circles[1].setOutlineThickness(circles[1].getRadius() * 3);
	circles[2].setOutlineThickness(circles[2].getRadius() * 2.8);
	circles[3].setOutlineThickness(circles[3].getRadius() * 3.3);

}

void updateDescricao(Text * descricao, int mapa) {
	string a;
	if (mapa == 0) {
		a = "Não tinha medo o tal João de Santo Cristo\nEra o que todos diziam quando ele se perdeu\nDeixou pra trás todo o marasmo da fazenda\nSó pra sentir no seu sangue o ódio que Jesus lhe deu\nQuando criança só pensava em ser bandido\nAinda mais quando com um tiro de soldado o pai morreu\nEra o terror da sertania onde morava\nE na escola até o professor com ele aprendeu\nIa pra igreja só pra roubar o dinheiro\nQue as velhinhas colocavam na caixinha do altar\nSentia mesmo que era mesmo diferente\nSentia que aquilo ali não era o seu lugar\n.............";
	}
	else if (mapa == 1) {
		a = "Inaugurado em 08 de junho de 2017, o Shopping\nPeixoto já é o maior centro de compras e lazer\nda região, com uma ABL(Área Bruta Locável) de \n16 mil metros quadrados, ocupando um espaço de\nárea construída de 23.800 mil metros quadrados.\n" 	"São 76 lojas em operação, sendo 04 lojas âncora,\nentre elas : Le Biscuit e Americanas, 04 megalojas\n,01 supermercado, ampla praça de alimentação, 04 salas\nde cinema com capacidade para centenas de pessoas,\ncerca de 900 vagas de estacionamento gratuitas,\nincluindo vagas para vans e ônibus de turismo.";
	}
	else if (mapa == 2) {
		a = "Descendo a serra Jogando uma bola\nCom alma e paixão Três cores na faixa\nAlegria do povo É o seu campeão\nEm casa ou distante O ardor é o mesmo\nNo campo de ação Na vitória ou derrota\nA disputa com luta E o abraço do irmão\nSomos Itabaiana Cidade celeiro\nQue vibra no esporte Com o seu Tremendão\n";
	}
	else {
		a = "O Ceasa de Salvador é um local super agradável\ncom variedade de lojinhas seja de artesanato,\nhortifruti, cereais, bebidas ou frutos do mar.\nPossui praça de alimentação, com variedades,\nvocê encontrará algumas no estilo lanchonete e\n o outras mais restaurantes, no meio da Praça\ntem espaço para apresentação de voz e violão.\nTem espaço infantil, estacionamento, lojinha de picolés.\nAgrada desde ao público local, como os turistas.\n";
	}
	descricao->setString(a);
}

Texture* selecionarMapa(RenderWindow * window) {

	escurecer(*window);
	Texture mapas[5];
	
	for (int i = 0; i < 5; i++) {
		mapas[i].loadFromFile("maps/" + std::to_string(i) + ".png");
	}
	RectangleShape NORDESTE;
	NORDESTE.setTexture(mapas);
	NORDESTE.setSize(Vector2f(window->getSize().x * 0.3, window->getSize().y * 0.6));
	NORDESTE.setPosition(window->getSize().x * 0.10, window->getSize().y * 0.12);


	RectangleShape Map;
	Map.setFillColor(Color::Transparent);


	CircleShape circles[4];
	CircleShape __circles[4];
	updateCircle(circles, window);
	for (int i = 0; i < 4; i++) {
		__circles[i].setRadius(circles[i].getRadius() + circles[i].getOutlineThickness());
		__circles[i].setPosition(circles[i].getPosition().x - circles[i].getOutlineThickness(), circles[i].getPosition().y - circles[i].getOutlineThickness());
	}

	Mapa maps[4];
	maps[0].nome = "Faroeste";
	maps[1].nome = "Shopping";
	maps[2].nome = "Itabaiana";
	maps[3].nome = "Ceasa";

	maps[0].finalfile = "maps/cenario faroeste.png";
	maps[1].finalfile = "maps/shopping.png";
	maps[2].finalfile = "maps/itabaiana.png";
	maps[3].finalfile = "maps/ceasa.png";

	maps[0].file = "maps/cenario faroeste name.png";
	maps[1].file = "maps/shopping name.png";
	maps[2].file = "maps/itabaiana name.png";
	maps[3].file = "maps/ceasa name.png";

	Texture textures[4];
	for (int i = 0; i < 4; i++) {
		textures[i].loadFromFile(maps[i].file);
	}

	Map.setSize(Vector2f(window->getSize().x * 0.35, window->getSize().y * 0.35));
	Map.setPosition(window->getSize().x * 0.55, window->getSize().y * 0.15);
	Map.setOutlineColor(Color::Red);
	Map.setOutlineThickness(2);

	Text descricao;
	Font arial;
	arial.loadFromFile("fonts/ARIAL.TTF");
	descricao.setFont(arial);
	descricao.setCharacterSize(SCREEN_WIDTH / 60);
	descricao.setPosition(Map.getPosition().x, Map.getPosition().y + Map.getSize().y * 1.05);
	
	RectangleShape cancel;
	RectangleShape confirm;

	Vector2f buttonSize;
	Vector2f buttonPosition;
	buttonSize.x = window->getSize().x * 0.12;
	buttonSize.y = window->getSize().y * 0.07;

	buttonPosition.x = window->getSize().x * 0.1;
	buttonPosition.y = window->getSize().y * 0.8;

	cancel.setSize(buttonSize);
	confirm.setSize(buttonSize);

	confirm.setPosition(buttonPosition);
	cancel.setPosition(buttonPosition.x + buttonSize.x * 1.3, buttonPosition.y);

	confirm.setFillColor(Color::Black);
	cancel.setFillColor(Color::Black);
	
	confirm.setOutlineThickness(2);
	cancel.setOutlineThickness(2);

	confirm.setOutlineColor(Color::Red);
	cancel.setOutlineColor(Color::Red);

	int selectedMap = -1;

	while (window->isOpen())
	{
		Event e;

		while (window->pollEvent(e))
		{
			int mousex = Mouse::getPosition(*window).x;
			int mousey = Mouse::getPosition(*window).y;

			if (e.type == Event::Closed)
			{
				window->close();
			}
			

			if (e.type == Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == Mouse::Left) {

					int temp = -1;
					for (int i = 0; i < 4; i++) {
						if (ButtonCheck::checkCircleHover(__circles[i], mousex, mousey)) {
							temp = i;
						}
					}

					if (temp != -1) {
						temp++;
						Map.setTexture(&textures[temp - 1]);
						Map.setFillColor(Color::White);
						NORDESTE.setTexture(mapas + temp);
						updateDescricao(&descricao, temp - 1);
						selectedMap = temp - 1;
					}


					if (ButtonCheck::isButtonComMouseNele(confirm, mousex, mousey)) {
						if (selectedMap != -1) {
							Texture* t = new Texture();
							t->loadFromFile(maps[selectedMap].finalfile);
							return t;
						}

					}

					else if (ButtonCheck::isButtonComMouseNele(cancel, mousex, mousey)) {
						return NULL;
					}

				}


			}

			
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			
		}

		

		window->clear();
		window->draw(NORDESTE);
		for (int i = 0; i < 4; i++) {
			window->draw(circles[i]);
		}
		window->draw(descricao);
		window->draw(Map);
		window->draw(confirm);
		window->draw(cancel);
		window->display();

	}



}

#endif // !RECLAME_MAIS_DESSA_SELECAO_WALTER_CORNO
