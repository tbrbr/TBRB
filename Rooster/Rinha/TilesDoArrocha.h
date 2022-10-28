/*agora sim*/
/*
#define  TECLAS  4
#define  TECLASPRETAS  3

void setup(RectangleShape teclas[],int sizex,int sizey) {

	for (int i = 0; i < TECLAS; i++) {
		teclas[i].setSize(Vector2f(sizex, sizey));
		teclas[i].setPosition(SCREEN_WIDTH / 2 - sizex * 2 + sizex * i, SCREEN_HEIGHT / 2 - sizey / 2);
		teclas[i].setFillColor(Color::White);
		teclas[i].setOutlineThickness(SCREEN_WIDTH / 150);
		teclas[i].setOutlineColor(Color::Black);
	}
}
void setupBlack(RectangleShape teclasPretas[], int sizepretax, int sizepretay,int sizex) {
	for (int i = 0; i < TECLASPRETAS; i++) {
		teclasPretas[i].setSize(Vector2f(sizepretax, sizepretay));
		teclasPretas[i].setPosition(
			SCREEN_WIDTH / 2 - sizex * 2 + sizex * i + sizepretax * 1.5 - SCREEN_WIDTH / 300,
			SCREEN_HEIGHT * 0.3
		);
		teclasPretas[i].setFillColor(Color::Black);
	}
}
*/

Vector2f coordCertas(Vector2f vec, float baseMenor, float baseMaior, float altura) {





}



bool pianoTiles(RenderWindow* window) {


	Sprite fundo;


	ConvexShape trapezio;
	trapezio.setPointCount(4);


	float baseMenor = 5;
	float baseMaior = 30;
	float altura = 17;

	trapezio.setPoint(0, Vector2f(-baseMenor/2, -altura/2));
	trapezio.setPoint(1, Vector2f(baseMenor/2, -altura/2));
	trapezio.setPoint(2, Vector2f(baseMaior/2, altura/2));
	trapezio.setPoint(3, Vector2f(-baseMaior/2, altura/2));


	float xScl = SCREEN_WIDTH / 60;
	float yScl = SCREEN_HEIGHT / 25;

	trapezio.setScale(xScl, yScl);	
	
	trapezio.setPosition(
		SCREEN_WIDTH/2,
		SCREEN_HEIGHT/2 - (SCREEN_HEIGHT - altura*yScl)/2
	);

	trapezio.setFillColor(Color::Blue);
	
	float trapX = trapezio.getPosition().x;
	float trapY = trapezio.getPosition().y;

	Vertex lines[3][2];
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

	float clickAltura = altura*0.65;

	float clickBase = baseMenor + (clickAltura / altura) * (baseMaior - baseMenor);


	Vertex clickLine[] =
	{
		Vertex(Vector2f(trapX -clickBase*xScl/2, trapY - altura*yScl/2 + clickAltura*yScl)),
		Vertex(Vector2f(trapX +clickBase*xScl/2, trapY - altura*yScl/2 + clickAltura*yScl))
	};

	Texture teclado;
	teclado.loadFromFile("sprites/teclas.png");	Sprite teclas[4];

	for (int i = 0; i < 4; i++) {
		teclas[i].setTexture(teclado);
		teclas[i].setTextureRect(IntRect(445 * i,0,445,250));

		teclas[i].setPosition(trapX - (baseMaior * xScl)/2 + (i * baseMaior * xScl) / 4, altura * yScl);
		teclas[i].setScale(Vector2f((float) SCREEN_WIDTH/3840, (float) SCREEN_HEIGHT/2160));
	}


	 

	ConvexShape notas;
	teclado.loadFromFile("sprites/teclas.png");

	for (int i = 0; i < 4; i++) {
		teclas[i].setTexture(teclado);
		teclas[i].setTextureRect(IntRect(445 * i,0,445,250));

		teclas[i].setPosition(trapX - (baseMaior * xScl)/2 + (i * baseMaior * xScl) / 4, altura * yScl);
		teclas[i].setScale(Vector2f((float) SCREEN_WIDTH/3840, (float) SCREEN_HEIGHT/2160));
	}


	 

	//std::Vector <ConvexShape> notas;

	


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
		window->draw(trapezio);
		for (int i = 0; i < 3; i++) {
			window->draw(lines[i], 2, sf::Lines);
		}
		window->draw(clickLine, 2, sf::Lines);
		for (int i = 0; i < 4; i++) {
			window->draw(teclas[i]);
		}
		window->display();
	}

	
	
}