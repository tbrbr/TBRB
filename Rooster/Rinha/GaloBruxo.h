

#ifndef GALOBRUXO_H_INCLUDED
#define GALOBRUXO_H

#include "Galo.h"

namespace Rooster {

	class Bruxo : public Galo {

		Texture t;
		float legWalkAngFase = 0;
		Clock clockFatal;
		SoundBuffer defenseBuffer;
		Sound defenseSound;

		

	public:
		Bruxo(struct GaloStats _stats, int _state, bool isp1) : Galo(_stats, _state, isp1) {
			// Stats
			this->name = "Bruxo";

			// Creating Attacks
			this->hiKick = new Ataques(
				9, 8, HitBox{ Vector2f(0, 0), 0 },
				20, 10, -PI / 4, milliseconds(1200), ""
			);

			this->louKick = new Ataques(
				9, 5, HitBox{ Vector2f(0, 0), 0 },
				20, 10, PI / 4, milliseconds(1250), "sounds\\smoke-bomb-6761.ogg"
			);

			this->ultimateShot = new Ataques(
				10, 0.9, HitBox{ Vector2f(0, 0), 0 },
				10, 3, 0, milliseconds(1500),
				"sounds\\doctorStrangeMagicShorter.ogg"
			);

			this->superAtack = new Ataques(15, 10, HitBox{ Vector2f(0, 0), 0 }, 20, 10, 0, milliseconds(2000), "sounds\\mg34.ogg");

			
			//println("before Defense try");
			Projectile* defense = new Projectile(
				Vector2f(0, 0),
				"sprites\\escudo.png",
				0, 0, Vector2f(0.25, 0.25)
			);

			defense->setOriginCenter();
			defense->isTrans = true;
			Transform te;
			te.scale(0.5, 0.75);
			defense->setTransfrom(te);

			projectiles.push_back(*defense);
			projectiles.push_back(*defense);

			//println("Defense done");

			Projectile* fumaca = new Projectile(
				Vector2f(0, 0),
				"sprites\\efeitoFumaca.png",
				0, 0, Vector2f(0.25, 0.25)
			);

			atacking = NOT_ATTACK;
			projectiles.push_back(*fumaca);

			//println("Fumaca");

			Projectile* flame = new Projectile(
				Vector2f(0, 0),
				"sprites\\flame.png",
				0, 0, Vector2f(0.25, 0.25)
			);
			projectiles.push_back(*flame);

			//println("Flame");

			t.loadFromFile("sprites/galoBruxo.png");

			model.tex = &t;
			model.loadModel("models/bruxoModel.txt");

			defenseBuffer.loadFromFile("sounds\\shield-guard-6963.ogg");
			defenseSound.setBuffer(defenseBuffer);

			model.autoSetBounds(model.at("Body"), model.at("BackShoe"), model.at("Head"));


			HitBox* hit = new HitBox;
			for (int i = 0; i < model.allBones.size(); i++) {

				hit->center = model.at(i)->drawPos;
				hit->radius = model.at(i)->sprite.getGlobalBounds().width / 2;

				hurtBox.push_back(*hit);
			}
			delete hit;

			struct Animation agacharAnim;
			agacharAnim.init("animations/SecondAnim.txt");
			agacharAnim.playingSpeed = 1;
			agacharAnim.connectLoop = false;
			animations.push_back(agacharAnim);

			struct Animation danceAnim;
			danceAnim.init("animations/bruxoDance3.txt");
			danceAnim.playingSpeed = 0.1;
			danceAnim.connectLoop = true;
			animations.push_back(danceAnim);


			bar = new LifeBar(maxHp, isp1, name.c_str());

		}

