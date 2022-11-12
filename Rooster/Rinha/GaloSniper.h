#ifndef GALOSNIPER_H_INCLUDED
#define GALOSNIPER_H_INCLUDED

#include "Galo.h"

namespace Rooster {


	enum bodyParts {
		CORPO = 0,
		CABECA,
		RABO,
		ASA_FRENTE,
		ASA_ATRAS,
		PERNA_FRENTE,
		PERNA_ATRAS,
		PE_ATRAS,
		PE_FRENTE,
		BIGODE_FRENTE,
		BIGODE_ATRAS
	};

	class Sniper : public Galo {

		Texture t;

		float legWalkAngFase = 0;
		float ArmSpinAngFase = 0;
		float Arm2SpinAngFase = 0;
		SoundBuffer defenseBuffer;
		Sound defenseSound;

		Texture grenade;
		Sprite granada;
		Vector2f posGrenade;
	


	public:
		Sniper(struct GaloStats _stats, int _state, bool isp1) : Galo(_stats, _state, isp1) {
			this->name = "Sniper";

			bar = new LifeBar(maxHp, isp1, name.c_str());

			this->hiKick = new Ataques(0, 10, HitBox{ Vector2f(0, 0), 0 }, 35, 10, -PI / 4, milliseconds(500), "sounds\\fist-punch-or-kick-7171.ogg");
			this->louKick = new Ataques(1, 10, HitBox{ Vector2f(0, 0), 0 }, 30, 10, PI / 4, milliseconds(500), "sounds\\punch-2-123106.ogg");
			this->ultimateShot = new Ataques(2, 5, HitBox{ Vector2f(0, 0), 0 }, 40, 20, 0, milliseconds(1000), "sounds\\awp.ogg");
			this->superAtack = new Ataques(14, 5, HitBox{ Vector2f(0, 0), 0 }, 20, 10, 0, milliseconds(3000), "sounds\\mg34.ogg");
			// o que esse stun tem que diminuir é brincadeira
			superAtack->invFrames = 10;

			Projectile* bullet = new Projectile(Vector2f(0, 0),"sprites\\bullet.png" , 0, 0, Vector2f(0, 0));
			projectiles.push_back(*bullet);
			Projectile* n2 = new Projectile(true);
			projectiles.push_back(*n2);

			t.loadFromFile("sprites/galoSniper.png");

			model.tex = &t;
			model.loadModel("models/SniperModel.txt");

			model.autoSetBounds(model.at("Body"), model.at("BackShoe"), model.at("Head"));

			//println("Sniper Carregou");

			HitBox* hit = new HitBox;
			for (int i = 0; i < model.allBones.size(); i++) {

				if (model.boneMap.at("Sniper") != i) {
					hit->center = model.at(i)->drawPos;
					hit->radius = model.at(i)->sprite.getGlobalBounds().width / 2;

					hurtBox.push_back(*hit);
				}
			}

			delete hit;

			struct Animation agacharAnim;
			agacharAnim.init("animations/SecondAnim.txt");
			agacharAnim.playingSpeed = 1;
			agacharAnim.connectLoop = false;
			animations.push_back(agacharAnim);

			struct Animation danceAnim;
			danceAnim.init("animations/sniperDance4.txt");
			danceAnim.playingSpeed = 0.1;
			danceAnim.connectLoop = true;
			animations.push_back(danceAnim);



			defenseBuffer.loadFromFile("sounds\\block-6839.ogg");
			defenseSound.setBuffer(defenseBuffer);

			

			grenade.loadFromFile("sprites\\sniperGrenade.png");

		}


		void weatherAnim(int frames) {
			model.at(CORPO)->angle += 0;
			model.at(RABO)->angle = sin(frames / 200.f) * 20;
		}
		void jumpAnim() {

			if (facingRight) {
				ArmSpinAngFase = -(vspeed / 8) * 45;
				Arm2SpinAngFase = -(vspeed / 8) * 45;
			}
			else {
				ArmSpinAngFase = (vspeed / 8) * 45;
				Arm2SpinAngFase = (vspeed / 8) * 45;
			}

			model.at(PERNA_FRENTE)->angle = vspeed * 2;
			model.at(PERNA_FRENTE)->offset.y += vspeed / 5;
			model.at(PE_FRENTE)->angle += vspeed / 5;

			model.at(PERNA_ATRAS)->angle = vspeed / 2;
			model.at(PERNA_ATRAS)->offset.y += vspeed / 10;
			model.at(PE_ATRAS)->angle += vspeed / 5;

			model.at(BIGODE_FRENTE)->angle += vspeed / 2;
			model.at(BIGODE_ATRAS)->angle += vspeed / 2;


		}
		void cairAnim() {
			model.at(PERNA_FRENTE)->offset.y *= 0.25;
			model.at(PERNA_ATRAS)->offset.y *= 0.25;

			model.at(PE_FRENTE)->angle = 0;
			model.at(PE_ATRAS)->angle = 0;

			model.at(BIGODE_FRENTE)->angle = 345;
			model.at(BIGODE_ATRAS)->angle = 25;
		}
		void runAnim() {
			legWalkAngFase += hspeed;
			legWalkAngFase -= ((int)legWalkAngFase / 360) * 360;
			model.at(PERNA_FRENTE)->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at(PERNA_ATRAS)->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

			model.at(ASA_FRENTE)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at(ASA_ATRAS)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;

			model.at(BIGODE_FRENTE)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at(BIGODE_ATRAS)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;
		}
		void runReset() {
			legWalkAngFase *= 0.8;
			ArmSpinAngFase *= 0.8;
			Arm2SpinAngFase *= 0.8;

			model.at(PERNA_FRENTE)->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at(PERNA_ATRAS)->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

			model.at(ASA_FRENTE)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at(ASA_ATRAS)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;

			model.at(BIGODE_FRENTE)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at(BIGODE_ATRAS)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;

			model.at(CORPO)->offset.y *= 0.5;
			model.at(PE_FRENTE)->offset.y *= 0.25;
			model.at(PE_ATRAS)->offset.y *= 0.25;


		}

