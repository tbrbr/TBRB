
#include <SFML/Graphics.hpp>


using namespace sf;

int muitoJogadores(RenderWindow*, RectangleShape&);
int minigame(RenderWindow*, RectangleShape& );
void selectInput(RenderWindow*, RectangleShape& );

struct WarningBox {
public:
	RectangleShape warning;
	RectangleShape Y;
	RectangleShape N;
	
	Font f;
	Text t;
	Text t2;
	Text ty;
	Text tn;
	bool isVisible = false;

	WarningBox() {

		t.setFillColor(Color::Red);
		t2.setFillColor(Color::Red);
		ty.setFillColor(Color::Red);
		tn.setFillColor(Color::Red);

		f.loadFromFile("fonts/blops.ttf");
		t.setFont(f);
		t2.setFont(f);
		tn.setFont(f);
		ty.setFont(f);

		warning.setSize(Vector2f(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.45));
		warning.setPosition(SCREEN_WIDTH / 2 - warning.getSize().x / 2, SCREEN_HEIGHT / 2 - warning.getSize().y / 2);
		warning.setFillColor(Color::Black);
		warning.setOutlineColor(Color::Red);
		warning.setOutlineThickness(4);

		t.setCharacterSize(warning.getSize().y * 0.035);
		t2.setCharacterSize(warning.getSize().y * 0.04);
		t.setLineSpacing(warning.getSize().y / 140);

		if (LANG.getLang() == LANGUAGE::PORTUGUESE) {
			t.setString("as mudancas serao aplicadas na\nproxima vez que o jogo for aberto");
			t2.setString("Deseja continuar");
		}
		if (LANG.getLang() == LANGUAGE::ENGLISH) {
			t.setString("as mudancas serao aplicadas na\nproxima vez que o jogo for aberto");
			t2.setString("Deseja continuar");
		}


		tn.setCharacterSize(warning.getSize().y * 0.06);
		tn.setString(LANG.getLine(LANGUAGE::NO));

		ty.setCharacterSize(warning.getSize().y * 0.06);
		ty.setString(LANG.getLine(LANGUAGE::YES));

		Y.setSize(Vector2f(warning.getSize().x * 0.15, warning.getSize().y * 0.2));
		N.setSize(Vector2f(warning.getSize().x * 0.15, warning.getSize().y * 0.2));

		N.setPosition(Vector2f(warning.getSize().x + warning.getPosition().x - (tn.getGlobalBounds().width) - warning.getSize().x * 0.2, warning.getSize().y * 0.7 + warning.getPosition().y));
		Y.setPosition(Vector2f(warning.getSize().x * 0.2 + warning.getPosition().x, warning.getSize().y * 0.7 + warning.getPosition().y));

		t.setPosition(warning.getPosition().x + warning.getSize().x * 0.07, warning.getPosition().y + warning.getSize().y * 0.2);
		t2.setPosition(warning.getPosition().x + warning.getSize().x / 2 - t2.getGlobalBounds().width / 2, t.getPosition().y + t.getGlobalBounds().height + warning.getSize().y * 0.1);

		tn.setPosition(N.getPosition().x + N.getSize().x / 2 - N.getGlobalBounds().width / 2, N.getPosition().y + N.getSize().y / 2 - N.getGlobalBounds().height / 2);
		ty.setPosition(Y.getPosition().x + Y.getSize().x / 2 - Y.getGlobalBounds().width / 2, Y.getPosition().y + Y.getSize().y / 2 - Y.getGlobalBounds().height / 2);

	}

	void draw(RenderWindow* window) {
		if (isVisible) {
			window->draw(warning);
			window->draw(ty);
			window->draw(tn);
			window->draw(t);
			window->draw(t2);
		}
	}