		Vector2f getFrontHandPos() {
			float coordXPaint = 550;
			float coordYPaint = 900;

			float ax = coordXPaint - model.at("FrontArm")->sprArea.texRect.left;
			float ay = coordYPaint - model.at("FrontArm")->sprArea.texRect.top;

			float difx = ax - model.at("FrontArm")->center.x;
			float dify = ay - model.at("FrontArm")->center.y;

			float ang = toRadiAnus(model.at("FrontArm")->finalAngle);

			float xScl = model.at("FrontArm")->finalXScl;
			float yScl = model.at("FrontArm")->finalYScl;

			float rotx = cos(ang) * difx - sin(ang) * dify;
			float roty = sin(ang) * difx + cos(ang) * dify;

			rotx *= xScl;
			roty *= yScl;

			Vector2f mao;
			mao.y = model.at("FrontArm")->drawPos.y + roty;
			mao.x = model.at("FrontArm")->drawPos.x + rotx;
			return mao;

		}

		Vector2f getBackHandPos() {
			float coordXPaint = 17;
			float coordYPaint = 600;

			float ax = coordXPaint - model.at("BackArm")->sprArea.texRect.left;
			float ay = coordYPaint - model.at("BackArm")->sprArea.texRect.top;
			float difx = ax - model.at("BackArm")->center.x;

			float dify = ay - model.at("BackArm")->center.y;

			float ang = toRadiAnus(model.at("BackArm")->finalAngle);

			float xScl = model.at("BackArm")->finalXScl;

			float yScl = model.at("BackArm")->finalYScl;

			float rotx = cos(ang) * difx - sin(ang) * dify;
			float roty = sin(ang) * difx + cos(ang) * dify;

			rotx *= xScl;
			roty *= yScl;

			Vector2f mao;
			mao.y = model.at("BackArm")->drawPos.y + roty;
			mao.x = model.at("BackArm")->drawPos.x + rotx;

			return mao;

		}


		void jumpAnim() {


			model.at("FrontArm")->angle = (vspeed / 8) * 45;
			model.at("BackArm")->angle = (vspeed / 8) * 45;

			model.at("Hat")->offset.y += vspeed / 8;

			if (model.at("Hat")->offset.y > 0) {
				model.at("Hat")->offset.y = 0;
			}
			model.at("FrontShoe")->angle = vspeed;
			model.at("BackShoe")->angle = vspeed;

			model.at("FrontBigode")->angle += vspeed / 2;
			model.at("BackBigode")->angle += vspeed / 2;
		}
		void cairAnim() {
			model.at("Hat")->offset.y = 0;
			model.at("FrontBigode")->angle *= 0.9;
			model.at("BackBigode")->angle *= 0.9;

			model.at("Body")->angle *= 0.7;
		}
		void runAnim() {
			legWalkAngFase += hspeed;
			legWalkAngFase -= ((int)legWalkAngFase / 360) * 360;

			model.at("FrontShoe")->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at("BackShoe")->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

			model.at("FrontBigode")->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at("BackBigode")->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

			model.at("FrontArm")->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at("BackArm")->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

			model.at("Hat")->angle += -sin(2 * PI * legWalkAngFase / 360);

			projectiles.at(0).setVisibility(false);
		}
		void runReset() {


			model.at("FrontShoe")->angle *= 0.8;
			model.at("BackShoe")->angle *= 0.8;

			model.at("FrontArm")->angle = 0;
			model.at("BackArm")->angle = 0;

			model.at("Hat")->angle *= 0.9;

			model.at("Body")->offset.y = 0;
			model.at("BackShoe")->offset.y = 0;
			model.at("FrontShoe")->offset.y = 0;

			projectiles.at(0).setVisibility(false);

		}

		void defend() override {
			estado = DEFENDING;
		}

		void agachadinha() {

			hspeed = 0;
			static int angle = 0;
			angle++;

			projectiles[0].isTrans = true;

			projectiles[0].setScale(1, 1);

			Transform trans;

			float xScale = model.xScl*0.1;
			float yScale = model.yScl*0.2;


			projectiles[0].setSpriteAngle(angle*sign(xScale));

			Vector2f shieldPos = model.at("Body")->drawPos;
			shieldPos.x -= 140 * model.xScl;
			shieldPos.y -= model.getBounds().height/2.5;

			trans.translate(shieldPos);
			trans.scale(xScale, yScale);
			
			
			projectiles[0].setPosition(shieldPos);
			projectiles[0].setTransfrom(trans);

			
			projectiles[0].setImpulse(0, 0);
			projectiles[0].setVisibility(true);
			projectiles[0].update();

			
			defense.center = shieldPos;		
			defense.radius = (projectiles[0].getSize().y /2) * xScale;


		}


