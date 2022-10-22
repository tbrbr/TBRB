
#include <SFML/Graphics.hpp>


using namespace sf;

int selecionarModo(RenderWindow * window, RectangleShape & background, Text & title) {

	

	Text* t[4];
	Font font;
	font.loadFromFile("fonts/blops.ttf");


	t[0] = new Text("SINGLEPLAYER", font, SCREEN_HEIGHT / 30);
	t[1] = new Text("MULTIPLAYER", font, SCREEN_HEIGHT / 30);
	t[2] = new Text("MINIGAMES", font, SCREEN_HEIGHT / 30);
	t[3] = new Text("BACK", font, SCREEN_HEIGHT / 30);

	int textXPosition = SCREEN_WIDTH * 0.6;
	int textyPosition = SCREEN_HEIGHT * 0.5;

	for (int i = 0; i < 4; i++) {
		t[i]->setPosition(textXPosition, textyPosition);
		t[i]->setFillColor(Color::Red);
		textyPosition = textyPosition + SCREEN_HEIGHT * 0.10;
	}


	RectangleShape divs[4];
	for (int i = 0; i < 4; i++) {
		divs[i].setPosition(t[i]->getPosition().x, t[i]->getPosition().y - t[i]->getGlobalBounds().height / 2);
		divs[i].setSize(Vector2f(t[i]->getGlobalBounds().width, t[i]->getGlobalBounds().height * 2));
		divs[i].setFillColor(Color::Transparent);
	}



	while (window->isOpen()) {
		int __temp = ButtonCheck::checkButtonHover(divs, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y, 0, 3);
		Event e;

		while (window->pollEvent(e)) {
			if (e.type == Event::Closed) {
				window->close();
			}

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Escape) {
					return -1;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {

						if (__temp == 0) {
							return Rooster::UMJOGADORES;;
						}
						else if (__temp == 1) {
							return Rooster::UMJOGADORES;
						}
						else if (__temp == 2) {
							return Rooster::ISPATOTIME;
						}
						else if (__temp == 3) {
							return -1;
						}
					}
				}
			}
		}

		if (__temp != -1) {
			for (int i = 0; i < 4; i++) {
				if (__temp != i)
					t[i]->setFillColor(Color::Red);
				else
					t[__temp]->setFillColor(Color::Color(64, 14, 24));
			}

		}
		else {
			for (int i = 0; i < 4; i++) {
					t[i]->setFillColor(Color::Red);
			}
		}

		window->clear();
		window->draw(background);
		window->draw(title);
	
		for (int i = 0; i < 4; i++) {
			window->draw(*t[i]);
			window->draw(divs[i]);
		}
		window->display();

	}


}

int MenuPrincipal(RenderWindow * window) {
	
	window->setMouseCursorVisible(true);
	Texture background_t;
	RectangleShape background(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	background.setPosition(0, 0);
	background_t.loadFromFile("sprites/background_menu.png");

	background.setTexture(&background_t);

	Font font;
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");

	Text title("MAIN MENU", titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);
	Text* t[3];
	

	t[0] = new Text("Start", font, SCREEN_HEIGHT / 30);
	t[1] = new Text("Settings", font, SCREEN_HEIGHT / 30);
	t[2] = new Text("Quit", font, SCREEN_HEIGHT / 30);

	RectangleShape divs[3];

	int textXPosition = SCREEN_WIDTH * 0.6;
	int textyPosition = SCREEN_HEIGHT * 0.5;

	for (int i = 0; i < 3; i++) {
		t[i]->setPosition(textXPosition, textyPosition);
		t[i]->setFillColor(Color::Red);
		textyPosition = textyPosition + SCREEN_HEIGHT * 0.10;
	}
	

	for (int i = 0; i < 3; i++) {
		divs[i].setPosition(t[i]->getPosition().x, t[i]->getPosition().y - t[i]->getGlobalBounds().height / 2);
		divs[i].setSize(Vector2f(t[i]->getGlobalBounds().width, t[i]->getGlobalBounds().height * 2));
		divs[i].setFillColor(Color::Transparent);
	}



	while (window->isOpen()) {
		int __temp = ButtonCheck::checkButtonHover(divs, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y, 0, 2);
		Event e;
		while (window->pollEvent(e)) {
			if (e.type == Event::Closed) {
				window->close();
			}

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Escape) {
					window->close();
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {

						if (__temp == 2) {
							window->close();
						}
						else if (__temp == 1) {
							window->close();
						}
						else if(__temp == 0) {
							int __op = selecionarModo(window, background, title);
							if (__op != -1) {
								return __op;
							}
						}
					}
				}
			}
		}

		if (__temp != -1) {
			for (int i = 0; i < 3; i++) {
				if(__temp != i)
					t[i]->setFillColor(Color::Red);
				else
					t[__temp]->setFillColor(Color::Color(64, 14, 24));
			}
		
		}
		else {
			for (int i = 0; i < 3; i++) {
				t[i]->setFillColor(Color::Red);
			}
		}

		window->clear();
		window->draw(background);
		for (int i = 0; i < 3; i++) {
			window->draw(*t[i]);
			window->draw(divs[i]);
		}
		window->draw(title);
		window->display();

	}


}