		void defend() override {
			estado = DEFENDING;
		}

		void agachadinha() {
			hspeed = 0;
		}

		void highKick() override {
			if (atacking == NOT_ATTACK)
				atacking = HIGH_KICK;
			hiKick->init.restart();


		}
		void lowKick() override {
			if (atacking == NOT_ATTACK)
				atacking = LOW_KICK;
			louKick->init.restart();
		}

		void especial() override {
			if (atacking == NOT_ATTACK)
				atacking = SPECIAL;
			ultimateShot->init.restart();
		}
		void super() override {
			bar->resetPower();
			
			if (atacking == NOT_ATTACK)
				atacking = SUPER;				
			superAtack->init.restart();
		}

		void superAnim() {

			Time t = superAtack->init.getElapsedTime();

			if (t > superAtack->timeLapse) {
				atacking = NOT_ATTACK;
			}

			float percentage = (float)t.asMilliseconds() / (superAtack->timeLapse.asMilliseconds());

			if (percentage < 0.25f / 3.f) {

				float thisPercentage = percentage * 3;
				model.at("Sniper")->angle += 45;
				model.at("Sniper")->sprite.setColor(Color(125,0,0,0));
				model.at(ASA_ATRAS)->angle = -45 * -sin(thisPercentage * PI / 2);
				model.at(ASA_FRENTE)->angle = -90 * sin(thisPercentage * PI / 2);

			}
			else if (percentage < 1.f / 3.f) {
				float thisPercentage = percentage * 3;

				model.at("Sniper")->angle = 0;
				model.at(ASA_ATRAS)->angle = 0;
				model.at(ASA_FRENTE)->angle = 0;
				model.at(CABECA)->angle = -10 + sin(frames) * 10;
				model.at(PERNA_ATRAS)->offset.y = -10;
				model.at(PERNA_FRENTE)->offset.y = -10;
				model.at(PERNA_ATRAS)->angle = -10;
				model.at(PERNA_FRENTE)->angle = -10;
				model.at(PE_ATRAS)->angle = 10;
				model.at(PE_FRENTE)->angle = 10;
				position.y += 10;

			}
			else if (percentage < 1.02f / 3.f) {
				superAtack->playSound();
			}
			else if (percentage < 1.3f / 3.f) {

				projectiles[0].setVisibility(true);
				projectiles[0].setScale(Vector2f(1, 1));

				projectiles[0].setPosition(
					Vector2f(model.at("Sniper")->drawPos.x,
						(model.at("Sniper")->drawPos.y - projectiles[0].getSize().y / 2)
					)
				);

				if (facingRight) {
					projectiles[0].setImpulse(120, 0);
					projectiles[0].setScale(Vector2f(0.1, 0.1));
				}
				else {
					projectiles[0].setImpulse(-120, 0);
					projectiles[0].setScale(Vector2f(-0.1, 0.1));
				}

				superAtack->isAtacking = true;
			}
			else if (percentage < 1.6f / 3.f) {

				
				model.at("Sniper")->offset.x -= 1;				
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;
				position.x += facingRight ? -1 : 1;

			}
			else if (percentage < 1.8f / 3.f) {

				model.at("Sniper")->offset.x += 1;
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;				

			}
			else if (percentage < 1.9f / 3.f) {

				projectiles[0].setVisibility(true);
				projectiles[0].setScale(Vector2f(1, 1));

				projectiles[0].setPosition(
					Vector2f(model.at("Sniper")->drawPos.x,
						(model.at("Sniper")->drawPos.y - projectiles[0].getSize().y / 2)
					)
				);

				if (facingRight) {
					projectiles[0].setImpulse(120, 0);
					projectiles[0].setScale(Vector2f(0.1, 0.1));
				}
				else {
					projectiles[0].setImpulse(-120, 0);
					projectiles[0].setScale(Vector2f(-0.1, 0.1));
				}

				superAtack->isAtacking = true;
			}
			else if (percentage < 2.f / 3.f) {

				model.at("Sniper")->angle += 1;			
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;

			}
			else if (percentage < 2.1f / 3.f) {

				model.at("Sniper")->offset.x += 1;
				model.at("Sniper")->angle -= 1;
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;

			}

			else if (percentage < 2.2f / 3.f) {

				projectiles[0].setVisibility(true);
				projectiles[0].setScale(Vector2f(1, 1));

				projectiles[0].setPosition(
					Vector2f(model.at("Sniper")->drawPos.x,
						(model.at("Sniper")->drawPos.y - projectiles[0].getSize().y / 2)
					)
				);

				if (facingRight) {
					projectiles[0].setImpulse(120, 0);
					projectiles[0].setScale(Vector2f(0.1, 0.1));
				}
				else {
					projectiles[0].setImpulse(-120, 0);
					projectiles[0].setScale(Vector2f(-0.1, 0.1));
				}

				superAtack->isAtacking = true;
			}
			else if (percentage < 2.3f / 3.f) {

				model.at("Sniper")->angle += 1;
				model.at("Sniper")->offset.x -= 1;
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;

			}
			else if (percentage < 2.35f / 3.f) {

				model.at("Sniper")->offset.x += 1;
				model.at("Sniper")->angle -= 1;
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;

			}
			else if (percentage < 2.4f / 3.f) {

				projectiles[0].setVisibility(true);
				projectiles[0].setScale(Vector2f(1, 1));

				projectiles[0].setPosition(
					Vector2f(model.at("Sniper")->drawPos.x,
						(model.at("Sniper")->drawPos.y - projectiles[0].getSize().y / 2)
					)
				);

				if (facingRight) {
					projectiles[0].setImpulse(120, 0);
					projectiles[0].setScale(Vector2f(0.1, 0.1));
				}
				else {
					projectiles[0].setImpulse(-120, 0);
					projectiles[0].setScale(Vector2f(-0.1, 0.1));
				}

				superAtack->isAtacking = true;
			}
			else if (percentage < 2.5f / 3.f) {

				model.at("Sniper")->angle += 1;
				model.at(ASA_ATRAS)->angle += 1;
				model.at(ASA_FRENTE)->angle += 1;
				model.at(CABECA)->angle += 1;
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;

			}
			else if (percentage < 2.55f / 3.f) {

				model.at("Sniper")->angle -= 1;
				model.at(ASA_ATRAS)->angle -= 1;
				model.at(ASA_FRENTE)->angle -= 1;
				model.at(CABECA)->angle -= 1;
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;

			}
			else if (percentage < 2.6f / 3.f) {

				projectiles[0].setVisibility(true);
				projectiles[0].setScale(Vector2f(1, 1));

				projectiles[0].setPosition(
					Vector2f(model.at("Sniper")->drawPos.x,
						(model.at("Sniper")->drawPos.y - projectiles[0].getSize().y / 2)
					)
				);

				if (facingRight) {
					projectiles[0].setImpulse(120, 0);
					projectiles[0].setScale(Vector2f(0.1, 0.1));
				}
				else {
					projectiles[0].setImpulse(-120, 0);
					projectiles[0].setScale(Vector2f(-0.1, 0.1));
				}

				superAtack->isAtacking = true;
			}
			else if (percentage < 2.7f / 3.f) {

				model.at("Sniper")->angle += 1;
				model.at(ASA_ATRAS)->angle += 1;
				model.at(ASA_FRENTE)->angle += 1;
				model.at(CABECA)->angle += 1;
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;

			}
			else if (percentage < 2.9 / 3.f) {
				model.at("Sniper")->angle *= 0.9;
				model.at("Sniper")->offset.x *= 0.9;
				model.at(ASA_ATRAS)->angle *= 0.9;
				model.at(ASA_FRENTE)->angle *= 0.9;
				model.at(BIGODE_FRENTE)->angle *= 0.9;
				model.at(BIGODE_ATRAS)->angle *= 0.9;
				model.at(CABECA)->angle *= 0.9;

			}
			else {
				model.at("Sniper")->angle = 0;
				model.at(ASA_ATRAS)->angle = 0;
				model.at(ASA_FRENTE)->angle = 0;
				model.at(CABECA)->angle = 0;
				model.at("Sniper")->offset.x = 0;
			}
		}

