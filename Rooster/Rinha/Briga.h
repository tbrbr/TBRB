


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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			galo.setState(Rooster::state::RUNNING);
			galo.facingRight = true;
			galo.animRun();

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			galo.setState(Rooster::state::RUNNING);
			galo.facingRight = false;
			galo.animRun();

		}
		else
		{
			galo.setState(Rooster::state::STOPPED);
			galo.setHspeed(0);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			galo.animJump();
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			galo.LightAttack();
			galo.isLightAttack = true;
			galo.apanhar(2);
			galo2.apanhar(1);
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