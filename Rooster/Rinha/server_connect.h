#ifndef KKKKKKKKKKKKKKKKKKKKK  
#define KKKKKKKKKKKKKKKKKKKKK
#include <functional> 
#include "textBox.h"

bool isHost = false;

void waitConnection(TcpSocket* socket, TcpListener* listener, bool* connect) {
	socket->setBlocking(true);
	listener->listen(59000);
	listener->accept(*socket);
	*connect = true;

}

int create(RenderWindow* window, RectangleShape& background, TcpSocket* socket, TcpListener* listener) {
	socket->disconnect();
	listener->close();
	Text* t[3];

	Font font;
	Font titleFont;
	Font ipFont;
	titleFont.loadFromFile("fonts/CloisterBlack.ttf");
	font.loadFromFile("fonts/blops.ttf");
	ipFont.loadFromFile("fonts/ARIAL.TTF");


	Text title("CREATE MATCH", titleFont, SCREEN_HEIGHT / 13);
	title.setPosition(SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.15);
	title.setFillColor(Color::Red);

	RectangleShape rectangle;
	rectangle.setSize(Vector2f(SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.4));
	rectangle.setPosition(SCREEN_WIDTH / 2 - rectangle.getSize().x / 2, SCREEN_HEIGHT / 2 - rectangle.getSize().y / 2);
	rectangle.setFillColor(Color::Black);
	rectangle.setOutlineThickness(4);
	rectangle.setOutlineColor(Color::Red);

	Text ip(IpAddress::getLocalAddress().toString(), ipFont, SCREEN_HEIGHT / 15);
	ip.setFillColor(Color::Red);
	ip.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2 - ip.getGlobalBounds().width / 2, rectangle.getPosition().y + rectangle.getSize().y * 0.1);

	Text wait("Waiting connection", font, SCREEN_HEIGHT / 60);
	Text p(" . . .", ipFont, SCREEN_HEIGHT / 20);
	p.setFillColor(Color::Red);

	int pontos = 3;
	Clock clock;
	clock.restart();
	wait.setFillColor(Color::Red);
	wait.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2 - wait.getGlobalBounds().width / 2 - p.getGlobalBounds().width / 2, ip.getPosition().y + ip.getGlobalBounds().height * 2.5);
	p.setPosition(wait.getPosition().x + wait.getGlobalBounds().width, wait.getPosition().y - wait.getGlobalBounds().height * 1.5);

	bool con = false;
	Thread connect(std::bind(&waitConnection, socket, listener, &con));
	connect.launch();

	Text cancel("CANCEL", font, SCREEN_HEIGHT / 35);
	RectangleShape cancelButton(Vector2f(cancel.getGlobalBounds().width * 1.3, cancel.getGlobalBounds().height * 2.5));
	cancelButton.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2 - cancelButton.getSize().x / 2, rectangle.getPosition().y + rectangle.getSize().y * 0.7);
	cancel.setPosition(cancelButton.getPosition().x + cancelButton.getSize().x / 2 - cancel.getGlobalBounds().width / 2, cancelButton.getPosition().y + cancelButton.getSize().y / 2 - cancel.getGlobalBounds().height / 1.5);
	cancel.setFillColor(Color::Red);
	cancelButton.setOutlineThickness(3);
	cancelButton.setOutlineColor(Color::Red);
	cancelButton.setFillColor(Color::Transparent);

	while (window->isOpen()) {

		Event e;

		while (window->pollEvent(e)) {
			if (e.type == Event::Closed) {
				window->close();
				connect.terminate();
			}

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Escape) {
					connect.terminate();
					return MULTI_MODE;
				}
			}

			if (e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left) {

					
					if (ButtonCheck::isButtonComMouseNele(cancelButton, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
						connect.terminate();
						return MULTI_MODE;
					}

				}
			}
		}


		if (con) {
			println("CONECTOU");
			connect.terminate();
			isHost = true;
			return MULTI_SELECT;
		}

		if (clock.getElapsedTime().asMilliseconds() >= 400) {
			if (pontos == 3) {
				p.setString("");
				pontos = 0;
			}
			else {
				pontos++;
				p.setString(p.getString().toAnsiString() + " .");
			}
			clock.restart();
		}

		window->clear();
		window->draw(background);
		window->draw(rectangle);
		window->draw(ip);
		window->draw(wait);
		window->draw(p);
		window->draw(cancelButton);
		window->draw(cancel);
		window->display();
	}
}

int join(RenderWindow* window, RectangleShape& background, TcpSocket* socket, TcpListener* listener) {
	listener->close();
	socket->disconnect();

	RectangleShape area;
	Vector2f area_size;
	Vector2f area_position;
	area_size.x = window->getSize().x * 0.4;
	area_size.y = window->getSize().y * 0.4;

	area_position.x = window->getSize().x / 2 - area_size.x / 2;
	area_position.y = window->getSize().y / 2 - area_size.y / 2;

	area.setSize(area_size);
	area.setPosition(area_position);
	area.setFillColor(Color::Black);
	area.setOutlineColor(Color::Red);
	area.setOutlineThickness(4);

	

	while (window->isOpen() && false) {
		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed) {
				window->close();
				return INTRO;
			}

			if(e.type == Event::MouseButtonPressed) {
				if (e.mouseButton.button == Mouse::Left)
				{

				}
			}
		}

		window->draw(area);
		window->display();

	}

	socket->connect("10.50.208.56", 59000);
	return MULTI_SELECT;
}
#endif // ! 
