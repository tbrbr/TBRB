#ifndef ITATECH_JR
#define ITATECH_JR


namespace Rooster {
	

	typedef struct {
		Vector2f center;
		int radius;


		/*
		void draw(sf::RenderWindow& window) {
			sf::CircleShape circle(radius);
			circle.setPosition(center.x, center.y);
			circle.setOrigin(radius, radius);
			circle.setFillColor(sf::Color::White);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(2);

			window.draw(circle);

		}
		*/


	} HitBox;


	class Projectile {

		Vector2f position;
		Texture texture;
		Sprite sprite;
		float hSpeed;
		float vSpeed;
		float vAcc;
		Vector2f scl;
		bool isVisible = false;

	public:
		Projectile(Vector2f position,  const char* textureFile, float hSpeed, float vSpeed, Vector2f scl) {
			this->position = position;
			this->texture = texture;
			this->hSpeed = hSpeed;
			this->vSpeed = vSpeed;
			this->vAcc = Gravity / 10;

			texture;
			texture.loadFromFile(textureFile);
			sprite.setTexture(texture);
			sprite.setPosition(position);
			sprite.setScale(scl);

		}
		void setVisibility(bool isVisible) {
			this->isVisible = isVisible;
		}
		void setScale(Vector2f scale) {
			scl = scale;
		}
		void update() {

			position.x += hSpeed;
			position.y += (vAcc - vSpeed);

			sprite.setPosition(position);
			sprite.setScale(scl);
		}
		void draw(RenderWindow& window) {
			if (isVisible) {
				window.draw(sprite);
			}
		}


	};


	class Ataques {
	public:
		float Stun;
		float CoolDown;
		HitBox hitbox;
		int Damage;
		float KnockBack;

		float angle;

		bool isAtacking = false;
		Clock init;
		Time timeLapse;
		
			
		Ataques(float Stun,float CoolDown,HitBox hitbox,int Damage,float KnockBack,float angle,Time timelapse) {
			this->Stun = Stun;
			this->CoolDown = CoolDown;
			this->hitbox = hitbox;
			this->Damage = Damage;
			this->KnockBack = KnockBack;
			this->timeLapse = timelapse;
			this->angle = angle;

		}


		bool CheckCollision(HitBox galo) {
			if (isAtacking) {
				return (pointDistance(galo.center, hitbox.center) < galo.radius + hitbox.radius);
			}
			return false;
			
		}

	};
}


#endif