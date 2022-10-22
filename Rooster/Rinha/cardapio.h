
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
	Texture cursorT;
	Sprite cursor;

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

		cursorT.loadFromFile("sprites/cursor.png");
		cursor.setTexture(cursorT);
		cursor.setScale(0.05, 0.05);
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
		window->setMouseCursorVisible(false);

		
		
		

		Vector2i mouseP = Mouse::getPosition();
		cursor.setPosition(mouseP.x, mouseP.y);

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
		window->draw(cursor);
		window->display();



	}


};

struct StatusViewer {
public:
	RectangleShape table;
	int atk;
	int def;
	int speed;
	int ulti;
	bool visibility = false;

	RectangleShape bars[4];

	StatusViewer(int atk, int def, int speed, int ulti, int positionx, int positiony) {
		this->atk = atk;
		this->def = def;
		this->speed = speed;
		this->ulti = ulti;

		table.setSize(Vector2f(SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.15));
		table.setPosition(positionx, positiony);

		for (int i = 0; i < 4; i++) {
			bars[i].setFillColor(Color::Blue);
			//bars[i].setPosition()
		}
	}

	void draw(RenderWindow * window) {
		if (!visibility)
			return;
		window->draw(table);
		for (int i = 0; i < 4; i++) {
			window->draw(bars[i]);
		}
	}


	void update(int atk, int def, int speed, int ulti) {
		this->atk = atk;
		this->def = def;
		this->speed = speed;
		this->ulti = ulti;
	}

};

class SelectionSinglePlayer {

	Texture fundo;
	Sprite sprFundo;
	IntRect rec;

	Texture podium;
	Sprite podiumP1;
	Sprite podiumP2;

	std::vector <Texture> roostersTextures;
	Texture sniperT;

	std::vector <CircleShape> circlesLine;
	std::vector <CircleShape> roosters;

	Font fontTitle;
	Text title;

	Font P;
	Text P1;
	Text P2;

	CircleShape borderP1;
	CircleShape borderP2;

	Font stats;

	std::vector <Text> statusp1;
	std::vector <Text> statusp2;

	std::vector <struct Model> models;

	bool isp1Time = true;

	int selectionp1;
	int selectipnp2;

	CircleShape circlePodium1;
	CircleShape circlePodium2;

	int p1 = -1 , p2 = -1;

	StatusViewer status = StatusViewer(0, 0, 0, 0, 0, 0);

public:
	 SelectionSinglePlayer() {

		

		 fundo.loadFromFile("sprites\\oldfarmbk.png");
		 sprFundo.setTexture(fundo);
		 rec.width = SCREEN_WIDTH;
		 rec.height = SCREEN_HEIGHT;
		 rec.left = 0;
		 rec.top = 0;
		 sprFundo.setTextureRect(rec);

		 fontTitle.loadFromFile("fonts\\Act_Of_Rejection.ttf");
		 title.setFont(fontTitle);
		 title.setString("Choose your Rooster!");
		 Color corTitulo(250, 77, 2);
		 title.setFillColor(corTitulo);
		 title.setOutlineThickness(SCREEN_WIDTH / 200);
		 title.setOutlineColor(Color(250, 200, 0));
		 title.setCharacterSize(SCREEN_WIDTH/20);
		 title.setPosition(SCREEN_WIDTH / 2 - title.getGlobalBounds().width /2, SCREEN_HEIGHT/50);
		 

		 for (int i = 1; i < 6; i++) {
			 string s = "sprites\\galo" + std::to_string(i);
			 s += ".png";
			 Texture t;
			 t.loadFromFile(s);
			 roostersTextures.push_back(t);
		 }

		 CircleShape sniperCircle(SCREEN_WIDTH / 24);
		
		 sniperCircle.setTexture(&roostersTextures[0]);
		 IntRect rec(100,100, 506, 519);
		 sniperCircle.setTextureRect(rec);
		 sniperCircle.setPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);

		 roosters.push_back(sniperCircle);

		 CircleShape sniperBorder(SCREEN_WIDTH / 24);
		 sniperBorder.setOutlineThickness(SCREEN_WIDTH / 100);
		 Color cor(255, 0, 0, 100);
		 sniperBorder.setFillColor(cor);
		
