
class MenuPrincipal {

	int mousex = 0;
	int mousey = 0;

	int OptionMenuPrincipal = 0;
	int OptionMenuIniciar = 0;
	bool iniciar = false;

	
	Texture backgroundTexture;
	RectangleShape fundo;

	Font fontTitle;
	Text title;

	Font fontOption;
	Text option1;
	Text option2;
	Text option3;

	Texture garrinha;
	Sprite garra;

	RectangleShape borda;
	Text optionInit;
	Text optionInit2;
	Text optionInit3;



public: 
	MenuPrincipal() {

		/*background rooster*/
		backgroundTexture.loadFromFile("sprites/background_menu.png");
		fundo.setSize((Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT)));
		fundo.setTexture(&backgroundTexture);

		/*title*/
		fontTitle.loadFromFile("fonts/CloisterBlack.ttf");

		title.setFont(fontTitle);
		title.setString("Menu Principal");
		title.setCharacterSize(SCREEN_WIDTH / 16);
		title.setPosition(SCREEN_WIDTH / 1.4 - title.getGlobalBounds().width / 2, SCREEN_HEIGHT / 9);
		title.setFillColor(Color(205,0,0));

		/*options*/
		fontOption.loadFromFile("fonts/blops.ttf");
		option1.setFont(fontOption);
		option1.setString("Iniciar");
		option1.setCharacterSize(SCREEN_WIDTH / 48);
		option1.setPosition(SCREEN_WIDTH / 1.4 - option1.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2);
		option1.setFillColor(Color(193, 0, 0));


		option2.setFont(fontOption);
		option2.setString("Ajustes");
		option2.setCharacterSize(SCREEN_WIDTH / 48);
		option2.setPosition(SCREEN_WIDTH / 1.4 - option2.getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 + option1.getGlobalBounds().height * 2);

		option2.setFillColor(Color(193, 0, 0));


		option3.setFont(fontOption);
		option3.setString("sair do jogo");
		option3.setCharacterSize(SCREEN_WIDTH / 48);
		option3.setPosition(SCREEN_WIDTH / 1.4 - option3.getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 + option1.getGlobalBounds().height * 4);

		option3.setFillColor(Color(193, 0, 0));

		//garrinha

		garrinha.loadFromFile("sprites/garra_menu.png");

		garra.setTexture(garrinha);
		garra.setTextureRect(IntRect(0, 0, 420, 221));
		garra.setScale((float)SCREEN_WIDTH / 6400, (float)SCREEN_HEIGHT / 3600);

		borda.setSize(Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		borda.setPosition(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4);
		borda.setFillColor(Color::Black);
		borda.setOutlineThickness(SCREEN_WIDTH / 200);
		borda.setOutlineColor(Color(193, 0, 0));

		optionInit.setFont(fontOption);
		optionInit.setString("Multiplayer");
		optionInit.setCharacterSize(SCREEN_WIDTH / 48);
		optionInit.setPosition(
			SCREEN_WIDTH / 2 - optionInit.getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + option1.getGlobalBounds().height
		);
		optionInit.setFillColor(Color(193, 0, 0));

		int spaceYBetween = optionInit.getGlobalBounds().height;

		optionInit2;
		optionInit2.setFont(fontOption);
		optionInit2.setString("Singleplayer");
		optionInit2.setCharacterSize(SCREEN_WIDTH / 48);
		optionInit2.setPosition(
			SCREEN_WIDTH / 2 - optionInit2.getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + spaceYBetween * 4
		);
		optionInit2.setFillColor(Color(193, 0, 0));

		optionInit3;
		optionInit3.setFont(fontOption);
		optionInit3.setString("MiniGames");
		optionInit3.setCharacterSize(SCREEN_WIDTH / 48);
		optionInit3.setPosition(
			SCREEN_WIDTH / 2 - optionInit3.getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + spaceYBetween * 7
		);
		optionInit3.setFillColor(Color(193, 0, 0));
	}

