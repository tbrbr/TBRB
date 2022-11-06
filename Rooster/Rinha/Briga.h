class pause {

	RectangleShape Fundo;
	RectangleShape buttonResume;
	RectangleShape buttonMenu;
	RectangleShape options;

public:
	pause() {

		Fundo.setFillColor(Color::Magenta);
		Fundo.setSize(Vector2f(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2));
		Fundo.setPosition(Vector2f(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4));

		buttonResume.setSize(Vector2f(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 7));
		buttonMenu.setSize(Vector2f(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 7));
		options.setSize(Vector2f(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 7));


		Vector2f posFundo = Fundo.getPosition();
		buttonResume.setPosition(Vector2f(posFundo.x / 2 - SCREEN_WIDTH / 12, posFundo.y / 3 - SCREEN_HEIGHT / 16));
		buttonMenu.setPosition(Vector2f(posFundo.x / 2 - SCREEN_WIDTH / 12, posFundo.y / 3 - (2 * SCREEN_HEIGHT / 16)));
		options.setPosition(Vector2f(posFundo.x / 2 - SCREEN_WIDTH / 12, posFundo.y / 3 - (3 * SCREEN_HEIGHT / 16)));

	}


};





void singlePlayer(RenderWindow* window, Galo& galo, Galo& galo2, int& option, RectangleShape fundo) {

	// BREGA
	//-------------------------------------------------------------------------------------------
	struct TilesInfo info;
	info.init();


	sf::View baseTilesView;

	float tilesVspeedPort = 0;
	float tilesYPort = -1;
	bool tilesReady = false;

	bool tilesFall = randFloat(1) < 0.1;

	

	float wid = 1280;
	float hei = 720;

	sf::FloatRect visibleArea(0.f, 0.f, 1280, 720);
	baseTilesView.setSize(visibleArea.width, visibleArea.height);
	baseTilesView.setCenter(visibleArea.left + visibleArea.width/2, visibleArea.top + visibleArea.height / 2);
	baseTilesView.setViewport(FloatRect(0, tilesYPort+1, 1, 1));

	bool flores = false;



	//-------------------------------------------------------------------------------------------


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
	int framesWin = 0;


	Music musicas[8];
	musicas[0].openFromFile("sounds/Braces and Boots.ogg");
	musicas[1].openFromFile("sounds/Coloured Candles.ogg");
	musicas[2].openFromFile("sounds/Copper On The Beat.ogg");
	musicas[3].openFromFile("sounds/Happy Whistler.ogg");
	musicas[4].openFromFile("sounds/In A Hurry.ogg");
	musicas[5].openFromFile("sounds/John Charles Fiddy.ogg");
	musicas[6].openFromFile("sounds/Running Away.ogg");
	musicas[7].openFromFile("sounds/Walking The Dog.ogg");

	int index = rand() % 8;
	musicas[index].play();

	while (window->isOpen()) {
		window->clear();
		window->setView(window->getDefaultView());
		window->draw(fundo);

		if (musicas[index].Stopped) {
			index = rand() % 8;
			musicas[index].play();
		}
		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window->close();
			}

			if (e.type == Event::MouseMoved) {
				mainInput.mousePos = Vector2f(e.mouseMove.x, e.mouseMove.y);
			}

			if (e.type == sf::Event::Resized)
			{
				float wid = 1280;
				float hei = 720;
				float xScl = (float)e.size.width / wid;
				float yScl = (float)e.size.height / hei;

				if (xScl > yScl) {
					wid *= yScl;
					hei = e.size.height;
				}
				else {

					hei *= xScl;
					wid = e.size.width;
				}

				xScl = wid / (float)e.size.width;
				yScl = hei / (float)e.size.height;

				sf::FloatRect visibleArea(0.f, 0.f, 1280, 720);
				baseTilesView.setSize(visibleArea.width, visibleArea.height);
				baseTilesView.setCenter(visibleArea.left + visibleArea.width/2, visibleArea.top + visibleArea.height / 2);
				baseTilesView.setViewport(FloatRect((1 - xScl) / 2, tilesYPort + (1 - yScl) / 2, xScl, yScl));
				
			}

		}
		if (false) {
			musicas[index].stop();
			galo.fatality(window, &galo2, fundo);

		}


		mainInput.update();


		if (mainInput.keyboardState[sf::Keyboard::Escape][1]) {

			bool state = info.alcides->playing;

			info.alcides->pause();
			int a = Pause::pauseMenu(window);
			if (!!!!!!!!!!(!!a == !!0)) {
				option = GAMEMODE;
				info.clear();
				return;
			}

			if (state) {
				info.alcides->play();
			}
		}

		//PLAYER 1 CONTROLES

		int player = 0;

		if (mainInput.inputState[player][GOUP][1])
		{
			galo.jump();
		}
		else if (mainInput.inputState[player][LIGHT_ATTACK][1]) {
			if (mainInput.inputState[player][GODOWN][0]) {
				galo.lowKick();
			}
			else
				galo.highKick();

		}
		else if (mainInput.inputState[player][STRONG_ATTACK][1]) {
			if (galo.onFire)
				galo.super();
			else
				galo.especial();	
		}



		if (mainInput.inputState[player][GORIGHT][0])
		{

			galo.run(true);

		}
		else if (mainInput.inputState[player][GOLEFT][0])
		{
			galo.run(false);
		}
		else if (mainInput.inputState[player][GODOWN][0])
		{
			galo.defend();
		}
		else if (mainInput.inputState[player][DANCE][0]) {
			galo.setState(Rooster::state::DANCING);
		}
		else {
			galo.setState(Rooster::state::STOPPED);
		}


		//PLAYER 2 CONTROLES

		player = 1;

		if (mainInput.inputState[player][GOUP][1])
		{
			galo2.jump();
		}

		else if (mainInput.inputState[player][LIGHT_ATTACK][1]) {
			if (mainInput.inputState[player][GODOWN][0]) {
				galo2.lowKick();
			}

			else
				galo2.highKick();

		}
		else if (mainInput.inputState[player][STRONG_ATTACK][1]) {
			if (galo2.onFire)
				galo2.super();
			else
				galo2.especial();
		}



		if (mainInput.inputState[player][GORIGHT][0])
		{

			galo2.run(true);

		}
		else if (mainInput.inputState[player][GOLEFT][0])
		{

			galo2.run(false);

		}
		else if (mainInput.inputState[player][GODOWN][0])
		{
			galo2.defend();
		}
		else if (mainInput.inputState[player][DANCE][0]) {
			galo2.setState(Rooster::state::DANCING);
		}
		else
		{
			galo2.setState(Rooster::state::STOPPED);

		}

		for (int i = 0; i < galo.hurtBox.size(); i++) {

			if (galo2.hiKick->CheckCollision(galo.hurtBox[i])) {
				if (galo.isDefending) {
					if (galo2.hiKick->CheckCollision(galo.defense)) {
						galo.defended(galo2, galo2.hiKick, galo2.facingRight);
					}
					else
						galo.apanhar(*galo2.hiKick, galo2.facingRight);
				}
				else
					galo.apanhar(*galo2.hiKick, galo2.facingRight);

			}
			if (galo2.louKick->CheckCollision(galo.hurtBox[i])) {
				if (galo.isDefending) {
					if (galo2.louKick->CheckCollision(galo.defense)) {
						galo.defended(galo2, galo2.louKick, galo2.facingRight);
					}
					else
						galo.apanhar(*galo2.louKick, galo2.facingRight);
				}
				else
					galo.apanhar(*galo2.louKick, galo2.facingRight);
			}

			if (galo2.ultimateShot->CheckCollision(galo.hurtBox[i])) {

				if (galo2.ultimateShot->id == 5) {
					if (galo.isDefending) {
						if (galo2.ultimateShot->CheckCollision(galo.defense)) {
							galo.defended(galo2, galo2.ultimateShot, galo2.facingRight);
						}
						else if (!galo2.ultimateShot->getHitted) {
							galo2.ultimateShot->getHitted = true;
							galo2.ultimateShot->init2.restart();
						}
					}
					else if (!galo2.ultimateShot->getHitted) {
						galo2.ultimateShot->getHitted = true;
						galo2.ultimateShot->init2.restart();
					}
				}
				else {
					if (galo.isDefending) {
						if (galo2.ultimateShot->CheckCollision(galo.defense)) {
							galo.defended(galo2, galo2.ultimateShot, galo2.facingRight);
						}
						else
							galo.apanhar(*galo2.ultimateShot, galo2.facingRight);
					}
					else
					{
						galo.apanhar(*galo2.ultimateShot, galo2.facingRight);
						galo2.ultimateShot->getHitted = true;
					}
				}
			}
		}

		for (int i = 0; i < galo2.hurtBox.size(); i++) {

			if (galo.hiKick->CheckCollision(galo2.hurtBox[i])) {
				if (galo2.isDefending) {
					if (galo.hiKick->CheckCollision(galo2.defense)) {
						galo2.defended(galo, galo.hiKick, galo.facingRight);
					}
					else
						galo2.apanhar(*galo.hiKick, galo.facingRight);
				}
				else
					galo2.apanhar(*galo.hiKick, galo.facingRight);

			}
			if (galo.louKick->CheckCollision(galo2.hurtBox[i])) {
				if (galo.isDefending) {
					if (galo.louKick->CheckCollision(galo2.defense)) {
						galo2.defended(galo, galo.louKick, galo.facingRight);
					}
					else
						galo2.apanhar(*galo.louKick, galo.facingRight);
				}
				else
					galo2.apanhar(*galo.louKick, galo.facingRight);
			}

			if (galo.ultimateShot->CheckCollision(galo2.hurtBox[i])) {

				if (galo.ultimateShot->id == 5) {
					if (galo2.isDefending) {
						if (galo.ultimateShot->CheckCollision(galo2.defense)) {
							galo2.defended(galo, galo.ultimateShot, galo.facingRight);
						}
						else if (!galo.ultimateShot->getHitted) {
							galo.ultimateShot->getHitted = true;
							galo.ultimateShot->init2.restart();
						}
					}
					else if (!galo.ultimateShot->getHitted) {
						galo.ultimateShot->getHitted = true;
						galo.ultimateShot->init2.restart();
					}
				}
				else {
					if (galo2.isDefending) {
						if (galo.ultimateShot->CheckCollision(galo2.defense)) {
							galo2.defended(galo, galo.ultimateShot, galo.facingRight);
						}
						else
							galo2.apanhar(*galo.ultimateShot, galo.facingRight);
					}
					else
					{
						galo2.apanhar(*galo.ultimateShot, galo.facingRight);
						galo2.ultimateShot->getHitted = true;
					}
				}
			}
		}


		if (galo.ultimateShot->getHitted && galo.ultimateShot->id == 5) {
			galo.apanharByKalsa(&galo2, window);
		}
		else if (galo2.ultimateShot->getHitted && galo2.ultimateShot->id == 5) {
			galo2.apanharByKalsa(&galo, window);
		}

		galo.update();
		galo2.update();

		galo.comboCounter = galo2.getHits();
		galo2.comboCounter = galo.getHits();

		galo.bar->draw(window);
		galo2.bar->draw(window);

		galo.show(*window);
		galo2.show(*window);



		if (galo.gethp() < 0) {

			rounds++;
			if (rounds == 3 || p2Rounds == 2) {
				framesWin = 60;
			}
			else {
				framesRound = 60;
				galo.sethp(galo.getMaxhp());
				galo2.sethp(galo2.getMaxhp());
				p2Rounds++;
			}
		}
		else if (galo2.gethp() < 0) {
			rounds++;
			if (rounds == 3 || p1Rounds == 2) {
				framesWin = 60;
			}
			else {
				framesRound = 60;
				galo.sethp(galo.getMaxhp());
				galo2.sethp(galo2.getMaxhp());
				p1Rounds++;
			}

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
		if (framesWin > 0) {
			return;
		}



		if (tilesFall) {

			
			sf::View currentView = baseTilesView;

			FloatRect currentPort = currentView.getViewport();

			info.tilesView = currentView;

			info.tilesView.setViewport(FloatRect( currentPort.left, tilesYPort + currentPort.top, currentPort.width, currentPort.height));

			if (!tilesReady) {

				tilesVspeedPort += 0.0005;

				tilesYPort += tilesVspeedPort;
				if (tilesYPort > 0) {
					tilesVspeedPort *= -0.5;
					tilesYPort = 0;

					FloatRect area(0, SCREEN_HEIGHT-40, SCREEN_WIDTH, 80);

					AreaEffect* effect = new AreaEffect(area, Color::White);
					effect->tilesPreset();
					effect->textPreset();
					effect->text.setString("Poeira");
					effect->color = Color(200, 250, 100);

					effect->createMultipleParticles(abs(5000*tilesVspeedPort));

					mainPartSystem.addEffect(effect);


					if (abs(tilesVspeedPort) < 0.001) {
						tilesVspeedPort = 0;
						tilesReady = true;
						info.alcides->play();
						musicas[index].stop();
					}
				}
			}
			else {
				info.update(*window);

				if (info.alcides->getPlayingSeconds() > 46 && !flores) {
					flores = true;

					FloatRect area(0, - 1000, SCREEN_WIDTH, 1000);

					AreaEffect* effect = new AreaEffect(area, Color::White);
					effect->floresPreset();
					//effect->color = Color(200, 250, 100);

					effect->createMultipleParticles(100);

					mainPartSystem.addEffect(effect);
				}
			}

			window->setView(info.tilesView);
			info.draw(*window);
		}

		window->setView(window->getDefaultView());

		mainPartSystem.update();
		mainPartSystem.draw(*window);

		window->display();
	}
}