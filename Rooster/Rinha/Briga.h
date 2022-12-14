
void BotControls(Rooster::Galo& galo, int input) {
	
	if (0 == input) {
		galo.jump();
	}
	else if (1 == input) {
		galo.highKick();
	}
	else if (2 == input) {
		galo.lowKick();	
	}
	else if (3 == input) {
		if (galo.onFire)
			galo.super();
		else
			galo.especial();
	}
	else if (4 == input) {
		galo.run(false);
	}
	else if (5 == input) {
		galo.run(true);
	}
	else if (6 == input) {
		galo.setState(Rooster::state::DANCING);

	}else if(7 == input){

		galo.defend();
	}
	else {
		galo.setState(Rooster::state::STOPPED);
	}
}

void galoControls(Rooster::Galo& galo, int player) {
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
}

void galoHandleAttack(Rooster::Galo& attacker, Rooster::Galo& defender, Rooster::Ataques* attack) {
	bool facing = attacker.facingRight;

	// Kalsa Ultimate Attack
	if (attack->id == 5) {
		for (int i = 0; i < defender.hurtBox.size(); i++) {
			if (attack->CheckCollision(defender.hurtBox[i])) {
				if (defender.isDefending) {
					if (attack->CheckCollision(defender.defense)) {
						defender.defended(attacker, attack, facing);
					}
					else if (!attack->getHitted) {
						attack->getHitted = true;
						attack->init2.restart();
					}
				}
				else if (!attack->getHitted) {
					attack->getHitted = true;
					attack->init2.restart();
				}
			}
		}
	}
	//bruxo super atack
	else if (attack->id == 15) {
		for (int i = 0; i < defender.hurtBox.size(); i++) {
			if (attack->CheckCollision(defender.hurtBox[i])) {
				if (defender.isDefending) {
					if (attack->CheckCollision(defender.defense)) {
						defender.defended(attacker, attack, facing);
					}
					else if (!attack->getHitted) {
						attack->getHitted = true;
						defender.apanhar(*attack, facing);
					}
				}
				else if (!attack->getHitted) {
					attack->getHitted = true;
					defender.apanhar(*attack, facing);
				}
			}
		}
	} else if(attack->id == 28){
		for (int i = 0; i < defender.hurtBox.size(); i++) {
			if (attack->CheckCollision(defender.hurtBox[i])) {
				if (defender.isDefending) {
					if (attack->CheckCollision(defender.defense)) {
						defender.defended(attacker, attack, facing);
					}
					else if (!attack->getHitted) {
						attack->getHitted = true;
						defender.apanhar(*attack, facing);
					}
				}
				else if (!attack->getHitted) {
					attack->getHitted = true;
					defender.apanhar(*attack, facing);
				}
			}
		}
	}
	// Other Attacks
	else {
		for (int i = 0; i < defender.hurtBox.size(); i++) {
			if (attack->CheckCollision(defender.hurtBox[i])) {
				if (defender.isDefending) {
					if (attack->CheckCollision(defender.defense)) {
						defender.defended(attacker, attack, facing);
					}
					else
						defender.apanhar(*attack, facing);
				}
				else
					defender.apanhar(*attack, facing);
			}
		}
	}
}

void galoAttacks(Rooster::Galo& attacker, Rooster::Galo& defender) {

	if (!defender.invunerable) {
		galoHandleAttack(attacker, defender, attacker.hiKick);

		galoHandleAttack(attacker, defender, attacker.louKick);

		galoHandleAttack(attacker, defender, attacker.ultimateShot);

		galoHandleAttack(attacker, defender, attacker.superAtack);

		if (attacker.hasProjectileAtack) {
			if (attacker.projectileAtack->isAtacking) {
				galoHandleAttack(attacker, defender, attacker.projectileAtack);
			}
		}
	}
}

