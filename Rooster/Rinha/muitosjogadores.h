#ifndef VASCO_DA_GAMA
#define VASCO_DA_GAMA

#include <functional> 

#include "server_connect.h"

void galo2move(Galo* galo, char* data) {

	if (data[0] == 'w')
	{
		galo->jump();
	}
	else if (data[0] == 'f') {
		if (data[1] == 's') {
			galo->lowKick();
			data[1] = '\0';
		}
		else {
			galo->highKick();
		}
	}
	else if (data[0] == 'g') {
		galo->especial();
	}

	if (data[5] == 'd')
	{
	
		galo->run(true);

	}
	else if (data[5] == 'a')
	{
	
		galo->run(false);

	}
	else if (data[5] == 's')
	{
		galo->defend();
	}
	else
	{
		galo->setState(Rooster::state::STOPPED);
	}

}


void multiPlayer(RenderWindow* window, Galo& galo, Galo & galo2, int& option, RectangleShape fundo, TcpSocket * socket) {

	if (isHost) {
		galo2.facingRight = false;
		galo.facingRight = true;
	}
	else {
		galo2.facingRight = true;
		galo.facingRight = false;
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

	//=================================================================

	char* data = (char*)malloc(10);
	data[0] = '\0';
	size_t size;

	//=================================================================
	


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
		//galo.fatality(window,&galo2,fundo);

		mainInput.update();

		if (mainInput.keyboardState[sf::Keyboard::Escape][1]) {
			window->close();
		}


		//PLAYER 1 CONTROLES

		int player = 0;

		if (mainInput.inputState[player][GOUP][1])
		{
			data[0] = 'w';
			galo.jump();
		}
		else if (mainInput.inputState[player][LIGHT_ATTACK][1]) {
			if (mainInput.inputState[player][GODOWN][0]) {
				strcpy(data, "fs\0");
				galo.lowKick();
			}

			else {
				strcpy(data, "f");
				galo.highKick();
			}
		}
		else if (mainInput.inputState[player][STRONG_ATTACK][1]) {
			strcpy(data, "g");
			galo.especial();
		}



		if (mainInput.inputState[player][GORIGHT][0])
		{
			strcpy(data + 5, "d");
			
			galo.run(true);

		}
		else if (mainInput.inputState[player][GOLEFT][0])
		{
			strcpy(data + 5, "a");
			
			galo.run(false);

		}
		else if (mainInput.inputState[player][GODOWN][0])
		{
			strcpy(data + 5, "s");
			galo.defend();
		}
		else
		{
			data[5] = '\0';
			galo.setState(Rooster::state::STOPPED);
		}

		//===============================

		if (socket->send(data, 10) != Socket::Done) {
			data[0] = '\0';
			data[5] = '\0';
			data[1] = '\0';
		}
		
		if (socket->receive(data, 10, size) == Socket::Done) {
			galo2move(&galo2, data);
		}

		//==============================
		
		
		//PLAYER 2 CONTROLES

		player = 1;


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
					println("A");
					galo.apanhar(*galo2.ultimateShot, galo2.facingRight);
					galo2.ultimateShot->getHitted = true;
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
				else {
					println("A");
					galo2.apanhar(*galo.ultimateShot, galo.facingRight);
					galo.ultimateShot->getHitted = true;
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


		galo.bar->draw(window);
		galo2.bar->draw(window);

		galo.show(*window);
		galo2.show(*window);

		mainPartSystem.update();
		mainPartSystem.draw(*window);

		if (galo.gethp() < 0) {

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


		//exp->update();
		//exp->draw(*window);

		data[0] = '\0';
		data[5] = '\0';
		window->display();
	}



}



#endif