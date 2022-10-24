

struct StatusViewer {
public:
	RectangleShape table;
	float allStatus[4];
	bool visibility = false;

	RectangleShape bars[4];
	RectangleShape outLines[4];

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


	}

	void draw(RenderWindow* window) {
		if (!visibility)
			return;
		window->draw(table);
		for (int i = 0; i < 4; i++) {
			window->draw(outLines[i]);
			window->draw(bars[i]);


		}
	}


	void update(float atk, float def, float speed, float ulti) {

		allStatus[0] = atk;
		allStatus[1] = def;
		allStatus[2] = speed;
		allStatus[3] = ulti;

		for (int i = 0; i < 4; i++) {
			bars[i].setSize(Vector2f(table.getSize().x * 0.8 * allStatus[i], bars[i].getSize().y));
			outLines[i].setSize(Vector2f( bars[i].getSize().x + 4, bars[i].getSize().y + 4));
		}

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

	int p1 = -1, p2 = -1;

	StatusViewer statusPlayer1;
	StatusViewer statusPlayer2;

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

		Model Sniper;

		sniperT.loadFromFile("sprites/galoSniper.png");
		Sniper.tex = &sniperT;
		Sniper.loadModel("SniperModel.txt");


		Sniper.autoSetBounds(Sniper.at("Body"), Sniper.at("BackShoe"), Sniper.at("Head"));

		Sniper.xScl = -(float)SCREEN_WIDTH / 1280;
		Sniper.yScl = (float)SCREEN_WIDTH / 1280;

		Sniper.pos = Vector2f(
			SCREEN_WIDTH / 10 + podiumP1.getGlobalBounds().width / 2,

			SCREEN_HEIGHT - podiumP1.getGlobalBounds().height - (Sniper.bounds.height - Sniper.center.y) * Sniper.yScl

		);




		models.push_back(Sniper);
		circlePodium1.setRadius(circlesLine[0].getRadius());
		circlePodium1.setPosition(podiumP1.getPosition().x + podiumP1.getGlobalBounds().width / 2 - circlePodium1.getRadius(), podiumP1.getPosition().y);
		circlePodium1.setScale(-1, 1);

		statusPlayer1.table.setPosition(podiumP1.getPosition().x + podiumP1.getGlobalBounds().width, SCREEN_HEIGHT * 0.7);
		statusPlayer2.table.setPosition(podiumP2.getPosition().x - statusPlayer2.table.getSize().x, SCREEN_HEIGHT * 0.7);

		int spaceBetween = statusPlayer1.table.getSize().y * 0.1;
		int ypos = statusPlayer1.table.getPosition().y + spaceBetween;
		for (int i = 0; i < 4; i++) {
			statusPlayer1.bars[i].setPosition(statusPlayer1.table.getPosition().x + statusPlayer1.table.getSize().x * 0.1, ypos);
			statusPlayer2.bars[i].setPosition(statusPlayer2.table.getPosition().x + statusPlayer2.table.getSize().x * 0.1, ypos);
			statusPlayer1.outLines[i].setPosition(statusPlayer1.bars[i].getPosition().x - 2, statusPlayer1.bars[i].getPosition().y - 2);
			statusPlayer2.outLines[i].setPosition(statusPlayer2.bars[i].getPosition().x - 2, statusPlayer2.bars[i].getPosition().y - 2);
			ypos += spaceBetween * 2;
		}


	}



	void show(RenderWindow* window, int& option, Galo** galop1, Galo** galop2) {

		int mousex = Mouse::getPosition(*window).x;
		int mousey = Mouse::getPosition(*window).y;

		statusPlayer1.visibility = !(p1 == -1);
		statusPlayer2.visibility = false;


		if (p2 != -1) {
			while (window->isOpen())
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

					struct GaloStats sniperSt;
					struct GaloStats kalsaSt;
					struct GaloStats bruxoSt;

					sniperSt = { 100, 10, 10, 10, 5 };
					kalsaSt = { 100, 10, 10, 10, 5 };
					bruxoSt = { 60, 10, 10, 10, 5 };



					for (int i = 0; i < 5; i++) {
						if (ButtonCheck::checkCircleHover(circlesLine[i], mousex, mousey)) {
							if (i == 0) {




								if (isp1Time) {
									*galop1 = new Sniper(sniperSt, Rooster::state::STOPPED, true);

								}
								else {
									*galop2 = new Sniper(sniperSt, Rooster::state::STOPPED, false);
								}


							}
							else if (i == 1) {
								return;
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


		int rooster = -1;

		for (int i = 0; i < 5; i++) {

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

		if (isp1Time) {
			if (rooster == 0) {
				statusPlayer1.update(0.7, 0.5, 0.4, 0.9);
			}
			else if (rooster == 1) {
				statusPlayer1.update(30, 0.7, 0.2, 15);
			}
			else if (rooster == 2) {
				statusPlayer1.update(1, 0.5, 0.2, 0);
			}
			else if (rooster == 3) {
				statusPlayer1.update(0.7, 0.5, 0.4, 0.9);
			}
			else if (rooster == 4) {
				statusPlayer1.update(0.7, 0.5, 0.4, 0.9);
			}
			else {
				statusPlayer1.update(0, 0, 0, 0);
			}
		}
		else {
			if (rooster == 0) {
				statusPlayer2.update(0.7, 0.5, 0.4, 0.9);
			}
			else if (rooster == 1) {
				statusPlayer2.update(30, 0.7, 0.2, 15);
			}
			else if (rooster == 2) {
				statusPlayer2.update(1, 0.5, 0.2, 0);
			}
			else if (rooster == 3) {
				statusPlayer2.update(0.7, 0.5, 0.4, 0.9);
			}
			else if (rooster == 4) {
				statusPlayer2.update(0.7, 0.5, 0.4, 0.9);
			}
			else {
				statusPlayer2.update(0, 0, 0, 0);
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

		statusPlayer1.draw(window);
		statusPlayer2.draw(window);

		window->display();

	}

};
