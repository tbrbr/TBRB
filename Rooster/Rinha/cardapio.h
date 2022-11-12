

struct StatusViewer {
public:
	RectangleShape table;
	float allStatus[4];
	bool visibility = false;

	RectangleShape bars[4];
	RectangleShape outLines[4];

	Texture t_icons[4];
	RectangleShape icons[4];

	StatusViewer() {

		table.setFillColor(Color::White);
		table.setSize(Vector2f(SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.15));


		for (int i = 0; i < 4; i++) {
			bars[i].setFillColor(Color::Blue);
			bars[i].setSize(Vector2f(0, table.getSize().y * 0.15));
			outLines[i].setFillColor(Color::Black);
			outLines[i].setSize(Vector2f(SCREEN_WIDTH * 0.8 + 4, bars[i].getSize().y + 4));
			allStatus[i] = 0;
		}

		t_icons[0].loadFromFile("icons/sword.png");
		t_icons[1].loadFromFile("icons/shild.png");
		t_icons[2].loadFromFile("icons/speed.png");
		t_icons[3].loadFromFile("icons/book.png");


		for (int i = 0; i < 4; i++) {
			icons[i].setTexture(&t_icons[i]);
			icons[i].setSize(Vector2f(table.getSize().y * 0.2, table.getSize().y * 0.15));
		}


	}

	void draw(RenderWindow* window) {
		if (!visibility)
			return;
		window->draw(table);
		for (int i = 0; i < 4; i++) {
			window->draw(outLines[i]);
			window->draw(bars[i]);
			window->draw(icons[i]);

		}
	}


	void update(float atk, float def, float speed, float ulti) {

		// Spd Min = 8 Spd Max = 15
		// Atk Min = 8 Atk Max = 15;
		// Def Min = 2 Def Max = 10
		// Hp Min = 50 Hp Max = 120;


		allStatus[0] = ruleOfThree(atk, 8, 15, 0, 1);
		allStatus[1] = ruleOfThree(def, 2, 10, 0, 1);
		allStatus[2] = ruleOfThree(speed, 8, 15, 0, 1);
		allStatus[3] = ruleOfThree(ulti, 50, 120, 0, 1);

		for (int i = 0; i < 4; i++) {
			bars[i].setSize(Vector2f(table.getSize().x * 0.8 * allStatus[i], bars[i].getSize().y));
			outLines[i].setSize(Vector2f(bars[i].getSize().x + 4, bars[i].getSize().y + 4));
		}

	}

	void update(struct GaloStats stats) {
		update(stats.atk, stats.def, stats.speed, stats.hp);
	}

};

class SelectionSinglePlayer {

protected:
	Texture fundo;
	Sprite sprFundo;
	IntRect rec;

	Texture podium;
	Sprite podiumP1;
	Sprite podiumP2;



	std::vector <Texture> roostersTextures;
	std::vector <Sprite> roosterSpritesForPodium;
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

	int p1 = -1, p2 = -1;

	StatusViewer statusPlayer1;
	StatusViewer statusPlayer2;


	RectangleShape confirmDiv;
	RectangleShape OKbutton;
	RectangleShape cancelButton;
	Text t_ok;
	Text t_x;

	struct GaloStats sniperSt;
	struct GaloStats kalsaSt;
	struct GaloStats bruxoSt;
	struct GaloStats pesteSt;
	struct GaloStats botaSt;

	struct GaloStats statsValues[5];
	
	



