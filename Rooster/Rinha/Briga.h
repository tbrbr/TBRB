
void singlePlayer(RenderWindow* window, Galo& galo, Galo& galo2, int& option,RectangleShape fundo) {

	int rounds = 0;
	int p1Rounds = 0;
	int p2Rounds = 0;
	int maxComboP1 = 0;
	int maxComboP2 = 0;
	
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
			SCREEN_WIDTH / 2 - round[i].getGlobalBounds().width/2,
			SCREEN_HEIGHT / 2 - round[i].getGlobalBounds().height/2
		);
	}	

	Text fight("Fight !!!", fonte, SCREEN_WIDTH / 20);
	fight.setFillColor(Color::Red);
	fight.setOutlineColor(Color::Black);
	fight.setOutlineThickness(SCREEN_WIDTH / 1000);
				
	fight.setPosition(
		SCREEN_WIDTH / 2 - fight.getGlobalBounds().width/2,
		SCREEN_HEIGHT / 2 - fight.getGlobalBounds().height/2
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
		
	Clock matchTime;
	matchTime.restart();
	while (window->isOpen()) {
		window->clear();
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

		}
		if (true) {
			musicas[index].stop();
			galo.fatality(window, &galo2, fundo);

		}
		
		

		mainInput.update();
		if (mainInput.keyboardState[Keyboard::Space][1]) {
			int a = Pause::rematchScreen(window, galo2, galo, fundo, maxComboP1, matchTime);
		}

		if (mainInput.keyboardState[sf::Keyboard::Escape][1]) {
			int a = Pause::pauseMenu(window);
			if (!!!!!!!!!!(!!a == !!0)) {
				option = GAMEMODE;
				return;
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
		else{		
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
					}else 
						galo.apanhar(*galo2.hiKick, galo2.facingRight);
				}else 
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


		if (galo.ultimateShot->getHitted && galo.ultimateShot->id==5) {
			galo.apanharByKalsa(&galo2, window);
		}
		else if (galo2.ultimateShot->getHitted && galo2.ultimateShot->id == 5) {
			galo2.apanharByKalsa(&galo, window);
		}

		galo.update();
		galo2.update();

		galo.comboCounter = galo2.getHits();
		galo2.comboCounter = galo.getHits();

		if (galo.comboCounter > maxComboP1) {
			maxComboP1 = galo.comboCounter;
		}
		
		if (galo2.comboCounter > maxComboP1) {
			maxComboP2 = galo2.comboCounter;
		}
		galo.bar->draw(window);
		galo2.bar->draw(window);

		galo.show(*window);
		galo2.show(*window);

		mainPartSystem.update();
		mainPartSystem.draw(*window);

		if (galo.gethp() < 0 ) {

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


		window->display();
	}
}