		void highKick() override {
			if (atacking == NOT_ATTACK) {
				atacking = HIGH_KICK;
				hiKick->init.restart();
			}

		}

		void lowKick() override {
			if (atacking == NOT_ATTACK) {
				atacking = LOW_KICK;
				louKick->init.restart();
			}
		}

		void especial() override {
			if (atacking == NOT_ATTACK) {
				atacking = SPECIAL;
				ultimateShot->init.restart();
			}

		}
		void super() override {
			

			if (atacking == NOT_ATTACK) {
				bar->resetPower();
				atacking = SUPER;
				superAtack->init.restart();
			}

		}
		void superAnim() {
			Time t = superAtack->init.getElapsedTime();

			if (t > superAtack->timeLapse) {
				atacking = NOT_ATTACK;
			}

			float percentage = (float)t.asMilliseconds() / (superAtack->timeLapse.asMilliseconds());

			static int thisFrames = 0;

			if (percentage < 1.f / 3.f) {

				float thisPercentage = percentage * 3;

				model.at("Body")->angle = 30 * thisPercentage;
				model.at("FrontArm")->angle = -90 * thisPercentage;
				model.at("BackArm")->angle = -90 * thisPercentage;
				model.at("Head")->angle = 20 * thisPercentage;
				model.at("Hat")->angle = -10 * thisPercentage;

				model.at("Hat")->yScl = model.at("Hat")->yScl +  (model.at("Hat")->yScl/2)  * thisPercentage;
				model.at("Hat")->yScl = model.at("Hat")->xScl + (model.at("Hat")->xScl / 3) * thisPercentage;

			}
			else if (percentage < 2.f / 3.f) {

				thisFrames++;

				model.at("Body")->angle = -30;
				model.at("FrontArm")->angle = -90;
				model.at("BackArm")->angle = -90;
				model.at("Head")->angle = -20;
				model.at("Hat")->angle = 30;
				
				if (facingRight) {
					projectiles[3].setSpriteScale((float)- thisFrames / 30, (float)SCREEN_WIDTH / 1920);

					projectiles[3].setSpritePosition(
						model.at("Hat")->drawPos.x + model.at("Hat")->sprite.getGlobalBounds().width/5 + projectiles[3].getSize().x,
						model.at("Hat")->drawPos.y + model.at("Hat")->sprite.getGlobalBounds().height/2 - projectiles[3].getSize().y
					);
				}
				else {

					projectiles[3].setSpriteScale((float)thisFrames/30, (float)SCREEN_WIDTH / 1920);

					projectiles[3].setSpritePosition(
						model.at("Hat")->drawPos.x - model.at("Hat")->sprite.getGlobalBounds().width / 5 -  projectiles[3].getSize().x,
						model.at("Hat")->drawPos.y + model.at("Hat")->sprite.getGlobalBounds().height / 2 - projectiles[3].getSize().y
					);
				}
				
				projectiles[3].setVisibility(true);
				superAtack->isAtacking = true;
				
				superAtack->hitbox.center.x = (facingRight) ?
					projectiles[3].getSpritePosition().x + projectiles[3].getSize().x / 4:
					projectiles[3].getSpritePosition().x - projectiles[3].getSize().x / 4;

				superAtack->hitbox.center.y = projectiles[3].getSpritePosition().y + projectiles[3].getSize().y / 2;
				superAtack->hitbox.radius = projectiles[3].getSize().y / 2;
			}
			else if(percentage < 2.9f / 3.f) {

				thisFrames = 0;
				projectiles[3].setVisibility(false);

				model.at("Body")->angle *= 0.99;
				model.at("BackArm")->angle *= 0.99;
				model.at("Head")->angle *= 0.99;
				model.at("Hat")->angle *= 0.99;

				model.at("Hat")->yScl = model.at("Hat")->getBaseScale().x;			
				model.at("Hat")->yScl = model.at("Hat")->getBaseScale().y;

				superAtack->isAtacking = false;
			}
			else {

				model.at("Body")->angle = 0;
				model.at("BackArm")->angle = 0;
				model.at("Head")->angle = 0;
				model.at("Hat")->angle = 0;
				

			}

		}

