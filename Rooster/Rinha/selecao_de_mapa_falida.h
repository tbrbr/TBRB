#ifndef RECLAME_MAIS_DESSA_SELECAO_WALTER_CORNO
#define RECLAME_MAIS_DESSA_SELECAO_WALTER_CORNO

// Deus me perdoe mota, mas a demora pro bot escolher o mapa corroeu a minha alma

#include <SFML/Graphics.hpp>
using namespace sf;


struct Confirm {
	RectangleShape confirmDiv;
	RectangleShape OKbutton;
	RectangleShape cancelButton;
	Text t_ok;
	Text t_x;
	Font f;

	Confirm() {

		f.loadFromFile("fonts\\Act_Of_Rejection.ttf");
		confirmDiv.setSize(Vector2f(SCREEN_WIDTH * 0.23, SCREEN_HEIGHT * 0.08));
		confirmDiv.setPosition(SCREEN_WIDTH / 2 - confirmDiv.getSize().x / 2, SCREEN_HEIGHT * 0.9);

		OKbutton.setSize(Vector2f(confirmDiv.getSize().x * 0.45, confirmDiv.getSize().y));
		cancelButton.setSize(Vector2f(confirmDiv.getSize().x * 0.45, confirmDiv.getSize().y));

		OKbutton.setFillColor(Color::Green);
		cancelButton.setFillColor(Color::Red);

		OKbutton.setPosition(confirmDiv.getPosition());
		cancelButton.setPosition(confirmDiv.getPosition().x + cancelButton.getSize().x + confirmDiv.getSize().x * 0.1, confirmDiv.getPosition().y);

		t_x.setCharacterSize(confirmDiv.getSize().y * 0.85);
		t_x.setString("X");
		t_x.setFont(f);
		t_x.setFillColor(Color::Black);

		t_ok.setCharacterSize(confirmDiv.getSize().y * 0.85);
		t_ok.setString("OK");
		t_ok.setFont(f);
		t_ok.setFillColor(Color::Black);

		t_x.setPosition(cancelButton.getPosition().x + cancelButton.getSize().x / 2 - t_x.getGlobalBounds().width / 2, cancelButton.getPosition().y - 4);
		t_ok.setPosition(OKbutton.getPosition().x + OKbutton.getSize().x / 2 - t_ok.getGlobalBounds().width / 2, cancelButton.getPosition().y - 4);

	}

	void update(RenderWindow* w) {
		if (ButtonCheck::isButtonComMouseNele(OKbutton, Mouse::getPosition(*w).x, Mouse::getPosition(*w).y)) {
			OKbutton.setFillColor(Color::Yellow);
		}
		else {
			OKbutton.setFillColor(Color::Green);
		}

		if (ButtonCheck::isButtonComMouseNele(cancelButton, Mouse::getPosition(*w).x, Mouse::getPosition(*w).y)) {
			cancelButton.setFillColor(Color::Yellow);
		}
		else {
			cancelButton.setFillColor(Color::Red);
		}

	}
	void draw(RenderWindow* window) {
		update(window);
		window->draw(OKbutton);
		window->draw(cancelButton);
		window->draw(t_x);
		window->draw(t_ok);
	}

	int getEvent(RenderWindow* w) {
		if (ButtonCheck::isButtonComMouseNele(OKbutton, Mouse::getPosition(*w).x, Mouse::getPosition(*w).y)) {
			return 1;
		}
		if (ButtonCheck::isButtonComMouseNele(cancelButton, Mouse::getPosition(*w).x, Mouse::getPosition(*w).y)) {
			return 0;
		}
		return -1;
	}
};

class MapSelector {

private:
	static const int num_de_mapas = 3;

	Texture t_maps[num_de_mapas];
	Texture * finalTexture = NULL;
	RectangleShape r_map;

	RectangleShape player1_map_selected;
	RectangleShape player2_map_selected;

	Text text_player1;
	Text text_player2;
	Font font;

	int map_player1 = -1;
	int map_player2 = -1;
	int map = 0;
	int __map = 0;
	bool isp1time = true;
	bool isSinglePlayerSelection;

	RectangleShape arrowL;
	RectangleShape arrowR;
	Texture t_arrow;

	Confirm confirm = Confirm();

	
	bool sorteioAnim = false; //n sei sorteio em ingles
	bool randAnim_ = false; //n sei sorteio em ingles