		void especialAnim() {
			Time t = ultimateShot->init.getElapsedTime();

			if (t > ultimateShot->timeLapse) {
				atacking = NOT_ATTACK;
			}

			float percentage = (float)t.asMilliseconds() / (ultimateShot->timeLapse.asMilliseconds());

			int angFix = -1;

			if (percentage < 0.5f / 3.f) {


				float thisPercentage = percentage * 3;
				model.at("Sniper")->angle += 45;
				model.at(ASA_ATRAS)->angle = angFix * 45 * -sin(thisPercentage * PI / 2);
				model.at(ASA_FRENTE)->angle = angFix * 90 * sin(thisPercentage * PI / 2);

			}
			else if (percentage < 2.f / 3.f) {
				float thisPercentage = percentage * 3;

				model.at("Sniper")->angle = 0;
				model.at(ASA_ATRAS)->angle = 0;
				model.at(ASA_FRENTE)->angle = 0;
				model.at(CABECA)->angle = -10;
				model.at(PERNA_ATRAS)->offset.y = -10;
				model.at(PERNA_FRENTE)->offset.y = -10;
				model.at(PERNA_ATRAS)->angle = -10;
				model.at(PERNA_FRENTE)->angle = -10;
				model.at(PE_ATRAS)->angle = 10;
				model.at(PE_FRENTE)->angle = 10;
				position.y += 10;

			}
			else if (percentage < 2.05f / 3.f) {
				ultimateShot->playSound();
			}
			else if (percentage < 2.2f / 3.f) {



				projectiles[0].setVisibility(true);
				projectiles[0].setScale(Vector2f(1, 1));

				projectiles[0].setPosition(
					Vector2f(model.at("Sniper")->drawPos.x,
						(model.at("Sniper")->drawPos.y - projectiles[0].getSize().y / 2)
					)
				);

				if (facingRight) {
					projectiles[0].setImpulse(90, 0);
					projectiles[0].setScale(Vector2f(0.1, 0.1));
				}

				else {
					projectiles[0].setImpulse(-90, 0);
					projectiles[0].setScale(Vector2f(-0.1, 0.1));
				}


				ultimateShot->isAtacking = true;
			}
			else if (percentage < 2.5f / 3.f) {

				model.at("Sniper")->angle += 5;
				model.at(ASA_ATRAS)->angle += 5;
				model.at(ASA_FRENTE)->angle += 5;
				model.at(CABECA)->angle += 5;
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;

				if (facingRight)
					position.x -= 2;
				else
					position.x += 2;


			}
			else if (percentage < 2.9 / 3.f) {
				model.at("Sniper")->angle *= 0.9;
				model.at(ASA_ATRAS)->angle *= 0.9;
				model.at(ASA_FRENTE)->angle *= 0.9;
				model.at(BIGODE_FRENTE)->angle *= 0.9;
				model.at(BIGODE_ATRAS)->angle *= 0.9;
				model.at(CABECA)->angle *= 0.9;
			}
			else {
				model.at("Sniper")->angle = 0;
				model.at(ASA_ATRAS)->angle = 0;
				model.at(ASA_FRENTE)->angle = 0;
				model.at(CABECA)->angle = 0;
			}
		}