		void especialAnim() {
			Time t = ultimateShot->init.getElapsedTime();

			if (t > ultimateShot->timeLapse) {
				atacking = NOT_ATTACK;
			}

			float percentage = (float)t.asMilliseconds() / (ultimateShot->timeLapse.asMilliseconds());

			int angFix = (facingRight) ? 1 : -1;
			angFix = -1;

			static int angle = 0;
			angle++;


			
			if (percentage > 2.f / 3.f && percentage < 2.9f/3.f) {
				if (!ultimateShot->soundPlayed) {
					ultimateShot->playSound();
					ultimateShot->soundPlayed = true;
				}
				
			}
			else if (percentage > 1.75f / 3.f) {
				
				ultimateShot->soundPlayed = false;
				
			}
			else if (percentage > 1.5f / 3.f){
				if (!ultimateShot->soundPlayed) {
					ultimateShot->playSound();
					ultimateShot->soundPlayed = true;
				}
				

			}


			if (percentage < 0.5f / 3.f) {

				float thisPercentage = percentage * 6;

				model.at("FrontArm")->angle = percentage * -90;
				model.at("BackArm")->angle = percentage * 90;
				model.at("Head")->angle = percentage * 30;
				model.at("Body")->angle = percentage * 30;
				model.at("FrontBigode")->angle = percentage * -30;
				model.at("BackBigode")->angle = percentage * -30;
				projectiles[0].isTrans = false;

				projectiles[0].setImpulse(0, 0);
				projectiles[0].setSpriteAngle(angle);

				projectiles[0].setScale((float)SCREEN_WIDTH / 7680 * percentage, (float)SCREEN_WIDTH / 7680 * percentage);

				projectiles[0].setPosition(getBackHandPos());

				projectiles[0].setVisibility(true);
				projectiles[0].update();

				projectiles[1].isTrans = false;
				projectiles[1].setImpulse(0, 0);
				projectiles[1].setSpriteAngle(angle);

				projectiles[1].setScale((float)SCREEN_WIDTH / 15360 * percentage, (float)SCREEN_WIDTH / 15360 * percentage);

				projectiles[1].setPosition(getFrontHandPos());

				projectiles[1].setVisibility(true);
				projectiles[1].update();

				

			}
			else if (percentage < 1.5f / 3.f) {
				float thisPercentage = (percentage * 3) / 1.5;

				model.at("FrontArm")->angle = percentage * -90;
				model.at("BackArm")->angle = percentage * 90;

				model.at("Head")->angle = percentage * 30;
				model.at("Body")->angle = percentage * 30;
				model.at("FrontBigode")->angle = percentage * -30;
				model.at("BackBigode")->angle = percentage * -30;

				projectiles[0].isTrans = false;
				projectiles[0].setImpulse(0, 0);
				projectiles[0].setSpriteAngle(angle);

				projectiles[0].setScale((float)SCREEN_WIDTH / 7680 * percentage, (float)SCREEN_WIDTH / 7680 * percentage);

				projectiles[0].setPosition(getBackHandPos());

				projectiles[0].setVisibility(true);
				projectiles[0].update();

				projectiles[1].isTrans = false;
				projectiles[1].setImpulse(0, 0);
				projectiles[1].setSpriteAngle(angle);

				projectiles[1].setScale((float)SCREEN_WIDTH / 15360 * percentage, (float)SCREEN_WIDTH / 15360 * percentage);

				projectiles[1].setPosition(getFrontHandPos());

				projectiles[1].setVisibility(true);
				projectiles[1].update();

				
			}
			else if (percentage < 1.55f / 3.f) {
				
			}
			else if (percentage < 2.f / 3.f) {

				float thisPercentage = (percentage * 3) / 2;

				model.at("BackArm")->angle = percentage * -90;

				model.at("Head")->angle = percentage * -30;
				model.at("Body")->angle = percentage * -30;
				model.at("FrontBigode")->angle = percentage * 30;
				model.at("BackBigode")->angle = percentage * 30;

				projectiles[0].setVisibility(true);

				if (facingRight) {
					projectiles[0].setImpulse(20, 0);
					projectiles[0].setScale((float)SCREEN_WIDTH / 7680 * percentage, (float)SCREEN_WIDTH / 7680 * percentage);
				}

				else {
					projectiles[0].setImpulse(-20, 0);
					projectiles[0].setScale((float)SCREEN_WIDTH / 7680 * percentage, (float)SCREEN_WIDTH / 7680 * percentage);
				}

				projectiles[0].update();

				ultimateShot->isAtacking = true;
				ultimateShot->hitbox.center = projectiles[0].getPosition();
				ultimateShot->hitbox.radius = projectiles[0].getSize().x / 2;
			}
			else if (percentage < 2.5f / 3.f) {

				static bool go = true;
				if (go) {
					//ultimateShot->playSound();
				}
				model.at("FrontArm")->angle = percentage * 90;

				model.at("Head")->angle = percentage * 30;
				model.at("Body")->angle = percentage * 30;
				model.at("FrontBigode")->angle = percentage * -30;
				model.at("BackBigode")->angle = percentage * -30;

				projectiles[0].setVisibility(false);
				projectiles[1].setVisibility(true);

				projectiles[1].setScale((float)SCREEN_WIDTH / 15360 * percentage, (float)SCREEN_WIDTH / 15360 * percentage);

				if (facingRight) {
					projectiles[1].setImpulse(30, 0);
				}
				else {
					projectiles[1].setImpulse(-30, 0);
				}

				projectiles[1].update();

				ultimateShot->isAtacking = true;

				ultimateShot->hitbox.center = projectiles[1].getPosition();
				ultimateShot->hitbox.radius = projectiles[1].getSize().x / 2;
			}
			else if (percentage < 2.9 / 3.f) {

				projectiles[1].setScale((float)SCREEN_WIDTH / 15360 * percentage, (float)SCREEN_WIDTH / 15360 * percentage);
				projectiles[1].update();
				model.at("FrontArm")->angle *= 0.9;
				model.at("BackArm")->angle *= 0.9;
				model.at("Head")->angle *= 0.9;
				model.at("Body")->angle *= 0.9;
				model.at("FrontBigode")->angle *= 0.9;
				model.at("BackBigode")->angle *= 0.9;

				ultimateShot->hitbox.center = projectiles[1].getPosition();
				ultimateShot->hitbox.radius = projectiles[1].getSize().x / 2;
			}
			else {

				projectiles[1].setVisibility(false);
				ultimateShot->isAtacking = false;
				ultimateShot->soundPlayed = false;

				model.at("FrontArm")->angle = 0;
				model.at("BackArm")->angle = 0;

				model.at("Head")->angle = 0;
				model.at("Body")->angle = 0;
				model.at("FrontBigode")->angle = 0;
				model.at("BackBigode")->angle = 0;
			}

		}