	void SorteioAnim() {
		static int frame = 0;
		static int changeValue = 0;
		static bool temp = false;

		if (temp) {
			player1_map_selected.setOutlineColor(Color::Red);
			player2_map_selected.setOutlineColor(Color::White);
		}
		else {
			player1_map_selected.setOutlineColor(Color::White);
			player2_map_selected.setOutlineColor(Color::Red);
		}

		int finalFrame = player1_map_selected.getTexture() == finalTexture ? 210 :  200;
		if (frame == finalFrame) {
			frame = -1;
			sorteioAnim = false;
		}

		if (changeValue == 10) {
			temp = !temp;
			changeValue = -1;
		}

		frame++;
		changeValue++;
	}

	void confirmMap() {
		if (isp1time) {
			map_player1 = map;
			player1_map_selected.setTexture(t_maps + map_player1);
			isp1time = false;
			if (isSinglePlayerSelection && map_player2 == -1) {
				randAnim_ = true;
				

			}
		}
		else {

			if (map_player2 != -1) {
				finalTexture = (Texture *) sortearMapa(player1_map_selected.getTexture(), player2_map_selected.getTexture());
				__map = 1;
				if(player1_map_selected.getTexture() != player2_map_selected.getTexture())
					sorteioAnim = true;
			}
			else {
				map_player2 = map;
				player2_map_selected.setTexture(t_maps + map_player2);
			}
		}
	}

	void incrementMap() {
		if (map_player2 != -1) {
			return;
		}
		if (map == num_de_mapas - 1) {
			this->map = 0;
		}
		else {
			this->map++;
		}
		r_map.setTexture((t_maps + map));
	}

	void decreaseMap() {
		if (map_player2 != -1) {
			return;
		}
		if (map == 0) {
			this->map = num_de_mapas - 1;
		}
		else {
			this->map--;
		}
		r_map.setTexture((t_maps + map));
	}

	void resetMaps() {

			if (map_player2 != -1) {
				map_player2 = -1;
				player2_map_selected.setTexture(NULL);
				player2_map_selected.setOutlineColor(Color::White);
				player1_map_selected.setOutlineColor(Color::White);
				finalTexture = NULL;
				__map = 0;
			}
			else {
				player1_map_selected.setTexture(NULL);
				map_player1 = -1;
				isp1time = true;
			}

			if (isSinglePlayerSelection) {
				player1_map_selected.setTexture(NULL);
				map_player1 = -1;
				isp1time = true;
			}
		
	
	}

	static Texture* sortearMapa(Texture* mapas, int tam) {
		unsigned seed = time(0);
		srand(seed);
		int ret = rand() % tam;
		return &mapas[ret];
	}

	static const Texture* sortearMapa(const Texture * mapas1, const Texture * mapas2) {
		unsigned seed = time(0);
		srand(seed);
		if ((rand() % 2) == 1)
			return mapas1;
		else
			return mapas2;
	}

	void randAnim() {
		int frames = 30;
		static int animFrames = 0;

		if (animFrames % 10 == 0) {
			this->incrementMap();
		}

		animFrames++;
		if (animFrames == frames) {
			animFrames = 0;
			randAnim_ = false;
			map_player2 = 1;
			player2_map_selected.setTexture(sortearMapa(t_maps, this->num_de_mapas));

			for (int i = 0; i < num_de_mapas; i++) {
				if (t_maps + i == player2_map_selected.getTexture()) {
					map = i;
					r_map.setTexture(t_maps + map);
				}
			}
		}

	}

public:
	MapSelector() {

		t_maps[0].loadFromFile("maps/ceasa.png");
		t_maps[1].loadFromFile("maps/cenario faroeste.png");
		t_maps[2].loadFromFile("maps/shopping.png");


		r_map.setTexture(t_maps);
		r_map.setSize(Vector2f(SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.4));
		r_map.setPosition(SCREEN_WIDTH / 2 - r_map.getSize().x / 2, SCREEN_HEIGHT * 0.15);
		r_map.setOutlineThickness(5);

		player1_map_selected.setOutlineThickness(4);
		player1_map_selected.setOutlineColor(Color::White);
		player1_map_selected.setSize(Vector2f(SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.15));
		player1_map_selected.setPosition(SCREEN_WIDTH * 0.2, SCREEN_HEIGHT * 0.7);
		player2_map_selected.setOutlineThickness(4);
		player2_map_selected.setOutlineColor(Color::White);
		player2_map_selected.setSize(Vector2f(SCREEN_WIDTH * 0.15, SCREEN_HEIGHT * 0.15));
		player2_map_selected.setPosition(SCREEN_WIDTH * 0.8 - player2_map_selected.getSize().x, SCREEN_HEIGHT * 0.7);

		font.loadFromFile("fonts/Mortal-Kombat-MK11.otf");

		text_player1.setCharacterSize(SCREEN_HEIGHT * 0.03);
		text_player1.setFont(font);
		text_player1.setString("Player 1");
		text_player1.setPosition(player1_map_selected.getPosition().x, player1_map_selected.getPosition().y - text_player1.getGlobalBounds().height * 2);

		text_player2.setCharacterSize(SCREEN_HEIGHT * 0.03);
		text_player2.setFont(font);
		text_player2.setString("Player 2");
		text_player2.setPosition(player2_map_selected.getPosition().x, player2_map_selected.getPosition().y - text_player2.getGlobalBounds().height * 2);

		t_arrow.loadFromFile("icons\\arrow.png");
		arrowL.setFillColor(Color::White);
		arrowR.setTexture(&t_arrow);
		arrowL.setTexture(&t_arrow);

		arrowR.setSize(Vector2f(SCREEN_WIDTH * 0.05, SCREEN_HEIGHT * 0.06));
		arrowL.setSize(Vector2f(SCREEN_WIDTH * 0.05, SCREEN_HEIGHT * 0.06));

		arrowL.setPosition(r_map.getPosition().x - arrowL.getSize().x - 3, r_map.getPosition().y + r_map.getSize().y / 2 - arrowL.getSize().y / 2);
		arrowR.setPosition(r_map.getPosition().x + r_map.getSize().x + arrowR.getSize().x + 3, r_map.getPosition().y + r_map.getSize().y / 2 - arrowL.getSize().y / 2);

		arrowR.setScale(-1, 1);
	}