void singlePlayer(RenderWindow* window, Galo& galo, Galo& galo2, int& option, RectangleShape fundo) {

	

	// Dev tools
	bool skipToWin = false;
	bool skipToFatality = false;

	galo.noGravity = false;
	galo2.noGravity = false;

	//a f?sica ajeita no versus kkkkkkkkkkkkkkkkkkkkkkkkkkk perai


	// BREGA
	//-------------------------------------------------------------------------------------------
	struct TilesInfo info;
	info.init(1);
	//info.alcides->editing = false;


	sf::View baseTilesView;

	float tilesVspeedPort = 0;
	float tilesYPort = -1;
	bool tilesReady = false;

	bool tilesFall = false;



	float wid = 1280;
	float hei = 720;

	sf::FloatRect visibleArea(0.f, 0.f, 1280, 720);
	baseTilesView.setSize(visibleArea.width, visibleArea.height);
	baseTilesView.setCenter(visibleArea.left + visibleArea.width / 2, visibleArea.top + visibleArea.height / 2);
	baseTilesView.setViewport(FloatRect(0, tilesYPort + 1, 1, 1));


	bool flores = false;



	//-------------------------------------------------------------------------------------------

	bool executarFatality = false;
	bool tilesEnd = false;



	bool cordaFall = false;
	bool cordaReady = false;
	bool cordaPull = false;
	int  cordaFrames = 100;



	// Tenho que botar algo no come?o pra garantir que nao vai crashar e pro codigo rodar
	Rooster::Galo* winner = &galo;
	Rooster::Galo* looser = &galo2;

	//-------------------------------------------------------------------------------------------

	int rounds = 0;
	int p1Rounds = 0;
	int p2Rounds = 0;
	int maxComboP1 = 0;
	int maxComboP2 = 0;



	// Textos Insanos
	//-------------------------------------------------------------------------------------------
	Font fonte;
	fonte.loadFromFile("fonts/Mortal-Kombat-MK11.otf");

	// Rounds
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

	// Fight
	Text fight("Fight !!!", fonte, SCREEN_WIDTH / 20);
	fight.setFillColor(Color::Red);
	fight.setOutlineColor(Color::Black);
	fight.setOutlineThickness(SCREEN_WIDTH / 1000);

	fight.setPosition(
		SCREEN_WIDTH / 2 - fight.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - fight.getGlobalBounds().height / 2
	);

	// Finish Him
	Text finishHim("Finish Him!", fonte, SCREEN_WIDTH / 20);
	finishHim.setFillColor(Color::Red);
	finishHim.setOutlineColor(Color::Black);
	finishHim.setOutlineThickness(SCREEN_WIDTH / 1000);

	finishHim.setPosition(
		SCREEN_WIDTH / 2 - finishHim.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - finishHim.getGlobalBounds().height / 2
	);






	// Teclado Yamaha (Placeholder)
	Texture yamahaTex;
	yamahaTex.loadFromFile("sprites/tecladoYamaha.png");

	float yamahaY = -400;
	float yamahaVspeed = 0;

	Sprite yamahaSpr(yamahaTex);
	yamahaSpr.setOrigin(yamahaSpr.getLocalBounds().width / 2, yamahaSpr.getLocalBounds().height * 0.8);
	yamahaSpr.setPosition(0, yamahaY);


	SoundBuffer yamahaFallSndBuffer;
	yamahaFallSndBuffer.loadFromFile("sounds/Explosion.ogg");
	Sound yamahaFallSnd(yamahaFallSndBuffer);





	// Corda
	Texture cordaTex;
	cordaTex.loadFromFile("sprites/cordaFalidamenteExtendida.png");

	

	Sprite cordaSpr(cordaTex);
	cordaSpr.setOrigin(cordaSpr.getLocalBounds().width / 2, 0);
	cordaSpr.setScale(0.4, 0.4);

	float cordaY = -2*cordaSpr.getGlobalBounds().height;
	float cordaX = 200;
	float cordaVspeed = 0;
	cordaSpr.setPosition(cordaX, cordaY);

	
	SoundBuffer roldanaSndBuffer;
	roldanaSndBuffer.loadFromFile("sounds/roldana.ogg");
	Sound roldanaSnd(roldanaSndBuffer);
	

	// Earthquake
	SoundBuffer earthquakeSndBuffer;
	earthquakeSndBuffer.loadFromFile("sounds/Earthquake.ogg");
	Sound earthquakeSnd(earthquakeSndBuffer);

	// Pull corda
	SoundBuffer pullSndBuffer;
	pullSndBuffer.loadFromFile("sounds/Pull.ogg");
	Sound pullSnd(pullSndBuffer);







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

	bool fightWon = false;


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

	int pauseFrames = 120;





	// Adiantando as coisas
	if (skipToWin) {
		// Galo win
		framesWin = 250;
		musicas[index].stop();

		fightWon = true;

		winner = &galo;
		looser = &galo2;

		println("Ganhou");

		if (skipToFatality) {
			tilesEnd = true;
			executarFatality = true;
		}

	}

	
	
	//-----------------------------------------------------//
	/*bots falidos*/	

	Brain* brain = new SniperBrain(&galo2, &galo);

	//----------------------------------------------------//




	while (window->isOpen()) {



		//musicas[index].pause();
		//galo.fatality(window,&galo2,fundo);
		


		if (mainInput.keyboardState[sf::Keyboard::Escape][1]) {

			//bool state = info.alcides->playing;

			//info.alcides->pause();
			int a = Pause::pauseMenu(window);
			if (!!!!!!!!!!(!!a == !!0)) {
				option = GAMEMODE;
				info.clear();
				return;
			}

			//if (state) {
				//info.alcides->play();
			//}
		}


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
				baseTilesView.setCenter(visibleArea.left + visibleArea.width / 2, visibleArea.top + visibleArea.height / 2);
				baseTilesView.setViewport(FloatRect((1 - xScl) / 2, tilesYPort + (1 - yScl) / 2, xScl, yScl));

			}
		}



		mainInput.update();

		

		

		

		if (fightWon) {
			window->draw(yamahaSpr);
		}


		// PLAYER CONTROLES

		if (!fightWon) {

			if (pauseFrames <=  0) {
				galoControls(galo, 0);
				BotControls(galo2, brain->update());
			}
			else {
				pauseFrames--;
			}
			


			// GALO ATAQUES
			galoAttacks(galo, galo2);
			galoAttacks(galo2, galo);



			// Ataque de Cinto
			if (galo.ultimateShot->getHitted && galo.ultimateShot->id == 5) {
				galo.apanharByKalsa(&galo2, window);
			}
			else if (galo2.ultimateShot->getHitted && galo2.ultimateShot->id == 5) {
				galo2.apanharByKalsa(&galo, window);
			}
			//ataque de fogo
			if (galo.superAtack->getHitted && galo.superAtack->id == 15) {
				galo.superAtack->getHitted = galo2.getHitByBruxoSuper(window);
			}
			else if (galo2.superAtack->getHitted && galo2.superAtack->id == 15) {
				galo2.superAtack->getHitted = galo.getHitByBruxoSuper(window);
			}


			galo.update();
			galo2.update();

			// Combo
			galo.comboCounter = galo2.getHits();
			galo2.comboCounter = galo.getHits();

			if (galo.comboCounter > maxComboP1) {
				maxComboP1 = galo.comboCounter;
			}

			if (galo2.comboCounter > maxComboP1) {
				maxComboP2 = galo2.comboCounter;
			}

			// Health Bar
			galo.bar->draw(window);
			galo2.bar->draw(window);

			// Draw
			galo.show(*window);
			galo2.show(*window);
		}

		// Rounds


		if (!fightWon) {

			if (galo.gethp() < 0) {
				rounds++;
				p2Rounds++;
				
				
				if (rounds == 3 || p2Rounds == 2) {
					// Galo 2 Win
					framesWin = 250;
					musicas[index].stop();

					fightWon = true;

					winner = &galo2;
					looser = &galo;

					println("Ganhou");
				}
				else {
					// New Round
					framesRound = 60;
					pauseFrames = 120;
					galo.resetPosition();
					galo2.resetPosition();
					
					galo.resetHp();
					galo2.resetHp();

				}
			}
			else if (galo2.gethp() < 0) {
				rounds++;
				p1Rounds++;

				if (rounds == 3 || p1Rounds == 2) {
					// Galo win
					framesWin = 250;
					musicas[index].stop();

					fightWon = true;

					winner = &galo;
					looser = &galo2;

					println("Ganhou");
				}
				else {
					// New Round
					framesRound = 60;
					pauseFrames = 120;
					galo.resetPosition();
					galo2.resetPosition();				
					
					galo.resetHp();
					galo2.resetHp();
				}
			}

			// Round Extra Stuff
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

		}




		// Isso embaixo ? um pesadelo
		// Yamaha Falling
		//-------------------------------------------------------------------------------
		if (winner == &galo) {
			if (fightWon) {

				float yamahaX = winner->model.at("Body")->drawPos.x - winner->model.xScl * 120;
				yamahaSpr.setScale(-winner->model.xScl * 0.75, winner->model.yScl * 0.75);

				yamahaY += yamahaVspeed;


				if (yamahaY > Rooster::floorY) {
					yamahaVspeed = 0;
					yamahaY = Rooster::floorY;

					yamahaFallSnd.play();

					roldanaSnd.play();

					if (!cordaPull) {
						cordaFall = true;
					}

					Effect* effect = new Effect();
					effect->position = Vector2f(yamahaX, Rooster::floorY);
					effect->spreadPreset(yamahaSpr.getGlobalBounds().width, yamahaSpr.getGlobalBounds().height / 2);
					effect->poeiraPreset();

					effect->sclMin = 0.5;
					effect->sclMax = 3;

					effect->fadeOutAlpha = true;
					effect->lifeMin = 60;
					effect->lifeMax = 150;
					effect->createMultipleParticles(40);
					mainPartSystem.addEffect(effect);
				}
				else if (yamahaY < Rooster::floorY) {
					yamahaVspeed = constrain(yamahaVspeed + 0.2, -40, 40);
				}
				yamahaSpr.setPosition(yamahaX, yamahaY);

				if (framesWin > 0) {
					window->draw(finishHim);
					framesWin--;
				}

				if (framesWin <= 0) {
					if (!cordaPull) {
						cordaFall = true;
					}
				}


				if (tilesEnd) {
					if (executarFatality) {
						winner->fatality(window, looser, fundo);
					}
					option = GAMEMODE;
					return;
				}

				if (cordaFall) {



					if (!cordaPull) {

						if (cordaReady) {
							cordaFrames--;
							if (cordaFrames <= 0) {
								cordaVspeed += 15;
								cordaPull = true;
								pullSnd.play();
							}
						}

						if (cordaY < -cordaSpr.getGlobalBounds().height / 2) {
							cordaVspeed += 0.2;
						}
						else {
							cordaReady = true;


							roldanaSnd.pause();


							cordaY = -cordaSpr.getGlobalBounds().height / 2;
							cordaVspeed *= -0.5;


						}
					}
					else {
						cordaVspeed -= 0.7;

						if (cordaY < -cordaSpr.getGlobalBounds().height) {
							cordaFall = false;
							tilesFall = true;
						}
					}

					cordaVspeed = constrain(cordaVspeed, -20, 15);

					cordaY += cordaVspeed;

					cordaSpr.setPosition(cordaX, cordaY);
					window->draw(cordaSpr);
				}

				// Piano Tiles
				if (tilesFall) {




					sf::View currentView = baseTilesView;

					if (info.result != -1) {
						tilesFall = false;

						//info.alcides->pause();
						tilesEnd = true;

						executarFatality = ((info.result == 1) || GODMODE);
					}


					FloatRect currentPort = currentView.getViewport();

					info.tilesView = currentView;

					info.tilesView.setViewport(FloatRect(currentPort.left, tilesYPort + currentPort.top, currentPort.width, currentPort.height));

					if (!tilesReady) {

						tilesVspeedPort += 0.001;

						tilesYPort += tilesVspeedPort;
						if (tilesYPort > 0) {

							earthquakeSnd.setVolume(tilesVspeedPort * 1000);
							earthquakeSnd.play();


							tilesVspeedPort *= -0.5;
							tilesYPort = 0;



							FloatRect area(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, 80);

							AreaEffect* effect = new AreaEffect(area, Color::White);
							effect->tilesPreset();
							effect->poeiraPreset();
							effect->vspeedMin = -2;
							effect->vspeedMax = 2;
							effect->sclMin = 1.5;
							effect->sclMax = 4;
							effect->gravity.y = 0;
							effect->friction = 0.95;
							effect->fadeOutAlpha = true;
							//effect->fadeInAlpha = true;


							effect->color = Color(200, 250, 100);

							effect->createMultipleParticles(abs(20000 * tilesVspeedPort));

							mainPartSystem.addEffect(effect);


							if (abs(tilesVspeedPort) < 0.002) {
								tilesVspeedPort = 0;
								tilesReady = true;
								//info.alcides->play();
								musicas[index].stop();
							}
						}
					}
					else {
						info.update(*window);

						if (info.xavier->getPlayingSeconds() > 46 && !flores) {
							flores = true;

							FloatRect area(0, -1000, SCREEN_WIDTH, 1000);

							AreaEffect* effect = new AreaEffect(area, Color::White);
							effect->floresPreset();
							//effect->color = Color(200, 250, 100);

							effect->createMultipleParticles(100);

							mainPartSystem.addEffect(effect);
						}
					}

					window->setView(info.tilesView);
					info.draw(*window);
					window->setView(window->getDefaultView());


				}
			}
		}
		else if (winner == &galo2) {
			winner->fatality(window, looser, fundo);
			option = Pause::rematchScreen(*window, *winner, *looser, fundo);
			return;
		}
		mainPartSystem.update();
		mainPartSystem.draw(*window);

		window->display();

	}
}