		void louKickAnim() {
			Time t = louKick->init.getElapsedTime();

			if (t > louKick->timeLapse) {
				atacking = STOPPED;
			}

			float percentage = (float)t.asMilliseconds() / (louKick->timeLapse.asMilliseconds());
			static bool go = true;

			if (percentage < 0.25f / 3.f) {
				model.resetToBase();
			}
			else if (percentage < 1.f / 3.f) {

				float thisPercentage = percentage * 3;

				model.at("BackArm")->angle = 90 * thisPercentage;
				projectiles[2].setVisibility(true);

				projectiles[2].setSpriteScale((SCREEN_WIDTH / 1920) * thisPercentage, -(SCREEN_HEIGHT / 1080) * thisPercentage * 2);

				projectiles[2].setPosition(position.x - projectiles[0].getSize().x / 2, SCREEN_HEIGHT);

				position.x += (frames % 2) * -8 + 4;
			}
			else if (percentage < 1.1f / 3.f) {

				projectiles[2].setVisibility(false);
				if (go) {
					int x = position.x - SCREEN_WIDTH / 2;
					position.x += sign(x) * -SCREEN_WIDTH / 2;
					if (position.x < 0) {
						position.x = 0;
					}
					else if (position.x > SCREEN_WIDTH) {
						position.x = SCREEN_WIDTH - SCREEN_WIDTH / 300;
					}
					louKick->playSound();
					go = false;
				}


			}
			else if (percentage < 2.f / 3.f) {
				float thisPercentage = (percentage * 3) / 2;

				go = true;

				model.at("FrontArm")->angle = 45 * thisPercentage;
				model.at("BackArm")->angle = -90 * thisPercentage;
				model.at("Head")->angle = 20 * thisPercentage;
				model.at("Body")->angle = 20 * thisPercentage;
				model.at("Hat")->angle = 10 * thisPercentage;
				louKick->isAtacking = true;
				louKick->hitbox.center = getBackHandPos();
				louKick->hitbox.radius = 100;
			}
			else if (percentage < 2.9f / 3.f) {

				louKick->isAtacking = false;
				model.at("FrontArm")->angle *= 0.9;
				model.at("BackArm")->angle *= 0.9;
				model.at("Head")->angle *= 0.9;
				model.at("Body")->angle *= 0.9;

			}
			else {

				model.at("FrontArm")->angle = 0;
				model.at("BackArm")->angle = 0;
				model.at("Head")->angle = 0;
				model.at("Body")->angle = 0;
				model.at("Hat")->angle = 0;
			}

		}