	int checkColision(RenderWindow * window) {
		if (ButtonCheck::isButtonComMouseNele(this->N, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
			return -1;
		}

		if (ButtonCheck::isButtonComMouseNele(this->Y, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
			return 1;
		}

		return 0;
	}

	void changeButtonColor(RenderWindow * window) {
		if (ButtonCheck::isButtonComMouseNele(this->N, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
			this->tn.setFillColor(Color::Color(64, 14, 24));
			return;
		}
		if (ButtonCheck::isButtonComMouseNele(this->Y, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
			this->ty.setFillColor(Color::Color(64, 14, 24));
			return;
		}

		this->tn.setFillColor(Color::Red);
		this->ty.setFillColor(Color::Red);
	}

	void updateText() {

		//t.setString(LANG.getLine(LANGUAGE::RESTART_GAME));


		tn.setString(LANG.getLine(LANGUAGE::NO));
		ty.setString(LANG.getLine(LANGUAGE::YES));
	}

};

void selectLang(RenderWindow* window, RectangleShape& background) {
	Text* t[3];
	Font font;
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");


	Text title(LANG.getLine(LANGUAGE::SETTINGS), titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);


	t[0] = new Text("English", font, SCREEN_HEIGHT / 30);
	t[1] = new Text("Portugays", font, SCREEN_HEIGHT / 30);
	t[2] = new Text(LANG.getLine(LANGUAGE::BACK), font, SCREEN_HEIGHT / 30);

	int textXPosition = SCREEN_WIDTH * 0.6;
	int textyPosition = SCREEN_HEIGHT * 0.5;

	for (int i = 0; i < 3; i++) {
		t[i]->setPosition(textXPosition, textyPosition);
		t[i]->setFillColor(Color::Red);
		textyPosition = textyPosition + SCREEN_HEIGHT * 0.10;
	}


	RectangleShape divs[3];
	for (int i = 0; i < 3; i++) {
		divs[i].setPosition(t[i]->getPosition().x, t[i]->getPosition().y - t[i]->getGlobalBounds().height / 2);
		divs[i].setSize(Vector2f(t[i]->getGlobalBounds().width, t[i]->getGlobalBounds().height * 2));
		divs[i].setFillColor(Color::Transparent);
	}

	
	WarningBox warning;

	while (window->isOpen()) {
		int __temp = -1;
		if(!warning.isVisible)
			__temp = ButtonCheck::checkButtonHover(divs, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y, 0, 2);

		Event e;

		while (window->pollEvent(e)) {
			if (e.type == Event::Closed) {
				window->close();
			}

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Escape) {
					return;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {
						if (__temp == 0) {
							warning.isVisible = true;
							LANG.update(LANGUAGE::ENGLISH);
						}
						else if (__temp == 1) {
							warning.isVisible = true;
							LANG.update(LANGUAGE::PORTUGUESE);
						}
						else if (__temp == 2) {
							for (int i = 0; i < 3; i++) {
								delete t[i];
							}
							return;
						}
						warning.updateText();
					}

					if (warning.isVisible) {
						int a = warning.checkColision(window);
						if (a == 1) {
							warning.isVisible = false;
						}
						else if (a == -1) {
							LANG.update((LANGUAGE::Lang)LANG.getLastLang());
							warning.isVisible = false;
						}
					}
				}
			}
		}

		warning.changeButtonColor(window);

		if (__temp != -1) {
			for (int i = 0; i < 3; i++) {
				if (__temp != i)
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
		window->draw(title);

		for (int i = 0; i < 3; i++) {
			window->draw(*t[i]);
			window->draw(divs[i]);
		}

		warning.draw(window);

		window->display();

	}


}

int configScreen(RenderWindow* window, RectangleShape& background) {


	// Com sua licença vou tentar adicionar um menu para os keybinds

	const int optionNum = 4;

	Text* t[optionNum];
	Font font;
	Font titleFont;

	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");


	Text title(LANG.getLine(LANGUAGE::SETTINGS), titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);


	float textSize = SCREEN_HEIGHT / 30;
	t[0] = new Text(LANG.getLine(LANGUAGE::SELECT_LANG), font, textSize);
	t[1] = new Text("INPUT", font, textSize);
	t[2] = new Text("KEYBINDINGS", font, textSize);
	t[3] = new Text(LANG.getLine(LANGUAGE::BACK), font, textSize);
	

	int textXPosition = SCREEN_WIDTH * 0.6;
	int textyPosition = SCREEN_HEIGHT * 0.5;

	for (int i = 0; i < optionNum; i++) {
		t[i]->setPosition(textXPosition, textyPosition);
		t[i]->setFillColor(Color::Red);
		textyPosition = textyPosition + SCREEN_HEIGHT * 0.10;
	}


	RectangleShape divs[optionNum];
	for (int i = 0; i < optionNum; i++) {
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
					return MENU_PRINCIPAL;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {
						if (__temp == 0) {		
							selectLang(window, background);
						}
						else if (__temp == 1) {
							selectInput(window, background);
						}
						else if (__temp == 2) {
							mapeamento(window);
						}
						else if (__temp == 3)
						{
							for (int i = 0; i < optionNum; i++) {
								delete t[i];
							}
							return MENU_PRINCIPAL;
						}
					}
				}
			}
		}

		if (__temp != -1) {
			for (int i = 0; i < optionNum; i++) {
				if (__temp != i)
					t[i]->setFillColor(Color::Red);
				else
					t[__temp]->setFillColor(Color::Color(64, 14, 24));
			}

		}
		else {
			for (int i = 0; i < optionNum; i++) {
				t[i]->setFillColor(Color::Red);
			}
		}

		window->clear();
		window->draw(background);
		window->draw(title);

		for (int i = 0; i < optionNum; i++) {
			window->draw(*t[i]);
			window->draw(divs[i]);
		}
		window->display();

	}


}

int selecionarModo(RenderWindow * window, RectangleShape & background) {

	

	Text* t[4];

	Font font;
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");


	Text title(LANG.getLine(LANGUAGE::MODE), titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);


	t[0] = new Text(LANG.getLine(LANGUAGE::SINGLE), font, SCREEN_HEIGHT / 30);
	t[1] = new Text(LANG.getLine(LANGUAGE::MULTI), font, SCREEN_HEIGHT / 30);
	t[2] = new Text(LANG.getLine(LANGUAGE::MINI), font, SCREEN_HEIGHT / 30);
	t[3] = new Text(LANG.getLine(LANGUAGE::BACK), font, SCREEN_HEIGHT / 30);

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
					return MENU_PRINCIPAL;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {

						if (__temp == 0) {
							mode = SINGLE;
							return Rooster::SELECTION_SINGLE_FALIDA;
						}
						else if (__temp == 1) {
							return MULTI;

						}
						else if (__temp == 2) {
							return MINIGAME;
						}
						else if (__temp == 3) {
							return MENU_PRINCIPAL;
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

int MenuPrincipal(RenderWindow * window, RectangleShape& background) {
	
	window->setMouseCursorVisible(true);
	
	
	Font font;
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");

	Text title(LANG.getLine(LANGUAGE::MAIN_MENU), titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);
	Text* t[3];
	

	t[0] = new Text(LANG.getLine(LANGUAGE::START), font, SCREEN_HEIGHT / 30);
	t[1] = new Text(LANG.getLine(LANGUAGE::SETTINGS), font, SCREEN_HEIGHT / 30);
	t[2] = new Text(LANG.getLine(LANGUAGE::QUIT), font, SCREEN_HEIGHT / 30);

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
							return CONFIG;
						}
						else if(__temp == 0) {
							return GAMEMODE;
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

int minigame(RenderWindow* window, RectangleShape& background) {
	Text* t[3];
	Font font;
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");


	Text title(LANG.getLine(LANGUAGE::MODE), titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);


	t[0] = new Text("Pato's Game", font, SCREEN_HEIGHT / 30);
	t[1] = new Text("Arrocha's Tiles", font, SCREEN_HEIGHT / 30);
	t[2] = new Text(LANG.getLine(LANGUAGE::BACK), font, SCREEN_HEIGHT / 30);

	int textXPosition = SCREEN_WIDTH * 0.6;
	int textyPosition = SCREEN_HEIGHT * 0.5;

	for (int i = 0; i < 3; i++) {
		t[i]->setPosition(textXPosition, textyPosition);
		t[i]->setFillColor(Color::Red);
		textyPosition = textyPosition + SCREEN_HEIGHT * 0.10;
	}


	RectangleShape divs[3];
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
					return GAMEMODE;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {

						if (__temp == 0) {
							return ISPATOTIME;
						}
						else if (__temp == 1) {
							return BOTAPRAARROCHAR;
						}
						else if (__temp == 2) {
							for (int i = 0; i < 3; i++) {
								delete t[i];
							}
							return GAMEMODE;
						}

					}
				}
			}
		}

		if (__temp != -1) {
			for (int i = 0; i < 3; i++) {
				if (__temp != i)
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
		window->draw(title);

		for (int i = 0; i < 3; i++) {
			window->draw(*t[i]);
			window->draw(divs[i]);
		}
		window->display();

	}
}

int multoJogadoresMode(RenderWindow* window, RectangleShape& background) {
	Text* t[3];

	Font font;
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");


	Text title(LANG.getLine(LANGUAGE::MODE), titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);


	t[0] = new Text("CREATE", font, SCREEN_HEIGHT / 30);
	t[1] = new Text("JOIN", font, SCREEN_HEIGHT / 30);
	t[2] = new Text(LANG.getLine(LANGUAGE::BACK), font, SCREEN_HEIGHT / 30);

	int textXPosition = SCREEN_WIDTH * 0.6;
	int textyPosition = SCREEN_HEIGHT * 0.5;

	for (int i = 0; i < 3; i++) {
		t[i]->setPosition(textXPosition, textyPosition);
		t[i]->setFillColor(Color::Red);
		textyPosition = textyPosition + SCREEN_HEIGHT * 0.10;
	}


	RectangleShape divs[3];
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
					return MULTI;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {

						if (__temp == 0) {
							return CREATE;
						}
						else if (__temp == 1) {
							return JOIN;
						}
						else if (__temp == 2) {
							for (int i = 0; i < 3; i++) {
								delete t[i];
							}
							return MULTI;
						}

					}
				}
			}
		}

