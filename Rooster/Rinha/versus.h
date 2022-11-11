#ifndef KAUAEHALENDADOPHOTOSHONDAPRACOMPETIROCARAEHFODAAAAAAAAAAAAAAAAA
#define KAUAEHALENDADOPHOTOSHONDAPRACOMPETIROCARAEHFODAAAAAAAAAAAAAAAAA


#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>
#include "particula_falida.h"

#pragma warning(disable : 4996)

using namespace sf;

#define DEBUG

void escurecer(RenderWindow & window) {
	RectangleShape sombra;
	sombra.setFillColor(Color::Color(0, 0, 0, 0));
	int a = 1;
	sombra.setSize((Vector2f)window.getSize());

	while (window.isOpen()) {
		sombra.setFillColor(Color::Color(0, 0, 0, a));
		a += 1;
		if (a == 60) {
			return;
		}
		window.draw(sombra);
		window.display();
	}
}

void inline moveGalo(Galo& g, int x, int y) {
	g.setPosition(Vector2f(g.getPosition().x + x, g.getPosition().y + y));
}

int versus(RenderWindow & window, Galo & p1, Galo & p2, RectangleShape & fundoluta, int __map)
{


	SoundBuffer buffer;
	if (__map == 3)
		buffer.loadFromFile("sounds/audiofeira.ogg");
	else {
		buffer.loadFromFile("sounds/audiofeira.ogg");
	}

	Sound sound(buffer);
	sound.play();

	escurecer(window);

	ParticleAnimation p;
	Texture* __azul = new Texture();
	Texture* __vermelho = new Texture();
	Texture* __fundo = new Texture();

	Texture* __versus = new Texture();

	__fundo->loadFromFile("C:\\TBRB\\Rooster\\Rinha\\sprites\\confrontobase.png");
	__azul->loadFromFile("C:\\TBRB\\Rooster\\Rinha\\sprites\\confrontoazul.png");
	__vermelho->loadFromFile("C:\\TBRB\\Rooster\\Rinha\\sprites\\confrontovermelho.png");
	__versus->loadFromFile("C:\\TBRB\\Rooster\\Rinha\\sprites\\confrontoversus.png");
	

	RectangleShape azul;
	RectangleShape vermelho;
	RectangleShape fundo;
	RectangleShape versus;
	Font font;
	font.loadFromFile("C:\\TBRB\\Rooster\\Rinha\\fonts\\blops.ttf");

	string __galo1 = p1.getName();
	string __galo2 = p2.getName();

	Text galo1(__galo1, font, window.getSize().y / 30);
	Text galo2(__galo2, font, window.getSize().y / 30);


	// galo2.setPosition();

	azul.setTexture(__azul);
	vermelho.setTexture(__vermelho);
	versus.setTexture(__versus);
	fundo.setTexture(__fundo);
	int arraysize = window.getSize().y / 2;
	float size = window.getSize().x;

	azul.setPosition(-size * 0.7, 0);
	vermelho.setPosition(size * 0.7, 0);
	fundo.setPosition(0, 0);
	versus.setPosition(0, 0);


	azul.setSize((Vector2f)window.getSize());
	vermelho.setSize((Vector2f)window.getSize());
	fundo.setSize((Vector2f)window.getSize());
	versus.setSize((Vector2f)window.getSize());
	Clock time;
	Clock opacityTime;


	galo1.setPosition(window.getSize().x * 0.45 + azul.getPosition().x - galo1.getGlobalBounds().width, window.getSize().y * 0.3);
	galo2.setPosition(window.getSize().x * 0.55 + vermelho.getPosition().x, window.getSize().y * 0.65);
	
	p2.setPosition(Vector2f(galo2.getPosition().x + galo2.getCharacterSize() * 5 * 2.2, galo2.getPosition().y - galo2.getGlobalBounds().height));
	p1.setPosition(Vector2f(galo1.getPosition().x - galo1.getCharacterSize() * 5 * 1.2, p1.getPosition().y - galo1.getGlobalBounds().height * 1.5));

	p2.noGravity = true;
	p1.noGravity = true;

	p1.setState(DANCING);
	p2.setState(DANCING);

	float pauseMilisec = 8000;
	int animState = 1;
	int opacity = 0;
	int fundoopacity = 0;
	float movefactor = (float)window.getSize().x / 60;
	bool versusvisible = false;
	time.restart();
	opacityTime.restart();
	fundo.setFillColor(Color::Color(255, 255, 255, 0));
	fundoluta.setFillColor(Color::Color(0, 0, 0, 255));

	while (window.isOpen()) {
		int mousex = Mouse::getPosition(window).x;
		int mousey = Mouse::getPosition(window).y;
		printf("x: %f% y: %f%\r", (float)mousex / window.getSize().x, (float)mousey / window.getSize().y);


		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}

			if (e.type == Event::KeyPressed) {
				p2.noGravity = false;
				p1.noGravity = false;
				fundoluta.setFillColor(Color::White);
				return 0;
			}
		}

		
		
		if (fundoopacity == 255) {
			return 0;
		}


		if (opacityTime.getElapsedTime().asMicroseconds() >= 4000) {
			if (animState == 1) {
				if (opacity < 255) {
					opacity += 10;
					if (opacity > 255) {
						opacity = 255;
					}

				}
			}

			else if (animState == -1) {
				if (opacity > 0) {
					opacity -= 5;
					if (opacity < 0) {
						opacity = 0;
					}
				}

				if (fundoopacity < 255) {
					fundoopacity += 2;
					if (fundoopacity > 255) {
						fundoopacity = 255;
					}
					
				}

				fundoluta.setFillColor(Color::Color(255, 255, 255, fundoopacity));
			}

			opacityTime.restart();
			fundo.setFillColor(Color::Color(255, 255, 255, opacity));
		}



		if (animState == 1) {
			if (azul.getPosition().x - movefactor < 0 && azul.getPosition().x < 0) {
				if (time.getElapsedTime().asMilliseconds() >= 6) {
					azul.move(movefactor, 0);
					vermelho.move(-movefactor, 0);
					galo1.move(movefactor, 0);
					galo2.move(-movefactor, 0);

					moveGalo(p1, movefactor, 0);
					moveGalo(p2, -movefactor, 0);

					movefactor += 0.2;
					time.restart();
				}
			}
			else {
				azul.setPosition(0, 0);
				vermelho.setPosition(0, 0);
				galo1.setPosition(window.getSize().x * 0.45 - galo1.getGlobalBounds().width, galo1.getPosition().y);
				galo2.setPosition(window.getSize().x * 0.55, galo2.getPosition().y);
				animState = 0;
				time.restart();
			}

		}
		else if (animState == 0) {
			static float frames = 0;
			versusvisible = true;

			versus.move(sin(frames) * 2, cos(frames) * 2);
			frames += 01;

			static bool createAnim = true;
			if (createAnim) {
				p.create(arraysize, window.getSize().x * 0.666666 - arraysize, 0);
				p.setColor(Color::Yellow);
				createAnim = false;
			}
			if (time.getElapsedTime().asMilliseconds() >= pauseMilisec) {
				animState = -1;
				time.restart();
				versusvisible = false;
				p.~ParticleAnimation();
				createAnim = true;
			}
		}

		else if (animState == -1) {
			movefactor = window.getSize().x / 60;
			if (azul.getPosition().x >= -size * 0.7) {
				if (time.getElapsedTime().asMilliseconds() >= 6) {
					azul.move(-movefactor, 0);
					vermelho.move(movefactor, 0);
					galo1.move(-movefactor, 0);
					galo2.move(movefactor, 0);
					time.restart();
					p2.noGravity = false;
					p1.noGravity = false;
				}
			}
	

		}

		if (!p1.noGravity || animState == 0) {
			p1.update();
			p2.update();
		}
		else {
			p1.updateWithoutPhysics();
			p2.updateWithoutPhysics();
		}
		window.clear();
		window.draw(fundoluta);
		window.draw(fundo);
		window.draw(azul);
		window.draw(vermelho);
		if (versusvisible)
			window.draw(versus);
		window.draw(galo1);
		window.draw(galo2);
		p.update();
		p.show(&window);
		
		p1.show(window);
		p2.show(window);

		window.display();
	}



}


#endif