	void ShowMenu(RenderWindow* window, int& option) {
		Event e;
		while (window->pollEvent(e))
		{

			mousex = e.mouseMove.x;
			mousey = e.mouseMove.x;

			if (e.type == Event::KeyPressed)
			{
				if (iniciar) {
					if (e.key.code == Keyboard::Escape)
					{
						window->close();
					}
					if (e.key.code == Keyboard::W)
					{
						OptionMenuIniciar--;
						if (OptionMenuIniciar < 0)
							OptionMenuIniciar = 2;
					}
					else if (e.key.code == Keyboard::S) {
						OptionMenuIniciar++;
						if (OptionMenuIniciar > 2)
							OptionMenuIniciar = 0;
					}
					else if (e.key.code == Keyboard::Up)
					{
						OptionMenuIniciar--;
						if (OptionMenuIniciar < 0)
							OptionMenuIniciar = 2;
					}
					else if (e.key.code == Keyboard::Down) {
						OptionMenuIniciar++;
						if (OptionMenuIniciar > 2)
							OptionMenuIniciar = 0;
					}
					if (e.key.code == Keyboard::Enter) {
						switch (OptionMenuIniciar)
						{
						case 0:
						{
							break;
						}
						case 1:
						{
							option = 0;
							break;
						}
						case 2:
							option = 3;
						default:
							break;
						}
					}

				}
				else {
					if (e.key.code == Keyboard::Escape)
					{
						window->close();
					}
					if (e.key.code == Keyboard::W)
					{
						OptionMenuPrincipal--;
						if (OptionMenuPrincipal < 0)
							OptionMenuPrincipal = 2;
					}
					else if (e.key.code == Keyboard::S) {
						OptionMenuPrincipal++;
						if (OptionMenuPrincipal > 2)
							OptionMenuPrincipal = 0;
					}
					else if (e.key.code == Keyboard::Up)
					{
						OptionMenuPrincipal--;
						if (OptionMenuPrincipal < 0)
							OptionMenuPrincipal = 2;
					}
					else if (e.key.code == Keyboard::Down) {
						OptionMenuPrincipal++;
						if (OptionMenuPrincipal > 2)
							OptionMenuPrincipal = 0;
					}

					if (e.key.code == Keyboard::Enter) {
						switch (OptionMenuPrincipal)
						{
						case 0:
						{
							iniciar = true;
							break;
						}
						default:
							break;
						}
					}
				}
			}

		}
		int spaceBetween = garra.getGlobalBounds().width;

		switch (OptionMenuPrincipal)
		{
		case 0:
			garra.setPosition(SCREEN_WIDTH / 1.4 - option1.getGlobalBounds().width / 2 - spaceBetween,
				SCREEN_HEIGHT / 2);
			break;
		case 1:
			garra.setPosition(SCREEN_WIDTH / 1.4 - option2.getGlobalBounds().width / 2 - spaceBetween,
				SCREEN_HEIGHT / 2 + option1.getGlobalBounds().height * 2);
			break;
		case 2:
			garra.setPosition(SCREEN_WIDTH / 1.4 - option3.getGlobalBounds().width / 2 - spaceBetween,
				SCREEN_HEIGHT / 2 + option1.getGlobalBounds().height * 4);
			break;
		}

		window->draw(fundo);
		window->draw(title);
		window->draw(option1);
		window->draw(option2);
		window->draw(option3);


		if (iniciar) {

			window->draw(borda);
			window->draw(optionInit);
			window->draw(optionInit2);
			window->draw(optionInit3);

			int spaceBetween = garra.getGlobalBounds().width;
			int spaceYBetween = optionInit.getGlobalBounds().height;

			switch (OptionMenuIniciar)
			{
			case 0:
				garra.setPosition(
					SCREEN_WIDTH / 2 - optionInit.getGlobalBounds().width / 2 - spaceBetween,
					SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + option1.getGlobalBounds().height
				);
				break;
			case 1:
				garra.setPosition(
					SCREEN_WIDTH / 2 - optionInit2.getGlobalBounds().width / 2 - spaceBetween,
					SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + spaceYBetween * 4
				);
				break;
			case 2:
				garra.setPosition(
					SCREEN_WIDTH / 2 - optionInit3.getGlobalBounds().width / 2 - spaceBetween,
					SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + spaceYBetween * 7
				);
				break;
			}


		}
		window->draw(garra);
		window->display();



	}


};