		if (__temp != -1) {
			for (int i = 0; i < 3; i++) {
				if (__temp != i)
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
		window->draw(title);

		for (int i = 0; i < 3; i++) {
			window->draw(*t[i]);
			window->draw(divs[i]);
		}
		window->display();

	}
}

int muitoJogadores(RenderWindow* window, RectangleShape& background) {
	Text* t[3];

	Font font;
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");


	Text title(LANG.getLine(LANGUAGE::MODE), titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);


	t[0] = new Text("LOCAL", font, SCREEN_HEIGHT / 30);
	t[1] = new Text("ONLINE", font, SCREEN_HEIGHT / 30);
	t[2] = new Text(LANG.getLine(LANGUAGE::BACK), font, SCREEN_HEIGHT / 30);

	int textXPosition = SCREEN_WIDTH * 0.6;
	int textyPosition = SCREEN_HEIGHT * 0.5;

	for (int i = 0; i < 3; i++) {
		t[i]->setPosition(textXPosition, textyPosition);
		t[i]->setFillColor(Color::Red);
		textyPosition = textyPosition + SCREEN_HEIGHT * 0.10;
	}


	RectangleShape divs[3];
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
					return GAMEMODE;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {

						if (__temp == 0) {
							mode = LOCAL;
							return Rooster::SELECTION;
						}
						else if (__temp == 1) {
							mode = LAN;
							return MULTI_MODE;
						}
						else if (__temp == 2) {
							return GAMEMODE;
						}
						
					}
				}
			}
		}

		if (__temp != -1) {
			for (int i = 0; i < 3; i++) {
				if (__temp != i)
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
		window->draw(title);

		for (int i = 0; i < 3; i++) {
			window->draw(*t[i]);
			window->draw(divs[i]);
		}
		window->display();

	}

}