	~MapSelector() {

	}

	Texture* getSelectedMap() {
		return finalTexture;
	}
	void update(RenderWindow* window, int & option) {

		Event e;
		static float arrowAnim = 0;
		int pauseFrames = 60;
		static int p_frame = 0;

		while (window->pollEvent(e)) {

			if (e.type == Event::Closed) {
				window->close();
			}
			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Escape) {
					window->close();
				}
			}

			if (!this->sorteioAnim) {
				if (e.type == Event::KeyPressed) {

					if (e.key.code == Keyboard::Left) {
						this->decreaseMap();
					}

					if (e.key.code == Keyboard::Right) {
						this->incrementMap();
					}

					if (e.key.code == Keyboard::Enter) {
						this->confirmMap();
						p_frame = 1;
					}


				}

				if (e.type == Event::MouseButtonPressed) {
					if (e.mouseButton.button == Mouse::Left) {

						int i = confirm.getEvent(window);
						if (i == 1) {
							this->confirmMap();
							p_frame = 1;
						}
						else if (i == 0) {
							if (this->__map == 0)
								this->resetMaps();
						}

						if (ButtonCheck::isButtonComMouseNele(arrowL, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
							this->decreaseMap();
						}
						//sum the sizex of arrowR because the scale is -1, 
						/*
							if(walter.reclamouDoIngles()){
								mota.falar("Walter, vá se foder");
							}
							else{
								mota.falar("primeiramente, qual é o seu nome?\nSegundamente, cale a boca e segue a call");
							}
						*/
						else if (ButtonCheck::isButtonComMouseNele(arrowR, Mouse::getPosition(*window).x + arrowR.getSize().x, Mouse::getPosition(*window).y)) {
							this->incrementMap();
						}
					}
				}
			}
		}

		
		arrowL.move(cos(arrowAnim), 0);
		arrowR.move(-cos(arrowAnim), 0);

		arrowAnim += 0.1;

		if (isp1time) {
			text_player1.setFillColor(Color::Black);
			text_player2.setFillColor(Color::White);

		}
		else {
			text_player1.setFillColor(Color::White);
			text_player2.setFillColor(Color::Black);
		}

		if (randAnim_) {
			this->randAnim();
		}

		if (sorteioAnim) {
			this->SorteioAnim();
		}
		else if(__map == 1) {

			if (p_frame < pauseFrames) {
				p_frame++;
			}

			if (p_frame == pauseFrames) {
				p_frame = 0;
				option = UMJOGADORES;
				__map = 0;
			}
		}
	}

	void draw(RenderWindow* window, int & option, bool isSinglePlayerSelection = false) {
		this->isSinglePlayerSelection = isSinglePlayerSelection;
		update(window, option);
		window->clear(Color::Blue);
		window->draw(r_map);
		window->draw(player1_map_selected);
		window->draw(player2_map_selected);
		window->draw(text_player1);
		window->draw(text_player2);
		window->draw(arrowL);
		window->draw(arrowR);
		confirm.draw(window);
		window->display();
	}


	Texture* getTexture() {
		return t_maps + map;
	}
};


#endif // !RECLAME_MAIS_DESSA_SELECAO_WALTER_CORNO
