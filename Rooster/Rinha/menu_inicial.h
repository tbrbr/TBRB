
#include <SFML/Graphics.hpp>


using namespace sf;

int muitoJogadores(RenderWindow*, RectangleShape&);
int minigame(RenderWindow* window, RectangleShape& background);

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

Keyboard::Key mapKey(RenderWindow* window) {

	//Caixa de espera vai ser desenhada em brave
	while (window->isOpen())
	{
		Event e;
		if (window->pollEvent(e)) {
			if (e.type == Event::KeyPressed)
			{
				if (e.key.code <= 25)
				{
					return e.key.code;
				}
			}
		}
	}
}

void editComands(RenderWindow* window, RectangleShape& background, int player)
{
#define COMANDS 8
	RectangleShape div[COMANDS];
	Font font;
	Text comands[COMANDS];

	font.loadFromFile("fonts/blops.ttf");

	Vector2f divSize(window->getSize().x * 0.2, window->getSize().y * 0.06);
	Vector2f divPositions(window->getSize().x * 0.2, window->getSize().y * 0.3);

	for (int i = 0; i < COMANDS / 2; i++)
	{
		div[i].setSize(divSize);
		div[i].setPosition(divPositions);
		divPositions.y += divSize.y * 1.5;
	}

	divPositions.x = window->getSize().x * 0.6;
	divPositions.y = window->getSize().y * 0.3;
	for (int i = COMANDS / 2; i < COMANDS; i++)
	{
		div[i].setSize(divSize);
		div[i].setPosition(divPositions);
		divPositions.y += divSize.y * 1.5;
	}

	struct inputInfo mInput;
	struct inputInfo kInput;
	struct inputInfo jInput;

	kInput.type = 0;
	mInput.type = 1;
	jInput.type = 2;

	while (window->isOpen())
	{
		int __temp = ButtonCheck::checkButtonHover(div, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y, 0, COMANDS - 1);
		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window->close();
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {
						if (__temp == 0) {
							mainInput.board[player - 1][GOLEFT][KEYBOARD] = kInput.setKey(mapKey(window));
						}
						else if (__temp == 1)
						{
							editComands(window, background, 1);
						}
						else if (__temp == 2) {
							return;
						}

					}
				}
			}
		}

		window->clear();
		for (int i = 0; i < COMANDS; i++)
		{
			window->draw(div[i]);
		}
		window->display();
	}
	
}

int selectComandos(RenderWindow* window, RectangleShape& background) {
	Text* t[3];
	Font font;
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");


	Text title(LANG.getLine(LANGUAGE::SETTINGS), titleFont, SCREEN_HEIGHT / 13);
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
					return MENU_PRINCIPAL;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {
						if (__temp == 0) {
							editComands(window, background, 1);
						}
						else if (__temp == 1)
						{
							editComands(window, background, 1);
						}
						else if (__temp == 2) {
							for (int i = 0; i < 3; i++) {
								delete t[i];
							}
							return 0;
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
			for (int i = 0; i < 2; i++) {
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

int configScreen(RenderWindow* window, RectangleShape& background) {
	Text* t[3];
	Font font;
	Font titleFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");


	Text title(LANG.getLine(LANGUAGE::SETTINGS), titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);


	t[0] = new Text(LANG.getLine(LANGUAGE::SELECT_LANG), font, SCREEN_HEIGHT / 30);
	t[1] = new Text("COMANDS", font, SCREEN_HEIGHT / 30);
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
					return MENU_PRINCIPAL;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					if (__temp != -1) {
						if (__temp == 0) {		
							selectLang(window, background);
						}
						else if (__temp == 1)
						{
							int a = selectComandos(window, background);
						}
						else if (__temp == 2) {
							for (int i = 0; i < 3; i++) {
								delete t[i];
							}
							return MENU_PRINCIPAL;
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
			for (int i = 0; i < 2; i++) {
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
							return Rooster::SELECTION;
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
					return -1;
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