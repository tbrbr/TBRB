


	void singlePlayer(RenderWindow* window, Galo& galo, Galo& galo2, int& option,RectangleShape fundo) {

		
		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window->close();
			}
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
		}

		//options p1
		
		if ( keyboardState[Keyboard::W][1])
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
		else if ((keyboardState[Keyboard::G][1])){
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
		

		//options p2

		if (keyboardState[Keyboard::Up][1])
		{
			galo2.jump();
		}
		else if (keyboardState[Keyboard::K][1]) {
			if (keyboardState[Keyboard::Down][0]) {
				galo2.lowKick();

			}
			else
				galo2.highKick();

		}
		else if ((keyboardState[Keyboard::L][1])) {
			galo2.especial();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			galo2.setState(Rooster::state::RUNNING);
			galo2.facingRight = true;
			galo2.run();

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			galo2.setState(Rooster::state::RUNNING);
			galo2.facingRight = false;
			galo2.run();

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{

			galo2.defend();

		}
		else
		{
			galo2.setState(Rooster::state::STOPPED);
			//galo2.setHspeed(0);

		}
		

		for (int i = 0; i < galo.hurtBox.size(); i++) {

			if (galo2.hiKick->CheckCollision(galo.hurtBox[i])) {
				galo.apanhar(*galo2.hiKick, galo2.facingRight);
				
			}
			if (galo2.louKick->CheckCollision(galo.hurtBox[i])) {
				galo.apanhar(*galo2.louKick, galo2.facingRight);

			}
			if (galo2.ultimateShot->CheckCollision(galo.hurtBox[i])) {
				galo.apanhar(*galo2.ultimateShot,galo2.facingRight);

			}
		}
		

		for (int i = 0; i < galo2.hurtBox.size(); i++) {

			if (galo.hiKick->CheckCollision(galo2.hurtBox[i])) {
				galo2.apanhar(*galo.hiKick,galo.facingRight);
				
			}
			if (galo.louKick->CheckCollision(galo2.hurtBox[i])) {
				galo2.apanhar(*galo.louKick,galo.facingRight);
			}
			if (galo.ultimateShot->CheckCollision(galo2.hurtBox[i])) {
				galo2.apanhar(*galo.ultimateShot,galo.facingRight);
			}

		}
		
		

		galo.update();
		
		galo2.update();
		


		window->clear();		
		window->draw(fundo);

		galo.bar->draw(window);
		
		galo2.bar->draw(window);
		
		galo.show(*window);
		
		galo2.show(*window);
		
		window->display();

	}