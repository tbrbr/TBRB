
struct musica {
	Music music;
	//mapa de teclas que eu vou implementar nstt
};


Vector2f fixCoord(float baseMenor, float baseMaior, float altura, Vector2f vec) {
	



	float y = vec.y;
	float x = vec.x * (baseMaior - baseMenor) * (vec.y / altura);
			
	//return 
	

}


class nota {

	int vAcc = 1;
	Vector2f position;
	ConvexShape trapezio;
public:
	nota(int coluna) {
		this->position.x = coluna;

		
		trapezio.setPointCount(4);

		float baseMenor = 1.25 * SCREEN_WIDTH/60;
		//float baseMaior = 30;
		float altura = 2 * SCREEN_HEIGHT / 25;

		trapezio.setPoint(0, Vector2f(0,0));
		trapezio.setPoint(1, Vector2f(baseMenor, 0));
		trapezio.setPoint(2, Vector2f(baseMenor, altura));
		trapezio.setPoint(3, Vector2f(0, altura));

		trapezio.setFillColor(Color::Red);


		// eu queria deixar eles na posicao inicial
		// ai voce tems sla x teclas
		//elas comecam la em cima no y = 0;
		int x = coluna - 2;
		trapezio.setPosition(SCREEN_WIDTH/ 2  + (x * baseMenor),0);
	}

	void update() {
		int baseMenor = 1.25 * SCREEN_WIDTH / 60;
		position.y += vAcc;
		trapezio.setPosition(SCREEN_WIDTH / 2 + ((position.x - 2) * baseMenor), position.y);
	}
	void draw(RenderWindow* window) {
		// Nicer
		window->draw(trapezio);
	}
	bool checkCollision() {
		// Nice
	}
	
	
};


class Yamaha {

	std::vector<nota> notas;

	int bpm = 100;//ui UUUIII

	Vector2f position; //x = Barra 0, 1, 2, 3 y = Altura que a nota ta


	Sprite fundo;


	ConvexShape trapezio;
	
	float baseMenor = 5;
	float baseMaior = 30;
	float altura = 17;

	float xScl = SCREEN_WIDTH / 60;
	float yScl = SCREEN_HEIGHT / 25;


	float trapX = trapezio.getPosition().x;
	float trapY = trapezio.getPosition().y;

	Vertex lines[3][2];
	

	float clickAltura = altura * 0.65;

	float clickBase = baseMenor + (clickAltura / altura) * (baseMaior - baseMenor);


	Vertex clickLine[2];

	Sprite teclas[4];

	Texture teclado;
	
	
public:
	Yamaha() {
		
		nota a(rand() % 4);
		notas.push_back(a);

		trapezio.setPointCount(4);
		

		trapezio.setPoint(0, Vector2f(-baseMenor / 2, -altura / 2));
		trapezio.setPoint(1, Vector2f(baseMenor / 2, -altura / 2));
		trapezio.setPoint(2, Vector2f(baseMaior / 2, altura / 2));
		trapezio.setPoint(3, Vector2f(-baseMaior / 2, altura / 2));


		trapezio.setScale(xScl, yScl);

		trapezio.setPosition(
			SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 2 - (SCREEN_HEIGHT - altura * yScl) / 2
		);

		trapezio.setFillColor(Color::Blue);

		for (int i = 0; i < 3; i++) {

			lines[i][0] = Vertex(Vector2f(
				trapezio.getPosition().x - baseMenor * xScl / 2 + (i + 1) * baseMenor * xScl / 4,
				trapezio.getPosition().y - altura * yScl / 2)
			);

			lines[i][1] = Vertex(Vector2f(
				trapezio.getPosition().x - (baseMaior * xScl / 2) + (i + 1) * baseMaior * xScl / 4,
				trapezio.getPosition().y + altura * yScl / 2)
			);
		}
	

		teclado.loadFromFile("sprites/teclas.png");


		for (int i = 0; i < 4; i++) {
			teclas[i].setTexture(teclado);
			teclas[i].setTextureRect(IntRect(445 * i, 0, 445, 250));

			teclas[i].setPosition(trapX - (baseMaior * xScl) / 2 + (i * baseMaior * xScl) / 4, altura * yScl);
			teclas[i].setScale(Vector2f((float)SCREEN_WIDTH / 3840, (float)SCREEN_HEIGHT / 2160));
		}

		for (int i = 0; i < 4; i++) {
			teclas[i].setTexture(teclado);
			teclas[i].setTextureRect(IntRect(445 * i, 0, 445, 250));

			teclas[i].setPosition(trapX - (baseMaior * xScl) / 2 + (i * baseMaior * xScl) / 4, altura * yScl);
			teclas[i].setScale(Vector2f((float)SCREEN_WIDTH / 3840, (float)SCREEN_HEIGHT / 2160));
		}

		clickLine[0] = Vertex(Vector2f(trapX - clickBase * xScl / 2, trapY - altura * yScl / 2 + clickAltura * yScl));
		clickLine[1] = Vertex(Vector2f(trapX + clickBase * xScl / 2, trapY - altura * yScl / 2 + clickAltura * yScl));

	}

	void update() {
		static int frames = 0;
		frames++;
		if (frames % bpm == 0) {
			nota a(rand() % 4);
			notas.push_back(a);
		}
			
		for (int i = 0; i < notas.size(); i++) {
			notas[i].update();
		}
	}

	void draw(RenderWindow* window) {
		window->draw(trapezio);

		for (int i = 0; i < 3; i++) {
			window->draw(lines[i], 2, sf::Lines);
		}

		window->draw(clickLine, 2, sf::Lines);
		for (int i = 0; i < 4; i++) {
			window->draw(teclas[i]);
		}

		for (int i = 0; i < notas.size(); i++) {
			notas[i].draw(window);
		}

	}

};

bool pianoTiles(RenderWindow* window) {



	Yamaha alcides;


	Clock timer;
	timer.restart();

	while (window->isOpen()) {

		window->clear();
		int time = timer.getElapsedTime().asMilliseconds();

		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::Escape)
				{
					window->close();
				}
				if (e.key.code == Keyboard::Space)
				{
					return 1;
				}

			}
		}

			
		alcides.update();
		alcides.draw(window);
		window->display();
	}

	
	
}