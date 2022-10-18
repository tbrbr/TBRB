


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
			galo.setHspeed(0);

		}

		//options p2
		if (e.type == Event::KeyPressed) {
			if (e.key.code == Keyboard::Up)
			{
				galo2.jump();
			}
			else if (e.key.code == Keyboard::K) {
				if (e.key.code == Keyboard::Down)
					galo2.lowKick();
				else
					galo2.highKick();
			}
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
			galo2.setHspeed(0);

		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
		
			galo2.highKick();

		}
		galo.update();
		galo2.update();

		if (pointDistance(galo.hitbox.center, galo2.hitbox.center) < galo.hitbox.radius + galo2.hitbox.radius) {
			//cout << "Colidiu" << endl;
		}

		
	

		window->clear();
		

		window->draw(fundo);
		galo.bar->draw(window);
		galo2.bar->draw(window);
		galo.show(*window);
		galo2.show(*window);
		window->display();

	}