		 sniperBorder.setOutlineColor(Color::Red);
		 sniperBorder.setPosition(
			 SCREEN_WIDTH / 4,
			 SCREEN_HEIGHT / 4 
		 );

		 circlesLine.push_back(sniperBorder);
		 
		 CircleShape pesteCircle(SCREEN_WIDTH / 24);
		 pesteCircle.setTexture(&roostersTextures[4]);

		 IntRect rec2(0, 0, 1641, 1648.5);
		 pesteCircle.setTextureRect(rec2);
		 pesteCircle.setPosition(
			 SCREEN_WIDTH / 2 - SCREEN_WIDTH / 24,
			 SCREEN_HEIGHT / 6 
		 );

		 roosters.push_back(pesteCircle);

		 CircleShape pesteBorder(SCREEN_WIDTH / 24);
		 pesteBorder.setOutlineThickness(SCREEN_WIDTH / 100);
		 Color cor2(0, 255, 2,100);
		 pesteBorder.setFillColor(cor2);
		 pesteBorder.setOutlineColor(Color::Green);
		 pesteBorder.setPosition(
			 SCREEN_WIDTH / 2 - SCREEN_WIDTH / 24,
			 SCREEN_HEIGHT / 6
		 );

		 circlesLine.push_back(pesteBorder);

		 CircleShape kalsaCircle(SCREEN_WIDTH / 24);
		 kalsaCircle.setTexture(&roostersTextures[1]);
		 IntRect rec3(0, 0,581 ,656);
		 kalsaCircle.setTextureRect(rec3);
		 kalsaCircle.setPosition(
			 SCREEN_WIDTH - SCREEN_WIDTH / 4 - SCREEN_WIDTH/12,
			 SCREEN_HEIGHT / 4
		 );

		 roosters.push_back(kalsaCircle);

		 CircleShape kalsaBorder(SCREEN_WIDTH / 24);
		 kalsaBorder.setOutlineThickness(SCREEN_WIDTH / 100);
		 Color cor3(0, 0, 255, 100);
		 kalsaBorder.setFillColor(cor3);
		 kalsaBorder.setOutlineColor(Color::Blue);
		 kalsaBorder.setPosition(
			 SCREEN_WIDTH - SCREEN_WIDTH / 4 - SCREEN_WIDTH / 12,
			 SCREEN_HEIGHT / 4
		 );

		 circlesLine.push_back(kalsaBorder);

		 CircleShape magoCircle(SCREEN_WIDTH / 24);
		 magoCircle.setTexture(&roostersTextures[3]);
		 IntRect rec4(200,700, 1021.33,844);
		 magoCircle.setTextureRect(rec4);
		 magoCircle.setPosition(
			 SCREEN_WIDTH / 4 + SCREEN_WIDTH / 8,
			 SCREEN_HEIGHT / 4 + SCREEN_WIDTH / 12
		 );

		 roosters.push_back(magoCircle);

		 CircleShape magoBorder(SCREEN_WIDTH / 24);
		 magoBorder.setOutlineThickness(SCREEN_WIDTH / 100);
		 Color cor4(255,0, 255, 100);
		 magoBorder.setFillColor(cor4);
		 magoBorder.setOutlineColor(Color::Magenta);
		 magoBorder.setPosition(
			 SCREEN_WIDTH / 4 + SCREEN_WIDTH / 8,
			 SCREEN_HEIGHT / 4 + SCREEN_WIDTH / 12
		 );

		 circlesLine.push_back(magoBorder);

		 CircleShape botasCircle(SCREEN_WIDTH / 24);
		 botasCircle.setTexture(&roostersTextures[2]);
		 //IntRect rec5(200, 700, 1021.33, 844);
		 //botasCircle.setTextureRect(rec5);
		 botasCircle.setPosition(
			 SCREEN_WIDTH - (SCREEN_WIDTH / 4 + SCREEN_WIDTH / 8) - SCREEN_WIDTH / 12,
			 SCREEN_HEIGHT / 4  + SCREEN_WIDTH / 12
		 );

		 roosters.push_back(botasCircle);

