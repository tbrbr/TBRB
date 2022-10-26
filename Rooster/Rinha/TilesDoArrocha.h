/*agora sim*/

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

bool pianoTiles(RenderWindow* window) {

	RectangleShape teclas[TECLAS];
	RectangleShape teclasPretas[TECLASPRETAS];

	int sizex = SCREEN_WIDTH / 16;
	int sizey = SCREEN_HEIGHT * 0.3;
	setup(teclas, sizex, sizey);
	
	int sizepretax = SCREEN_WIDTH / 32;
	int sizepretay = SCREEN_HEIGHT * 0.25;

	setupBlack(teclasPretas, sizepretax, sizepretay,sizex);

	
	

	while (window->isOpen()) {

		window->clear();
		

		

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
					return 2;
				}

			}
		}
		for (int i = 0; i < 4; i++) {
			window->draw(teclas[i]);

		}
		for (int i = 0; i < TECLASPRETAS; i++) {
			window->draw(teclasPretas[i]);
		}
		window->display();
	}

	
	
}