		void highAtackAnim() {
			Time t = hiKick->init.getElapsedTime();

			if (t > hiKick->timeLapse) {
				atacking = STOPPED;
			}

			float percentage = (float)t.asMilliseconds() / (hiKick->timeLapse.asMilliseconds());


			if (percentage < 1.f / 3.f) {

				float thisPercentage = percentage * 3;

				model.at("FrontArm")->angle = 180 * thisPercentage;
				model.at("FrontArm")->offset.y = -20 * thisPercentage;
				model.at("BackArm")->angle = -90 * thisPercentage;
				model.at("Head")->angle = -20 * thisPercentage;
				model.at("Body")->angle = -10 * thisPercentage;
				model.at("Hat")->angle = -10 * thisPercentage;

			}
			else if (percentage < 2.f / 3.f) {

				float thisPercentage = (percentage * 3) / 2;


				static int hspeed = -20;
				static int vspeed = 10;


				model.at("Hat")->offset.x += hspeed;
				model.at("Hat")->offset.y += vspeed;

				if (frames % 4 == 0)
					model.at("Hat")->xScl *= -1;

				model.at("FrontArm")->angle = -120 * thisPercentage;
				model.at("BackArm")->angle = -80 * thisPercentage;
				model.at("Head")->angle = -20 * thisPercentage;
				model.at("Body")->angle = 10 * thisPercentage;
				model.at("Hat")->angle = frames % 60;
				hiKick->isAtacking = true;
				hiKick->hitbox = hurtBox[2];
			}
			else if (percentage < 2.9f / 3.f) {

				model.at("FrontArm")->angle *= 0.9;
				model.at("BackArm")->angle *= 0.9;
				model.at("Head")->angle *= 0.9;
				model.at("Body")->angle *= 0.9;
				model.at("Hat")->angle = frames % 60;

				if (frames % 4 == 0)
					model.at("Hat")->xScl *= -1;

				model.at("Hat")->offset.x *= 0.99;
				model.at("Hat")->offset.y *= 0.99;

				hiKick->isAtacking = true;
				hiKick->hitbox = hurtBox[2];
			}
			else {
				hiKick->isAtacking = false;

				model.at("FrontArm")->angle = 0;
				model.at("BackArm")->angle = 0;
				model.at("Head")->angle = 0;
				model.at("Body")->angle = 0;
				model.at("Hat")->angle = 0;

				model.at("Hat")->xScl *= model.at("Hat")->xScl < 0 ? -1 : 1;

				model.at("Hat")->offset.x *= 0;
				model.at("Hat")->offset.y *= 0;
			}

		}

