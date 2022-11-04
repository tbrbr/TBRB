#ifndef BAYERN_DE_MUNIQUE_8__2__BARCELONA
#define BAYERN_DE_MUNIQUE_8__2__BARCELONA

class Pause {
public:
	//LEMBRAR DE DELETAR OS PONTEIROS
	static int pauseMenu(RenderWindow * window) {

		Texture* texture = new Texture();
		texture->loadFromFile("sprites/borders.png");

		RectangleShape background;
		background.setSize(Vector2f(window->getSize().x, window->getSize().y));
		background.setPosition(0, 0);
		background.setTexture(texture);
		
		RectangleShape body;
		body.setSize(Vector2f(window->getSize().x * 0.7, window->getSize().y * 0.7));
		body.setPosition(window->getSize().x * 0.15, window->getSize().y * 0.15);

		while (window->isOpen()) {
			mainInput.update();
			Event e;

			while (window->pollEvent(e)) {
				if (e.type == Event::Closed) {
					window->close();
				}
			}

			if (mainInput.keyboardState[sf::Keyboard::Escape][1]) {
				return 1;
			}

			window->clear();
			window->draw(background);
			window->draw(body);
			window->display();
			
		}

	}

};


#endif // !BAYERN_DE_MUNIQUE_8__2__BARCELONA
