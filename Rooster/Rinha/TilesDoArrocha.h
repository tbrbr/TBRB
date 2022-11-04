
struct musica {
	Music music;
	//mapa de teclas que eu vou implementar nstt
};


// Função pra transformar retangulo em convexShape
ConvexShape rectToConvexShape(RectangleShape rect) {
	ConvexShape newShape(4);

	for (int i = 0; i < 4; i++) {
		newShape.setPoint(i, rect.getPoint(i));
	}

	return newShape;
}

ConvexShape rectToConvexShape(float x, float y, float wid, float hei) {
	ConvexShape newShape(4);

	newShape.setPoint(0, Vector2f(x, y));
	newShape.setPoint(1, Vector2f(x+wid, y));
	newShape.setPoint(2, Vector2f(x+wid, y+hei));
	newShape.setPoint(3, Vector2f(x, y+hei));

	return newShape;
}

ConvexShape rectToConvexShape(float wid, float hei) {
	ConvexShape newShape(4);

	newShape.setPoint(0, Vector2f(-wid/2, -hei/2));
	newShape.setPoint(1, Vector2f(wid/2, -hei/2));
	newShape.setPoint(2, Vector2f(wid/2, hei/2));
	newShape.setPoint(3, Vector2f(-wid/2, hei/2));

	return newShape;
}





class Nota {
public:
	int coluna = -1;
	int length = 1;
	int y = -1;

	float slided = 0;

	bool hitted = false;
	bool missed = false;
	bool holded = false;

	bool hovered = false;

	bool loose = false;


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

	float xScl = 1;
	float yScl = 1;

	Vector2f pos;

	float scrollY = 0;
	float scrollSpd = 10;

	vector<Nota*> notas;

	ConvexShape rect;

	ConvexShape bars[4];

	Texture teclado;
	Texture trapezioTexture;
	Sprite teclas[4];


	int maxLife = 300;
	int life = 300;

	

	float teclaXScl = 1;
	float teclaYScl = 1;

	bool teclaPressed[4];
	bool teclaState[4];


public:
	int combo = 0;

	int comboMax = 100;


	vector<Rooster::AreaEffect*> coisa;

	

