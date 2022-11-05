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
		Vector2f size;
		float hei;
		Transform t;
		
	public:
		bool NULO = false;
		bool isTrans = false;
		bool facingRight;

		Projectile(bool NUlO) {
			this->NULO = NULO;
		}
		Projectile(Vector2f position,  const char* textureFile, float hSpeed, float vSpeed, Vector2f scl) {
			this->position = position;
			this->texture = texture;
			this->hSpeed = hSpeed;
			this->vSpeed = vSpeed;
			this->vAcc = Gravity / 10;

			
			texture.loadFromFile(textureFile);
			sprite.setTexture(texture);
			sprite.setPosition(position);
			size.x = sprite.getGlobalBounds().width;
			size.y = sprite.getGlobalBounds().height;
			
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
		void setOriginCenter() {
			sprite.setOrigin(size.x / 2, size.y / 2);
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
		void setScale(float x, float y) {
			setScale(Vector2f(x, y));
		}
		void setSpriteScale(float x, float y) {
			sprite.setScale(x,y);
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
		void setPosition(float x,float y) {
			setPosition(Vector2f(x, y));
		}
		Vector2f getSize() {
			return Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height);
		}
		Vector2f getLocalSize() {
			float lastAngle = sprite.getRotation();
			sprite.setRotation(0);
			Vector2f a(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
			sprite.setRotation(lastAngle);
			return a;
		}
		Vector2f getPosition() {
			return position;
		}
		void setSpriteAngle(float angle) {
			sprite.setRotation(angle);
		}
		void setTransfrom(Transform trans) {
			t = trans;
		}
		Transform getTransform() {
			return t;
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
		void drawTrans(RenderWindow& window) {
			if (isVisible) {
				window.draw(sprite,t);
				
			}
		}
		
	};

	

	class Ataques {
	public:
		int id;
		float Stun;
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
		
		
			
		Ataques(int id,float Stun,HitBox hitbox,int Damage,float KnockBack,float angle,Time timelapse,const char* txt) {
			this->id = id;
			this->Stun = Stun;		
			this->hitbox = hitbox;
			this->Damage = Damage;
			this->KnockBack = KnockBack;
			this->timeLapse = timelapse;
			this->angle = angle;
			bufferCollision.loadFromFile(txt);
			soundCollision.setBuffer(bufferCollision);

			colPos.x = 0;
			colPos.y = 0;

			colDif.x = 0;
			colDif.y = 0;
		}
		Ataques(int id, float Stun, HitBox hitbox, int Damage, float KnockBack,
			float angle, Time timelapse,const char* txt, Time timelapse2) {
			this->id = id;
			this->Stun = Stun;
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
		void setTimeLapse(Time timeLapse) {
			this->timeLapse = timeLapse;
		}
		
		bool CheckCollision(HitBox galo) {
			if (isAtacking) {
				colPos.x = (galo.center.x + hitbox.center.x) / 2;
				colPos.y = (galo.center.y + hitbox.center.y) / 2;
				colPos = hitbox.center;
				colDif = (galo.center - hitbox.center);

				colDif = normalizar(colDif);

				colAngle = vecToAngle(colDif);


				return (pointDistance(galo.center, hitbox.center) < galo.radius + hitbox.radius);
			}
			return false;
			
		}

		void createBlood(ParticleSystem& partSys) {

			//Vector2f(colDif.x * ((float)Damage/4), colDif.y * ((float)Damage / 4)), 10, colAngle, 60

			ExplosionEffect* exp = new ExplosionEffect(colPos, 10, angle, 180, 0, 0);
			
			exp->sanguePreset();
			exp->createMultipleParticles(500);
			partSys.addEffect(exp);
		}

	};
}


#endif