#ifndef VASCO_DA_GAMA
#define VASCO_DA_GAMA

#include <functional> 

#include "server_connect.h"

void galo2thread(Galo * galo2, TcpSocket * socket, bool * loss) {
	char data[10] = "\0";
	size_t received;
	while (1) {

		socket->receive(data, 10, received);
		if (data[0] == 'x') {
			*loss = true;
		}
		
		if (data[0] == 'w')
		{
			galo2->jump();
		}
		else if (data[0] == 'f') {
			if (data[1] == 's') {
				galo2->lowKick();
			}
			else
				galo2->highKick();

		}
		else if (data[0] == 'g') {
			if (galo2->onFire)
				galo2->super();
			else
				galo2->especial();
		}

		if (data[5] == 'd')
		{
			galo2->run(true);
		}
		else if (data[5] == 'a')
		{
			galo2->run(false);
		}
		else if (data[5] == 's')
		{
			galo2->defend();
		}
		else if (data[5] == 'q') {
			galo2->setState(Rooster::state::DANCING);
		}
		else {
			galo2->setState(Rooster::state::STOPPED);
		}
		data[1] = '\0';
		data[5] = '\0';
	}

}

void galo1thread(Galo * galo, TcpSocket* socket, int * pauseFrames) {


	static char data[10] = "\0";
	//while (1) {
		if (*pauseFrames <= 0) {
			if (mainInput.inputState[0][GOUP][1])
			{
				data[0] = 'w';
				galo->jump();
			}
			else if (mainInput.inputState[0][LIGHT_ATTACK][1]) {
				data[0] = 'f';
				if (mainInput.inputState[0][GODOWN][0]) {
					data[1] = 's';
					galo->lowKick();
				}
				else {
					data[1] = '0';
					galo->highKick();
				}

			}
			else if (mainInput.inputState[0][STRONG_ATTACK][1]) {
				data[0] = 'g';
				if (galo->onFire)
					galo->super();
				else
					galo->especial();
			}
			else {
				data[0] = '0';
			}

			if (mainInput.inputState[0][GORIGHT][0])
			{
				data[5] = 'd';
				galo->run(true);

			}
			else if (mainInput.inputState[0][GOLEFT][0])
			{
				data[5] = 'a';
				galo->run(false);
			}
			else if (mainInput.inputState[0][GODOWN][0])
			{
				data[5] = 's';
				galo->defend();
			}
			else if (mainInput.inputState[0][DANCE][0]) {
				data[5] = 'q';
				galo->setState(Rooster::state::DANCING);
			}
			else {
				data[5] = '0';
				galo->setState(Rooster::state::STOPPED);
			}
		}
		else {
			data[0] = '0';
			data[1] = '0';
			data[5] = '0';
			(*pauseFrames)--;
		}

		socket->send(data, 10);
		
		///mainInput.update();
	//}
}

void lan(RenderWindow* window, Galo& galo, Galo& galo2, int& option, RectangleShape fundo, TcpSocket * socket) {


	//-------------------------------------------------------------------------------------------
	bool executarFatality = false;

	// Tenho que botar algo no começo pra garantir que nao vai crashar e pro codigo rodar
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

	char data[10] = "\0";

	bool connectionLoss = false;

	Thread send(std::bind(&galo1thread, &galo ,socket, &pauseFrames));
	Thread receive(std::bind(&galo2thread, &galo2, socket, &connectionLoss));
	

	//send.launch();
	receive.launch();

	while (window->isOpen()) {


		/*
		musicas[index].pause();
		galo.fatality(window,&galo2,fundo);
		*/

		if (connectionLoss) {
			send.terminate();
			receive.terminate();
			socket->disconnect();
			option = MULTI_MODE;
			return;
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
				socket->send("x", 2);
				socket->disconnect();
				send.terminate();
				receive.terminate();
				window->close();
			}

			if (e.type == Event::MouseMoved) {
				mainInput.mousePos = Vector2f(e.mouseMove.x, e.mouseMove.y);
			}

			if (e.type == sf::Event::Resized)
			{

			}
		}

		mainInput.update();

		// PLAYER CONTROLES

		if (!fightWon) {

			
			galo1thread(&galo, socket, &pauseFrames);
		

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
					executarFatality = true;
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
					executarFatality = true;
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

		if (executarFatality) {
			println("Fatalitou");
			winner->fatality(window, looser, fundo);
			send.terminate();
			receive.terminate();
			option = MENU_PRINCIPAL;
			return;
		}

		mainPartSystem.update();
		mainPartSystem.draw(*window);
		window->display();

	}

	

}




#endif