		void updateAnimations() override {
			if (estadoUpdate) {
				model.resetToBase();
				animations[0].playingFrame = 0;
			}

			if (!stunned) {

				if (estado == RUNNING) {
					runAnim();
					isDefending = false;
				}
				else if (estado == DEFENDING) {

					if (atacking == NOT_ATTACK) {

						agachadinha();

						animations[0].update();
						if (animations[0].playingFrame > 15) {
							animations[0].playingFrame = 15;
						}
						model.updateWithAnimation(animations[0]);

						isDefending = true;
					}

				}
				else if (estado == STOPPED) {
					runReset();
					isDefending = false;
				}





				if (air) {
					jumpAnim();
				}
				else {
					cairAnim();
				}

				if (atacking == HIGH_KICK) {
					highAtackAnim();
					isDefending = false;
				}
				else if (atacking == LOW_KICK) {
					louKickAnim();
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
				
			}
			if (estado == INVISIBLE) {
				sumir();
			}

			if (estado != INVISIBLE) {
				aparecer();
			}
			// projectiles[0].update();

		}

		/*
		void defended(Galo& galo2, Ataques* atk, bool facingRight) override {

			galo2.apanhar(*ultimateShot,facingRight);

		}*/

		void fatality(RenderWindow* window, Galo* galo2, RectangleShape fundo) override {

			Clock Timer;
			Timer.restart();

			estado = FATALITY;
			galo2->position.x = SCREEN_WIDTH / 2;
			position.x = SCREEN_WIDTH / 4 + model.getBounds().width * abs(model.xScl);

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

			Text bruxowins("Bruxo Wins", mortal, SCREEN_WIDTH / 50);

			bruxowins.setPosition(
				SCREEN_WIDTH / 2 - bruxowins.getGlobalBounds().width / 2,
				garra2.getPosition().y - bruxowins.getGlobalBounds().height
			);
			bruxowins.setFillColor(Color(250, 250, 250));
			bruxowins.setOutlineThickness(SCREEN_WIDTH / 700);
			bruxowins.setOutlineColor(Color(255, 255, 10));


			SoundBuffer grito;
			grito.loadFromFile("sounds\\Fatality_Scream.wav");
			Sound gritoSound;
			gritoSound.setBuffer(grito);
			gritoSound.setLoop(true);


			model.resetToBase();

			// Testando adicionar partes extras


			model.addElement(*model.at("FrontArm"), "FrontArm2", 0);
			model.at("FrontArm2")->setBaseAlpha(0);


			model.addElement(*model.at("FrontArm"), "FrontArm3", model.allBones.size() - 1);
			model.at("FrontArm3")->setBaseAngle(0);
			model.at("FrontArm3")->setBaseAlpha(0);


			model.addElement(*model.at("FrontArm"), "FrontArm4", 0);
			model.at("FrontArm4")->setBaseAngle(0);
			model.at("FrontArm4")->setBaseAlpha(0);

			model.addElement(*model.at("FrontArm"), "FrontArm5", 0);
			model.at("FrontArm5")->setBaseAngle(0);
			model.at("FrontArm5")->setBaseAlpha(0);

			model.addElement(*model.at("FrontArm"), "FrontArm6", model.allBones.size() - 1);

			model.at("FrontArm6")->setBaseAngle(0);
			model.at("FrontArm6")->setBaseAlpha(0);

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

			ExplosionEffect* exp = new ExplosionEffect(Vector2f(0, 0), 10);
			exp->sanguePreset();
			exp->depthSpdMin = -1;
			exp->depthSpdMax = 4;
			exp->depthMin = 100;
			exp->depthMax = 100;
			exp->mortal = false;
			

			SoundBuffer bufferfeit;
			bufferfeit.loadFromFile("sounds/Wingardium_Leviosa.ogg");
			Sound feit;
			feit.setBuffer(bufferfeit);


			int timeFrames = 0;

			Music fatalpeste;
			fatalpeste.openFromFile("sounds/fatalpeste.ogg");
			fatalpeste.setVolume(60);			
			fatalpeste.play();

			bool istime = true;
			bool istimeagain = true;
			int blue = 255;
			int red = 255;
			int green = 255;
			bool lets = true;
			bool letsgo = true;

			while (window->isOpen()) {

				float time = Timer.getElapsedTime().asMilliseconds();

				window->clear();
				window->draw(fundo);
				show(*window);

				exp->update();
				exp->draw(*window);

				galo2->show(*window);
				

				Event e;
				while (window->pollEvent(e))
				{
					if (e.type == Event::Closed)
					{
						window->close();
					}

				}


				float perc = 0;
				if (time < 1500) {

					

					if (green > 0)
						green -= 2;
					else
						green = 0;
					blue--;
					red--;

					fundo.setFillColor(Color(red, green, blue));


					perc = time / 1500;

					model.at("BackArm")->angle = perc * 90;
					model.at("FrontArm")->angle = perc * -45;
					model.at("FrontArm2")->angle = perc * 60;
					model.at("FrontArm3")->angle = perc * -60;
					model.at("FrontArm4")->angle = perc * 90;
					model.at("FrontArm5")->angle = perc * 90;
					model.at("FrontArm6")->angle = perc * -75;


				}
				else if (time < 2500) {
					float thisTime = time - 1500;

					perc = thisTime / 1000;

					model.at("BackArm")->angle = 90;
					model.at("FrontArm")->angle = -45;
					model.at("FrontArm2")->angle = 60;
					model.at("FrontArm3")->angle = -60;
					model.at("FrontArm4")->angle = 90;
					model.at("FrontArm5")->angle = 90;
					model.at("FrontArm6")->angle = -75;
					
					position.y = SCREEN_HEIGHT - ((SCREEN_HEIGHT / 2) * perc);

				}
				else if (time < 3000) {
					

					model.at("BackArm")->angle = 45;
					model.at("BackArm")->offset.x = 5;
					model.at("FrontArm")->angle = -100;
					model.at("FrontArm2")->angle = 90;
					model.at("FrontArm3")->angle = -60;
					model.at("FrontArm4")->angle = 120;
					model.at("FrontArm5")->angle = 180;
					model.at("FrontArm6")->angle = -30;
					if (time > 2500) {
						
						if (istime) {
							feit.play();
							istime = false;
						}
					}
				}
				else if (time < 6000) {

					// Ta nem usando esse thisTime né safado
					float thisTime = (time - 2500) / 6000;

					
					if (istimeagain) {
						gritoSound.play();
						istimeagain = false;
					}
					position.y = SCREEN_HEIGHT / 2;

					
					model.at("BackArm")->angle = 45;
					model.at("BackArm")->offset.x = 5;
					model.at("FrontArm")->angle = -100;
					model.at("FrontArm2")->angle = 90;
					model.at("FrontArm3")->angle = -60;
					model.at("FrontArm4")->angle = 120;
					model.at("FrontArm5")->angle = 180;
					model.at("FrontArm6")->angle = -30;

					model.at("Body")->angle = cos(frames);

					
					galo2->getHitByBruxoFatality();

					// insano
					if (timeFrames % 20 == 0) {

						Model model = galo2->getModel();

						exp->position = model.at("Body")->drawPos;

						exp->createMultipleParticles(500);
					}
					timeFrames++;
					
				}
				else {
					if (time > 6000) {
						 
						
						if (lets)
							fatalitysound.play();
						lets = false;
						window->draw(fatal);
						if (time > 8000) {
							if (time < 12000) {
															
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
							window->draw(bruxowins);
						}
					}
				}

				if (time > 15000) {
					return;
				}

				updateWithoutPhysics();

				galo2->updateWithoutPhysics();
				
				window->display();
			}
		}

	};


}

#endif // GALOBRUXO_H_INCLUDED