		 CircleShape botasBorder(SCREEN_WIDTH / 24);
		 botasBorder.setOutlineThickness(SCREEN_WIDTH / 100);
		 Color cor5(255, 255, 0, 100);
		 botasBorder.setFillColor(cor5);
		 botasBorder.setOutlineColor(Color::Yellow);
		 botasBorder.setPosition(
			 SCREEN_WIDTH - (SCREEN_WIDTH / 4 + SCREEN_WIDTH / 8) - SCREEN_WIDTH / 12,
			 SCREEN_HEIGHT / 4 + SCREEN_WIDTH / 12
		 );

		 circlesLine.push_back(botasBorder);


		 podium.loadFromFile("sprites\\ninho.png");
		 podiumP1.setTexture(podium);
		 podiumP2.setTexture(podium);
		 podiumP1.setPosition(SCREEN_WIDTH / 10, SCREEN_HEIGHT - podiumP1.getGlobalBounds().height);
		 podiumP2.setPosition(
			 SCREEN_WIDTH - SCREEN_WIDTH / 10 - podiumP2.getGlobalBounds().width,
			 SCREEN_HEIGHT - podiumP1.getGlobalBounds().height
		 );

		 P.loadFromFile("fonts/Overfield.ttf");
		 P1.setFont(P);
		 P2.setFont(P);

		 P1.setOutlineColor(Color(200, 200, 200));
		 P1.setOutlineThickness(SCREEN_WIDTH / 200);
		 P1.setCharacterSize(SCREEN_WIDTH / 50);
		 P1.setFillColor(Color(85, 185, 230));
		 P1.setString("P1");

		 P2.setOutlineColor(Color(200, 200, 200));
		 P2.setOutlineThickness(SCREEN_WIDTH / 200);
		 P2.setCharacterSize(SCREEN_WIDTH / 50);
		 P2.setFillColor(Color(145, 0, 0));
		 P2.setString("P2");

		 borderP1.setRadius(SCREEN_WIDTH / 24);
		 borderP1.setOutlineThickness(SCREEN_WIDTH / 100);
		 borderP1.setFillColor(Color::Transparent);
		 borderP1.setOutlineColor(Color(85, 185, 230));

		 borderP2.setRadius(SCREEN_WIDTH / 24);
		 borderP2.setOutlineThickness(SCREEN_WIDTH / 100);
		 borderP2.setFillColor(Color::Transparent);
		 borderP2.setOutlineColor(Color(145, 0, 0));

		 Model Sniper;

		 sniperT.loadFromFile("sprites/galoSniper.png");
		 Sniper.tex = &sniperT;
		 Sniper.loadModel("SniperModel.txt");

		 Sniper.pos = Vector2f(
			 SCREEN_WIDTH / 10 + podiumP1.getGlobalBounds().width / 2,

			 SCREEN_HEIGHT - podiumP1.getGlobalBounds().height - Sniper.at(PE_FRENTE)->sprArea.texRect.height/2
			 
		 );
		 Sniper.xScl = -(float)SCREEN_WIDTH / 1280;
		 Sniper.yScl = (float)SCREEN_WIDTH / 1280;

		 models.push_back(Sniper);
		 circlePodium1.setRadius(circlesLine[0].getRadius());
		 circlePodium1.setPosition(podiumP1.getPosition().x + podiumP1.getGlobalBounds().width / 2 - circlePodium1.getRadius(), podiumP1.getPosition().y);
		 circlePodium1.setScale(-1, 1);
		
