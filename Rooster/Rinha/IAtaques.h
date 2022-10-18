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


	class Ataques {
	public:
		float Stun;
		float CoolDown;
		HitBox hitbox;
		int Damage;
		float KnockBack;
		bool isAtacking = false;
		Clock init;
		Time timeLapse;
		
		
		
		Ataques(float Stun,float CoolDown,HitBox hitbox,int Damage,float KnockBack,Time timelapse) {
			this->Stun = Stun;
			this->CoolDown = CoolDown;
			this->hitbox = hitbox;
			this->Damage = Damage;
			this->KnockBack = KnockBack;
			this->timeLapse = timelapse;

		}
		bool CheckCollision(HitBox galo) {
			return (pointDistance(galo.center, hitbox.center) < galo.radius + hitbox.radius);
		}

		void draw(sf::RenderWindow& window) {


		}
		
	};
}


#endif