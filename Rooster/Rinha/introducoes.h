
class introducao {
	Texture vetorT[52];
	Sprite vetor[52];

	Texture marcadoresT[6];
	Sprite marcadores[6];

	Texture pichadaT[4];
	Sprite pichada[4];

	Texture logoT;
	Sprite logo;
	
	Music music;

	RectangleShape fundo;
	
	
public:
	bool firstTime = true;
	Clock time;
	introducao() {
		
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
			marcadores[i].setTexture(vetorT[i]);
		}
		for (int i = 0; i < 4; i++) {
			string s = "IntroFiles\\pichado" + std::to_string(i + 1);
			s += ".png";

			pichadaT[i].loadFromFile(s);
			pichada[i].setTexture(vetorT[i]);
		}

		logoT.loadFromFile("IntroFiles\\logo.png");
		logo.setTexture(logoT);
		music.openFromFile("IntroFiles\\music intro.ogg");

		fundo.setFillColor(Color::Black);
		fundo.setPosition(0, 0);
		fundo.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	}
	void draw(RenderWindow * window,int& menuOption) {
		window->clear();
		window->draw(fundo);
		
		int timer = time.getElapsedTime().asMilliseconds();
		if (timer < 1000) {
			music.play();
		}
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
		music.play();
		window->display();
	}
};
