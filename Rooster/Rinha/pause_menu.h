#ifndef BAYERN_DE_MUNIQUE_8__2__BARCELONA
#define BAYERN_DE_MUNIQUE_8__2__BARCELONA

class Pause {
public:
	//LEMBRAR DE DELETAR OS PONTEIROS
	static int pauseMenu(RenderWindow * window) {

		Texture* texture = new Texture();
		RectangleShape* options = new RectangleShape[3];
		RectangleShape background;
		RectangleShape body;

		texture->loadFromFile("sprites/borders.png");
		
		background.setSize(Vector2f(window->getSize().x, window->getSize().y));
		background.setPosition(0, 0);
		background.setTexture(texture);
		
		body.setSize(Vector2f(window->getSize().x * 0.6, window->getSize().y * 0.6));
		body.setPosition(window->getSize().x * 0.2, window->getSize().y * 0.2);
		
		int lineSpace = body.getSize().y * 0.05;
		for (int i = 0; i < 3; i++) {
			(options + i)->setSize(Vector2f(body.getSize().x * 0.5, body.getSize().y * 0.2));
			(options + i)->setPosition(body.getPosition().x + body.getSize().x / 2 - (options + i)->getSize().x / 2, body.getPosition().y + (i > 0 ? -body.getPosition().y + (options - 1 + i)->getPosition().y + (options - 1 + i)->getSize().y + lineSpace : body.getSize().y * 0.15));
		}
		
		options[0].setFillColor(Color::Green);
		options[1].setFillColor(Color::Red);
		options[2].setFillColor(Color::Yellow);


		while (window->isOpen()) {

			mainInput.update();
			int mousex = Mouse::getPosition(*window).x;
			int mousey = Mouse::getPosition(*window).y;
			Event e;

			while (window->pollEvent(e)) {
				if (e.type == Event::Closed) {
					window->close();
				}
			}

			int i = ButtonCheck::checkButtonHover(options, mousex, mousey, 0, 2);

			if (i != -1) {
				if (mainInput.mouseState[sf::Mouse::Left][1]) {
					if (i == 0) {
						delete texture;
						delete[] options;
						return 1;
					}
					else if (i == 1) {

					}
					else {
						delete texture;
						delete[] options;
						return 0;
					}
				}
			}

			if (mainInput.keyboardState[sf::Keyboard::Escape][1]) {
				delete texture;
				delete[] options;
				return 1;
			}

			window->clear();
			window->draw(background);
			window->draw(body);
			for (int i = 0; i < 3; i++) {
				window->draw(options[i]);
			}
			window->display();
		}

	}


	int rematchScreen(RenderWindow* window, Galo& galo1, Galo& galo2, bool whowins) {

		RectangleShape fundo(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

		Texture texFundo;



		while (window->isOpen()) {

			window->clear();

			Event e;

			while (window->pollEvent(e))
			{
				if (e.type == Event::Closed)
				{
					window->close();
				}

				if (e.type == Event::KeyPressed) {
					if (e.KeyPressed == Keyboard::Escape) {
						window->close();
					}
				}
			}

			window->clear();
			window->display();

		}
	}




};


#endif // !BAYERN_DE_MUNIQUE_8__2__BARCELONA