#define MOVE 0
#define STRONG 1
#define LIGHT 2
#define DANCE 3

void vendoCelta(RectangleShape * icons, Texture * textures, int player) {



	if (player == 0) {
		if (mainInput.p1Hud == 0) {

			textures[STRONG].loadFromFile("controlsIcons/g.png");
			textures[LIGHT].loadFromFile("controlsIcons/f.png");

		}

		else if (mainInput.p1Hud == 1) {
			textures[STRONG].loadFromFile("controlsIcons/mrb.png");
			textures[LIGHT].loadFromFile("controlsIcons/mlb.png");
		}
		textures[MOVE].loadFromFile("controlsIcons/wasd.png");
		textures[DANCE].loadFromFile("controlsIcons/q.png");

		for (int i = 0; i < 4; i++)
		{
			icons[i].setTexture(textures + i);
		}
	}

	else
	{
		if (mainInput.p2Hud == 0) {

			textures[STRONG].loadFromFile("controlsIcons/k.png");
			textures[LIGHT].loadFromFile("controlsIcons/l.png");

		}
		textures[MOVE].loadFromFile("controlsIcons/setas.png");
		textures[DANCE].loadFromFile("controlsIcons/p.png");

		for (int i = 0; i < 4; i++)
		{
			icons[i].setTexture(textures + i);
		}
	}
}

