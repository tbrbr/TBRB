
namespace Rooster {

	class Particle {
		Vector2f position;
		float hSpeed = 0;
		float vSpeed = 0;
		float friction = 0.999;
		float vAcc = Gravity / 10;
		Color color;
		CircleShape point;
	public:

		Particle(Color color) {
			point.setRadius(1);
			this->color = color;
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
			this-> hSpeed = hSpeed;
			this-> vSpeed = vSpeed;
		}
		void update() {
			position.x += hSpeed;
			hSpeed *= friction;
			position.y += vSpeed + vAcc;
		}
		void draw(RenderWindow& window) {
			window.draw(point);
		}
	};

	class effects {
	protected:
		std::vector <Particle> gotas;
		Vector2f position;
		
	public:

		void setPosition(Vector2f position) {
			this->position = position;
		}
		void setPosition(float x, float y) {
			this->position.x = x;
			this->position.y = y;
		}
		
		virtual void update() = 0;
		virtual void draw(RenderWindow& pqp) = 0;

	};

	class explosion : public effects {
		float radius;
		Vector2f center;
		Vector2f impact;

	public:
		explosion(float radius, Vector2f center,Color cor, Vector2f impact){
			float diameter = radius * 2;
			for (int i = 0; i < diameter;i++) {
				Particle p(cor);
				p.setPosition(center);
				p.setImpulse(
					sin (360/i * impact.x),
					cos (360/i * impact.y)
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
		void draw(RenderWindow& pqp) override {
			for (int i = 0; i < gotas.size(); i++) {
				gotas[i].draw(pqp);
			}
			
		}
	};
}