		 status.table.setPosition(podiumP1.getPosition().x + podiumP1.getGlobalBounds().width, SCREEN_HEIGHT * 0.7);

	 }

	 

	 void show(RenderWindow* window, int& option,Galo** galop1, Galo** galop2) {

		 int mousex = Mouse::getPosition(*window).x;
		 int mousey = Mouse::getPosition(*window).y;

		 status.visibility = false;
		 if (p2 != -1) {
			 while(window->isOpen())
				 if (sf::Keyboard::isKeyPressed(Keyboard::Escape) || sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
					 option = Rooster::UMJOGADORES;
					 return;
				 }
		 }
		 Event e;
		 while (window->pollEvent(e))
		 {
			 if (e.type == Event::Closed)
			 {
				 window->close();
			 }
			 


			 if (e.type == Event::MouseButtonPressed) {
				 if (e.mouseButton.button == Mouse::Left) {
					 
					 for (int i = 0; i < 5; i++) {
						 if (ButtonCheck::checkCircleHover(circlesLine[i], mousex, mousey)) {
								 if (i == 0) {
									 if (isp1Time) {
										 *galop1 = new Sniper(20, 20, 20, Rooster::state::STOPPED, true);
										 
									 }
									 else {
										 *galop2 = new Sniper(20, 20, 20, Rooster::state::STOPPED, false);
									 }


								 }
								 else if (i == 1) {
									 return;
								 }
								 else if (i == 2) {
									 if (isp1Time) {
										 *galop1 = new Kalsa(20, 20, 20, Rooster::state::STOPPED, true);
									 }
									 else {
										 *galop2 = new Kalsa(20, 20, 20, Rooster::state::STOPPED, false);
									 }

								 }
								 else if (i == 3) {
									 if (isp1Time) {
										*galop1 = new Bruxo(20, 20, 20, Rooster::state::STOPPED, true);
									 }
									 else {
										 *galop2 = new Bruxo(20, 20, 20, Rooster::state::STOPPED, false);
									 }
								 }
								 else if (i == 4) {
									 return;
								 
								 }

								 if (!isp1Time) {
									 p2 = i;
								 }
								 else
									 p1 = i;
								 isp1Time = false;
						 }
					 }

				 }
			 }
		 }

		 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			 window->close();
		 }
		 
		 window->draw(sprFundo);
		 window->draw(title);
		 
		 for (int i = 0; i < 5; i++) {
			 window->draw(circlesLine[i]);
		 }
		 for (int i = 0; i < 5; i++) {
			 window->draw(roosters[i]);
		 }

		 
		 

		 for (int i = 0; i < 5; i++) {

			 if(ButtonCheck::checkCircleHover(circlesLine[i], mousex, mousey))
			 {
				 if (isp1Time) {
					 borderP1.setPosition(circlesLine[i].getPosition());
					 P1.setPosition(
						 circlesLine[i].getPosition().x + SCREEN_WIDTH / 12,
						 circlesLine[i].getPosition().y
					 );
					 window->draw(borderP1);
					 window->draw(P1);
					 
					 //models[0].draw(*window);

				 }
				 else {
					 borderP2.setPosition(circlesLine[i].getPosition());
					 P2.setPosition(
						 circlesLine[i].getPosition().x + SCREEN_WIDTH / 12,
						 circlesLine[i].getPosition().y
					 );
					 window->draw(borderP2);
					 window->draw(P2);
					// models[0].update();
					// models[0].draw(*window);
				 }
				
				 status.visibility = true;

			 }
				 
		 }

	

		 window->draw(podiumP1);
		

		 window->draw(podiumP2);
		 //models[0].update();
		 //models[0].draw(*window);
		
		 if (p1 != -1) {
			 Vector2f temp = circlesLine[p1].getPosition();
			 circlesLine[p1].setPosition(podiumP1.getPosition().x + podiumP1.getGlobalBounds().width / 2 - circlesLine[p1].getRadius(), podiumP1.getPosition().y);
			 window->draw(circlesLine[p1]);


			 Vector2f temp2 = roosters[p1].getPosition();
			 roosters[p1].setPosition(circlesLine[p1].getPosition());
			 window->draw(roosters[p1]);

			 roosters[p1].setPosition(temp2);
			 circlesLine[p1].setPosition(temp);
		 }

		 if (p2 != -1) {
			 Vector2f temp = circlesLine[p2].getPosition();
			 circlesLine[p2].setPosition(podiumP2.getPosition().x + podiumP2.getGlobalBounds().width / 2 - circlesLine[p2].getRadius(), podiumP2.getPosition().y);
			 window->draw(circlesLine[p2]);


			 Vector2f temp2 = roosters[p2].getPosition();
			 roosters[p2].setPosition(circlesLine[p2].getPosition());
			 window->draw(roosters[p2]);

			 roosters[p2].setPosition(temp2);
			 circlesLine[p2].setPosition(temp);
		 }

		 status.draw(window);
		
		 window->display();

	 }

};