		void highKickAnim() {
			Time t = hiKick->init.getElapsedTime();

			if (t > hiKick->timeLapse) {
				atacking = STOPPED;
			}

			float percentage = (float)t.asMilliseconds() / (hiKick->timeLapse.asMilliseconds());

			int angFix = (facingRight) ? 1 : -1;
			angFix = -1;

			static bool go = true;
			if (percentage < 1.f / 3.f) {


				float thisPercentage = percentage * 3;
				model.at(CORPO)->angle = angFix * 45 * -sin(thisPercentage * PI / 2);
				model.at(PERNA_FRENTE)->angle = angFix * -320;
				model.at(PERNA_ATRAS)->angle = angFix * 90 * -sin(thisPercentage * PI / 2);
				model.at(ASA_ATRAS)->angle = angFix * 45 * -sin(thisPercentage * PI / 2);
				model.at(ASA_FRENTE)->angle = angFix * 90 * sin(thisPercentage * PI / 2);

			}
			else if (percentage < 2.f / 3.f) {
				float thisPercentage = percentage * 3;
				model.at(CORPO)->angle = angFix * -45;
				model.at(PERNA_FRENTE)->angle = angFix * -320;
				model.at(PERNA_ATRAS)->angle = angFix * -90;
				model.at(PERNA_ATRAS)->offset.x = angFix * SCREEN_WIDTH / 75;
				model.at(PERNA_ATRAS)->offset.y = -SCREEN_WIDTH / 75;
				model.at(ASA_ATRAS)->angle = angFix * -45;
				model.at(ASA_FRENTE)->angle = angFix * 90;

				hiKick->hitbox.center = model.at(PE_ATRAS)->drawPos;
				hiKick->hitbox.radius = model.at(PE_ATRAS)->sprite.getGlobalBounds().width / 2;
				hiKick->isAtacking = true;
				if (go) {
					hiKick->playSound();
					go = false;
				}

			}
			else if (percentage < 2.9f / 3.f) {

				model.at(CORPO)->angle *= 0.9;
				model.at(PERNA_FRENTE)->angle *= 0.9;
				model.at(PERNA_ATRAS)->angle *= 0.9;
				model.at(PERNA_ATRAS)->offset.x = 0;
				model.at(PERNA_ATRAS)->offset.y = 0;
				model.at(ASA_ATRAS)->angle *= 0.9;
				model.at(ASA_FRENTE)->angle *= 0.9;

				hiKick->hitbox.center = { 0,0 };
				hiKick->hitbox.radius = 0;
				hiKick->isAtacking = false;
				go = true;

			}
			else {
				model.at(CORPO)->angle = 0;
				model.at(PERNA_FRENTE)->angle = 0;
				model.at(PERNA_ATRAS)->angle = 0;
				model.at(PERNA_ATRAS)->offset.x = 0;
				model.at(PERNA_ATRAS)->offset.y = 0;
				model.at(ASA_ATRAS)->angle = 0;
				model.at(ASA_FRENTE)->angle = 0;
			}


		}