class SelectionSinglePlayer {

	Texture fundo;
	Sprite sprFundo;
	IntRect rec;
	std::vector <Texture> roostersTextures;
	std::vector <CircleShape> circlesLine;
	std::vector <CircleShape> roosters;
	
public:
	 SelectionSinglePlayer() {

		 fundo.loadFromFile("sprites\\oldfarmbk.png");
		 sprFundo.setTexture(fundo);
		 rec.width = SCREEN_WIDTH;
		 rec.height = SCREEN_HEIGHT;
		 rec.left = 0;
		 rec.top = 0;
		 sprFundo.setTextureRect(rec);

		 for (int i = 1; i < 6; i++) {
			 string s = "sprites\\galo" + std::to_string(i);
			 s += ".png";
			 Texture t;
			 t.loadFromFile(s);
			 roostersTextures.push_back(t);
		 }

		 CircleShape sniperCircle(SCREEN_WIDTH / 16);
		 sniperCircle.setTexture(&roostersTextures[0]);
		 IntRect rec(0, 0, 506, 519);
		 sniperCircle.setTextureRect(rec);
		 sniperCircle.setPosition(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 4);

		 roosters.push_back(sniperCircle);

		 CircleShape sniperBorder(SCREEN_WIDTH / 16);
		 sniperBorder.setOutlineThickness(SCREEN_WIDTH / 75);
		 sniperBorder.setFillColor(Color::Transparent);
		 sniperBorder.setOutlineColor(Color::Yellow);
		 sniperBorder.setPosition(
			 SCREEN_WIDTH / 8 - sniperBorder.getOutlineThickness() / 2,
			 SCREEN_HEIGHT / 4 - sniperBorder.getOutlineThickness() / 2
		 );

		 circlesLine.push_back(sniperBorder);
		 
		 CircleShape pesteCircle(SCREEN_WIDTH / 16);
		 pesteCircle.setTexture(&roostersTextures[4]);
		 IntRect rec2(0, 0, 1641, 1648.5);
		 pesteCircle.setTextureRect(rec2);
		 pesteCircle.setPosition(
			 SCREEN_WIDTH / 2 - SCREEN_WIDTH / 16,
			 SCREEN_HEIGHT / 10 
		 );

		 roosters.push_back(pesteCircle);

		 CircleShape pesteBorder(SCREEN_WIDTH / 16);
		 pesteBorder.setOutlineThickness(SCREEN_WIDTH / 75);
		 pesteBorder.setFillColor(Color::Transparent);
		 pesteBorder.setOutlineColor(Color::Green);
		 pesteBorder.setPosition(
			 SCREEN_WIDTH / 2 - SCREEN_WIDTH / 16, 
			 SCREEN_HEIGHT / 10
		 );

		 circlesLine.push_back(pesteBorder);

		 CircleShape kalsaCircle(SCREEN_WIDTH / 16);
		 kalsaCircle.setTexture(&roostersTextures[1]);
		 IntRect rec3(0, 0,581 ,656);
		 kalsaCircle.setTextureRect(rec3);
		 kalsaCircle.setPosition(
			 SCREEN_WIDTH - SCREEN_WIDTH / 4,
			 SCREEN_HEIGHT / 4
		 );

		 roosters.push_back(kalsaCircle);

		 CircleShape kalsaBorder(SCREEN_WIDTH / 16);
		 kalsaBorder.setOutlineThickness(SCREEN_WIDTH / 75);
		 kalsaBorder.setFillColor(Color::Transparent);
		 kalsaBorder.setOutlineColor(Color::Blue);
		 kalsaBorder.setPosition(
			 SCREEN_WIDTH - SCREEN_WIDTH / 4,
			 SCREEN_HEIGHT / 4
		 );

		 circlesLine.push_back(kalsaBorder);

	 }
	 void show(RenderWindow* window, int& option) {

		 window->draw(sprFundo);
		 for (int i = 0; i < 3; i++) {
			 window->draw(roosters[i]);
		 }
		 for (int i = 0; i < 3; i++) {
			 window->draw(circlesLine[i]);
		 }
		
		 
		 window->display();

	 }

};