	Yamaha() {



		base = 400;
		altura = 600;

		notaSize = altura / notasPorYamaha;

		baseMenor = base;

		bpm = 1;

		pos.x = SCREEN_WIDTH / 2;
		pos.y = 40;



	

		rect = rectToConvexShape(-base/2, 0, base, altura);








		for (int i = 0; i < 4; i++) {
			


			float baseQuart = base / 4;
			float baseAdd = (baseQuart * (i-2));

			bars[i] = rectToConvexShape(baseAdd, 0, baseQuart, altura);


		}



		teclado.loadFromFile("sprites/teclas.png");
		trapezioTexture.loadFromFile("");

		


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

			for (int j = 0; j < 200; j++) {
				if (randInt(8) == 0) {

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


		teclaPressed[0] = mainInput.keyboardState[sf::Keyboard::A][1];
		teclaPressed[1] = mainInput.keyboardState[sf::Keyboard::S][1];
		teclaPressed[2] = mainInput.keyboardState[sf::Keyboard::D][1];
		teclaPressed[3] = mainInput.keyboardState[sf::Keyboard::F][1];



		teclaState[0] = mainInput.keyboardState[sf::Keyboard::A][0];
		teclaState[1] = mainInput.keyboardState[sf::Keyboard::S][0];
		teclaState[2] = mainInput.keyboardState[sf::Keyboard::D][0];
		teclaState[3] = mainInput.keyboardState[sf::Keyboard::F][0];




		bool teclaMissed[] = {true, true, true, true};

		for (int j = 0; j < notas.size(); j++) {
			float notaY = notas[j]->y + scrollY;

			notas[j]->hovered = false;
			if (notaY < altura && notaY + notas[j]->length * notaSize * yScl > altura) {

				notas[j]->hovered = true;

			}

			for (int i = 0; i < 4; i++) {






				if (notas[j]->coluna == i && !notas[j]->missed) {





					


					if (notas[j]->hovered) {

						if (teclaState[i] && !notas[j]->loose){

							if (notas[j]->hitted) {
								if (notas[j]->length != 1) {
									notas[j]->slided = 1 - constrain((altura - notaY) / (yScl*notaSize * (notas[j]->length - 1)), 0, 1);
									
									for (int k = 0; k < (notas[j]->slided*10)*notas[j]->length / 5; k++) {
										coisa[i]->createParticle();
									}

								}

								coisa[i]->createParticle();
							}
						}
						else {
							if (notas[j]->hitted) {
								notas[j]->loose = true;
							}
						}

						if (teclaPressed[i]) {
							if (!notas[j]->hitted) {
								notas[j]->hitted = true;
								if (notas[j]->length > 1) {
									notas[j]->holded = true;
								}
								teclaMissed[i] = false;

								combo++;
							}
						}

					

						
					}




					
				}
					
				
			}




			if (notaY + (notas[j]->length-1)*notaSize > altura) {
				if (!notas[j]->missed && !notas[j]->hitted) {
					notas[j]->missed = true;
					life -= 5;
					combo = 0;
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			if (teclaPressed[i]) {
				if (teclaMissed[i]) {
					life -= 5;
					combo = 0;
				}
			}

			coisa[i]->update();
		}







	}




	void draw(RenderWindow* window, int frames) {



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




			bar.setFillColor(Color(0,0,255,10));
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

			
			noteShape = rectToConvexShape(noteX, noteY, baseQuart, noteLen);

			convertNoteToTrap(noteShape, baseMenor);


			noteShape.setPosition(pos);
			noteShape.setScale(xScl, yScl);

			if (notas[i]->hitted) {
				noteShape.setFillColor(Color::Green);
			}
			else if (notas[i]->missed) {
				noteShape.setFillColor(Color::Red);
			}
			else if (notas[i]->hovered) {
				noteShape.setFillColor(Color(100, 100, 200));
			}
			else {
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

				lineShape = rectToConvexShape(lineX, noteY, lineWid, -notaSize + noteLen);


				convertNoteToTrap(lineShape, baseMenor);



				lineShape.setPosition(pos);
				lineShape.setScale(xScl, yScl);

				if (notas[i]->hitted) {
					lineShape.setFillColor(Color(0, 100, 0));
				}
				else if (notas[i]->missed) {
					lineShape.setFillColor(Color::Red);
				}
				else {
					lineShape.setFillColor(Color(20, 20, 20));
				}

				lineShape.setOutlineColor(Color::White);
				lineShape.setOutlineThickness(2);

				window->draw(lineShape);



				ConvexShape sliderShape;
				sliderShape.setPointCount(4);
				float sliderWid = baseQuart / 3;
				float sliderX = noteX + baseQuart / 2 - sliderWid / 2;

				float sliderHei = sliderWid;
				float sliderY = noteY - (sliderHei / 2) + (noteLen-notaSize) * (1 - notas[i]->slided);

				sliderShape = rectToConvexShape(sliderX, sliderY, sliderWid, sliderHei);



				convertNoteToTrap(sliderShape, baseMenor);

				sliderShape.setPosition(pos);
				sliderShape.setScale(xScl, yScl);

				if (notas[i]->hitted) {
					sliderShape.setFillColor(Color(100, 200, 100));
				}
				else if (notas[i]->missed) {
					sliderShape.setFillColor(Color::Red);
				}
				else {
					sliderShape.setFillColor(Color(230, 230, 230));
				}

				sliderShape.setOutlineColor(Color::White);
				sliderShape.setOutlineThickness(2);

				window->draw(sliderShape);




			}


			

		}


		CircleShape c(20);

		c.setFillColor(Color(250, 100, 0, 100));

		for (int i = 0; i < 4; i++) {


			int texWid = teclas[i].getTexture()->getSize().x / 4;
			int texHei = teclas[i].getTexture()->getSize().y / 2;

			teclas[i].setTextureRect(IntRect(texWid * i, teclaState[i] * texHei, texWid, texHei));

			window->draw(teclas[i]);

			if (SHOWDEBUG) {
				float baseQuart = base / 4;
				float noteX = (baseQuart * (i - 2)) * xScl;
				c.setPosition(noteX + (baseQuart / 2), altura);
				window->draw(c);
			}

		}




		if (SHOWDEBUG) {
			RectangleShape r;
			r.setFillColor(Color(250, 200, 0, 100));

			for (int i = 0; i < notas.size(); i++) {

				float baseQuart = base / 4;
				float noteX = (baseQuart * (notas[i]->coluna - 2)) * xScl;

				r.setSize(Vector2f(baseQuart / 2, notas[i]->length * notaSize * yScl));
				c.setPosition(noteX + (baseQuart / 2), notas[i]->y + scrollY);
				r.setPosition(noteX + ((baseQuart / 2) - (baseQuart / 4)) * xScl, notas[i]->y + scrollY);

				window->draw(c);
				window->draw(r);

			}
		}


		RectangleShape rect;





		int outLine = 4;
		int offSet = 4;

		int x = 0;
		int y = 0;

		int wid = SCREEN_WIDTH;
		int hei = 40;

		rect.setFillColor(Color(250, 250 ,250, 255));
		rect.setSize(Vector2f(wid - 2*outLine, hei- 2*outLine));
		rect.setPosition(x+outLine, y+outLine);
		rect.setFillColor(Color(0, 0, 0, 0));
		rect.setOutlineColor(Color::White);
		rect.setOutlineThickness(outLine);




		window->draw(rect);

		rect.setOutlineThickness(0);
		rect.setFillColor(Color::Green);
		rect.setPosition(x + outLine + offSet, y + outLine + offSet);
		rect.setSize(Vector2f((wid - 2*(outLine + offSet)) * (float)life/maxLife, hei - 2*(outLine+offSet)));
		window->draw(rect);



		
		for (int i = 0; i < 4; i++) {
			coisa[i]->draw(*window);
		}
		




	}

};

class BregaMeter {

	Sprite sprite;

	float x;
	float y;
	float wid;
	float hei;

	float xScl;
	float yScl;

public:
	float percentage = 0;

	BregaMeter(Texture& bregaMeterTex) {
		
		sprite.setTexture(bregaMeterTex);



		float bregaSprWid = bregaMeterTex.getSize().x / 2;
		float bregaSprHei = bregaMeterTex.getSize().y;

		wid = SCREEN_WIDTH / 5;
		

		sprite.setTextureRect(IntRect(0, 0, bregaSprWid, bregaSprHei));


		xScl = wid / bregaSprWid;
		yScl = xScl;

		sprite.setScale(xScl, yScl);


		hei = bregaSprHei * yScl;

		x = SCREEN_WIDTH - wid;
		y = SCREEN_HEIGHT - (bregaSprHei * yScl);

		
	}

	void draw(RenderWindow& window) {


		sprite.setScale(xScl, yScl);
		sprite.setPosition(x, y);
		window.draw(sprite);





		RectangleShape ponteiro(Vector2f(wid * 0.4, yScl * 20));
		ponteiro.setFillColor(Color(0, 0, 0));
		ponteiro.setPosition(x + wid / 2 + xScl * 18, y + (sprite.getLocalBounds().height - 112) * xScl);
		ponteiro.setOrigin(wid * 0.4, xScl * 10);
		ponteiro.setRotation(-5 + 185 * percentage);

		window.draw(ponteiro);
	}

	


};





bool pianoTiles(RenderWindow* window) {


	Yamaha alcides;

	
	Clock timer;
	timer.restart();

	int frames = 0;

	struct Rooster::GaloStats kalsaSt = { 100, 10, 10, 10, 5 };

	Rooster::Galo* galoPeste  = new Rooster::Peste(kalsaSt, Rooster::state::DANCING, false);
	Rooster::Galo* galoKalsa  = new Rooster::Kalsa(kalsaSt, Rooster::state::DANCING, true );
	Rooster::Galo* galoSniper = new Rooster::Sniper(kalsaSt, Rooster::state::DANCING, false);

	galoSniper->setPosition(Vector2f((float)SCREEN_WIDTH/1.05, Rooster::floorY));
	galoKalsa->facingRight = true;

	Texture fundao;
	fundao.loadFromFile("sprites/tiringa.png");

	RectangleShape rect(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	rect.setTexture(&fundao);
	rect.setFillColor(Color(255, 0, 255, 255));


	Texture bregaMeterTex;
	bregaMeterTex.loadFromFile("sprites/medidorBrega.png");

	BregaMeter bregaMeter(bregaMeterTex);

	



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

			if (e.type == Event::Closed)
			{
				window->close();
			}
			if (e.type == sf::Event::Resized)
			{
				float wid = 1280;
				float hei = 720;
				float xScl = (float)e.size.width / wid;
				float yScl = (float)e.size.height / hei;

				if (xScl > yScl) {
					wid *= yScl;
					hei = e.size.height;
				}
				else {

					hei *= xScl;
					wid = e.size.width;
				}

				xScl = wid / (float)e.size.width;
				yScl = hei/(float)e.size.height;

				sf::FloatRect visibleArea(0.f, 0.f, 1280, 720);
				sf::View view(visibleArea);
				view.setViewport(FloatRect((1-xScl)/2,(1-yScl)/2, xScl, yScl));
				window->setView(view);
			}
		}

		mainInput.update();

		window->clear();

		frames++;

		


		window->draw(rect);

			
		alcides.update(frames);
		alcides.draw(window, frames);

		
		galoPeste->update();
		galoPeste->show(*window);
		galoKalsa->update();
		galoKalsa->show(*window);
		galoSniper->update();
		galoSniper->show(*window);
		



		bregaMeter.percentage = (float)alcides.combo / alcides.comboMax;
		bregaMeter.draw(*window);



		window->display();
	}

	
	
}
