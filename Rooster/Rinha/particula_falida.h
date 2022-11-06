
#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <vector>

struct __Particle {

	sf::RectangleShape particle;
	int xspeed = 0;
	int yspeed = 0;
	sf::Vector2f pos;
	sf::Vector2f size;


	__Particle(int sizex, int sizey, int xspeed, int ypeed, int posx, int posy) {
		this->setPosition(posx, posy);
		this->setSize(sizex, sizey);
		particle.setFillColor(sf::Color::White);
		this->xspeed = xspeed;
		this->yspeed = ypeed;
	}

	void update() {
		yspeed += 1;
		pos.y += yspeed;
		pos.x += xspeed;
		particle.setPosition(pos);
	}

	void setSize(sf::Vector2f v) {
		size = v;
		particle.setSize(size);
	}

	void setSize(int x, int y) {
		setSize(sf::Vector2f(x, y));
	}

	void setPosition(sf::Vector2f v) {
		pos = v;
		particle.setPosition(v);
	}

	void setPosition(float x, float y) {
		setPosition(sf::Vector2f(x, y));
	}

	void draw(sf::RenderWindow* window) {
		window->draw(particle);
	}

	void setColor(sf::Color color) {
		particle.setFillColor(color);
	}

};


class ParticleAnimation {
private:
	std::vector<__Particle> particles;

public:
	ParticleAnimation(std::size_t, int, int);
	ParticleAnimation();
	~ParticleAnimation();
	void update();
	void show(sf::RenderWindow* window);
	void reset(int, int);
	void create(std::size_t, int, int);
	void setColor(sf::Color color);

};

ParticleAnimation::ParticleAnimation(std::size_t size, int posx, int posy) {
	this->create(size, posx, posy);
}

ParticleAnimation::~ParticleAnimation() {
	particles.clear();
}


void ParticleAnimation::reset(int posx, int posy) {
	std::size_t size = particles.size();
	particles.clear();
	this->create(size, posx, posy);
}
void ParticleAnimation::show(sf::RenderWindow* window)
{
	for (std::size_t i = 0; i < particles.size(); i++)
	{
		particles.at(i).draw(window);
	}
}

void ParticleAnimation::update()
{
	static sf::Clock clock;
	if (clock.getElapsedTime().asMilliseconds() >= 17)
	{
		for (std::size_t i = 0; i < particles.size(); i++)
		{
			particles.at(i).update();
		}
		clock.restart();
	}
}

void ParticleAnimation::create(std::size_t size, int posx, int posy) {
	if (this->particles.size() > 0) {
		this->particles.clear();
	}
	for (std::size_t i = 0; i < size; i++) {
		particles.push_back(__Particle(3, 3, rand() % 60 - 30 + 1, rand() % 7 - 8, posx + size - i * 1.2, posy + (i * 2)));
	}
}

ParticleAnimation::ParticleAnimation() {

}

void ParticleAnimation::setColor(sf::Color color) {
	for (std::size_t i = 0; i < particles.size(); i++) {
		particles.at(i).setColor(color);
	}
}