#ifndef ITATECH_JR
#define ITATECH_JR

namespace Rooster {
	

	typedef struct {
		Vector2f center;
		int radius;

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

			
			texture.loadFromFile(textureFile);
			sprite.setTexture(texture);
			sprite.setPosition(position);
			sprite.setScale(scl);

		}
		Projectile(Vector2f position, const char* textureFile, float hSpeed, float vSpeed, Vector2f scl,IntRect spriteRec) {
			this->position = position;
			this->texture = texture;
			this->hSpeed = hSpeed;
			this->vSpeed = vSpeed;
			this->vAcc = Gravity / 10;

			texture.loadFromFile(textureFile);
			sprite.setTexture(texture);
			sprite.setPosition(position);
			sprite.setScale(scl);
			sprite.setTextureRect(spriteRec);

		}

		void setVisibility(bool isVisible) {
			this->isVisible = isVisible;
		}
		bool getVisibility() {
			return isVisible;
		}
		void setScale(Vector2f scale) {
			scl = scale;
		}
		void setImpulse(float hSpeed, float vSpeed) {
			this->hSpeed = hSpeed;
			this->vSpeed = vSpeed;
		}
		void setTextureRec(IntRect rec) {
			sprite.setTextureRect(rec);
		}
		Sprite getSprite() {
			return sprite;
		}
		void setPosition(Vector2f position) {
			this->position = position;
		}
		Vector2f getSize() {
			return Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height);
		}
		Vector2f getPosition() {
			return position;
		}
		void update() {


			position.x += hSpeed;
			position.y += vSpeed;

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
		int id;
		float Stun;
		float CoolDown;
		HitBox hitbox;
		int Damage;
		float KnockBack;

		float angle;

		bool isAtacking = false;
		bool getHitted = false;
		Clock init;
		Time timeLapse;
		Clock init2;
		Time timeLapse2;
		

		Vector2f colPos;
		Vector2f colDif;
		float colAngle = 0;



		SoundBuffer bufferCollision;
		Sound soundCollision;
		
		
			
		Ataques(int id,float Stun,float CoolDown,HitBox hitbox,int Damage,float KnockBack,float angle,Time timelapse,const char* txt) {
			this->id = id;
			this->Stun = Stun;
			this->CoolDown = CoolDown;
			this->hitbox = hitbox;
			this->Damage = Damage;
			this->KnockBack = KnockBack;
			this->timeLapse = timelapse;
			this->angle = angle;
			bufferCollision.loadFromFile(txt);
			soundCollision.setBuffer(bufferCollision);
		}
		Ataques(int id, float Stun, float CoolDown, HitBox hitbox, int Damage, float KnockBack,
			float angle, Time timelapse,const char* txt, Time timelapse2) {
			this->id = id;
			this->Stun = Stun;
			this->CoolDown = CoolDown;
			this->hitbox = hitbox;
			this->Damage = Damage;
			this->KnockBack = KnockBack;
			this->timeLapse = timelapse;
			this->angle = angle;
			this->timeLapse2 = timelapse2;
			bufferCollision.loadFromFile(txt);
			soundCollision.setBuffer(bufferCollision);

			colPos.x = 0;
			colPos.y = 0;

			colDif.x = 0;
			colDif.y = 0;
		}

		void playSound() {
			soundCollision.play();
		}
		
		
		bool CheckCollision(HitBox galo) {
			if (isAtacking) {
				colPos.x = (galo.center.x + hitbox.center.x) / 2;
				colPos.y = (galo.center.y + hitbox.center.y) / 2;
				colPos = galo.center;
				colDif = (galo.center - hitbox.center);

				colDif = normalizar(colDif);

				colAngle = vecToAngle(colDif);


				return (pointDistance(galo.center, hitbox.center) < galo.radius + hitbox.radius);
			}
			return false;
			
		}

		void createBlood(ParticleSystem& partSys) {
			ExplosionEffect* exp = new ExplosionEffect(10, colPos, Color::Red, Vector2f(colDif.x * Damage, colDif.y * Damage), 10, colAngle, 60);
			partSys.effects.push_back(exp);
		}

	};
}


#endif