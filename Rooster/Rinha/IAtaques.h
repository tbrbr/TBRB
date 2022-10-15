#ifndef ITATECH_JR
#define ITATECH_JR


namespace Rooster {
	

	typedef struct {
		Vector2f center;
		int radius;


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
		
	};
}


#endif