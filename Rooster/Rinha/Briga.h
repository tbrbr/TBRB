


	void singlePlayer(RenderWindow* window, Galo& galo, Galo& galo2, int& option,RectangleShape fundo) {

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


			mainInput.update();

			if (mainInput.keyboardState[sf::Keyboard::Escape][1]) {
				window->close();
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
				galo.setState(Rooster::state::RUNNING);
				galo.facingRight = true;
				galo.run();

			}
			else if (mainInput.inputState[player][GOLEFT][0])
			{
				galo.setState(Rooster::state::RUNNING);
				galo.facingRight = false;
				galo.run();

			}
			else if (mainInput.inputState[player][GODOWN][0])
			{
				galo.defend();
			}
			else
			{
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
				galo2.setState(Rooster::state::RUNNING);
				galo2.facingRight = true;
				galo2.run();

			}
			else if (mainInput.inputState[player][GOLEFT][0])
			{
				galo2.setState(Rooster::state::RUNNING);
				galo2.facingRight = false;
				galo2.run();

			}
			else if (mainInput.inputState[player][GODOWN][0])
			{
				galo2.defend();
			}
			else
			{
				galo2.setState(Rooster::state::STOPPED);

			}


			


			for (int i = 0; i < galo.hurtBox.size(); i++) {

				if (galo2.hiKick->CheckCollision(galo.hurtBox[i])) {
					galo.apanhar(*galo2.hiKick, galo2.facingRight);

				}
				if (galo2.louKick->CheckCollision(galo.hurtBox[i])) {
					galo.apanhar(*galo2.louKick, galo2.facingRight);

				}
				if (galo2.ultimateShot->CheckCollision(galo.hurtBox[i])) {
					if (galo2.ultimateShot->id == 5) {
						if (!galo2.ultimateShot->getHitted) {
							galo2.ultimateShot->getHitted = true;
							galo2.ultimateShot->init2.restart();
						}	
					}
					else {
						galo.apanhar(*galo2.ultimateShot, galo2.facingRight);
					}
				}
			}


			for (int i = 0; i < galo2.hurtBox.size(); i++) {

				if (galo.hiKick->CheckCollision(galo2.hurtBox[i])) {
					galo2.apanhar(*galo.hiKick, galo.facingRight);

				}
				if (galo.louKick->CheckCollision(galo2.hurtBox[i])) {
					galo2.apanhar(*galo.louKick, galo.facingRight);
				}
				if (galo.ultimateShot->CheckCollision(galo2.hurtBox[i])) {
					if (galo.ultimateShot->id == 5) {

						if (!galo.ultimateShot->getHitted) {
							galo.ultimateShot->getHitted = true;
							galo.ultimateShot->init2.restart();
						}
					}
					else
						galo2.apanhar(*galo.ultimateShot, galo.facingRight);


				}

			}

			if (galo.ultimateShot->getHitted) {
				galo.apanharByKalsa(&galo2, window);
			}
			else if (galo2.ultimateShot->getHitted) {
				galo2.apanharByKalsa(&galo, window);
			}

			galo.update();

			galo2.update();


			galo.bar->draw(window);
			galo2.bar->draw(window);

			galo.show(*window);

			galo2.show(*window);

			mainPartSystem.update();
			mainPartSystem.draw(*window);

			if (galo.gethp() < 0 ) {

				rounds++;
				if (rounds == 3 || p2Rounds) {
					framesWin = 60;
				}
				else {
					framesRound = 60;
					galo.sethp(galo.getMaxhp());
					galo2.sethp(galo.getMaxhp());
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
					galo2.sethp(galo.getMaxhp());
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