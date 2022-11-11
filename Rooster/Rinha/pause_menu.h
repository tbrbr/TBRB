#ifndef BAYERN_DE_MUNIQUE_8__2__BARCELONA
#define BAYERN_DE_MUNIQUE_8__2__BARCELONA
#include <SFML/Graphics.hpp>
class Pause {

	static bool updateoption(float xspeed, float yspeed, RectangleShape* option) {
		option->move(xspeed, yspeed);
		if (yspeed > 0) {
			if (option->getPosition().y > 0) {
				option->setPosition(0, 0);
			}
		}
		return option->getPosition().y == 0;
	}

public:
	

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
		body.setFillColor(Color::Transparent);

		int lineSpace = body.getSize().y * 0.05;

		for (int i = 0; i < 3; i++) {
			options[i].setFillColor(Color::Transparent);
			options[i].setOutlineColor(Color::Green);
			options[i].setOutlineThickness(4);
			(options + i)->setSize(Vector2f(body.getSize().x * 0.5, body.getSize().y * 0.2));
			(options + i)->setPosition(body.getPosition().x + body.getSize().x / 2 - (options + i)->getSize().x / 2, body.getPosition().y + (i > 0 ? -body.getPosition().y + (options - 1 + i)->getPosition().y + (options - 1 + i)->getSize().y + lineSpace : body.getSize().y * 0.15));
		}

		Font f;
		f.loadFromFile("fonts/blops.ttf");
		
		Text t[3];
		t[0].setString("RESUME");
		t[1].setString("OPTIONS");
		t[2].setString("QUIT");

		for (int i = 0; i < 3; i++)
		{
			t[i].setCharacterSize(SCREEN_HEIGHT / 30);
			t[i].setFont(f);
			Vector2f position;
			position.x = options[i].getSize().x / 2 + options[i].getPosition().x - t[i].getGlobalBounds().width / 2;
			position.y = options[i].getSize().y / 2 + options[i].getPosition().y - t[i].getGlobalBounds().height / 2;
			t[i].setPosition(position);
		}

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