	static void UpdateGalo2(Galo** galop2, TcpSocket* socket, int* p2, bool* isready, bool * closs) {

		/*
		struct GaloStats {
			int hp;
			int speed;
			int atk;
			int def;
			int peso;
			int jumpSpd;
		};
		*/

		// Spd Min = 8 Spd Max = 15
		// Atk Min = 8 Atk Max = 15;
		// Def Min = 2 Def Max = 10
		// Hp Min = 50 Hp Max = 120;

		struct GaloStats sniperSt = { 100, 10, 15,  5, 5 , 15 };
		struct GaloStats kalsaSt =  { 100, 12, 12,  5, 6 , 20 };
		struct GaloStats bruxoSt =  { 60 , 15, 12,  5, 5 , 20 };
		struct GaloStats pesteSt =  { 120, 12, 10,  5, 6 , 12 };
		struct GaloStats botaSt =   { 80 , 13, 10,  5, 4 , 20 };

		char data[15];
		size_t received;

		while (1) {

			if (socket->receive(data, sizeof(data), received) == Socket::Done) {

				if (data[0] == '1') {
					*galop2 = new Sniper(sniperSt, Rooster::state::STOPPED, !isHost);
					*p2 = 1;

				}
				else if (data[0] == '2') {
					*galop2 = new Peste(pesteSt, Rooster::state::STOPPED, !isHost);
					*p2 = 2;
				}
				else if (data[0] == '3') {
					*galop2 = new Kalsa(kalsaSt, Rooster::state::STOPPED, !isHost);
					*p2 = 3;
				}
				else if (data[0] == '4') {
					*galop2 = new Bruxo(bruxoSt, Rooster::state::STOPPED, !isHost);
					*p2 = 4;
				}
				else if (data[0] == '5') {
					*galop2 = new Bota(botaSt, Rooster::state::STOPPED, !isHost);
					*p2 = 5;
				}
				else if (data[0] == 'c') {
					delete* galop2;
					*p2 = -1;
					*isready = false;
				}
				else if (data[0] == 'o') {
					*isready = true;
				}
				else if (data[0] == 'y') {
					*closs = true;
				}
				
			}

			data[0] = '\0';
		}





	}

	
	void selection(Galo** galop1, Galo** galop2, int i) {

		if (i == 0) {
			if (isp1Time) {
				*galop1 = new Sniper(sniperSt, Rooster::state::STOPPED, true);

			}
			else {
				*galop2 = new Sniper(sniperSt, Rooster::state::STOPPED, false);
			}

		}
		else if (i == 1) {
			if (isp1Time) {
				*galop1 = new Peste(pesteSt, Rooster::state::STOPPED, true);

			}
			else {
				*galop2 = new Peste(pesteSt, Rooster::state::STOPPED, false);
			}
		}
		else if (i == 2) {
			if (isp1Time) {
				*galop1 = new Kalsa(kalsaSt, Rooster::state::STOPPED, true);
			}
			else {
				*galop2 = new Kalsa(kalsaSt, Rooster::state::STOPPED, false);
			}

		}
		else if (i == 3) {
			if (isp1Time) {
				*galop1 = new Bruxo(bruxoSt, Rooster::state::STOPPED, true);
			}
			else {
				*galop2 = new Bruxo(bruxoSt, Rooster::state::STOPPED, false);
			}
		}
		else if (i == 4) {
			if (isp1Time) {
				*galop1 = new Bota(botaSt, Rooster::state::STOPPED, true);
			}
			else {
				*galop2 = new Bota(botaSt, Rooster::state::STOPPED, false);
			}

		}
	}

	void updateBars(int rooster) {
		if (p1 == -1) {
			statusPlayer1.update(statsValues[rooster]);
		}
		else if(p2 == -1) {
			statusPlayer2.update(statsValues[rooster]);
		}
	}