		void lowKickAnim() {
			Time t = louKick->init.getElapsedTime();

			if (t > louKick->timeLapse) {
				atacking = STOPPED;
			}

			float percentage = (float)t.asMilliseconds() / (louKick->timeLapse.asMilliseconds());

			static bool go;
			if (percentage < 1.f / 3.f) {


				float thisPercentage = percentage * 3;

				model.at(PERNA_FRENTE)->angle += 90 * sin(thisPercentage * PI / 4);
				model.at(PE_FRENTE)->angle += 90 * -sin(thisPercentage * PI / 4);

				model.at(PERNA_ATRAS)->angle = 90 * sin(thisPercentage * PI / 4);
				model.at(PE_ATRAS)->angle = 90 * -sin(thisPercentage * PI / 4);

				model.at(ASA_ATRAS)->angle = 45 * -sin(thisPercentage * PI / 2);
				model.at(ASA_FRENTE)->angle = 90 * sin(thisPercentage * PI / 2);

			}
			else if (percentage < 2.f / 3.f) {

				model.at(CORPO)->angle = 45;
				model.at(PERNA_FRENTE)->angle = -30;
				model.at(PE_FRENTE)->angle = -90;
				model.at(PERNA_ATRAS)->angle = 0;
				model.at(CABECA)->angle = -20;
				model.at(PERNA_ATRAS)->offset.x = -5;
				model.at(PERNA_ATRAS)->offset.y = 5;
				model.at(ASA_ATRAS)->angle = 45;
				model.at(ASA_FRENTE)->angle = 90;

				louKick->hitbox.center = model.at(PE_ATRAS)->drawPos;
				louKick->hitbox.radius = model.at(PE_ATRAS)->sprite.getGlobalBounds().width / 2;
				louKick->isAtacking = true;
				if (go) {
					louKick->playSound();
					go = false;
				}
			}
			else if (percentage < 2.9f / 3.f) {

				model.at(CORPO)->angle *= 0.9;
				model.at(PERNA_FRENTE)->angle *= 0.9;
				model.at(PERNA_ATRAS)->angle *= 0.9;
				model.at(PERNA_ATRAS)->offset.x = 0;
				model.at(PERNA_ATRAS)->offset.y = 0;
				model.at(ASA_ATRAS)->angle *= 0.9;
				model.at(ASA_FRENTE)->angle *= 0.9;
				model.at(CABECA)->angle *= 0.9;
				louKick->hitbox.center = { 0,0 };
				louKick->hitbox.radius = 0;
				louKick->isAtacking = false;
				go = true;
			}
			else {
				model.at(CORPO)->angle = 0;
				model.at(PERNA_FRENTE)->angle = 0;
				model.at(PERNA_ATRAS)->angle = 0;
				model.at(PERNA_ATRAS)->offset.x = 0;
				model.at(PERNA_ATRAS)->offset.y = 0;
				model.at(ASA_ATRAS)->angle = 0;
				model.at(ASA_FRENTE)->angle = 0;
				model.at(CABECA)->angle = 0;
			}


		}

		void defended(Galo& galo2, Ataques* atk, bool facingRight) override {
			Ataques* ataque = new Ataques(*atk);
			ataque->Damage *= 0.25;
			ataque->KnockBack *= 0.25;
			apanhar(*ataque, facingRight);
			defenseSound.play();
		}

