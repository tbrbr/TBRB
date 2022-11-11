#pragma once

#ifndef TEASSD
#define TEASSD


#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "checador_de_posicao.h"
#pragma warning(disable : 4996)

using namespace sf;

class TextBox {

	RectangleShape textBox;
	bool _isSelected = false;

	struct Cursor
	{
		RectangleShape cursor;
		bool isVisible;
		Clock clock;

		void draw(RenderWindow* window) {
			this->update();
			if (isVisible)
				window->draw(cursor);
		}

		void update() {
			if (clock.getElapsedTime().asMilliseconds() >= 500) {
				isVisible = !isVisible;
				clock.restart();
			}
		}
	};



	Cursor cursor;
	sf::Font font;
	sf::Text text;
	sf::Text placeHolder;

public:
	TextBox(const std::string placeholder, int xposition, int yposition, int characterSize, int sizex, int max_lenght = 100) {

		textBox.setPosition(xposition, yposition);
		textBox.setSize(Vector2f(sizex, characterSize * 1.5));

		font.loadFromFile("C:\\TBRB\\Rooster\\Rinha\\fonts\\Mortal-Kombat-MK11.otf");
		text.setCharacterSize(characterSize);
		text.setString("");
		text.setFont(font);
		text.setFillColor(Color::Red);
		text.setPosition(textBox.getPosition().x + 4, textBox.getPosition().y + textBox.getSize().y / 2 - characterSize / 1.5);

		placeHolder.setCharacterSize(characterSize);
		placeHolder.setString(placeholder);
		placeHolder.setFont(font);
		placeHolder.setFillColor(Color::Color(200, 200, 200));
		placeHolder.setPosition(text.getPosition());

		cursor.cursor.setSize(Vector2f(1, characterSize));
		cursor.cursor.setFillColor(Color::Black);
		cursor.cursor.setPosition(text.getPosition().x, text.getPosition().y + 6);
		cursor.clock.restart();
	}

	void draw(RenderWindow* window) {


		window->draw(textBox);
		if (text.getString().getSize() == 0) {
			window->draw(placeHolder);
		}
		window->draw(text);
		if (_isSelected)
			cursor.draw(window);
	}

	void update(char unicode) {
		if (!_isSelected) {
			return;
		}
		if (text.getString().getSize() == 15) {
			return;
		}
		text.setString(text.getString() + unicode);
		cursor.cursor.setPosition(text.getGlobalBounds().width + text.getPosition().x, cursor.cursor.getPosition().y);
	}

	void removeChar() {
		if (!_isSelected) {
			return;
		}
		std::string str = text.getString().toAnsiString();
		if (str.length() == 0) {
			return;
		}
		char v[20];
		strncpy_s(v, str.c_str(), str.length() - 1);
		text.setString(v);
		cursor.cursor.setPosition(text.getGlobalBounds().width + text.getPosition().x, cursor.cursor.getPosition().y);
	}



	Text inline getText() {
		return text;
	}

	void inline setTextBoxSelected(bool isSelected) {
		this->_isSelected = isSelected;
	}

	bool inline checkMouseColision(int mousex, int mousey) {
		return ButtonCheck::isButtonComMouseNele(this->textBox, mousex, mousey);
	}
	bool inline isSelected() {
		return this->_isSelected;
	}

	void setPosition(int x, int y) {
		textBox.setPosition(x, y);
		text.setPosition(textBox.getPosition().x + 4, textBox.getPosition().y + textBox.getSize().y / 2 - text.getCharacterSize() / 1.5);
		placeHolder.setPosition(text.getPosition());
		cursor.cursor.setPosition(text.getGlobalBounds().width + text.getPosition().x, text.getPosition().y + 6);
	}

	void setPosition(Vector2i pos) {
		setPosition(pos.x, pos.y);
	}
};




#endif // !TEASSD
