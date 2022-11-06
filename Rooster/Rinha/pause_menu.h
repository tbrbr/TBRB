#ifndef BAYERN_DE_MUNIQUE_8__2__BARCELONA
#define BAYERN_DE_MUNIQUE_8__2__BARCELONA
#include <SFML/Graphics.hpp>
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


	static int rematchScreen(RenderWindow* window, Galo& winner, Galo& loser, RectangleShape & fundo, int comboCounter, Clock timeElapsed) {
	
		
		RectangleShape body;
		body.setSize(Vector2f(window->getSize().x * 0.8, window->getSize().y * 0.8));
		body.setPosition(window->getSize().x * 0.1, window->getSize().y * 0.1);
		body.setFillColor(Color::Color(0, 0, 0, 150));
		body.setOutlineThickness(3);
		body.setOutlineColor(Color::Red);

		RectangleShape lines[4];

		int lineSpace = body.getSize().y * 0.15;
		for (int i = 0; i < 4; i++) {
			lines[i].setSize(Vector2f(body.getSize().x * 0.8, 3));
			lines[i].setFillColor(Color::Red);
			(lines + i)->setPosition(body.getPosition().x + body.getSize().x / 2 - (lines + i)->getSize().x / 2, body.getPosition().y + (i > 0 ? -body.getPosition().y + (lines - 1 + i)->getPosition().y + (lines - 1 + i)->getSize().y + lineSpace : body.getSize().y * 0.2));
		}

		
		struct Minute {
			int minute;
			int seconds;
			int milisec;

			Minute() {
				minute = 0;
				seconds = 0;
				milisec = 0;
			}

			void addMinute(int minutes) {
				minute += minutes;
			}

			void addSeconds(int seconds) {
				for (int i = 0; i < seconds; i++) {
					if (this->seconds < 59) {
						this->seconds++;
					}
					else {
						addMinute(1);
						this->seconds = 0;
					}
				}
			}
			void addCen(int c) {
				for (int i = 0; i < c; i++) {
					if (milisec < 999) {
						milisec++;
					}
					else {
						addSeconds(1);
						milisec = 0;
					}
				}
			}

			string to_string() {
				string s = "";
				s += minute > 9 ? std::to_string(minute) : "0" + std::to_string(minute);
				s += ":";
				s += seconds > 9 ? std::to_string(seconds) : "0" + std::to_string(seconds);
				s += ":";
				s += std::to_string(milisec);
				return s;
			}
		};

		Minute minute;
		minute.addCen(timeElapsed.getElapsedTime().asMilliseconds());


		Font f;
		f.loadFromFile("fonts/blops.ttf");

		Text time("TIME", f, SCREEN_HEIGHT / 30);
		Text maxCombo("MAX COMBO", f, SCREEN_HEIGHT / 30);
		
		


		winner.setState(DANCING);

		while (window->isOpen()) {

			window->clear();

			Event e;
			mainInput.update();
			while (window->pollEvent(e))
			{
				if (e.type == Event::Closed)
				{
					window->close();
				}

				if (mainInput.keyboardState[Keyboard::Space][1]) {
					return 0;
				}
			}

			winner.update();
			loser.update();

			window->clear();

			window->draw(fundo);
			
			winner.show(*window);
			loser.show(*window);

			window->draw(body);
			for (int i = 0; i < 4; i++) {
				window->draw(lines[i]);
			}
			window->display();

		}
	}




};


#endif // !BAYERN_DE_MUNIQUE_8__2__BARCELONA