		void updateAnimations() override {


			if (estadoUpdate) {
				model.resetToBase();
				animations[0].playingFrame = 0;
			}

			weatherAnim(frames);


			model.at("FrontArm")->angle = ArmSpinAngFase;
			model.at("BackArm")->angle = Arm2SpinAngFase;


			if (!stunned) {


				if (air) {
					jumpAnim();
				}
				else {
					cairAnim();
				}


				if (estado == RUNNING) {
					runAnim();
					isDefending = false;
				}
				else if (estado == DEFENDING) {

					animations[0].update();
					if (animations[0].playingFrame > 15) {
						animations[0].playingFrame = 15;
						isDefending = true;
						defense.center.x = model.at("Sniper")->drawPos.x;
						defense.center.y = model.at("Sniper")->drawPos.y;
						defense.radius = model.at("Sniper")->sprite.getGlobalBounds().height / 2;
					}
					else {
						isDefending = false;
					}

					model.updateWithAnimation(animations[0]);

				}
				else if (estado == STOPPED) {
					isDefending = false;
					runReset();
				}
				

				

				if (atacking == HIGH_KICK) {
					highKickAnim();
					isDefending = false;
				}
				else if (atacking == LOW_KICK) {
					lowKickAnim();
					isDefending = false;
				}
				else if (atacking == SPECIAL) {
					especialAnim();
					isDefending = false;
				}
				else if (atacking == SUPER) {
					superAnim();
					isDefending = false;
				}
				else if (estado == DANCING) { // nao tanko kkkkkkkkkkkkk
					animations[1].update();
					model.updateWithAnimation(animations[1]);
				}
				

				projectiles[0].update();

				ultimateShot->hitbox.center = projectiles[0].getPosition();
				ultimateShot->hitbox.radius = projectiles[0].getSize().y / 2;

				superAtack->hitbox.center = projectiles[0].getPosition();
				superAtack->hitbox.radius = projectiles[0].getSize().y / 2;

			}

			if (estado == INVISIBLE) {
				sumir();
			}

			if (estado != INVISIBLE) {
				aparecer();
			}
		}

		void updateGranada() {
			granada.setTexture(grenade);
			granada.setScale((float)SCREEN_WIDTH / 15360, (float)SCREEN_WIDTH / 15360);
			granada.setPosition(posGrenade);
			granada.setOrigin(granada.getGlobalBounds().width / 2, granada.getGlobalBounds().height / 2);
		}
		

		void jogarGranada(RenderWindow * window) {

			static int thisFrames = 0;
			int maxFrames = 360;

			if (thisFrames > maxFrames) {
				thisFrames = 0;
				model.at("Sniper")->alpha = 1;

				return;
			}

			
			float percentage = (float) thisFrames / (float) maxFrames;

			model.at("Sniper")->alpha = 0;
			
			

			if (percentage < 0.5f / 3.f) {
				facingRight = true;

				float thisPercentage = percentage * 6;

				Arm2SpinAngFase =  60 * thisPercentage;
				ArmSpinAngFase = -30 * thisPercentage;
				model.at(CABECA)->angle = -20 * thisPercentage;
				model.at(PE_FRENTE)->angle = -20 * thisPercentage;

				updateGranada();

				posGrenade.x = model.at(ASA_FRENTE)->drawPos.x;
				posGrenade.y = model.at(ASA_FRENTE)->drawPos.y - granada.getGlobalBounds().height/2;
			}
			else if (percentage < 2.f / 3.f) {
				
				float thisPercentage = (percentage * 2) - percentage/6;
				
				Arm2SpinAngFase = 60 * thisPercentage;
				ArmSpinAngFase = -30 * thisPercentage;

				model.at(CABECA)->angle = -15;
				model.at(PERNA_FRENTE)->angle = -10 * thisPercentage;
				model.at(PE_FRENTE)->angle = -15;
				
				posGrenade.x += posGrenade.x < SCREEN_WIDTH / 1.5 ? 10: 0;
				posGrenade.y += posGrenade.y < floorY - granada.getGlobalBounds().height ? 5 : - 1 / thisPercentage;

				updateGranada();
				
				window->draw(granada);
				
			}
			else {
				posGrenade.y = floorY - granada.getGlobalBounds().height;

				estado = DANCING;

				if (thisFrames % 15 == 0) {
					facingRight = !facingRight;
				}

				updateGranada(); 

				
				granada.setRotation(thisFrames % 45 - 30);
				window->draw(granada);
			}
			
			
			thisFrames++;

		}

