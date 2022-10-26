#ifndef VASCO_DA_GAMA
#define VASCO_DA_GAMA



void multiPlayer(RenderWindow* window, Galo& galo, Galo** galo2, int& option, RectangleShape fundo) {


	try {
		connectToServer("10.50.208.56", 59000);
	}
	catch (const char* e) {
		cout << e << endl;
	}

	int rounds = 0;
	int p1Rounds = 0;
	int p2Rounds = 0;

	Font fonte;
	fonte.loadFromFile("fonts/Mortal-Kombat-MK11.otf");

	Text round[3];

	for (int i = 0; i < 3; i++) {
		string name = "Round";
		name += to_string(i + 1);
		round[i].setString(name);
		round[i].setFont(fonte);
		round[i].setCharacterSize(SCREEN_WIDTH / 30);

		round[i].setFillColor(Color::Yellow);
		round[i].setOutlineColor(Color::Black);
		round[i].setOutlineThickness(SCREEN_WIDTH / 1000);

		round[i].setPosition(
			SCREEN_WIDTH / 2 - round[i].getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 - round[i].getGlobalBounds().height / 2
		);
	}

	Text fight("Fight !!!", fonte, SCREEN_WIDTH / 20);
	fight.setFillColor(Color::Red);
	fight.setOutlineColor(Color::Black);
	fight.setOutlineThickness(SCREEN_WIDTH / 1000);

	fight.setPosition(
		SCREEN_WIDTH / 2 - fight.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - fight.getGlobalBounds().height / 2
	);


	SoundBuffer player1winsbuf;
	player1winsbuf.loadFromFile("sounds/Player_1_Wins.wav");
	SoundBuffer player2winsbuf;
	player1winsbuf.loadFromFile("sounds/Player_2_Wins.wav");

	SoundBuffer roundBuf[3];
	Sound soundRound[3];

	SoundBuffer fightb;
	fightb.loadFromFile("sounds/Fight.wav");
	Sound s;
	s.setBuffer(fightb);

	for (int i = 0; i < 3; i++) {
		string name = "sounds/Round_";
		name += to_string(i + 1);
		name += ".wav";
		roundBuf[i].loadFromFile(name);
		soundRound[i].setBuffer(roundBuf[i]);
	}

	int framesRound = 60;
	int framesFight = 0;

	while (window->isOpen()) {
		window->clear();
		window->draw(fundo);

		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window->close();
			}

		}
		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {

			bool keyState = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);

			if (!keyboardState[i][0] && keyState) {
				keyboardState[i][1] = true;
			}
			else {
				keyboardState[i][1] = false;
			}

			if (keyboardState[i][0] && !keyState) {
				keyboardState[i][2] = true;
			}
			else {
				keyboardState[i][2] = false;
			}

			keyboardState[i][0] = keyState;

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
		}

		//options p1

		if (keyboardState[Keyboard::W][1])
		{
			galo.jump();
		}
		else if (keyboardState[Keyboard::F][1]) {
			if (keyboardState[Keyboard::S][0]) {
				galo.lowKick();

			}

			else
				galo.highKick();

		}
		else if ((keyboardState[Keyboard::G][1])) {
			galo.especial();
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			galo.setState(Rooster::state::RUNNING);
			galo.facingRight = true;
			galo.run();

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			galo.setState(Rooster::state::RUNNING);
			galo.facingRight = false;
			galo.run();

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			galo.defend();
		}
		else
		{
			galo.setState(Rooster::state::STOPPED);
			//galo.setHspeed(0);

		}

		

		galo.update();


		Packet* p = inputToPacket(&galo);
		sendData(*p);

		receiveData(*p);
		*galo2 = (Galo*) p->getData();


		if (galo.ultimateShot->getHitted) {
			galo.apanharByKalsa(galo2[0], window);
		}
		else if (galo2[0]->ultimateShot->getHitted) {
			galo2[0]->apanharByKalsa(&galo, window);
		}

		galo.bar->draw(window);
		galo2[0]->bar->draw(window);

		galo.show(*window);

		galo2[0]->show(*window);

		mainPartSystem.update();
		mainPartSystem.draw(*window);

		if (galo.gethp() < 0 || galo2[0]->gethp() < 0) {

			rounds++;
			framesRound = 60;
			galo.sethp(galo.getMaxhp());
			galo2[0]->sethp(galo.getMaxhp());
		}


		if (framesRound > 0) {
			if (framesRound == 60) {
				soundRound[rounds].play();
			}
			framesRound--;
			if (framesRound == 0) {
				s.play();
				framesFight = 60;
			}
			window->draw(round[rounds]);

		}
		if (framesFight > 0) {
			framesFight--;
			window->draw(fight);
		}


		window->display();
	}
}


#endif