
namespace Rooster {

	class Particle {
		Vector2f position;
		float hSpeed = 0;
		float vSpeed = 0;
		float vAcc = 0;
		float hAcc = 0;

		float maxHspd = 100;
		float maxVspd = 100;


		float ang = 0;
		float angSpeed = 0;
		float angAcc = 0;

		float angFriction = 0.999;

		float friction = 0.999;

		float life = 0;
		float active = false;



		bool hasSprite = false;


		float sprScl;
		Vector2f sprCenter;
		Sprite sprite;
		

		Color color;
		float radius = 2;
		
		CircleShape point;




	public:

		Particle(Color color) {
			point.setRadius(1);
			this->color = color;
			point.setFillColor(color);

		}
		Particle() {
			point.setRadius(10);
			color = Color::Red;
			point.setFillColor(color);

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
		void setImpulse(float hSpeed,float vSpeed) {
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

				hSpeed *= friction;
				vSpeed *= friction;

				hSpeed = constrain(hSpeed, -maxHspd, maxHspd);
				vSpeed = constrain(vSpeed, -maxVspd, maxVspd);

				position.x += hSpeed;
				position.y += vSpeed;


				if (hasSprite) {
					sprite.setPosition(position.x, position.y);
					sprite.setOrigin(sprCenter * sprScl);
					sprite.setScale(sprScl, sprScl);
				}
				else {
					point.setPosition(position.x, position.y);
					point.setOrigin(radius, radius);
					point.setRadius(radius);
				}

				life--;

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







	class Effects {
	protected:
		std::vector <Particle> gotas;
		Vector2f position;

		float depth = 0;
		
	public:

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






	class ExplosionEffect : public Effects {
		float radius;
		Vector2f center;
		Vector2f impact;

	public:
		ExplosionEffect(float radius, Vector2f center,Color cor, Vector2f impact){
			int diameter = radius * 2;

			for (int i = 0; i < diameter;i++) {


				Particle p(Color::Red);

				p.setPosition(center);
				int ang = rand() % 360;

				int impactx = rand() % (int)impact.x;
				int impacty = rand() % (int)impact.y;

				p.setImpulse(
					 cos(toRadiAnus(ang))*impactx + impact.x,
					 sin(toRadiAnus(ang))*impacty + impact.y
				);

				
				gotas.push_back(p);
			}

		}

		void setRadius(float radius) {
			this->radius = radius;
		}
		void update() override{
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].update();
			}

		}
		void draw(RenderWindow& window) override {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].draw(window);
			}
			

		}
	};
}