		void shitAtack() {

			static int thisFrames = 0;
			int maxFrames = 30;

			if (thisFrames > maxFrames) {
				
				thisFrames = 0;
			}

			float percentage = (float) thisFrames / maxFrames;

			int angFix = -1;

			if (percentage < 0.5f / 3.f) {


				float thisPercentage = percentage * 3;

				model.at("Sniper")->angle += 45;
				model.at(ASA_ATRAS)->angle = angFix * 45 * -sin(thisPercentage * PI / 2);
				model.at(ASA_FRENTE)->angle = angFix * 90 * sin(thisPercentage * PI / 2);

			}
			else if (percentage < 2.f / 3.f) {
				float thisPercentage = percentage * 3;

				model.at("Sniper")->angle = -10;
				model.at(ASA_ATRAS)->angle = 0;
				model.at(ASA_FRENTE)->angle = 0;
				model.at(CABECA)->angle = -10;
				model.at(PERNA_ATRAS)->offset.y = -10;
				model.at(PERNA_FRENTE)->offset.y = -10;
				model.at(PERNA_ATRAS)->angle = -10;
				model.at(PERNA_FRENTE)->angle = -10;
				model.at(PE_ATRAS)->angle = 10;
				model.at(PE_FRENTE)->angle = 10;
				position.y += 10;

			}
			else if (percentage < 2.05f / 3.f) {
				ultimateShot->playSound();
			}
			else if (percentage < 2.2f / 3.f) {



				projectiles[0].setVisibility(true);
				projectiles[0].setScale(Vector2f(1, 1));

				projectiles[0].setPosition(
					Vector2f(model.at("Sniper")->drawPos.x,
						(model.at("Sniper")->drawPos.y - projectiles[0].getSize().y / 2)
					)
				);

				if (facingRight) {
					projectiles[0].setImpulse(90, 30);
					projectiles[0].setScale(Vector2f(0.1, 0.1));
				}

				else {
					projectiles[0].setImpulse(-90, 30);
					projectiles[0].setScale(Vector2f(-0.1, 0.1));
				}

				projectiles[0].setSpriteAngle(15);

				ultimateShot->isAtacking = true;
			}
			else if (percentage < 2.5f / 3.f) {

				model.at("Sniper")->angle += 5;
				model.at(ASA_ATRAS)->angle += 5;
				model.at(ASA_FRENTE)->angle += 5;
				model.at(CABECA)->angle += 5;
				model.at(BIGODE_FRENTE)->angle += -90;
				model.at(BIGODE_ATRAS)->angle += -90;

				if (facingRight)
					position.x -= 2;
				else
					position.x += 2;


			}
			else if (percentage < 2.9 / 3.f) {
				model.at("Sniper")->angle *= 0.9;
				model.at(ASA_ATRAS)->angle *= 0.9;
				model.at(ASA_FRENTE)->angle *= 0.9;
				model.at(BIGODE_FRENTE)->angle *= 0.9;
				model.at(BIGODE_ATRAS)->angle *= 0.9;
				model.at(CABECA)->angle *= 0.9;
			}
			else {
				model.at("Sniper")->angle = 0;
				model.at(ASA_ATRAS)->angle = 0;
				model.at(ASA_FRENTE)->angle = 0;
				model.at(CABECA)->angle = 0;
			}

			thisFrames++;
		}