	void updateGaloView(RenderWindow* window, int i, int mousex, int mousey, int& rooster) {
		if (ButtonCheck::checkCircleHover(circlesLine[i], mousex, mousey))
		{
			if (isp1Time) {
				borderP1.setPosition(circlesLine[i].getPosition());
				P1.setPosition(
					circlesLine[i].getPosition().x + SCREEN_WIDTH / 12,
					circlesLine[i].getPosition().y
				);
				window->draw(borderP1);
				window->draw(P1);
				statusPlayer1.visibility = true;
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
				statusPlayer2.visibility = true;
				// models[0].update();
				// models[0].draw(*window);
			}

			rooster = i;


		}
	}
public:
	SelectionSinglePlayer() {


		// Galo stats
		/*
		struct GaloStats {
			int hp;
			int speed;
			int atk;
			int def;
			int peso;
			int jumpSpd;
		};
		*/

		// Spd Min = 8 Spd Max = 15
		// Atk Min = 8 Atk Max = 15;
		// Def Min = 2 Def Max = 10
		// Hp Min = 50 Hp Max = 120;

		sniperSt = { 100, 10, 15,  5, 5 , 15 };
		kalsaSt =  { 100, 12, 12,  5, 6 , 20 };
		bruxoSt =  { 60 , 15, 12,  5, 5 , 20 };
		pesteSt =  { 120, 12, 10,  5, 6 , 12 };
		botaSt =   { 80 , 13, 10,  5, 4 , 20 };

		statsValues[0] = sniperSt;
		statsValues[2] = kalsaSt;
		statsValues[3] = bruxoSt;
		statsValues[1] = pesteSt;
		statsValues[4] = botaSt;




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
		title.setCharacterSize(SCREEN_WIDTH / 20);
		title.setPosition(SCREEN_WIDTH / 2 - title.getGlobalBounds().width / 2, SCREEN_HEIGHT / 50);


		for (int i = 1; i < 6; i++) {
			string s = "sprites\\galo" + std::to_string(i);
			s += ".png";
			Texture t;
			t.loadFromFile(s);
			roostersTextures.push_back(t);
		}

		CircleShape sniperCircle(SCREEN_WIDTH / 24);

		sniperCircle.setTexture(&roostersTextures[0]);
		IntRect rec(100, 100, 506, 519);
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
		Color cor2(0, 255, 2, 100);
		pesteBorder.setFillColor(cor2);
		pesteBorder.setOutlineColor(Color::Green);
		pesteBorder.setPosition(
			SCREEN_WIDTH / 2 - SCREEN_WIDTH / 24,
			SCREEN_HEIGHT / 6
		);

		circlesLine.push_back(pesteBorder);

		CircleShape kalsaCircle(SCREEN_WIDTH / 24);
		kalsaCircle.setTexture(&roostersTextures[1]);
		IntRect rec3(0, 0, 581, 656);
		kalsaCircle.setTextureRect(rec3);
		kalsaCircle.setPosition(
			SCREEN_WIDTH - SCREEN_WIDTH / 4 - SCREEN_WIDTH / 12,
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
		IntRect rec4(200, 700, 1021.33, 844);
		magoCircle.setTextureRect(rec4);
		magoCircle.setPosition(
			SCREEN_WIDTH / 4 + SCREEN_WIDTH / 8,
			SCREEN_HEIGHT / 4 + SCREEN_WIDTH / 12
		);

		roosters.push_back(magoCircle);

		CircleShape magoBorder(SCREEN_WIDTH / 24);
		magoBorder.setOutlineThickness(SCREEN_WIDTH / 100);
		Color cor4(255, 0, 255, 100);
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
			SCREEN_HEIGHT / 4 + SCREEN_WIDTH / 12
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

		/*
		Model Sniper;

		sniperT.loadFromFile("sprites/galoSniper.png");
		Sniper.tex = &sniperT;
		Sniper.loadModel("models/SniperModel.txt");


		Sniper.autoSetBounds(Sniper.at("Body"), Sniper.at("BackShoe"), Sniper.at("Head"));

		Sniper.xScl = -(float)SCREEN_WIDTH / 1280;
		Sniper.yScl = (float)SCREEN_WIDTH / 1280;

		Sniper.pos = Vector2f(
			SCREEN_WIDTH / 10 + podiumP1.getGlobalBounds().width / 2,

			SCREEN_HEIGHT - podiumP1.getGlobalBounds().height - (Sniper.bounds.height - Sniper.center.y) * Sniper.yScl

		);

		models.push_back(Sniper);
		*/



		circlePodium1.setRadius(circlesLine[0].getRadius());
		circlePodium1.setPosition(podiumP1.getPosition().x + podiumP1.getGlobalBounds().width / 2 - circlePodium1.getRadius(), podiumP1.getPosition().y);
		circlePodium1.setScale(-1, 1);

		statusPlayer1.table.setPosition(podiumP1.getPosition().x + podiumP1.getGlobalBounds().width, SCREEN_HEIGHT * 0.7);
		statusPlayer2.table.setPosition(podiumP2.getPosition().x - statusPlayer2.table.getSize().x, SCREEN_HEIGHT * 0.7);

		int spaceBetween = statusPlayer1.table.getSize().y * 0.11;
		int ypos = statusPlayer1.table.getPosition().y + spaceBetween;


		for (int i = 0; i < 4; i++) {
			statusPlayer2.bars[i].setScale(-1, 1);
			statusPlayer2.icons[i].setScale(-1, 1);
			statusPlayer2.outLines[i].setScale(-1, 1);
		}

		for (int i = 0; i < 4; i++) {
			statusPlayer1.bars[i].setPosition(statusPlayer1.table.getPosition().x + statusPlayer1.icons[i].getSize().x, ypos);
			statusPlayer2.bars[i].setPosition(statusPlayer2.table.getPosition().x + statusPlayer2.table.getSize().x - statusPlayer2.icons[i].getSize().x, ypos);

			statusPlayer1.outLines[i].setPosition(statusPlayer1.bars[i].getPosition().x - 2, statusPlayer1.bars[i].getPosition().y - 2);
			statusPlayer2.outLines[i].setPosition(statusPlayer2.bars[i].getPosition().x + 2, statusPlayer2.bars[i].getPosition().y - 2);

			statusPlayer1.icons[i].setPosition(statusPlayer1.table.getPosition().x, statusPlayer1.bars[i].getPosition().y);
			statusPlayer2.icons[i].setPosition(statusPlayer2.table.getPosition().x + statusPlayer2.table.getSize().x, statusPlayer2.bars[i].getPosition().y);
			ypos += spaceBetween * 2;
		}


		confirmDiv.setSize(Vector2f(SCREEN_WIDTH * 0.23, SCREEN_HEIGHT * 0.08));
		confirmDiv.setPosition(SCREEN_WIDTH / 2 - confirmDiv.getSize().x / 2, SCREEN_HEIGHT * 0.9);

		OKbutton.setSize(Vector2f(confirmDiv.getSize().x * 0.45, confirmDiv.getSize().y));
		cancelButton.setSize(Vector2f(confirmDiv.getSize().x * 0.45, confirmDiv.getSize().y));

		OKbutton.setFillColor(Color::Green);
		cancelButton.setFillColor(Color::Red);

		OKbutton.setPosition(confirmDiv.getPosition());
		cancelButton.setPosition(confirmDiv.getPosition().x + cancelButton.getSize().x + confirmDiv.getSize().x * 0.1, confirmDiv.getPosition().y);

		t_x.setCharacterSize(confirmDiv.getSize().y * 0.85);
		t_x.setString("X");
		t_x.setFont(fontTitle);
		t_x.setFillColor(Color::Black);

		t_ok.setCharacterSize(confirmDiv.getSize().y * 0.85);
		t_ok.setString("OK");
		t_ok.setFont(fontTitle);
		t_ok.setFillColor(Color::Black);

		t_x.setPosition(cancelButton.getPosition().x + cancelButton.getSize().x / 2 - t_x.getGlobalBounds().width / 2, cancelButton.getPosition().y - 4);
		t_ok.setPosition(OKbutton.getPosition().x + OKbutton.getSize().x / 2 - t_ok.getGlobalBounds().width / 2, cancelButton.getPosition().y - 4);


	}

	void selection(Galo** galop1, int i, bool isp1 = isHost) {

		if (i == 0) {

			*galop1 = new Sniper(sniperSt, Rooster::state::STOPPED, isp1);

		}
		else if (i == 1) {

			*galop1 = new Peste(pesteSt, Rooster::state::STOPPED, isp1);

		}
		else if (i == 2) {

			*galop1 = new Kalsa(kalsaSt, Rooster::state::STOPPED, isp1);

		}
		else if (i == 3) {

			*galop1 = new Bruxo(bruxoSt, Rooster::state::STOPPED, isp1);

		}
		else if (i == 4) {

			*galop1 = new Bota(botaSt, Rooster::state::STOPPED, isp1);


		}
	}

	void reset() {
		this->p1 = -1;
		this->p2 = -1;
		this->isp1Time = true;

	}
	void show(RenderWindow* window, int& option, Galo** galop1, Galo** galop2) {

		int mousex = Mouse::getPosition(*window).x;
		int mousey = Mouse::getPosition(*window).y;

		Event e;
		statusPlayer1.visibility = (p1 != -1);
		statusPlayer2.visibility = (p2 != -1);

		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				option = -1;
				window->close();
			}


			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (ButtonCheck::isButtonComMouseNele(cancelButton, mousex, mousey) && isp1Time) {
						option = GAMEMODE;
						return;
					}

					
					if (p2 == -1) {
						if (ButtonCheck::isButtonComMouseNele(cancelButton, mousex, mousey) && p1 != -1) {
							delete* galop1;
							p1 = -1;
							isp1Time = true;
							
						}
					}
					if (p2 != -1) {
						if (ButtonCheck::isButtonComMouseNele(OKbutton, mousex, mousey)) {
							option = MAPA_FALIDO_E_ACHE_RUIM_WALTER;
							return;
						}

						if (ButtonCheck::isButtonComMouseNele(cancelButton, mousex, mousey)) {

							delete* galop1;
							delete* galop2;
							p1 = -1;
							p2 = -1;
							isp1Time = true;
							return;
						}

					}
					
					else {
						for (int i = 0; i < 5; i++) {
							if (ButtonCheck::checkCircleHover(circlesLine[i], mousex, mousey)) {

								this->selection(galop1, galop2, i);

								if (!isp1Time) {
									galop2[0]->facingRight = false;
									galop2[0]->setPosition(Vector2f(podiumP2.getGlobalBounds().width / 2 + podiumP2.getPosition().x, podiumP2.getPosition().y + podiumP2.getGlobalBounds().height * 0.3));
									p2 = i;
								}
								else {
									galop1[0]->facingRight = true;
									galop1[0]->setPosition(Vector2f(podiumP1.getGlobalBounds().width / 2 + podiumP1.getPosition().x, podiumP1.getPosition().y + podiumP1.getGlobalBounds().height * 0.3));
									p1 = i;
								}
								isp1Time = false;
							}
						}
					}

				}
			}
		}

		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
		}


		if (ButtonCheck::isButtonComMouseNele(OKbutton, mousex, mousey)) {
			OKbutton.setFillColor(Color::Yellow);
		}
		else {
			OKbutton.setFillColor(Color::Green);
		}

		if (ButtonCheck::isButtonComMouseNele(cancelButton, mousex, mousey)) {
			cancelButton.setFillColor(Color::Yellow);
		}
		else {
			cancelButton.setFillColor(Color::Red);
		}

		window->draw(sprFundo);
		window->draw(title);

		for (int i = 0; i < 5; i++) {
			window->draw(circlesLine[i]);
		}
		for (int i = 0; i < 5; i++) {
			window->draw(roosters[i]);
		}


		int rooster = -1;
		if (p2 == -1)
			for (int i = 0; i < 5; i++) {
				this->updateGaloView(window, i, mousex, mousey, rooster);
			}

		this->updateBars(rooster);

		window->draw(podiumP1);
		window->draw(podiumP2);


		if (p1 != -1) {

			galop1[0]->update();
			galop1[0]->show(*window);

		}

		if (p2 != -1) {

			galop2[0]->update();
			galop2[0]->show(*window);
		}

		statusPlayer1.draw(window);
		statusPlayer2.draw(window);

		window->draw(OKbutton);
		window->draw(cancelButton);
		window->draw(t_x);
		window->draw(t_ok);
		

		window->display();

	}

	void selecaode1galo(RenderWindow* window, int& option, Galo** galop1)
	{
		

		while (window->isOpen()) {

			Event e;
			statusPlayer1.visibility = (p1 != -1);

			int mousex = Mouse::getPosition(*window).x;
			int mousey = Mouse::getPosition(*window).y;

			while (window->pollEvent(e))
			{
				if (e.type == Event::Closed)
				{
					window->close();
				}


				if (e.type == Event::MouseButtonPressed) {
					if (e.mouseButton.button == Mouse::Left) {

						
						if (ButtonCheck::isButtonComMouseNele(cancelButton, mousex, mousey)) {
							if (p1 == -1) {
								option = GAMEMODE;
								return;
							}
							else {
								delete * galop1;
								p1 = -1;
							}
						}
						
						if (ButtonCheck::isButtonComMouseNele(OKbutton, mousex, mousey)) {
							if (p1 != -1) {
								option = VERSUS;
								mode = SINGLE;
								return;
							}
						}

						for (int i = 0; i < 5; i++) {
							if (ButtonCheck::checkCircleHover(circlesLine[i], mousex, mousey)) {
								this->selection(galop1, i, true);
								galop1[0]->facingRight = true;
								galop1[0]->setPosition(Vector2f(podiumP1.getGlobalBounds().width / 2 + podiumP1.getPosition().x, podiumP1.getPosition().y + podiumP1.getGlobalBounds().height * 0.3));
								p1 = i;
							}
						}

					}
				}
			}



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window->close();
			}


			if (ButtonCheck::isButtonComMouseNele(OKbutton, mousex, mousey)) {
				OKbutton.setFillColor(Color::Yellow);
			}
			else {
				OKbutton.setFillColor(Color::Green);
			}

			if (ButtonCheck::isButtonComMouseNele(cancelButton, mousex, mousey)) {
				cancelButton.setFillColor(Color::Yellow);
			}
			else {
				cancelButton.setFillColor(Color::Red);
			}

			window->draw(sprFundo);
			window->draw(title);

			for (int i = 0; i < 5; i++) {
				window->draw(circlesLine[i]);
			}
			for (int i = 0; i < 5; i++) {
				window->draw(roosters[i]);
			}


			int rooster = -1;
			if (p2 == -1)
				for (int i = 0; i < 5; i++) {
					this->updateGaloView(window, i, mousex, mousey, rooster);
				}

			this->updateBars(rooster);

			window->draw(podiumP1);
			


			if (p1 != -1) {

				galop1[0]->update();
				galop1[0]->show(*window);

			}

			statusPlayer1.draw(window);
			

			window->draw(OKbutton);
			window->draw(cancelButton);
			window->draw(t_x);
			window->draw(t_ok);


			window->display();
		}
	}

	int show(RenderWindow* window, Galo** galop1, Galo** galop2, TcpSocket* socket) {

		bool isready1 = false;
		bool isready2 = false;
		bool closs = false;
		sf::Thread th(std::bind(&UpdateGalo2, galop2, socket, &p2, &isready2, &closs));
		th.launch();

		char data[10] = "\0";
		socket->send(data, 10);

		RectangleShape cancel2;
		Vector2f buttonSize;
		buttonSize.x = window->getSize().x * 0.12;
		buttonSize.y = window->getSize().y * 0.07;

		cancel2.setSize(buttonSize);
		cancel2.setFillColor(Color::Black);
		cancel2.setOutlineThickness(2);
		cancel2.setOutlineColor(Color::Red);

		Font bops;
		bops.loadFromFile("fonts/blops.ttf");
		Text _cancel2("CANCEL", bops, SCREEN_HEIGHT / 60);
		_cancel2.setFillColor(Color::Black);
		_cancel2.setOutlineThickness(1);
		_cancel2.setOutlineColor(Color::Red);

		Vector2f _pos;

		RectangleShape rectangle;
		rectangle.setSize(Vector2f(window->getSize().x * 0.3, window->getSize().y * 0.3));
		rectangle.setPosition(window->getSize().x / 2 - rectangle.getSize().x / 2, window->getSize().y / 2 - rectangle.getSize().y / 2);
		rectangle.setFillColor(Color::Black);
		rectangle.setOutlineColor(Color::Red);
		rectangle.setOutlineThickness(4);
		_pos.x = rectangle.getPosition().x + rectangle.getSize().x / 2 - cancel2.getGlobalBounds().width / 2;
		_pos.y = rectangle.getPosition().y + rectangle.getSize().y * 0.6;
		cancel2.setPosition(_pos);

		Text t("Awaiting Oponent", bops, window->getSize().y / 60);
		t.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2 - t.getGlobalBounds().width / 2, rectangle.getPosition().y + rectangle.getSize().y * 0.13);
		t.setFillColor(Color::Red);

		_pos.x = cancel2.getPosition().x + cancel2.getSize().x / 2 - _cancel2.getGlobalBounds().width / 2;
		_pos.y = cancel2.getPosition().y + cancel2.getSize().y - _cancel2.getGlobalBounds().height * 2;
		_cancel2.setPosition(_pos);



		while (window->isOpen()) {
			data[0] = '\0';
			int mousex = Mouse::getPosition(*window).x;
			int mousey = Mouse::getPosition(*window).y;

			Event e;
			statusPlayer1.visibility = (p1 != -1);
			statusPlayer2.visibility = (p2 != -1);
			while (window->pollEvent(e))
			{
				if (e.type == Event::Closed)
				{
					window->close();
					socket->disconnect();
					th.terminate();
				}

				if (e.type == Event::MouseButtonPressed) {
					if (e.mouseButton.button == Mouse::Left) {

						if (!isready1) {
							for (int i = 0; i < 5; i++) {
								if (ButtonCheck::checkCircleHover(circlesLine[i], mousex, mousey)) {

									this->selection(galop1, i);
									galop1[0]->facingRight = true;
									galop1[0]->setPosition(Vector2f(podiumP1.getGlobalBounds().width / 2 + podiumP1.getPosition().x, podiumP1.getPosition().y + podiumP1.getGlobalBounds().height * 0.3));
									p1 = i;

									itoa(p1 + 1, data, 10);
									socket->send(data, sizeof(data));

								}
							}
						}

						if (ButtonCheck::isButtonComMouseNele(OKbutton, mousex, mousey)) {
							if (*galop1 != NULL) {
								data[0] = 'o';
								socket->send(data, sizeof(data));
								isready1 = true;
							}

						}

						if (isready1 && !isready2) {
							if (ButtonCheck::isButtonComMouseNele(cancel2, mousex, mousey)) {
								data[0] = 'c';
								socket->send(data, sizeof(data));
								delete* galop1;
								p1 = -1;
								isready1 = false;
							}
						}
						else {
							if (ButtonCheck::isButtonComMouseNele(cancelButton, mousex, mousey)) {
								if (p1 != -1) {
									data[0] = 'c';
									socket->send(data, sizeof(data));
									delete* galop1;
									p1 = -1;
									isready1 = false;
								}
								else {
									data[0] = 'y';
									socket->send(data, sizeof(data));
									th.terminate();
									println("insano");
									return MULTI_MODE;
								}
							}
						}
					}
				}
			}

			if (isready1 && isready2) {
				th.terminate();
				galop1[0]->resetPosition();				
				galop2[0]->resetPosition();

				galop2[0]->update();
				galop1[0]->update();

				return MAPA_FALIDO_E_ACHE_RUIM_WALTER;

			}

			if (closs) {
				th.terminate();
				socket->disconnect();
				this->reset();
				return MULTI_MODE;
			}


			if (p2 != -1) {
				galop2[0]->facingRight = false;
				galop2[0]->noGravity = true;
				galop2[0]->setPosition(Vector2f(podiumP2.getGlobalBounds().width / 2 + podiumP2.getPosition().x, podiumP2.getPosition().y + podiumP2.getGlobalBounds().height * 0.3));

			}
			

			if (!isready1) {
				if (ButtonCheck::isButtonComMouseNele(OKbutton, mousex, mousey)) {
					OKbutton.setFillColor(Color::Yellow);
				}
				else {
					OKbutton.setFillColor(Color::Green);
				}

				if (ButtonCheck::isButtonComMouseNele(cancelButton, mousex, mousey)) {
					cancelButton.setFillColor(Color::Yellow);
				}
				else {
					cancelButton.setFillColor(Color::Red);
				}
			}

			window->draw(sprFundo);
			window->draw(title);

			for (int i = 0; i < 5; i++) {
				window->draw(circlesLine[i]);
			}
			for (int i = 0; i < 5; i++) {
				window->draw(roosters[i]);
			}


			int rooster = -1;

			if (!isready1)
				for (int i = 0; i < 5; i++) {
					this->updateGaloView(window, i, mousex, mousey, rooster);
				}

			this->updateBars(rooster);

			window->draw(podiumP1);
			window->draw(podiumP2);


			if (p1 != -1) {

				galop1[0]->update();
				galop1[0]->show(*window);

			}

			if (p2 != -1) {
				galop2[0]->update();
				galop2[0]->show(*window);
			}

			//statusPlayer1.draw(window);
			//statusPlayer2.draw(window);

			
			window->draw(OKbutton);
			window->draw(cancelButton);
			window->draw(t_x);
			window->draw(t_ok);


			if (isready1 && !isready2) {
				window->draw(rectangle);
				window->draw(t);
				window->draw(cancel2);
				window->draw(_cancel2);
			}

			window->display();



		}


	}
};
