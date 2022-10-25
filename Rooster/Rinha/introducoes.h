
int introducao(RenderWindow* window) {

	window->setMouseCursorGrabbed(false);
	Texture vetorT[52];
	Sprite vetor[52];
	Texture marcadoresT[6];
	Sprite marcadores[6];
	Texture pichadaT[4];
	Sprite pichada[4];
	Texture logoT;
	Sprite logo;
	RectangleShape fundo;
	Clock time;

	Font price;
	price.loadFromFile("fonts\\pricedown.otf");
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	Font content;
	content.loadFromFile("fonts/blops.ttf");

	Text texto1;
	texto1.setFillColor(Color(255, 255, 255, 204));
	texto1.setCharacterSize(SCREEN_WIDTH / 40);
	texto1.setFont(price);

	texto1.setString("Shelby LTDA Presents");
	texto1.setPosition((SCREEN_WIDTH - texto1.getGlobalBounds().width) / 2,(SCREEN_HEIGHT - texto1.getGlobalBounds().height) / 2);

	Text texto2;
	texto2.setFillColor(Color(255, 255, 255, 204));
	texto2.setCharacterSize(SCREEN_WIDTH / 40);
	texto2.setFont(price);	
	texto2.setString("a game from the wild Sergipe");
	texto2.setPosition((SCREEN_WIDTH - texto2.getGlobalBounds().width) / 2, (SCREEN_HEIGHT - texto2.getGlobalBounds().height) / 2);

	int spaceInline = SCREEN_HEIGHT / 75;
	
	Text texto3;
	texto3.setFillColor(Color(217, 173, 43));
	texto3.setCharacterSize(SCREEN_WIDTH / 20);
	texto3.setFont(titleFont);
	texto3.setString("producer");
	texto3.setPosition((SCREEN_WIDTH - texto3.getGlobalBounds().width) / 2, SCREEN_HEIGHT / 2 - (texto3.getGlobalBounds().height + spaceInline));

	Text texto4;
	texto4.setFillColor(Color(255, 255, 255, 204));
	texto4.setCharacterSize(SCREEN_WIDTH / 90);
	texto4.setFont(content);
	texto4.setString("Kaua Brocador da Mota");
	texto4.setPosition((SCREEN_WIDTH - texto4.getGlobalBounds().width) / 2, SCREEN_HEIGHT / 2 + spaceInline);

	Text texto5;
	texto5.setFillColor(Color(217, 173, 43));
	texto5.setCharacterSize(SCREEN_WIDTH / 20);
	texto5.setFont(titleFont);
	texto5.setString("executive producer");
	texto5.setPosition((SCREEN_WIDTH - texto5.getGlobalBounds().width) / 2, SCREEN_HEIGHT / 2 - (texto5.getGlobalBounds().height + spaceInline));

	Text texto6;
	texto6.setFillColor(Color(255, 255, 255, 204));
	texto6.setCharacterSize(SCREEN_WIDTH / 90);
	texto6.setFont(content);
	texto6.setString("Walter Henrique Doideira");
	texto6.setPosition((SCREEN_WIDTH - texto6.getGlobalBounds().width) / 2, SCREEN_HEIGHT / 2 + spaceInline);

	for (int i = 0; i < 52; i++) {
		string s = "IntroFiles\\" + std::to_string(i + 1);
		s += ".png";

		vetorT[i].loadFromFile(s);
		vetor[i].setTexture(vetorT[i]);
		vetor[i].setScale((float)SCREEN_WIDTH / 1920, (float)SCREEN_WIDTH / 1920);
	}
	for (int i = 0; i < 6; i++) {
		string s = "IntroFiles\\marcado" + std::to_string(i + 1);
		s += ".png";

		marcadoresT[i].loadFromFile(s);
		marcadores[i].setTexture(marcadoresT[i]);
		marcadores[i].setScale((float)SCREEN_WIDTH / 1920, (float)SCREEN_WIDTH / 1920);
		marcadores[i].setPosition(SCREEN_WIDTH / 2 - marcadores[i].getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - marcadores[i].getGlobalBounds().height / 2);
		
	}
	for (int i = 0; i < 4; i++) {
		string s = "IntroFiles\\pichado" + std::to_string(i + 1);
		s += ".png";

		pichadaT[i].loadFromFile(s);
		pichada[i].setTexture(pichadaT[i]);
		pichada[i].setScale((float)SCREEN_WIDTH / 1920, (float)SCREEN_WIDTH / 1920);
		pichada[i].setPosition(SCREEN_WIDTH / 2 - pichada[i].getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - pichada[i].getGlobalBounds().height / 2);
	}

	logoT.loadFromFile("IntroFiles\\logo.png");
	logo.setTexture(logoT);
	logo.setScale((float)SCREEN_WIDTH / 1920, (float)SCREEN_WIDTH / 1920);
	logo.setPosition(SCREEN_WIDTH / 2 - logo.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - logo.getGlobalBounds().height / 2);

	fundo.setFillColor(Color::Black);
	fundo.setPosition(0, 0);
	fundo.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	RectangleShape piscada;

	piscada.setFillColor(Color::Black);
	piscada.setPosition(0, 0);
	piscada.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	Music music;
	music.openFromFile("IntroFiles\\fulerage.ogg");
	music.play();
	time.restart();
	int memoryTime = 0;
	int lastind = 0;

	while (window->isOpen()) {

		window->clear();
		window->draw(fundo);

		int timer = time.getElapsedTime().asMilliseconds();

		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::Escape)
				{
					window->close();
				}
				if (e.key.code == Keyboard::Space)
				{
					return 2;
				}

			}
		}
		if (timer > 2000 && timer < 3800) {
			int i = (timer - 2000) / 450;
			window->draw(pichada[i]);
		}
		else if (timer > 3800 && timer < 8400) {
			window->draw(pichada[3]);
		}
		else if (timer > 8600 && timer < 10100) {
			int i = (timer - 8600) / 350;
			window->draw(marcadores[i]);
		}
		else if (timer > 10100 && timer < 14000) {
			window->draw(marcadores[5]);
		}
		else if (timer > 15000 && timer < 18000) {
			if (timer < 16000) {
				texto1.setFillColor(Color(255, 255, 255, (204 * (timer - 15000)) / 1000));
			}
			else if (timer > 16000 && timer < 17000) {
				texto1.setFillColor(Color(255, 255, 255, 204));
			}
			else {
				texto1.setFillColor(Color(255, 255, 255, (204 - (204 * (timer - 17000)) / 1000)));
			}
			window->draw(texto1);
		}
		else if (timer > 19500 && timer < 24500) {
			if (timer < 20500) {
				texto2.setFillColor(Color(255, 255, 255, (204 * (timer - 20500)) / 1000));
			}
			else if (timer > 20500 && timer < 23500) {
				texto2.setFillColor(Color(255, 255, 255, 204));
			}
			else {
				texto2.setFillColor(Color(255, 255, 255, (204 - (204 * (timer - 23500)) / 1000)));
			}
			window->draw(texto2);
		}
		else if (timer > 25000 && timer < 29000) {
			//diminuindo a escala a todo momento

			if (timer < 25500) {
				//piscadinha e logo toda branca
				piscada.setFillColor(Color(255, 255, 255, 255 - (255 * (timer - 25000) / 500)));

				logo.setScale(1.5 - (0.5 * (timer - 25000) / 500), 1.5 - (0.5 * (timer - 25000) / 500));
				logo.setPosition(SCREEN_WIDTH / 2 - logo.getGlobalBounds().width / 2,
					SCREEN_HEIGHT / 2 - logo.getGlobalBounds().height / 2);
				window->draw(logo);
				window->draw(piscada);

			}
			else if (timer > 25500 && timer < 26500) {

				logo.setScale(1.0 - (0.10 * (timer - 25500) / 1000), 1.0 - (0.10 * (timer - 25500) / 1000));
				logo.setPosition(SCREEN_WIDTH / 2 - logo.getGlobalBounds().width / 2,
					SCREEN_HEIGHT / 2 - logo.getGlobalBounds().height / 2);
				window->draw(logo);

				//constante
			}
			else {
				logo.setScale(0.9 - (0.15 * (timer - 26500) / 2500), 0.9 - (0.15 * (timer - 26500) / 2500));
				logo.setPosition(SCREEN_WIDTH / 2 - logo.getGlobalBounds().width / 2,
					SCREEN_HEIGHT / 2 - logo.getGlobalBounds().height / 2);

				int c = 255 - (255 * (timer - 26500)) / 2500;
				logo.setColor(Color(c, c, c));
				window->draw(logo);
				//opacidade
			}

		}
		else if (timer >= 30000 && timer <= 82000) {



			int thisTime = (timer - 30000);
			int restTime = thisTime % 4000;

			int ind = 4 * (int)(thisTime / 4000);

			if (ind > 48) {
				ind = 48;
			}


			if (restTime < 1000) {
				if (restTime < 250) {
					window->draw(vetor[ind]);


				}
				else if (restTime < 500) {
					window->draw(vetor[ind]);
					window->draw(vetor[ind + 1]);


				}
				else if (restTime < 750) {
					window->draw(vetor[ind]);
					window->draw(vetor[ind + 1]);
					window->draw(vetor[ind + 2]);


				}
				else {
					window->draw(vetor[ind]);
					window->draw(vetor[ind + 1]);
					window->draw(vetor[ind + 2]);
					window->draw(vetor[ind + 3]);
				}

			}
			else {

				window->draw(vetor[ind]);
				window->draw(vetor[ind + 1]);
				window->draw(vetor[ind + 2]);
				window->draw(vetor[ind + 3]);
			}
		}
		else if (timer > 83000 && timer < 86000) {
			if (timer > 83000 && timer < 85000) {
				texto3.setFillColor(Color(217, 173, 43,204));
				texto4.setFillColor(Color(255, 255, 255, 204));
			}
			else {
				texto3.setFillColor(Color(217, 173, 43, (204 - (204 * (timer - 85000)) / 1000)));
				texto4.setFillColor(Color(255, 255, 255, (204 - (204 * (timer - 85000)) / 1000)));
			}
			window->draw(texto3);
			window->draw(texto4);
		}
		else if (timer > 86000 && timer < 89000) {
			if (timer > 86000 && timer < 88000) {
				texto5.setFillColor(Color(217, 173, 43, 204));
				texto6.setFillColor(Color(255, 255, 255, 204));
			}
			else {
				texto5.setFillColor(Color(217, 173, 43, (204 - (204 * (timer - 88000)) / 1000)));
				texto6.setFillColor(Color(255, 255, 255, (204 - (204 * (timer - 88000)) / 1000)));
			}
			window->draw(texto5);
			window->draw(texto6);
		}
		else if (timer > 89000) {
			return 2;
		}
		window->display();
	}
}
