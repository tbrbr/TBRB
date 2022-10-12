/*agora sim*/

#define  TECLAS  4
#define  TECLASPRETAS  3

class pianoYamaha {
	
	RectangleShape teclas[TECLAS];
	RectangleShape teclasPretas[TECLASPRETAS];

public:
	pianoYamaha() {
		
		int sizex = SCREEN_WIDTH / 16;
		int sizey = SCREEN_HEIGHT * 0.3;
		int sizepretax = SCREEN_WIDTH / 32;
		int sizepretay = SCREEN_HEIGHT * 0.25;


		for (int i = 0; i < TECLAS; i++) {
			teclas[i].setSize(Vector2f(sizex, sizey));
			teclas[i].setPosition(SCREEN_WIDTH/2 - sizex*2 + sizex*i, SCREEN_HEIGHT/2 - sizey/2);
			teclas[i].setFillColor(Color::White);
			teclas[i].setOutlineThickness(SCREEN_WIDTH / 150);
			teclas[i].setOutlineColor(Color::Black);
		}
		for (int i = 0; i < TECLASPRETAS; i++) {
			teclasPretas[i].setSize(Vector2f(sizepretax, sizepretay));
			teclasPretas[i].setPosition(SCREEN_WIDTH / 2 - sizex * 2 + sizex * i + sizepretax * 1.5 - SCREEN_WIDTH / 300, SCREEN_HEIGHT * 0.3);
			teclasPretas[i].setFillColor(Color::Black);
		}

	}
	void draw(RenderWindow & window) {
		for (int i = 0; i < 4; i++) {
			window.draw(teclas[i]);
			
		}
		for (int i = 0; i < TECLASPRETAS; i++) {
			window.draw(teclasPretas[i]);
		}
		window.display();
	}

};