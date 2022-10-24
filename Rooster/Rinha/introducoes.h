
void introducao(RenderWindow* window, int& menuOption) {
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

	
		
	for (int i = 0; i < 52; i++) {
		string s = "IntroFiles\\" + std::to_string(i + 1);
		s += ".png";

		vetorT[i].loadFromFile(s);
		vetor[i].setTexture(vetorT[i]);
	}
	for (int i = 0; i < 6; i++) {
		string s = "IntroFiles\\marcado" + std::to_string(i + 1);
		s += ".png";

		marcadoresT[i].loadFromFile(s);
		marcadores[i].setTexture(marcadoresT[i]);
	}
	for (int i = 0; i < 4; i++) {
		string s = "IntroFiles\\pichado" + std::to_string(i + 1);
		s += ".png";

		pichadaT[i].loadFromFile(s);
		pichada[i].setTexture(pichadaT[i]);
		pichada[i].setPosition(SCREEN_WIDTH / 2 - pichada[i].getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - pichada[i].getGlobalBounds().height / 2);
	}

	logoT.loadFromFile("IntroFiles\\logo.png");
	logo.setTexture(logoT);


	fundo.setFillColor(Color::Black);
	fundo.setPosition(0, 0);
	fundo.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	Music music;
	music.openFromFile("IntroFiles\\music intro.ogg");
	music.play();
	time.restart();

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
			}
		}
		if (timer > 1500 && timer < 3000) {
			int i = (timer - 1500) / 375;
			window->draw(pichada[i]);
		}
		
		window->display();
	}
}
