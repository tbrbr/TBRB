#ifndef GALOSNIPER_H_INCLUDED
#define GALOSNIPER_H

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



	public:
		Sniper(struct GaloStats _stats, int _state, bool isp1) : Galo(_stats, _state, isp1) {
			this->name = "Sniper";




			bar = new LifeBar(maxHp, isp1, name.c_str());
			
			this->hiKick = new Ataques(0, 20, 0.5, HitBox{ Vector2f(0, 0), 0 }, 20, 10, -PI / 4, milliseconds(1000),"");
			this->louKick = new Ataques(1,20, 0.5, HitBox{ Vector2f(0, 0), 0 }, 20, 10, PI / 4, milliseconds(1000),"");
			this->ultimateShot = new Ataques(2,10, 0.5, HitBox{ Vector2f(0, 0), 0 }, 10, 20, 0, milliseconds(2000),"sounds\\awp.ogg");



			const char const* txt = "sprites\\bullet.png";

			Projectile* bullet = new Projectile(Vector2f(0, 0), txt, 0, 0, Vector2f(0, 0));
			projectiles.push_back(*bullet);
			Projectile* n2 = new Projectile(true);
			projectiles.push_back(*n2);


			t.loadFromFile("sprites/galoSniper.png");

			model.tex = &t;
			model.loadModel("SniperModel.txt");

			model.autoSetBounds(model.at("Body"), model.at("BackShoe"), model.at("Head"));

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
			agacharAnim.init("SecondAnim.txt");
			agacharAnim.playingSpeed = 1;
			agacharAnim.connectLoop = false;
			animations.push_back(agacharAnim);

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

		void especialAnim() {
			Time t = ultimateShot->init.getElapsedTime();

			if (t > ultimateShot->timeLapse) {
				atacking = NOT_ATTACK;
			}

			float percentage = (float)t.asMilliseconds() / (ultimateShot->timeLapse.asMilliseconds());

			int angFix = (facingRight) ? 1 : -1;
			angFix = -1;


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
						    (model.at("Sniper")->drawPos.y - projectiles[0].getSize().y/2)
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


		/*
		void apanhar(Ataques atk, bool direction) override { 

			if (invFrames <= 0) {

				hp -= atk.Damage;


				// Calculando os impulsos


				atk.createBlood(mainPartSystem);

				
				vspeed += sin(atk.angle) * atk.KnockBack;
				hspeed += cos(atk.angle) * atk.KnockBack;

				if (vspeed < 0) {
					air = true;
				}
				if (!direction) {
					hspeed *= -1;
				}

				// Tempo de perda de controle sobre o Rooster
				stunFrames = atk.Stun;

				// Tempo de invulnerabilidade
				invFrames = 30;

				bar->update(hp);

				atk.playSound();
				
			}


		}

		*/


		void updateAnimations() override {
			if (estadoUpdate) {
				model.resetToBase();
				animations[0].playingFrame = 0;
			}

			weatherAnim(frames);


			if (air) {
				jumpAnim();
			}
			else {
				cairAnim();
			}


			model.at("FrontArm")->angle = ArmSpinAngFase;
			model.at("BackArm")->angle = Arm2SpinAngFase;

			if (estado == RUNNING) {
				runAnim();
			} else if (estado == DEFENDING) {
				animations[0].update();
				if (animations[0].playingFrame > 15) {
					animations[0].playingFrame = 15;
				}
				model.updateWithAnimation(animations[0]);

			} else if (estado == STOPPED) {
				runReset();
			}


			if (atacking == HIGH_KICK) {
				highKickAnim();
			}
			else if (atacking == LOW_KICK) {
				lowKickAnim();
			}
			else if (atacking == SPECIAL) {
				especialAnim();
			}

			projectiles[0].update();

			ultimateShot->hitbox.center = projectiles[0].getPosition();
			ultimateShot->hitbox.radius = projectiles[0].getSize().y / 2;

		}


		/*
		void update() override {

			// Timer 

			invFrames--;
			stunFrames--;


			projectiles[0].update();


			if (air) {
				vspeed += peso * Gravity / 100;
			}

			

			/// Aqui vem a suavização
			// A perda de velocidade
			// Simulando atrito com ar?



			for (int i = 0; i < hurtBox.size(); i++) {

				hurtBox[i].center = model.at(i)->drawPos;
				hurtBox[i].radius = model.at(i)->sprite.getGlobalBounds().width / 2;

			}

			frames++;
			


			if (position.y > floorY) {
				vspeed = 0;
				position.y = floorY;
				air = false;
			}

			position.x += hspeed;
			position.y += vspeed;


			model.pos = position;


			bar->update(hp);


			model.pos = position;
			model.xScl = 4 * (facingRight ? 1 : -1) * -(float)SCREEN_WIDTH / 5120;
			model.yScl = 4 * (float)SCREEN_WIDTH / 5120;



			model.update();


			estadoUpdate = false;



		}
		*/
	};


}

#endif // GALOSNIPER_H_INCLUDED