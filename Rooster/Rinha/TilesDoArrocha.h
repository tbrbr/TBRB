
struct musica {
	Music music;
	//mapa de teclas que eu vou implementar nstt
};


Vector2f fixCoord(float baseMenor, float baseMaior, float altura, Vector2f vec) {
	


}




class Nota {
public:
	int coluna = -1;
	int length = 1;
	int y = -1;

	bool hitted = false;
	bool missed = false;


	Nota(int c, int l, int yy) {
		coluna = c;
		length = l;
		y = yy;
	}


};

class Yamaha {

	float base;
	float baseMenor;
	float altura;

	float bpm;
	float notasPorYamaha = 4;
	float notaSize = 200;

	float xScl = 0.5;
	float yScl = 1;

	Vector2f pos;

	float scrollY = 0;
	float scrollSpd = 10;

	vector<Nota*> notas;

	ConvexShape rect;

	ConvexShape bars[4];

	Texture teclado;
	Sprite teclas[4];


	int maxLife = 1000;
	int life = 1000;

	

	float teclaXScl = 1;
	float teclaYScl = 1;

	bool teclaPressed[4];

	vector<Rooster::AreaEffect*> coisa;

	
public:
	Yamaha() {



		base = 800;
		altura = 800;

		notaSize = altura / notasPorYamaha;

		baseMenor = base;

		bpm = 1;

		pos.x = SCREEN_WIDTH / 2;
		pos.y = 40;





		rect.setPointCount(4);

		rect.setPoint(0, Vector2f(  -base / 2, 0));
		rect.setPoint(1, Vector2f(   base / 2, 0));
		rect.setPoint(2, Vector2f(   base / 2, altura));
		rect.setPoint(3, Vector2f(  -base / 2, altura));





		for (int i = 0; i < 4; i++) {
			
			bars[i].setPointCount(4);

			float baseQuart = base / 4;
			float baseAdd = (baseQuart * (i-2));

			bars[i].setPoint(0, Vector2f(baseAdd, 0));
			bars[i].setPoint(1, Vector2f(baseAdd + baseQuart, 0));
			bars[i].setPoint(2, Vector2f(baseAdd + baseQuart, altura));
			bars[i].setPoint(3, Vector2f(baseAdd , altura));
		}



		teclado.loadFromFile("sprites/teclas.png");


		


		for (int i = 0; i < 4; i++) {
			teclas[i].setTexture(teclado);
			teclas[i].setTextureRect(IntRect(445 * i, 0, 445, 250));

			teclaXScl = (base / 4) / teclas[i].getLocalBounds().width;
			teclaYScl = teclaXScl;

			float baseQuart = base / 4;
			float baseAdd = (baseQuart * (i - 2));
			Vector2f tecPos(baseAdd + baseQuart / 2, altura + 20);


			tecPos = convertToTrap(tecPos, baseMenor);
			tecPos.x *= xScl;
			tecPos.y *= yScl;
			tecPos.x += pos.x;
			tecPos.y += pos.y;

			teclas[i].setPosition(tecPos);
			teclas[i].setScale(xScl*teclaXScl, yScl*teclaYScl);


			teclas[i].setOrigin(teclas[i].getLocalBounds().width/2, teclas[i].getLocalBounds().height / 2);

			teclaPressed[i] = false;

			Color partColor;

			switch (i) {
			case 0:
				partColor = Color(255, 100, 100, 180);
				break;
			case 2:
				partColor = Color(100, 255, 100, 180);
				break;

			case 3:
				partColor = Color(255, 255, 100, 180);
				break;

			case 1:
				partColor = Color(100, 100, 255, 180);
				break;

			default:
				partColor = Color(100, 100, 100, 180);
			}

			coisa.push_back( new Rooster::AreaEffect(FloatRect(pos.x + baseAdd * xScl, pos.y + (altura + 20) * yScl, baseQuart * xScl, 20 * yScl), partColor));

		}

		for (int i = 0; i < 4; i++) {

			int insertInd = 0;

			for (int j = 0; j < 100; j++) {
				if (randInt(6) == 0) {

					int notaLen = randIntRange(1, 4);

					createNota(i, notaLen, -notaSize * insertInd -(notaSize * notaLen));
					insertInd += notaLen;
				}
				else {
					insertInd++;
				}
			}
		}

		







	}

	void createNota(int col, int len, int yy) {

		Nota* n = new Nota(col, len ,yy);

		notas.push_back(n);
	}