			window->clear(Color::Black);
			window->draw(background);
			window->draw(body);
			for (int i = 0; i < 3; i++) {
				window->draw(options[i]);
				window->draw(t[i]);
			}
			window->display();
		}

	}


	static int rematchScreen(RenderWindow& window, Galo& winner, Galo& loser, RectangleShape& fundo) {


		Texture __base;
		Texture __filtro;
		Texture __live;
		Texture __logo;
		Texture __opcoes;
		Texture __naoHover;
		Texture __simHover;

		__base.loadFromFile("rematch\\base.png");
		__filtro.loadFromFile("rematch\\filtro.png");
		__live.loadFromFile("rematch\\live.png");
		__logo.loadFromFile("rematch\\logo.png");
		__opcoes.loadFromFile("rematch\\opcoes.png");
		__naoHover.loadFromFile("rematch\\nao.png");
		__simHover.loadFromFile("rematch\\sim.png");


		Vector2f textPosition;
		textPosition.x = window.getSize().x * 0.07;
		textPosition.y = window.getSize().y * 0.805;

		RectangleShape base;
		RectangleShape filtro;
		RectangleShape live;
		RectangleShape logo;
		RectangleShape opcoes;

		Vector2f size((Vector2f)window.getSize());

		base.setTexture(&__base);
		base.setSize(size);
		base.setPosition(size.x, 0);

		Color filtroColor(255, 255, 255, 0);
		filtro.setTexture(&__filtro);
		filtro.setSize(size);
		filtro.setPosition(0, 0);
		filtro.setFillColor(filtroColor);

		live.setTexture(&__live);
		live.setSize(size);
		live.setPosition(size.x, 0);

		logo.setTexture(&__logo);
		logo.setSize(size);
		logo.setPosition(size.x, 0);

		opcoes.setTexture(&__opcoes);
		opcoes.setSize(size);
		opcoes.setPosition(0, size.y * 0.3);

		Vector2f opciosSpeed(0, -30);

		Clock liveClock;
		liveClock.restart();

		bool isVindoAnimation = true;
		Clock vindoAnim;
		vindoAnim.restart();

		float moveFactor = window.getSize().x / 90;
		bool updateOpcoes = false;

		RectangleShape sim;
		RectangleShape nao;

		nao.setPosition(window.getSize().x * 0.37, window.getSize().y * 0.908);

		Vector2f btnSize;
		btnSize.x = window.getSize().x * 0.12;
		btnSize.y = window.getSize().y * 0.08;

		nao.setSize(btnSize);

		sim.setPosition(window.getSize().x * 0.51, window.getSize().y * 0.908);
		sim.setSize(btnSize);

		Text text;
		Font font;
		font.loadFromFile("fonts\\MSSERIF.TTF");
		text.setFont(font);
		text.setCharacterSize(window.getSize().y / 25);
		text.setFillColor(Color::Black);


		text.setPosition(textPosition + base.getPosition());

		std::string galonome = "Galo " + winner.getName();
		std::string a = " derrota o adversário em combate pena a pena";

		text.setString(galonome + a);

		winner.setState(DANCING);

		while (window.isOpen()) {

			int mousex = Mouse::getPosition(window).x;
			int mousey = Mouse::getPosition(window).y;

			Event e;
			while (window.pollEvent(e))
			{
				if (e.type == Event::Closed) {
					window.close();
				}

				if (e.type == Event::KeyPressed)
				{
					if (e.key.code == Keyboard::Enter) {
						return GAMEMODE;
					}
					else if (e.key.code == Keyboard::Escape) {
						if (mode == LOCAL) {
							return UMJOGADORES;
						}
						else {
							return UMJOGADORES;
						}
						
					}
				}

				if (e.type == Event::MouseButtonPressed) {
					if (e.mouseButton.button == Mouse::Left) {
						if (nao.getGlobalBounds().contains(mousex, mousey)) {
							return GAMEMODE;
						}
						else if (sim.getGlobalBounds().contains(mousex, mousey)) {
							if (mode == LOCAL) {
								return UMJOGADORES;
							}
							else {
								return UMJOGADORES;
							}
						}

					}
				}



			}

			if (nao.getGlobalBounds().contains(mousex, mousey)) {
				opcoes.setTexture(&__naoHover);
			}
			else if (sim.getGlobalBounds().contains(mousex, mousey)) {
				opcoes.setTexture(&__simHover);
			}
			else {
				opcoes.setTexture(&__opcoes);
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				printf("X: %f\n", (float)mousex / window.getSize().x);
				printf("Y: %f\n", (float)mousey / window.getSize().y);
			}

			if (isVindoAnimation) {
				if (vindoAnim.getElapsedTime().asMilliseconds() >= 10) {
					if (base.getPosition().x - moveFactor > 0) {
						base.move(-moveFactor, 0);
						live.move(-moveFactor, 0);
						logo.move(-moveFactor, 0);
						text.move(-moveFactor, 0);
					}
					else {
						base.setPosition(0, 0);
						live.setPosition(0, 0);
						logo.setPosition(0, 0);
						text.setPosition(textPosition);
						updateOpcoes = true;
						isVindoAnimation = false;
					}
					if (filtroColor.a < 255) {
						float temp = filtroColor.a + moveFactor / 4;
						filtroColor.a = temp > 255 ? 255 : temp;
						filtro.setFillColor(filtroColor);

					}
					vindoAnim.restart();

				}
			}

			if (updateOpcoes) {
				updateOpcoes = !updateoption(opciosSpeed.x, opciosSpeed.y, &opcoes);
				opciosSpeed.y += 1;
			}
			
			winner.update();
			loser.update();

			window.clear(Color::Black);
			window.draw(fundo);
			window.draw(filtro);
			loser.show(window);
			winner.show(window);
			window.draw(base);
			window.draw(logo);

			if (liveClock.getElapsedTime().asMilliseconds() >= 500) {
				window.draw(live);
				if (liveClock.getElapsedTime().asMilliseconds() >= 1000) {
					liveClock.restart();
				}
			}
			window.draw(text);
			window.draw(opcoes);
			window.display();

		}
	}

};


#endif // !BAYERN_DE_MUNIQUE_8__2__BARCELONA
