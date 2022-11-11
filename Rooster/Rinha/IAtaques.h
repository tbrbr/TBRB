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

		// Sprite animações
		struct SpriteMap sprMap;
		float sprImage = 0;
		float sprImageSpeed = 0;

		// Physics
		float hSpeed;
		float vSpeed;
		float friction = 1;
		float vAcc;
		bool hasGravity = false;

		// Meaning of life
		int life = 1;
		bool mortal = false;
		
		

		

		Vector2f scl;

		// Pra alterar a escala sem mexer na escala base
		Vector2f sclMultiplier;
		Vector2f sclMultiplierSpeed;

		bool isVisible = false;
		Vector2f size;
		float hei;
		Transform t;

		// Se a textura ele mesmo criou ou se recebeu de fora
		//bool createdTexture = true;


	public:
		bool NULO = false;
		bool isTrans = false;
		bool facingRight;

		bool active = true;
		// 1 ou -1 vai multiplicar a escala em x
		int facingSign = 1;


		bool death = false;

		/*
		~Projectile() {
			if (createdTexture) {
				delete texture;
			}
		}
		*/

		Projectile(bool NUlO) {
			this->NULO = NULO;
		}
		Projectile(Vector2f position, const char* textureFile, float hSpeed, float vSpeed, Vector2f scl) {

			//texture = new Texture();

			this->position = position;
			this->hSpeed = hSpeed;
			this->vSpeed = vSpeed;
			this->vAcc = Gravity / 10;

			this->sclMultiplierSpeed.x = 0;
			this->sclMultiplierSpeed.y = 0;
			this->sclMultiplier.x = 0;
			this->sclMultiplier.y = 0;


			texture.loadFromFile(textureFile);
			sprite.setTexture(texture);
			sprite.setPosition(position);
			size.x = sprite.getLocalBounds().width;
			size.y = sprite.getLocalBounds().height;

			sprite.setScale(scl);


		}
		Projectile(Vector2f position, const char* textureFile, float hSpeed, float vSpeed, Vector2f scl, IntRect spriteRec) {

			//texture = new Texture();

			this->position = position;
			this->hSpeed = hSpeed;
			this->vSpeed = vSpeed;
			this->vAcc = Gravity / 10;

			this->sclMultiplierSpeed.x = 0;
			this->sclMultiplierSpeed.y = 0;
			this->sclMultiplier.x = 0;
			this->sclMultiplier.y = 0;

			texture.loadFromFile(textureFile);
			sprite.setTexture(texture);
			sprite.setPosition(position);
			sprite.setScale(scl);
			sprite.setTextureRect(spriteRec);
			size.x = sprite.getLocalBounds().width;
			size.y = sprite.getLocalBounds().height;

		}

		Projectile(Vector2f position, const char* textureFile, float hSpeed, float vSpeed, Vector2f scl, struct SpriteMap sprMap) {
			this->position = position;
			this->hSpeed = hSpeed;
			this->vSpeed = vSpeed;
			this->vAcc = Gravity / 10;

			this->sclMultiplierSpeed.x = 0;
			this->sclMultiplierSpeed.y = 0;
			this->sclMultiplier.x = 0;
			this->sclMultiplier.y = 0;

			texture.loadFromFile(textureFile);
			sprite.setTexture(this->texture);
			sprite.setPosition(position);
			sprite.setScale(scl);
			size.x = sprite.getLocalBounds().width;
			size.y = sprite.getLocalBounds().height;
			
			this->sprMap = sprMap;

			//createdTexture = false;
		}


		void setOriginCenter() {
			sprite.setOrigin(size.x / 2, size.y / 2);
		}

		void setOriginCenter(Vector2f origin) {
			sprite.setOrigin(origin);
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
			sprite.setScale(x, y);
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
		Vector2f getSpritePosition() {
			return sprite.getPosition();
		}

		void setPosition(Vector2f position) {
			this->position = position;
		}
		void setPosition(float x, float y) {
			setPosition(Vector2f(x, y));
		}
		void setSpritePosition(float x, float y) {
			sprite.setPosition(x,y);
		}
		Vector2f getSize() {
			return Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
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

		void setFriction(float friction) {
			this->friction = friction;
		}

		void setSpriteImage(int spriteImage) {
			this->sprImage = spriteImage;
		}

		float getSpriteImage() {
			return sprImage;
		}

		void setSpriteImageSpeed(float spriteImageSpeed) {
			this->sprImageSpeed = spriteImageSpeed;
		}

		void setMortality(bool isMortal) {
			mortal = isMortal;
		}

		void setLife(int lifeFrames) {
			life = lifeFrames;
		}

		void setScaleSpeed(float hspd, float vspd) {
			sclMultiplierSpeed.x = hspd;
			sclMultiplierSpeed.y = vspd;
		}

		void setScaleMultiplier(float x, float y) {
			sclMultiplier.x = x;
			sclMultiplier.y = y;
		}



		Transform getTransform() {
			return t;
		}
		void update() {
			death = false;

			if (active) {
				if (hasGravity) {
					vSpeed += vAcc;
				}

				hSpeed *= friction;
				vSpeed *= friction;

				position.x += hSpeed;
				position.y += vSpeed;

				// Animação de sprite
				if (sprMap.imgNumber > 0) {
					sprImage += sprImageSpeed;
					if (sprImage > sprMap.imgNumber) {
						sprImage -= sprMap.imgNumber;
					}

					sprite.setTextureRect(sprMap.images[sprImage]);
				}

				// Ideologia
				if (!isTrans) {
					sprite.setPosition(position);
				}


				sclMultiplier += sclMultiplierSpeed;

				sprite.setScale(Vector2f(scl.x * (1+sclMultiplier.x) * facingSign, scl.y * (1+sclMultiplier.y)));

				life -= mortal;
				if (life < 0) {
					isVisible = false;
					death = true;
					active = false;
				}
			}


		}
		void draw(RenderWindow& window) {
			if (isVisible) {
				window.draw(sprite);

			}
		}
		void drawTrans(RenderWindow& window) {
			if (isVisible) {
				window.draw(sprite, t);
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

		int invFrames = 30;

		Vector2f colPos;
		Vector2f colDif;
		float colAngle = 0;

		SoundBuffer bufferCollision;
		Sound soundCollision;

		bool soundPlayed = false;


		Ataques(int id, float Stun, HitBox hitbox, int Damage, float KnockBack, float angle, Time timelapse, const char* txt) {
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
			float angle, Time timelapse, const char* txt, Time timelapse2) {
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

				// Esses angulos nao estao funcionando
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

			ExplosionEffect* exp = new ExplosionEffect(colPos, 10, angle, 180, 0, 0);

			exp->sanguePreset();

			exp->createMultipleParticles(1 + Damage * 5);
			partSys.addEffect(exp);
		}

	};
}


#endif