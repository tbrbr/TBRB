
namespace Rooster {

	
		Texture star;
		Sprite estrelinha;
			
		
		void drawEstrelinhas(RenderWindow * window,Vector2f position) {
			star.loadFromFile("sprites\\estrelinhas.png");
			estrelinha.setTexture(star);
						
			static int frames = 0;
			frames++;
			if (frames > 60) {
				frames = 0;
			}
			int frameTime = frames % 11 - 5;
			if (frames == 5) {
				estrelinha.setScale(-10, 10);
				
			}
			else if(frames == -5) {
				estrelinha.setScale(10, 10);
			}
			
			estrelinha.setPosition(0, 0);
			window->draw(estrelinha);
			
			
		}
		
	
	class Particle {


	public:
		Vector2f position;
		float hSpeed = 0;
		float vSpeed = 0;
		float vAcc = 0;
		float hAcc = 0;

		float maxHspd = 10;
		float maxVspd = 10;


		float ang = 0;
		float angSpeed = 0;
		float angAcc = 0;

		float angFriction = 0.999;

		float friction = 0.999;

		int life = 500;
		bool mortal = true;
		float active = false;



		bool hasSprite = false;


		float sprScl;
		Vector2f sprCenter;
		Sprite sprite;


		Color color;
		float radius = 10;

		CircleShape point;





		Particle(Color color) {
			point.setRadius(1);
			this->color = color;
			point.setFillColor(color);
			active = true;

		}
		Particle() {
			point.setRadius(10);
			color = Color::Red;
			point.setFillColor(color);
			active = true;

		}
		void setPosition(Vector2f position) {
			this->position = position;
		}
		void setPosition(float x, float y) {
			this->position.x = x;
			this->position.y = y;
		}
		Vector2f getPosition() {
			return position;
		}
		void setImpulse(float hSpeed, float vSpeed) {
			this->hSpeed = hSpeed;
			this->vSpeed = vSpeed;
		}

		void addImpulse(float hSpeed, float vSpeed) {
			this->hSpeed += hSpeed;
			this->vSpeed += vSpeed;
		}



		void update() {

			if (active) {
				hSpeed += hAcc;
				vSpeed += vAcc;
				ang += angSpeed;

				hSpeed *= friction;
				vSpeed *= friction;
				angSpeed *= angFriction;

				hSpeed = constrain(hSpeed, -maxHspd, maxHspd);
				vSpeed = constrain(vSpeed, -maxVspd, maxVspd);

				position.x += hSpeed;
				position.y += vSpeed;
				ang += angSpeed;


				if (hasSprite) {
					sprite.setPosition(position.x, position.y);
					sprite.setOrigin(sprCenter * sprScl);
					sprite.setRotation(ang);
					sprite.setScale(sprScl, sprScl);
				}
				else {
					point.setPosition(position.x, position.y);
					point.setOrigin(radius, radius);
					point.setRadius(radius);
				}

				life -= mortal;

				if (life < 0) {
					active = false;
				}
			}

		}
		void draw(RenderWindow& window) {

			if (active) {
				if (hasSprite) {
					window.draw(sprite);
				}
				else {
					window.draw(point);
				}
			}
		}


		void draw(RenderWindow& window, Vector2f offset) {

			if (active) {
				if (hasSprite) {
					sprite.setPosition(sprite.getPosition().x + offset.x, sprite.getPosition().y + offset.y);

					window.draw(sprite);
				}
				else {
					point.setPosition(point.getPosition().x + offset.x, point.getPosition().y + offset.y);

					window.draw(point);
				}
			}
		}




	};







	class Effect {
	protected:
		std::vector <Particle> gotas;
		Vector2f position;


	public:

		bool active = true;
		int life = 100;
		float depth = 0;

		void setPosition(Vector2f position) {
			this->position = position;
		}
		void setPosition(float x, float y) {
			this->position.x = x;
			this->position.y = y;
		}

		virtual void update() = 0;
		virtual void draw(RenderWindow& window) = 0;

	};






	class ExplosionEffect : public Effect {
		float radius;
		Vector2f center;
		Vector2f impact;

	public:
		ExplosionEffect(float radius, Vector2f center, Color cor, Vector2f impactForce, float explosionForce, float angle, float angleFocus) {
			int diameter = radius * 2;

			life = 100;

			for (int i = 0; i < 500; i++) {


				Particle p(Color::Red);

				p.setPosition(center);
				p.vAcc = Gravity/80;
				p.mortal = true;
				p.life = randIntRange(50, 150);
				p.maxHspd = 40;
				p.maxVspd = 40;
				p.radius = randIntRange(1, 10);

				float ang = toRadiAnus(randFloatRangeNormal(angle-180,angle+180, angleFocus));


				float impact = randFloat(explosionForce);

				p.setImpulse(
					(cos(ang) * impact) + impactForce.x,
					(sin(ang) * impact) + impactForce.y
				);


				gotas.push_back(p);
			}

		}

		void setRadius(float radius) {
			this->radius = radius;
		}

		void update() override {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].update();			}

		}

		void draw(RenderWindow& window) override {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].draw(window);
			}
		}
	};




	class ParticleSystem {


	public:
		std::vector<Effect*> effects;



		ParticleSystem() {

		}

		void update() {
			for (int i = 0; i < effects.size(); i++) {
				effects[i]->update();
			}


			for (int i = 0; i < effects.size(); i++) {
				if (!effects[i]->active) {
					removeEffect(i);
				}
			}

		}






		void draw(RenderWindow& window) {
			for (int i = 0; i < effects.size(); i++) {
				effects[i]->draw(window);
			}
		}


		void removeEffect(int effectId) {
			delete effects[effectId];
			effects.erase(effects.begin() + effectId);
		}

		void clear() {
			for (int i = 0; i < effects.size(); i++) {
				delete effects[i];
			}

			effects.clear();
		}


	};
}