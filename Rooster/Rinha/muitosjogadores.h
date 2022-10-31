#ifndef VASCO_DA_GAMA
#define VASCO_DA_GAMA

#include <functional> 

bool ishost = false;

void galo2control(Galo** galo, TcpSocket * socket) {

	char data[10];
	size_t size;

	IpAddress ip;
	unsigned short port;
	socket->setBlocking(false);

	while (1) {


		//socket->receive(data, sizeof(data), size, ip, port);

		cout << data << endl;
		if (data[0] == 'w') {
			galo[0]->jump();
		}
	}

}



void multiPlayer(RenderWindow* window, Galo& galo, Galo & galo2, int& option, RectangleShape fundo) {
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

	TcpSocket socket;
	socket.setBlocking(false);
	TcpListener listener;
	IpAddress ip = "10.50.208.56";

	if (ishost) {
		listener.listen(59000);
		listener.accept(socket);
	}
	else {
		socket.connect(ip, 59000);
	}

	
	char data[10] = "";
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
			strcpy_s(data, "w");
			galo.jump();
		}
		else if (mainInput.inputState[player][LIGHT_ATTACK][1]) {
			if (mainInput.inputState[player][GODOWN][0]) {
				strcpy_s(data, "j");
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
			strcpy_s(data, "d");
			galo.setState(Rooster::state::RUNNING);
			galo.facingRight = true;
			galo.run();

		}
		else if (mainInput.inputState[player][GOLEFT][0])
		{
			strcpy_s(data, "a");
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

		//===============================

		socket.send(data, 10);
		data[0] = '\0';
		socket.receive(data, 10, size);

		//==============================
		
		//PLAYER 2 CONTROLES

		player = 1;

		if (data[0] == 'w')
		{
			cout << data << endl;
			galo2.jump();
		}

		else if (data[0] == 'j') {
			galo2.lowKick();

		}
		else if (mainInput.inputState[player][STRONG_ATTACK][1]) {
			galo2.especial();
		}



		if (data[0] == 'd')
		{
			galo2.setState(Rooster::state::RUNNING);
			galo2.facingRight = true;
			galo2.run();

		}
		else if (data[0] == 'a')
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
		window->display();
	}
}
void multiPlayer(RenderWindow* window, Galo& galo, Galo* galo2, int& option, RectangleShape fundo) {

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

	//=================================================================

	UdpSocket socket;
	unsigned short port = 59000;
	IpAddress ip = IpAddress::getLocalAddress();

	socket.bind(port);
	socket.setBlocking(false);
	char data[10];
	size_t size;

	//=================================================================
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
		}

		//options p1


		int player = 0;

		if (mainInput.inputState[player][GOUP][1])
		{
			strcpy_s(data, "w");
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



		if (mainInput.inputState[player][GORIGHT][1])
		{
			galo.setState(Rooster::state::RUNNING);
			galo.facingRight = true;
			galo.run();

		}
		else if (mainInput.inputState[player][GOLEFT][1])
		{
			galo.setState(Rooster::state::RUNNING);
			galo.facingRight = false;
			galo.run();

		}
		else if (mainInput.inputState[player][GODOWN][1])
		{
			galo.defend();
		}
		else
		{
			galo.setState(Rooster::state::STOPPED);

		}

		socket.send(data, 10, ip, port);
		unsigned short port2;
		socket.receive(data, 10, size, ip, port2);

		if (data[0] == 'w') {
			galo2->jump();
		}

		galo.update();

		if (galo.ultimateShot->getHitted) {
			galo.apanharByKalsa(galo2, window);
		}
		else if (galo2->ultimateShot->getHitted) {
			galo2->apanharByKalsa(&galo, window);
		}

		galo.bar->draw(window);
		galo2->bar->draw(window);

		galo.show(*window);

		galo2->show(*window);

		mainPartSystem.update();
		mainPartSystem.draw(*window);

		if (galo.gethp() < 0 || galo2->gethp() < 0) {

			rounds++;
			framesRound = 60;
			galo.sethp(galo.getMaxhp());
			galo2->sethp(galo.getMaxhp());
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