void controle(RenderWindow * window) {

	RectangleShape fundo;
	Texture tfundo;
	tfundo.loadFromFile("controlsIcons/controle.png");
	fundo.setSize((Vector2f)window->getSize());
	fundo.setTexture(&tfundo);

	
	Font f;
	f.loadFromFile("fonts/blops.ttf");

	RectangleShape back;
	Vector2f btnsize;
	Vector2f btnpos;

	btnsize.x = window->getSize().x * 0.2;
	btnsize.y = window->getSize().y * 0.1;

	btnpos.x = window->getSize().x / 2 - btnsize.x / 2;
	btnpos.y = window->getSize().y * 0.8;

	back.setSize(btnsize);
	back.setPosition(btnpos);
	back.setFillColor(Color::Black);
	back.setOutlineColor(Color::Red);
	back.setOutlineThickness(3);


	Text _back(LANG.getLine(LANGUAGE::BACK), f, SCREEN_HEIGHT / 40);

	_back.setFillColor(Color::Red);
	_back.setPosition(back.getPosition().x + back.getSize().x / 2 - _back.getGlobalBounds().width / 2, back.getPosition().y + back.getSize().y / 2 - _back.getGlobalBounds().height / 2);



	while (window->isOpen())
	{
		Event e;
		while (window->pollEvent(e) ){
			if (e.type == Event::Closed) {
				window->close();
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (ButtonCheck::isButtonComMouseNele(back, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
				return;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return;
		}
		window->clear();
		window->draw(fundo);
		window->draw(back);
		window->draw(_back);
		window->display();
	}
}
void updateInput(RenderWindow* window, RectangleShape& background, int player) {
	println(mainInput.gethudslected());
	if (mainInput.p1Hud == 2 && player == 1) {
		controle(window);
		return;
	}
	RectangleShape icons[4];
	Texture textures[4];
	vendoCelta(icons, textures, player);

	Vector2f size;
	Vector2f pos;

	size.x = window->getSize().x * 0.08;
	size.y = window->getSize().y * 0.1;

	for (int i = 0; i < 4; i++) {
		icons[i].setSize(size);
		
	}
	icons[MOVE].setSize(Vector2f(size.x * 3, size.y * 3));

	pos.x = window->getSize().x * 0.2;
	pos.y = window->getSize().y * 0.15;

	for (int i = 0; i < 4; i++) {
		icons[i].setPosition(pos);
		
		pos.y = icons[i].getSize().y + icons[i].getPosition().y + window->getSize().y * 0.03;
	}

	icons[MOVE].move(-size.x, 0);

	Font f;
	f.loadFromFile("fonts/blops.ttf");
	Text b[4];

	Vector2f tpos;
	tpos.x = window->getSize().x * 0.4;

	b[0].setString("MOVE");
	b[1].setString("STRONG ATTACK");
	b[2].setString("LIGHT ATTACK");
	b[3].setString("DANCE");

	for (int i = 0; i < 4; i++) {
		b[i].setCharacterSize(window->getSize().y / 40);
		b[i].setFont(f);
		b[i].setPosition(tpos.x, icons[i].getPosition().y + icons[i].getSize().y / 2);
	}
	
	RectangleShape mouse;
	RectangleShape back;
	Vector2f btnsize;
	Vector2f btnpos;

	btnsize.x = window->getSize().x * 0.2;
	btnsize.y = window->getSize().y * 0.1;

	btnpos.x = window->getSize().x * 0.7;
	btnpos.y = window->getSize().y * 0.5;


	mouse.setSize(btnsize);
	back.setSize(btnsize);

	mouse.setPosition(btnpos);
	back.setPosition(btnpos.x, btnpos.y + btnsize.y * 1.5);

	mouse.setFillColor(Color::Black);
	back.setFillColor(Color::Black);

	mouse.setOutlineColor(Color::Red);
	back.setOutlineColor(Color::Red);

	mouse.setOutlineThickness(3);
	back.setOutlineThickness(3);
	string mode = "MOUSE";
	if (mainInput.p1Hud == 0) {
		mode = "KEYBOARD";
	}
	Text _mouse("MOUSE", f, SCREEN_HEIGHT / 40);
	Text _back(LANG.getLine(LANGUAGE::BACK), f, SCREEN_HEIGHT / 40);

	_mouse.setFillColor(Color::Red);
	_back.setFillColor(Color::Red);

	_mouse.setPosition(mouse.getPosition().x + mouse.getSize().x / 2 - _mouse.getGlobalBounds().width / 2, mouse.getPosition().y + mouse.getSize().y / 2 - _mouse.getGlobalBounds().height / 2);
	_back.setPosition(back.getPosition().x + back.getSize().x / 2 - _back.getGlobalBounds().width / 2, back.getPosition().y + back.getSize().y / 2 - _back.getGlobalBounds().height / 2);



	while (window->isOpen()) {
		Event e;
		int mousex = Mouse::getPosition(*window).x;
		int mousey = Mouse::getPosition(*window).y;
		while (window->pollEvent(e)) {
			if (e.type == Event::Closed) {
				window->close();
			}

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Escape) {
					return;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {
					if (player == 0)
						if (ButtonCheck::isButtonComMouseNele(mouse, mousex, mousey)) {
							if (mainInput.p1Hud == 0) {
								mainInput.p1Hud = 1;
								vendoCelta(icons, textures, player);

								mode = "MOUSE";
								if (mainInput.p1Hud == 0) {
									mode = "KEYBOARD";
								}
								_mouse.setString(mode);
								_mouse.setPosition(mouse.getPosition().x + mouse.getSize().x / 2 - _mouse.getGlobalBounds().width / 2, mouse.getPosition().y + mouse.getSize().y / 2 - _mouse.getGlobalBounds().height / 2);
							}
							else if (mainInput.p1Hud == 1) {
								mainInput.p1Hud = 0;
								vendoCelta(icons, textures, player);

								mode = "MOUSE";
								if (mainInput.p1Hud == 0) {
									mode = "KEYBOARD";
								}
								_mouse.setString(mode);
								_mouse.setPosition(mouse.getPosition().x + mouse.getSize().x / 2 - _mouse.getGlobalBounds().width / 2, mouse.getPosition().y + mouse.getSize().y / 2 - _mouse.getGlobalBounds().height / 2);
							}
						}
				}
			}

			
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (ButtonCheck::isButtonComMouseNele(back, mousex, mousey)) {
				return;
			}

			
		}



	window->clear(Color::Black);
	if(mainInput.gethudslected() != 2)
		for (int i = 0; i < 4; i++) {
			window->draw(icons[i]);
			window->draw(b[i]);

		}
	if (player == 0)
	window->draw(mouse);

		window->draw(back);
		if (player == 0)
	window->draw(_mouse);

		window->draw(_back);
		window->display();
	}

}

void selectInput(RenderWindow * window, RectangleShape & background) {

	Text* t[3];

	Font font;
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");


	Text title("INPUT", titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);


	t[0] = new Text("PLAYER 1", font, SCREEN_HEIGHT / 30);
	t[1] = new Text("PLAYER 2", font, SCREEN_HEIGHT / 30);
	t[2] = new Text(LANG.getLine(LANGUAGE::BACK), font, SCREEN_HEIGHT / 30);

	int textXPosition = SCREEN_WIDTH * 0.6;
	int textyPosition = SCREEN_HEIGHT * 0.5;

	for (int i = 0; i < 3; i++) {
		t[i]->setPosition(textXPosition, textyPosition);
		t[i]->setFillColor(Color::Red);
		textyPosition = textyPosition + SCREEN_HEIGHT * 0.10;
	}


	RectangleShape divs[3];
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
					return;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {
						if (__temp == 2)
						{
							for (int i = 0; i < 2; i++) {
								delete t[i];
							}
							return;
						}
						else {
							updateInput(window, background, __temp);
						}
					}
				}
			}
		}

		if (__temp != -1) {
			for (int i = 0; i < 3; i++) {
				if (__temp != i)
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
		window->draw(title);

		for (int i = 0; i < 3; i++) {
			window->draw(*t[i]);
			window->draw(divs[i]);
		}
		window->display();

	}


}