void multiPlayerLocal(RenderWindow* window, Galo& galo, Galo& galo2, int& option, RectangleShape fundo) {


	// Dev tools
	bool skipToWin = false;
	bool skipToFatality = false;




	// BREGA
	//-------------------------------------------------------------------------------------------
	struct TilesInfo info;
	info.init(1);
	//info.alcides->editing = false;


	sf::View baseTilesView;

	float tilesVspeedPort = 0;
	float tilesYPort = -1;
	bool tilesReady = false;

	bool tilesFall = false;



	float wid = 1280;
	float hei = 720;

	sf::FloatRect visibleArea(0.f, 0.f, 1280, 720);
	baseTilesView.setSize(visibleArea.width, visibleArea.height);
	baseTilesView.setCenter(visibleArea.left + visibleArea.width / 2, visibleArea.top + visibleArea.height / 2);
	baseTilesView.setViewport(FloatRect(0, tilesYPort + 1, 1, 1));

	bool flores = false;



	//-------------------------------------------------------------------------------------------

	bool executarFatality = false;
	bool tilesEnd = false;



	bool cordaFall = false;
	bool cordaReady = false;
	bool cordaPull = false;
	int  cordaFrames = 100;



	// Tenho que botar algo no come?o pra garantir que nao vai crashar e pro codigo rodar
	Rooster::Galo* winner = &galo;
	Rooster::Galo* looser = &galo2;

	//-------------------------------------------------------------------------------------------

	int rounds = 0;
	int p1Rounds = 0;
	int p2Rounds = 0;
	int maxComboP1 = 0;
	int maxComboP2 = 0;



	// Textos Insanos
	//-------------------------------------------------------------------------------------------
	Font fonte;
	fonte.loadFromFile("fonts/Mortal-Kombat-MK11.otf");

	// Rounds
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

	// Fight
	Text fight("Fight !!!", fonte, SCREEN_WIDTH / 20);
	fight.setFillColor(Color::Red);
	fight.setOutlineColor(Color::Black);
	fight.setOutlineThickness(SCREEN_WIDTH / 1000);

	fight.setPosition(
		SCREEN_WIDTH / 2 - fight.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - fight.getGlobalBounds().height / 2
	);

	// Finish Him
	Text finishHim("Finish Him!", fonte, SCREEN_WIDTH / 20);
	finishHim.setFillColor(Color::Red);
	finishHim.setOutlineColor(Color::Black);
	finishHim.setOutlineThickness(SCREEN_WIDTH / 1000);

	finishHim.setPosition(
		SCREEN_WIDTH / 2 - finishHim.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - finishHim.getGlobalBounds().height / 2
	);






	// Teclado Yamaha (Placeholder)
	Texture yamahaTex;
	yamahaTex.loadFromFile("sprites/tecladoYamaha.png");

	float yamahaY = -400;
	float yamahaVspeed = 0;

	Sprite yamahaSpr(yamahaTex);
	yamahaSpr.setOrigin(yamahaSpr.getLocalBounds().width / 2, yamahaSpr.getLocalBounds().height * 0.8);
	yamahaSpr.setPosition(0, yamahaY);


	SoundBuffer yamahaFallSndBuffer;
	yamahaFallSndBuffer.loadFromFile("sounds/Explosion.ogg");
	Sound yamahaFallSnd(yamahaFallSndBuffer);





	// Corda
	Texture cordaTex;
	cordaTex.loadFromFile("sprites/cordaFalidamenteExtendida.png");



	Sprite cordaSpr(cordaTex);
	cordaSpr.setOrigin(cordaSpr.getLocalBounds().width / 2, 0);
	cordaSpr.setScale(0.4, 0.4);

	float cordaY = -2 * cordaSpr.getGlobalBounds().height;
	float cordaX = 200;
	float cordaVspeed = 0;
	cordaSpr.setPosition(cordaX, cordaY);


	SoundBuffer roldanaSndBuffer;
	roldanaSndBuffer.loadFromFile("sounds/roldana.ogg");
	Sound roldanaSnd(roldanaSndBuffer);


	// Earthquake
	SoundBuffer earthquakeSndBuffer;
	earthquakeSndBuffer.loadFromFile("sounds/Earthquake.ogg");
	Sound earthquakeSnd(earthquakeSndBuffer);

	// Pull corda
	SoundBuffer pullSndBuffer;
	pullSndBuffer.loadFromFile("sounds/Pull.ogg");
	Sound pullSnd(pullSndBuffer);







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

	bool fightWon = false;


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

	int pauseFrames = 120;





	// Adiantando as coisas
	if (skipToWin) {
		// Galo win
		framesWin = 250;
		musicas[index].stop();

		fightWon = true;

		winner = &galo;
		looser = &galo2;

		println("Ganhou");

		if (skipToFatality) {
			tilesEnd = true;
			executarFatality = true;
		}

	}







	while (window->isOpen()) {



		//musicas[index].pause();
		//galo.fatality(window,&galo2,fundo);



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
				baseTilesView.setCenter(visibleArea.left + visibleArea.width / 2, visibleArea.top + visibleArea.height / 2);
				baseTilesView.setViewport(FloatRect((1 - xScl) / 2, tilesYPort + (1 - yScl) / 2, xScl, yScl));

			}
		}



		mainInput.update();
		if (mainInput.keyboardState[sf::Keyboard::Escape][1]) {

			//bool state = info.alcides->playing;

			//info.alcides->pause();
			int a = Pause::pauseMenu(window);
			if (!!!!!!!!!!(!!a == !!0)) {
				option = GAMEMODE;
				info.clear();
				return;
			}

			//if (state) {
				//info.alcides->play();
				//info.xavier->play();
			//}
		}

		if (fightWon) {
			window->draw(yamahaSpr);
		}


		// PLAYER CONTROLES

		if (!fightWon) {

			if (pauseFrames <= 0) {
				galoControls(galo, 0);
				galoControls(galo2, 1);
			}
			else {
				pauseFrames--;
			}



			// GALO ATAQUES
			galoAttacks(galo, galo2);
			galoAttacks(galo2, galo);



			// Ataque de Cinto
			if (galo.ultimateShot->getHitted && galo.ultimateShot->id == 5) {
				galo.apanharByKalsa(&galo2, window);
			}
			else if (galo2.ultimateShot->getHitted && galo2.ultimateShot->id == 5) {
				galo2.apanharByKalsa(&galo, window);
			}
			//ataque de fogo
			if (galo.superAtack->getHitted && galo.superAtack->id == 15) {
				galo.superAtack->getHitted = galo2.getHitByBruxoSuper(window);
			}
			else if (galo2.superAtack->getHitted && galo2.superAtack->id == 15) {
				galo2.superAtack->getHitted = galo.getHitByBruxoSuper(window);
			}


			galo.update();
			galo2.update();

			// Combo
			galo.comboCounter = galo2.getHits();
			galo2.comboCounter = galo.getHits();

			if (galo.comboCounter > maxComboP1) {
				maxComboP1 = galo.comboCounter;
			}

			if (galo2.comboCounter > maxComboP1) {
				maxComboP2 = galo2.comboCounter;
			}

			// Health Bar
			galo.bar->draw(window);
			galo2.bar->draw(window);

			// Draw
			galo.show(*window);
			galo2.show(*window);
		}

		// Rounds


		if (!fightWon) {

			if (galo.gethp() < 0) {
				rounds++;
				p2Rounds++;


				if (rounds == 3 || p2Rounds == 2) {
					// Galo 2 Win
					framesWin = 250;
					musicas[index].stop();

					fightWon = true;

					winner = &galo2;
					looser = &galo;

					println("Ganhou");
				}
				else {
					// New Round
					framesRound = 60;
					pauseFrames = 120;
					galo.resetPosition();
					galo2.resetPosition();

					galo.resetHp();
					galo2.resetHp();

				}
			}
			else if (galo2.gethp() < 0) {
				rounds++;
				p1Rounds++;

				if (rounds == 3 || p1Rounds == 2) {
					// Galo win
					framesWin = 250;
					musicas[index].stop();

					fightWon = true;

					winner = &galo;
					looser = &galo2;

					println("Ganhou");
				}
				else {
					// New Round
					framesRound = 60;
					pauseFrames = 120;
					galo.resetPosition();
					galo2.resetPosition();

					galo.resetHp();
					galo2.resetHp();
				}
			}

			// Round Extra Stuff
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

		}




		// Isso embaixo ? um pesadelo
		// Yamaha Falling
		//-------------------------------------------------------------------------------
		if (fightWon) {

			float yamahaX = winner->model.at("Body")->drawPos.x - winner->model.xScl * 120;
			yamahaSpr.setScale(-winner->model.xScl * 0.75, winner->model.yScl * 0.75);

			yamahaY += yamahaVspeed;


			if (yamahaY > Rooster::floorY) {
				yamahaVspeed = 0;
				yamahaY = Rooster::floorY;

				yamahaFallSnd.play();

				roldanaSnd.play();

				if (!cordaPull) {
					cordaFall = true;
				}

				Effect* effect = new Effect();
				effect->position = Vector2f(yamahaX, Rooster::floorY);
				effect->spreadPreset(yamahaSpr.getGlobalBounds().width, yamahaSpr.getGlobalBounds().height / 2);
				effect->poeiraPreset();

				effect->sclMin = 0.5;
				effect->sclMax = 3;

				effect->fadeOutAlpha = true;
				effect->lifeMin = 60;
				effect->lifeMax = 150;
				effect->createMultipleParticles(40);
				mainPartSystem.addEffect(effect);
			}
			else if (yamahaY < Rooster::floorY) {
				yamahaVspeed = constrain(yamahaVspeed + 0.2, -40, 40);
			}
			yamahaSpr.setPosition(yamahaX, yamahaY);

			if (framesWin > 0) {
				window->draw(finishHim);
				framesWin--;
			}

			if (framesWin <= 0) {
				if (!cordaPull) {
					cordaFall = true;
				}
			}


			if (tilesEnd) {
				if (executarFatality) {
					winner->fatality(window, looser, fundo);
				}

				option = Pause::rematchScreen(*window, *winner, *looser, fundo);
				return;
			}

			if (cordaFall) {



				if (!cordaPull) {

					if (cordaReady) {
						cordaFrames--;
						if (cordaFrames <= 0) {
							cordaVspeed += 15;
							cordaPull = true;
							pullSnd.play();
						}
					}

					if (cordaY < -cordaSpr.getGlobalBounds().height / 2) {
						cordaVspeed += 0.2;
					}
					else {
						cordaReady = true;


						roldanaSnd.pause();


						cordaY = -cordaSpr.getGlobalBounds().height / 2;
						cordaVspeed *= -0.5;


					}
				}
				else {
					cordaVspeed -= 0.7;

					if (cordaY < -cordaSpr.getGlobalBounds().height) {
						cordaFall = false;
						tilesFall = true;
					}
				}

				cordaVspeed = constrain(cordaVspeed, -20, 15);

				cordaY += cordaVspeed;

				cordaSpr.setPosition(cordaX, cordaY);
				window->draw(cordaSpr);
			}

			// Piano Tiles
			if (tilesFall) {




				sf::View currentView = baseTilesView;

				if (info.result != -1) {
					tilesFall = false;

					//info.alcides->pause();
					//info.xavier->pause();
					tilesEnd = true;

					executarFatality = ((info.result == 1) || GODMODE);
				}


				FloatRect currentPort = currentView.getViewport();

				info.tilesView = currentView;

				info.tilesView.setViewport(FloatRect(currentPort.left, tilesYPort + currentPort.top, currentPort.width, currentPort.height));

				if (!tilesReady) {

					tilesVspeedPort += 0.001;

					tilesYPort += tilesVspeedPort;
					if (tilesYPort > 0) {

						earthquakeSnd.setVolume(tilesVspeedPort * 1000);
						earthquakeSnd.play();


						tilesVspeedPort *= -0.5;
						tilesYPort = 0;



						FloatRect area(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, 80);

						AreaEffect* effect = new AreaEffect(area, Color::White);
						effect->tilesPreset();
						effect->poeiraPreset();
						effect->vspeedMin = -2;
						effect->vspeedMax = 2;
						effect->sclMin = 1.5;
						effect->sclMax = 4;
						effect->gravity.y = 0;
						effect->friction = 0.95;
						effect->fadeOutAlpha = true;
						//effect->fadeInAlpha = true;


						effect->color = Color(200, 250, 100);

						effect->createMultipleParticles(abs(20000 * tilesVspeedPort));

						mainPartSystem.addEffect(effect);


						if (abs(tilesVspeedPort) < 0.002) {
							tilesVspeedPort = 0;
							tilesReady = true;
							//info.alcides->play();
							musicas[index].stop();
						}
					}
				}
				else {
					info.update(*window);

					if (info.xavier->getPlayingSeconds() > 46 && !flores) {
						flores = true;

						FloatRect area(0, -1000, SCREEN_WIDTH, 1000);

						AreaEffect* effect = new AreaEffect(area, Color::White);
						effect->floresPreset();
						//effect->color = Color(200, 250, 100);

						effect->createMultipleParticles(100);

						mainPartSystem.addEffect(effect);
					}
				}

				window->setView(info.tilesView);
				info.draw(*window);
				window->setView(window->getDefaultView());


			}
		}

		mainPartSystem.update();
		mainPartSystem.draw(*window);

		window->display();

	}
}