	void convertNoteToTrap(ConvexShape& note, float baseMenor) {
		
		

		for (int i = 0; i < 4; i++) {
			Vertex p = note.getPoint(i);
			Vector2f point = p.position;


			point = noteYPerspective(point, baseMenor);

			point = convertToTrap(point, baseMenor);

			note.setPoint(i, point);
		}

	}

	Vector2f noteYPerspective(Vector2f point, float baseMenor) {


		float y = point.y;

		

		if (base - baseMenor != 0) {
			// Isso da pra pre calcular
			float hSmall = baseMenor * altura / (base - baseMenor);

			float alturaTotal = hSmall + altura;

			if (-y + altura + 1 > 0.5) {

				y = (alturaTotal) / (-y + altura + 1);


			}
			else {
				y = alturaTotal/0.5;
			}

		}
		y = point.y;

		return Vector2f(point.x,y);
	}

	Vector2f convertToTrap(Vector2f point, float baseMenor) {



		float x = point.x;
		
		if (base - baseMenor != 0) {
			float hSmall = baseMenor * altura / (base - baseMenor);


			x = (hSmall + point.y) * (point.x / (hSmall + altura));
		}



		return Vector2f(x, point.y);
	}


	void update(int frames) {
		scrollY += scrollSpd;


		teclaPressed[0] = mainInput.keyboardState[sf::Keyboard::A][0];
		teclaPressed[1] = mainInput.keyboardState[sf::Keyboard::S][0];
		teclaPressed[2] = mainInput.keyboardState[sf::Keyboard::D][0];
		teclaPressed[3] = mainInput.keyboardState[sf::Keyboard::F][0];




		bool teclaMissed[] = {true, true, true, true};

		for (int j = 0; j < notas.size(); j++) {
			float notaY = notas[j]->y + scrollY;

			for (int i = 0; i < 4; i++) {
				if (teclaPressed[i]) {
					//println("TEclou " << i);
					if (notas[j]->coluna == i && !notas[j]->missed) {
						//println("Tentou");
						if (notaY < altura && notaY + notas[j]->length*notaSize*yScl > altura) {

							coisa[i]->createParticle();


							notas[j]->hitted = true;
							//println("Coinseguiu");
							teclaMissed[i] = false;
						}
					}
					
				}
			}

			if (notaY + (notas[j]->length-1)*notaSize > altura) {
				if (!notas[j]->missed && !notas[j]->hitted) {
					notas[j]->missed = true;
					life -= 5;
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			if (teclaPressed[i]) {
				if (teclaMissed[i]) {
					life -= 5;
				}
			}

			coisa[i]->update();
		}







	}




	void draw(RenderWindow* window, int frames) {

		//baseMenor = base*(ruleOfThree(sin((float)frames/20), -1, 1, 0, 1.5));


		ConvexShape trap;

		trap.setPointCount(4);
		for (int i = 0; i < 4; i++) {
			trap.setPoint(i, convertToTrap(rect.getPoint(i), baseMenor));
		}




		trap.setFillColor(Color::Blue);
		trap.setScale(xScl, yScl);
		trap.setPosition(pos);
		window->draw(trap);


		for (int j = 0; j < 4; j++) {

			ConvexShape bar;

			bar.setPointCount(4);
			for (int i = 0; i < 4; i++) {
				bar.setPoint(i, convertToTrap(bars[j].getPoint(i), baseMenor));
			}




			bar.setFillColor(Color::Blue);
			bar.setScale(xScl, yScl);
			bar.setPosition(pos);

			bar.setOutlineColor(Color::White);
			bar.setOutlineThickness(1);

			window->draw(bar);
		}

		for (int i = 0; i < notas.size(); i++) {
			
			ConvexShape noteShape;

			noteShape.setPointCount(4);

			int coluna = notas[i]->coluna;


			float baseQuart = base / 4;
			float noteX = (baseQuart * (coluna - 2));

			float noteY = notas[i]->y + scrollY;

			float noteLen = notaSize * notas[i]->length;

			

			noteShape.setPoint(0, Vector2f(noteX, noteY+0));
			noteShape.setPoint(1, Vector2f(noteX + baseQuart, noteY));
			noteShape.setPoint(2, Vector2f(noteX + baseQuart, noteY+noteLen));
			noteShape.setPoint(3, Vector2f(noteX, noteY + noteLen));

			convertNoteToTrap(noteShape, baseMenor);




			/*
			for (int i = 0; i < 4; i++) {
				noteShape.setPoint(i, convertToTrap(noteShape.getPoint(i), baseMenor));
			}
			*/

			noteShape.setPosition(pos);
			noteShape.setScale(xScl, yScl);

			if (notas[i]->hitted) {
				noteShape.setFillColor(Color::Green);
			}
			else if (notas[i]->missed) {
				noteShape.setFillColor(Color::Red);
			} else {
				noteShape.setFillColor(Color::Black);
			}

			noteShape.setOutlineColor(Color::White);
			noteShape.setOutlineThickness(2);

			window->draw(noteShape);


			if (notas[i]->length > 1) {
				ConvexShape lineShape;

				lineShape.setPointCount(4);

				float lineWid = baseQuart / 4;
				float lineX = noteX + baseQuart / 2 - lineWid / 2;



				lineShape.setPoint(0, Vector2f(lineX, noteY + 0));
				lineShape.setPoint(1, Vector2f(lineX + lineWid, noteY));
				lineShape.setPoint(2, Vector2f(lineX + lineWid, noteY - notaSize + noteLen));
				lineShape.setPoint(3, Vector2f(lineX, noteY - notaSize + noteLen));


				convertNoteToTrap(lineShape, baseMenor);




				lineShape.setPosition(pos);
				lineShape.setScale(xScl, yScl);

				if (notas[i]->hitted) {
					lineShape.setFillColor(Color::Green);
				}
				else if (notas[i]->missed) {
					lineShape.setFillColor(Color::Red);
				}
				else {
					lineShape.setFillColor(Color::Black);
				}

				lineShape.setOutlineColor(Color::White);
				lineShape.setOutlineThickness(2);

				window->draw(lineShape);
			}


			

		}


		CircleShape c(20);

		c.setFillColor(Color(250, 100, 0, 100));

		for (int i = 0; i < 4; i++) {


			int texWid = teclas[i].getTexture()->getSize().x / 4;
			int texHei = teclas[i].getTexture()->getSize().y / 2;

			teclas[i].setTextureRect(IntRect(texWid * i, teclaPressed[i] * texHei, texWid, texHei));

			window->draw(teclas[i]);
			float baseQuart = base / 4;
			float noteX = (baseQuart * (i - 2))*xScl;
			c.setPosition(noteX + (baseQuart / 2), altura);
			window->draw(c);

		}





		RectangleShape r;
		r.setFillColor(Color(250, 200, 0, 100));

		for (int i = 0; i < notas.size(); i++) {

			float baseQuart = base / 4;
			float noteX = (baseQuart * (notas[i]->coluna - 2))*xScl;

			r.setSize(Vector2f(baseQuart/2, notas[i]->length * notaSize * yScl));
			c.setPosition(noteX +(baseQuart / 2), notas[i]->y + scrollY);
			r.setPosition(noteX + ((baseQuart/2) -( baseQuart / 4))*xScl, notas[i]->y + scrollY);

			window->draw(c);
			window->draw(r);

		}


		RectangleShape rect;
		rect.setFillColor(Color(250, 250 ,250, 255));
		rect.setSize(Vector2f(SCREEN_WIDTH, 40));
		rect.setPosition(0, 0);
		rect.setFillColor(Color(0, 0, 0, 0));
		rect.setOutlineColor(Color::White);
		rect.setOutlineThickness(4);

		window->draw(rect);

		rect.setOutlineThickness(0);
		rect.setFillColor(Color::Green);
		rect.setPosition(0, 5);
		rect.setSize(Vector2f(SCREEN_WIDTH * (float)life/maxLife, 30));
		window->draw(rect);



		for (int i = 0; i < 4; i++) {
			coisa[i]->draw(*window);
		}




	}

};




bool pianoTiles(RenderWindow* window) {


	Yamaha alcides;



	Clock timer;
	timer.restart();

	int frames = 0;

	struct Rooster::GaloStats kalsaSt = { 100, 10, 10, 10, 5 };

	Rooster::Galo* galoPeste = new Rooster::Peste(kalsaSt, Rooster::state::DANCING, false);

	while (window->isOpen()) {

		
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

		mainInput.update();

		window->clear();

		frames++;

		RectangleShape rect(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		rect.setFillColor(Color::Black);


		window->draw(rect);

			
		alcides.update(frames);
		alcides.draw(window, frames);

		galoPeste->update();
		galoPeste->show(*window);




		window->display();
	}

	
	
}