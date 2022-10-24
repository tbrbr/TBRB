
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

	Font price;
	price.loadFromFile("fonts\\pricedown.otf");
	Text texto1;
	texto1.setFillColor(Color(255,255,255,204));
	texto1.setCharacterSize(SCREEN_WIDTH/40);
	texto1.setFont(price);
	
	texto1.setString("Shelby LTDA Presents");
	texto1.setPosition(
		(SCREEN_WIDTH - texto1.getGlobalBounds().width) / 2,
		(SCREEN_HEIGHT - texto1.getGlobalBounds().height) / 2
	);

	Text texto2;
	texto2.setFillColor(Color(255, 255, 255, 204));
	texto2.setCharacterSize(SCREEN_WIDTH / 40);
	texto2.setFont(price);	
	texto2.setString("a game from the wild Sergipe");
	texto2.setPosition(
		SCREEN_WIDTH / 2 - texto2.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - texto2.getGlobalBounds().height / 2
	);

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
		marcadores[i].setPosition(SCREEN_WIDTH / 2 - marcadores[i].getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - marcadores[i].getGlobalBounds().height / 2);
	}
	for (int i = 0; i < 4; i++) {
		string s = "IntroFiles\\pichado" + std::to_string(i + 1);
		s += ".png";

		pichadaT[i].loadFromFile(s);
		pichada[i].setTexture(pichadaT[i]);
		pichada[i].setPosition(SCREEN_WIDTH / 2 - pichada[i].getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 - pichada[i].getGlobalBounds().height / 2);
	}

	logoT.loadFromFile("IntroFiles\\logo.png");
	logo.setTexture(logoT);
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
	music.openFromFile("IntroFiles\\music intro.ogg");
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
					println(timer);
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
				texto1.setFillColor(Color(255, 255, 255, (204 * (timer-15000))/1000));
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
				piscada.setFillColor(Color(255,255,255, 255 - (255 * (timer - 25000)/500)));

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
		else if (timer >= 30000 && timer <= 82000){

			

			
			int thisTime = (timer - 30000);
			static int ind = 0;
			
			
			

			if (thisTime < 250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				
			}
			else if (thisTime < 500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 1000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if(thisTime < 4000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}else if (thisTime < 4250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 4500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 4750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 5000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 9000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}else if (thisTime < 9250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 9500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 9750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 10000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 14000) {
			static int lastind = ind;
			if (lastind == ind) {
				ind++;
			}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}else if (thisTime < 14250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 14500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 14750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 15000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 19000) {
			static int lastind = ind;
			if (lastind == ind) {
				ind++;
			}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}else if (thisTime < 19250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 19500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 19750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 20000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 24000) {
			static int lastind = ind;
			if (lastind == ind) {
				ind++;
			}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}else if (thisTime < 24250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 24500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 24750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 25000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 29000) {
			static int lastind = ind;
			if (lastind == ind) {
				ind++;
			}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}else if (thisTime < 29250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 29500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 29750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 30000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 34000) {
			static int lastind = ind;
			if (lastind == ind) {
				ind++;
			}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}else if (thisTime < 34250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 34500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 34750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 35000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 39000) {
			static int lastind = ind;
			if (lastind == ind) {
				ind++;
			}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}else if (thisTime < 39250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 39500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 39750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 40000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 44000) {
			static int lastind = ind;
			if (lastind == ind) {
				ind++;
			}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}else if (thisTime < 44250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 44500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 44750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 45000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 49000) {
			static int lastind = ind;
			if (lastind == ind) {
				ind++;
			}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}else if (thisTime < 49250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 49500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 49750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 50000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 54000) {
			static int lastind = ind;
			if (lastind == ind) {
				ind++;
			}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}if (thisTime < 250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 1000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 4000) {
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}if (thisTime < 250) {

				window->draw(vetor[ind]);
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}

			}
			else if (thisTime < 500) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 750) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 1000) {
				static int lastind = ind;
				if (lastind == ind) {
					ind++;
				}
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			else if (thisTime < 4000) {
				window->draw(vetor[ind - 3]);
				window->draw(vetor[ind - 2]);
				window->draw(vetor[ind - 1]);
				window->draw(vetor[ind]);
			}
			
			
		}
		window->display();
	}
}
