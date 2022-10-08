#ifndef VASCO_DA_GAMA
#define VASCO_DA_GAMA

void dataDealing(Packet pacotinho) {


}

char* dataDealed(Packet pacotinho) {


}


void  multiplayer(RenderWindow* window, Event& e, Galo& galo,Galo& galo2, int& option,Packet pacote) {


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

	galo.update();

	window->clear();
	RectangleShape fundo(Vector2f(1280, 720));
	fundo.setPosition(0, 0);
	fundo.setFillColor(Color(100, 100, 100));

	window->draw(fundo);
	galo.show(*window);
	window->display();

}



#endif