		void fatality(RenderWindow* window, Galo* galo2, RectangleShape fundo) override {
			Clock Timer;
			Timer.restart();

			estado = FATALITY;
			model.resetToBase();
			galo2->position.x = SCREEN_WIDTH / 1.5;

			position.x = SCREEN_WIDTH / 4;

			Font mortal;
			mortal.loadFromFile("fonts/Mortal-Kombat-MK11.otf");

			Text fatal("FATALITY", mortal, SCREEN_WIDTH / 10);
			fatal.setPosition(SCREEN_WIDTH / 2 - fatal.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - fatal.getGlobalBounds().height * 2);
			fatal.setFillColor(Color(100, 0, 0));
			fatal.setOutlineThickness(SCREEN_WIDTH / 700);
			fatal.setOutlineColor(Color(255, 10, 10));

			Texture garrinha;
			garrinha.loadFromFile("sprites/garrinhaDoFatality.png");
			Sprite garra1;
			Sprite garra2;
			garra1.setTexture(garrinha);
			garra2.setTexture(garrinha);
			garra1.setScale(-0.5, 0.5);
			garra2.setScale(0.5, 0.5);

			garra1.setPosition(
				SCREEN_WIDTH / 2 - fatal.getGlobalBounds().width / 2 - garra1.getGlobalBounds().width,
				SCREEN_HEIGHT / 2 - fatal.getGlobalBounds().height * 2 - garra1.getGlobalBounds().height * 2
			);

			garra2.setPosition(
				SCREEN_WIDTH / 2 - fatal.getGlobalBounds().width / 2 - garra1.getGlobalBounds().width,
				SCREEN_HEIGHT / 2 - fatal.getGlobalBounds().height * 2 - garra1.getGlobalBounds().height * 2
			);
			RectangleShape opening;

			opening.setFillColor(Color(255, 255, 0));
			opening.setOutlineColor(Color::Yellow);
			opening.setSize(Vector2f(0, SCREEN_HEIGHT / 100));

			Text kalsawins("Sniper Wins", mortal, SCREEN_WIDTH / 50);

			kalsawins.setPosition(
				SCREEN_WIDTH / 2 - kalsawins.getGlobalBounds().width / 2,
				garra2.getPosition().y - kalsawins.getGlobalBounds().height
			);
			kalsawins.setFillColor(Color(250, 250, 250));
			kalsawins.setOutlineThickness(SCREEN_WIDTH / 700);
			kalsawins.setOutlineColor(Color(255, 255, 10));


			SoundBuffer grito;
			grito.loadFromFile("sounds\\Fatality_Scream.wav");
			Sound gritoSound;
			gritoSound.setBuffer(grito);
			gritoSound.setLoop(true);


			model.resetToBase();


			SoundBuffer fatalityBuffer;
			fatalityBuffer.loadFromFile("sounds/fatality.ogg");
			Sound fatalitysound;
			fatalitysound.setBuffer(fatalityBuffer);
			fatalitysound.setLoop(false);

			SoundBuffer whowinsBuf;
			if (isp1) {
				whowinsBuf.loadFromFile("sounds/Player_1_Wins.wav");
			}
			else {
				whowinsBuf.loadFromFile("sounds/Player_2_Wins.wav");
			}
			Sound whowins;
			whowins.setBuffer(whowinsBuf);

			

			

			int explosionSizex = 256;
			int explosionSizey = 248;

			Texture explosion;
			
			Sprite explosionSpr;
			
			explosion.loadFromFile("sprites\\explosionSheet.png");
			explosionSpr.setTexture(explosion);
			

			bool lets = true;

			ExplosionEffect* axp = new ExplosionEffect(Vector2f(0, 0), 10);
			ExplosionEffect* exp = new ExplosionEffect(Vector2f(0, 0), 10);
			exp->sanguePreset();
			exp->depthSpdMin = -1;
			exp->depthSpdMax = 1;
			exp->depthMin = 100;
			exp->depthMax = 100;

			exp->mortal = false;

			axp->sanguePreset();
			axp->depthSpdMin = -1;
			axp->depthSpdMax = 4;
			axp->depthMin = 100;
			axp->depthMax = 300;

			axp->mortal = false;

			SoundBuffer avita;
			avita.loadFromFile("sounds\\avista.ogg");
			Sound hastalavista(avita);
			
			bool tome = true;

			while (window->isOpen()) {

				float time = Timer.getElapsedTime().asMilliseconds();


				window->clear();
				window->draw(fundo);
				show(*window);

				exp->update();
				exp->draw(*window);

				axp->update();
				axp->draw(*window);

				galo2->show(*window);


				Event e;
				while (window->pollEvent(e))
				{
					if (e.type == Event::Closed)
					{
						window->close();
					}

				}

				if (time < 6000) {

					if (tome) {
						hastalavista.play();
						tome = false;
					}
					estado = STOPPED;
					jogarGranada(window);
					update();
					galo2->setState(STOPPED);
					galo2->update();

				}
				else if (time < 12000) {

					facingRight = true;
					estado = STOPPED;
					model.at("Sniper")->alpha = 1;

					int thisTime = time - 6000;

					//vamos dividir as 48 imagens igualmentes em 6000 segundos
					int imgSpace = 6000 / 48;
					int imgSpaceY = 1000;

					//to mo cansado
					IntRect manoTaFoda;
					manoTaFoda.width = explosionSizex;
					manoTaFoda.height = explosionSizey;

			
					manoTaFoda.top = (int)(thisTime/imgSpace) * explosionSizey;

					manoTaFoda.left = ((int)(thisTime/ imgSpace) % 8) * explosionSizex;
					
					explosionSpr.setTextureRect(manoTaFoda);
					explosionSpr.setScale(4, 4);

					explosionSpr.setPosition(
						galo2->position.x - explosionSpr.getGlobalBounds().width / 2,
						galo2->position.y - explosionSpr.getGlobalBounds().height/2
					);

					galo2->explodir();
					galo2->update();
					update();
					window->draw(explosionSpr);

					if (frames % 20 == 0) {

						Model model = galo2->getModel();

						exp->position = model.at("Body")->drawPos;

						exp->createMultipleParticles(500);
					}

				}
				else {
					shitAtack();
					update();
					


					if (frames % 15 == 0) {

						Model model = galo2->getModel();

						axp->position = model.at("Head")->drawPos;

						axp->createMultipleParticles(100);
					}
				
					galo2->update();


					if (time > 14000) {


						if (lets)
							fatalitysound.play();
						lets = false;
						window->draw(fatal);

						if (time < 18000) {
							static bool letsgo = true;

							if (letsgo)
								whowins.play();
							letsgo = false;
							opening.setSize(Vector2f(ruleOfThree(time, 12000, SCREEN_WIDTH / 10), (float)SCREEN_HEIGHT / 100));
						}
						else {
							opening.setSize(Vector2f((float)SCREEN_WIDTH / 10, (float)SCREEN_HEIGHT / 100));

						}
						garra1.setPosition(opening.getPosition().x, garra1.getPosition().y);
						garra2.setPosition(opening.getPosition().x + opening.getSize().x, garra1.getPosition().y);
						opening.setPosition(
							SCREEN_WIDTH / 2 - opening.getSize().x / 2,
							garra2.getPosition().y + garra2.getGlobalBounds().height / 1.5);

						window->draw(opening);
						window->draw(garra1);
						window->draw(garra2);
						window->draw(kalsawins);
					}
				}
				
				
				if (time > 22000) {
					return;
				}


				window->display();

			}
		}


	};


}

#endif // GALOSNIPER_H_INCLUDED