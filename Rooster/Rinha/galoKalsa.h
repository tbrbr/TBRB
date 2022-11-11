
#ifndef GALOKALSA_H_INCLUDED
#define GALOKALSA_H

#include "Galo.h"

namespace Rooster {

	class Kalsa : public Galo {

		Texture t;

		float legWalkAngFase = 0;
		float ArmSpinAngFase = 0;
		float Arm2SpinAngFase = 0;

		Texture jbl;
		Sprite berimbau;
		Sprite caixinha;

		bool superIsOn = true;

	public:
		Kalsa(struct GaloStats _stats, int _state, bool isp1) : Galo(_stats, _state, isp1) {
			this->name = "Kalsa";

			bar = new LifeBar(maxHp, isp1, name.c_str());


			this->hiKick = new Ataques(
				3, 15, HitBox{ Vector2f(0, 0), 0 },
				20, 10, -PI / 4, milliseconds(650), "sounds\\fist-punch-or-kick-7171.ogg"
			);
			this->louKick = new Ataques(
				4, 10, HitBox{ Vector2f(0, 0), 0 },
				20, 10, PI / 4, milliseconds(500), "sounds\\rooster-crowing-80322.ogg"
			);

			this->louKick->soundCollision.setVolume(25);

			this->ultimateShot = new Ataques(
				5, 70, HitBox{ Vector2f(0, 0),0 },
				5, 3, 0, milliseconds(750),
				"sounds\\scorpion-get_over_here.ogg", milliseconds(2000)
			);
			this->ultimateShot->soundCollision.setVolume(75);


			this->superAtack = new Ataques(14, 10, HitBox{ Vector2f(0, 0), 0 }, 20, 10, 0, milliseconds(3000), "sounds\\mg34.ogg");

			Projectile* cinto = new Projectile(
				Vector2f(0, 0),
				"sprites\\Cinto.png",
				0, 0, Vector2f(1, 1),
				IntRect(0, 0, 603, 100)
			);

			Projectile* cintoAmarrado = new Projectile(true);

			atacking = NOT_ATTACK;
			projectiles.push_back(*cinto);
			projectiles.push_back(*cintoAmarrado);

			jbl.loadFromFile("sprites\\berimbau.png");
			berimbau.setTexture(jbl);
			caixinha.setTexture(jbl);

			IntRect rectBerimbau(0, 0, 809, 2659);
			IntRect rectcaixinha(809, 0, 2096, 2659);

			berimbau.setTextureRect(rectBerimbau);
			caixinha.setTextureRect(rectcaixinha);

			berimbau.setScale((float)SCREEN_WIDTH / 15360, (float)SCREEN_WIDTH / 15360);
			caixinha.setScale((float)SCREEN_WIDTH / 15360, (float)SCREEN_WIDTH / 15360);

			t.loadFromFile("sprites/galoKalsa.png");

			model.tex = &t;
			model.loadModel("models/kalsaModel.txt");
			model.autoSetBounds(model.at("Body"), model.at("BackLeg"), model.at("Head"));

			HitBox* hit = new HitBox;
			for (int i = 0; i < model.allBones.size(); i++) {

				hit->center = model.at(i)->drawPos;
				hit->radius = model.at(i)->sprite.getGlobalBounds().width / 2;

				hurtBox.push_back(*hit);
			}

			delete hit;



			struct Animation agacharAnim;
			agacharAnim.init("animations/kalsaDefend.txt");
			agacharAnim.playingSpeed = 1;
			agacharAnim.connectLoop = false;

			animations.push_back(agacharAnim);

			struct Animation danceAnim;
			danceAnim.init("animations/kalsaDance3.txt");
			danceAnim.playingSpeed = 0.1;
			danceAnim.connectLoop = true;

			animations.push_back(danceAnim);

		}


		Vector2f getFrontFootPos() {
			float coordXPaint = 600;
			float coordYPaint = 1095;

			float ax = coordXPaint - model.at("FrontLeg")->sprArea.texRect.left;
			float ay = coordYPaint - model.at("FrontLeg")->sprArea.texRect.top;

			float difx = ax - model.at("FrontLeg")->center.x;
			float dify = ay - model.at("FrontLeg")->center.y;

			float ang = toRadiAnus(model.at("FrontLeg")->finalAngle);

			float xScl = model.at("FrontLeg")->finalXScl;
			float yScl = model.at("FrontLeg")->finalYScl;

			float rotx = cos(ang) * difx - sin(ang) * dify;
			float roty = sin(ang) * difx + cos(ang) * dify;

			rotx *= xScl;
			roty *= yScl;

			Vector2f pe;
			pe.y = model.at("FrontLeg")->drawPos.y + roty;
			pe.x = model.at("FrontLeg")->drawPos.x + rotx;

			return pe;

		}

		Vector2f getBackFootPos() {
			float coordXPaint = 600;
			float coordYPaint = 1095;

			float ax = coordXPaint - model.at("BackLeg")->sprArea.texRect.left;
			float ay = coordYPaint - model.at("BackLeg")->sprArea.texRect.top;

			float difx = ax - model.at("BackLeg")->center.x;
			float dify = ay - model.at("BackLeg")->center.y;

			float ang = toRadiAnus(model.at("BackLeg")->finalAngle);

			float xScl = model.at("BackLeg")->finalXScl;
			float yScl = model.at("BackLeg")->finalYScl;

			float rotx = cos(ang) * difx - sin(ang) * dify;
			float roty = sin(ang) * difx + cos(ang) * dify;

			rotx *= xScl;
			roty *= yScl;

			Vector2f pe;
			pe.y = model.at("BackLeg")->drawPos.y + roty;
			pe.x = model.at("BackLeg")->drawPos.x + rotx;

			return pe;

		}


		void jumpAnim() {


			ArmSpinAngFase = -(vspeed / 16) * 45;
			Arm2SpinAngFase = -(vspeed / 16) * 45;


			model.at("FrontLeg")->angle -= (vspeed) * 2;
			model.at("BackLeg")->angle -= (vspeed) * 2;

			// mortal fodase?

			model.at("Body")->angle += hspeed / 2;

		}
		void cairAnim() {
			model.at("FrontLeg")->offset.y = 0;
			model.at("BackLeg")->offset.y = 0;

			model.at("Body")->angle *= 0.7;
		}
		void runAnim() {
			legWalkAngFase += hspeed;
			legWalkAngFase -= ((int)legWalkAngFase / 360) * 360;

			model.at("FrontLeg")->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at("BackLeg")->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

			model.at("FrontArm")->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at("BackArm")->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;

		}
		void runReset() {
			legWalkAngFase *= 0.8;
			ArmSpinAngFase *= 0.8;
			Arm2SpinAngFase *= 0.8;

			model.at("FrontLeg")->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at("BackLeg")->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

			model.at("FrontArm")->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;
			model.at("BackArm")->angle += sin(2 * PI * legWalkAngFase / 360) * 60;


			model.at("Body")->offset.y = 0;
			model.at("BackLeg")->offset.y = 0;
			model.at("FrontLeg")->offset.y = 0;

		}

		void defend() override {
			estado = DEFENDING;
		}

		void agachadinha() {
			hspeed = 0;
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
				ultimateShot->playSound();
			}

		}
		void super() override {
			
			if (atacking == NOT_ATTACK) {
				atacking = SUPER;
				superAtack->init.restart();
				superIsOn = true;
				bar->resetPower();
			}
			
		}

		void superAnim() {
			Time t = superAtack->init.getElapsedTime();

			 

			if (t > superAtack->timeLapse) {
				atacking = NOT_ATTACK;
				superAtack->isAtacking = false;
			}

			float percentage = (float)t.asMilliseconds() / (superAtack->timeLapse.asMilliseconds());

			

			if (superIsOn) {
				vspeed += air ? -1 : jumpSpeed / 1.5;
				air = true;
				superIsOn = false;
				
			}
			
			position.x += facingRight ? 1 : -1;


			if (vspeed > 0) {

				air = false;

				vspeed = 0.5;

				superAtack->isAtacking = true;

				

				model.at("Body")->angle = 90;

				float bAngle = -45 * sin(percentage * 32 * PI / 2);
				float fAngle = 45 * sin(percentage * 32 * PI / 2);

				model.at("BackLeg")->angle = bAngle;
				model.at("FrontLeg")->angle = fAngle;

				superAtack->hitbox.center = bAngle < fAngle ? getBackFootPos() : getFrontFootPos();
				superAtack->hitbox.radius = model.at("FrontLeg")->sprite.getGlobalBounds().height / 6;

				model.at("FrontEyebrow")->offset.y = 10;
				model.at("FrontEyebrow")->offset.x = -5;
				model.at("BackEyebrow")->offset.y = 5;

				model.at("Head")->angle = -45;

				model.at("FrontArm")->angle = -90;
				model.at("BackArm")->angle = -90;

			}

		

		}

		void especialAnim() {
			Time t = ultimateShot->init.getElapsedTime();

			if (t > ultimateShot->timeLapse) {
				atacking = NOT_ATTACK;
			}

			float percentage = (float)t.asMilliseconds() / (ultimateShot->timeLapse.asMilliseconds());

			int angFix = -1;

			if (!ultimateShot->getHitted) {
				if (percentage < 1.f / 3.f) {

					float thisPercentage = percentage * 3;
					if (model.at("FrontEyebrow")->offset.y < 6) {
						model.at("FrontEyebrow")->offset.y += 0.5;
						model.at("BackEyebrow")->offset.y += 0.5;
					}


					model.at("Head")->angle = -15 * sin(thisPercentage * PI / 2);
					model.at("FrontArm")->angle = -45 * sin(thisPercentage * PI / 2);
					model.at("BackArm")->angle = 20 * sin(thisPercentage * PI / 2);
					model.at("FrontLeg")->angle = -20 * sin(thisPercentage * PI / 2);

				}
				else if (percentage < 2.f / 3.f) {

					float thisPercentage = (percentage * 3) / 2;
					model.at("FrontArm")->angle = -20;
					model.at("BackArm")->angle = 120;
					model.at("FrontLeg")->angle = -20;

					projectiles[0].setVisibility(true);

					if (facingRight) {
						projectiles[0].setPosition(
							Vector2f(
								model.at("BackArm")->drawPos.x + model.at("BackArm")->sprite.getGlobalBounds().width / 2,
								model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4
							)
						);
					}
					else {
						projectiles[0].setPosition(
							Vector2f(
								model.at("BackArm")->drawPos.x - model.at("BackArm")->sprite.getGlobalBounds().width / 2,
								model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4
							)
						);
					}


					if (facingRight) {
						projectiles[0].setScale(Vector2f(0.5 * thisPercentage, 0.5));
					}
					else {
						projectiles[0].setScale(Vector2f(-0.5 * thisPercentage, 0.5));
					}


					if (facingRight) {
						ultimateShot->hitbox.center.x = (
							projectiles[0].getPosition().x +
							projectiles[0].getSize().x - projectiles[0].getSize().x / 6
							);
					}
					else {
						ultimateShot->hitbox.center.x = (
							projectiles[0].getPosition().x -
							projectiles[0].getSize().x + projectiles[0].getSize().x / 6
							);
					}

					ultimateShot->isAtacking = true;
					ultimateShot->hitbox.center.y = projectiles[0].getPosition().y + projectiles[0].getSize().y / 2;
					ultimateShot->hitbox.radius = projectiles[0].getSize().x / 10;


				}
				else if (percentage < 2.5f / 3.f) {

					float thisPercentage = (percentage * 3) / 2.5;
					model.at("FrontArm")->angle = -20;
					model.at("BackArm")->angle = 120;


					if (facingRight) {
						projectiles[0].setPosition(
							Vector2f(
								model.at("BackArm")->drawPos.x + model.at("BackArm")->sprite.getGlobalBounds().width / 2,
								model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4
							)
						);
					}
					else {
						projectiles[0].setPosition(
							Vector2f(
								model.at("BackArm")->drawPos.x - model.at("BackArm")->sprite.getGlobalBounds().width / 2,
								model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4
							)
						);
					}

					if (facingRight) {
						ultimateShot->hitbox.center.x = (
							projectiles[0].getPosition().x +
							projectiles[0].getSize().x - projectiles[0].getSize().x / 6
							);
					}
					else {
						ultimateShot->hitbox.center.x = (
							projectiles[0].getPosition().x -
							projectiles[0].getSize().x + projectiles[0].getSize().x / 6
							);
					}
					ultimateShot->isAtacking = true;
					ultimateShot->hitbox.center.y = projectiles[0].getPosition().y + projectiles[0].getSize().y / 2;
					ultimateShot->hitbox.radius = projectiles[0].getSize().x / 10;
				}
				else if (percentage < 2.9 / 3.f) {
					float thisPercentage = (percentage * 3) / 2.9;

					model.at("FrontArm")->angle = -20;
					model.at("BackArm")->angle = 120 / sin(thisPercentage * PI / 2);

					model.at("FrontEyebrow")->offset.y *= 0.9;
					model.at("BackEyebrow")->offset.y *= 0.9;
					model.at("Head")->angle *= 0.9;


					if (facingRight) {
						projectiles[0].setPosition(
							Vector2f(
								model.at("BackArm")->drawPos.x + model.at("BackArm")->sprite.getGlobalBounds().width / 2,
								model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4
							)
						);
					}
					else {
						projectiles[0].setPosition(
							Vector2f(
								model.at("BackArm")->drawPos.x - model.at("BackArm")->sprite.getGlobalBounds().width / 2,
								model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4
							)
						);
					}

					if (facingRight) {
						projectiles[0].setScale(Vector2f(0.1 / thisPercentage, 0.5));
					}
					else {
						projectiles[0].setScale(Vector2f(-0.1 / thisPercentage, 0.5));
					}
					ultimateShot->isAtacking = false;


				}
				else {
					projectiles[0].setVisibility(false);
					model.at("FrontEyebrow")->offset.y = 0;
					model.at("BackEyebrow")->offset.y = 0;
					model.at("FrontArm")->angle = 0;
					model.at("BackArm")->angle = 0;
				}
			}
			else {

				if (percentage < 2.f / 3.f) {

					float thisPercentage = (percentage * 3) / 2;
					model.at("FrontArm")->angle = -20;
					model.at("BackArm")->angle = 120;
					model.at("FrontLeg")->angle = -20;

					projectiles[0].setVisibility(true);


					projectiles[0].setPosition(
						Vector2f(model.at("BackArm")->drawPos.x + projectiles[0].getSize().x / 4,
							(model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4)
						)
					);

					if (facingRight) {
						projectiles[0].setScale(Vector2f(0.5 * thisPercentage, 0.5));
					}
					else {
						projectiles[0].setScale(Vector2f(-0.5 * thisPercentage, 0.5));
					}


					if (facingRight) {
						ultimateShot->hitbox.center.x = (
							projectiles[0].getPosition().x +
							projectiles[0].getSize().x - projectiles[0].getSize().x / 6
							);
					}
					else {
						ultimateShot->hitbox.center.x = (
							projectiles[0].getPosition().x -
							projectiles[0].getSize().x + projectiles[0].getSize().x / 6
							);
					}

					ultimateShot->isAtacking = true;
					ultimateShot->hitbox.center.y = projectiles[0].getPosition().y + projectiles[0].getSize().y / 2;
					ultimateShot->hitbox.radius = projectiles[0].getSize().x / 10;


				}
				else if (percentage < 2.5f / 3.f) {

					float thisPercentage = (percentage * 3) / 2.5;
					model.at("FrontArm")->angle = -20;
					model.at("BackArm")->angle = 120;

					projectiles[0].setPosition(
						Vector2f(model.at("BackArm")->drawPos.x,
							(model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4)
						)
					);

					if (facingRight) {
						ultimateShot->hitbox.center.x = (
							projectiles[0].getPosition().x +
							projectiles[0].getSize().x - projectiles[0].getSize().x / 6
							);
					}
					else {
						ultimateShot->hitbox.center.x = (
							projectiles[0].getPosition().x -
							projectiles[0].getSize().x + projectiles[0].getSize().x / 6
							);
					}
					ultimateShot->isAtacking = true;
					ultimateShot->hitbox.center.y = projectiles[0].getPosition().y + projectiles[0].getSize().y / 2;
					ultimateShot->hitbox.radius = projectiles[0].getSize().x / 10;
				}
				else if (percentage < 2.9 / 3.f) {
					float thisPercentage = (percentage * 3) / 2.9;

					model.at("FrontArm")->angle = -20;
					model.at("BackArm")->angle -= 1;

					model.at("FrontEyebrow")->offset.y *= 0.9;
					model.at("BackEyebrow")->offset.y *= 0.9;
					model.at("Head")->angle *= 0.9;

					if (facingRight) {
						projectiles[0].setPosition(
							Vector2f(
								projectiles[0].getPosition().x - 1,
								model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4
							)
						);
					}
					else {
						projectiles[0].setPosition(
							Vector2f(
								projectiles[0].getPosition().x + 1,
								model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4
							)
						);
					}

					if (facingRight) {
						projectiles[0].setScale(Vector2f(0.1 / thisPercentage, 0.5));
					}
					else {
						projectiles[0].setScale(Vector2f(-0.1 / thisPercentage, 0.5));
					}
					ultimateShot->isAtacking = false;


				}
				else {
					projectiles[0].setVisibility(false);
					model.at("FrontEyebrow")->offset.y = 0;
					model.at("BackEyebrow")->offset.y = 0;
					model.at("FrontArm")->angle = 0;
					model.at("BackArm")->angle = 0;
					ultimateShot->isAtacking = false;
				}
			}
		}




		void louKickAnim() {
			Time t = louKick->init.getElapsedTime();

			if (t > louKick->timeLapse) {
				atacking = NOT_ATTACK;
			}

			float percentage = (float)t.asMilliseconds() / (louKick->timeLapse.asMilliseconds());

			static bool go = true;

			if (percentage < 1.f / 3.f) {

				float thisPercentage = percentage * 3;
				model.at("FrontArm")->angle = 45 * sin(thisPercentage * PI / 2);
				model.at("BackArm")->angle = 20 * sin(thisPercentage * PI / 2);
				model.at("BackLeg")->angle = 20 * sin(thisPercentage * PI / 2);
				model.at("Head")->angle = -20 * sin(thisPercentage * PI / 2);
				model.at("FrontEyebrow")->offset.y += 0.5;
				model.at("BackEyebrow")->offset.y += 0.5;
				model.at("FrontLeg")->offset.y = -20 * thisPercentage;
				model.at("BackLeg")->offset.y = -20 * thisPercentage;
				model.at("Biko")->offset.x = -2;
				model.at("Body")->offset.y = -20 * thisPercentage;
				model.at("Body")->angle = 45 * sin(thisPercentage * PI / 2);
			}
			else if (percentage < 2.f / 3.f) {

				model.at("Body")->angle = -75;
				model.at("FrontArm")->angle = -60;
				model.at("BackArm")->angle = -60;

				model.at("BackLeg")->angle = 20;
				model.at("Head")->angle = 45;
				model.at("Head")->offset.x = -15;

				model.at("FrontLeg")->angle = 45;
				model.at("BackLeg")->angle = 45;
				louKick->hitbox.center = model.at("Biko")->drawPos;
				louKick->hitbox.radius = model.at("Biko")->sprite.getGlobalBounds().width / 2;
				louKick->isAtacking = true;

				if (go) {
					louKick->playSound();
					go = false;
				}

			}
			else if (percentage < 2.9f / 3.f) {

				go = true;
				model.at("FrontArm")->angle *= 0.9;
				model.at("BackArm")->angle *= 0.9;

				model.at("BackArm")->angle *= 0.9;
				model.at("BackLeg")->angle *= 0.9;

				model.at("Head")->angle *= 0.9;
				model.at("Head")->offset.x *= 0.9;

				model.at("FrontEyebrow")->offset.y *= 0.9;
				model.at("BackEyebrow")->offset.y *= 0.9;

				model.at("FrontLeg")->angle *= 0.9;
				model.at("BackLeg")->offset.y *= 0.9;

				model.at("Body")->angle *= 0.9;
				louKick->isAtacking = false;

			}
			else {

				model.at("FrontArm")->angle = 0;
				model.at("BackArm")->angle = 0;

				model.at("BackArm")->angle = 0;
				model.at("BackLeg")->angle = 0;

				model.at("Head")->angle = 0;
				model.at("Head")->offset.x = 0;

				model.at("FrontEyebrow")->offset.y = 0;
				model.at("BackEyebrow")->offset.y = 0;

				model.at("FrontLeg")->angle = 0;
				model.at("BackLeg")->offset.y = 0;

				model.at("Body")->angle = 0;
			}


		}

		void highAtackAnim() {
			Time t = hiKick->init.getElapsedTime();

			if (t > hiKick->timeLapse) {
				atacking = STOPPED;
			}

			float percentage = (float)t.asMilliseconds() / (hiKick->timeLapse.asMilliseconds());

			static bool go;
			if (percentage < 0.5 / 3.f) {

				float thisPercentage = percentage * 6;

				model.at("FrontArm")->angle = 45 * sin(thisPercentage * PI / 2);
				model.at("BackArm")->angle = -90 * sin(thisPercentage * PI / 2);
				model.at("BackLeg")->angle = 15 * sin(thisPercentage * PI / 2);
				model.at("Head")->angle = -20 * sin(thisPercentage * PI / 2);
				model.at("FrontEyebrow")->offset.y += 1;
				model.at("BackEyebrow")->offset.y += 1;
				model.at("FrontLeg")->offset.y = -20 * sin(thisPercentage * PI / 2);

			}
			else if (percentage < 1.f / 3.f) {
				float thisPercentage = percentage * 3;

				model.at("Body")->angle = -60 * sin(thisPercentage * PI / 2);
				model.at("BackLeg")->angle = 50 * sin(thisPercentage * PI / 2);

			}
			else if (percentage < 2.f / 3.f) {

				model.at("Body")->angle = 60;
				model.at("BackLeg")->angle = 50;
				model.at("FrontLeg")->angle = -45;
				model.at("BackLeg")->offset.x -= 1;
				model.at("BackLeg")->offset.y -= 1;
				model.at("FrontArm")->angle = -45;
				model.at("BackArm")->angle = 90;

				hiKick->hitbox.center = model.at("BackLeg")->drawPos;
				hiKick->hitbox.radius = model.at("BackLeg")->sprite.getGlobalBounds().width / 2;
				hiKick->isAtacking = true;
				if (go) {
					hiKick->playSound();
					go = false;
				}
			}
			else if (percentage < 2.9f / 3.f) {
				go = true;
				model.at("Body")->angle *= 0.9;
				model.at("BackLeg")->angle *= 0.9;
				model.at("BackLeg")->offset.x *= 0.9;
				model.at("BackLeg")->offset.y *= 0.9;
				model.at("FrontArm")->angle *= 0.9;
				model.at("BackArm")->angle *= 0.9;
				model.at("FrontLeg")->offset.y *= 0.9;
				model.at("Head")->angle *= 0.9;
				hiKick->isAtacking = false;
			}
			else {
				model.at("Body")->angle = 0;
				model.at("BackLeg")->angle = 0;
				model.at("BackLeg")->offset.x = 0;
				model.at("BackLeg")->offset.y = 0;
				model.at("FrontArm")->angle = 0;
				model.at("BackArm")->angle = 0;
				model.at("FrontLeg")->offset.y = 0;
				model.at("Head")->angle *= 0;
				model.at("FrontEyebrow")->offset.y = 0;
				model.at("BackEyebrow")->offset.y = 0;
			}
		}




		void updateAnimations() override {
			// Abaixo temos
			// CA OS TO TAL
			if (estadoUpdate) {
				model.resetToBase();
				animations[0].playingFrame = 0;
			}


			model.at("FrontArm")->angle = ArmSpinAngFase;
			model.at("BackArm")->angle = Arm2SpinAngFase;

			if (!stunned) {

				if (estado == RUNNING) {
					runAnim();
					isDefending = false;
				}
				else if (estado == DEFENDING) {
					animations[0].update();
					if (animations[0].playingFrame > 15) {
						animations[0].playingFrame = 15;
						isDefending = true;
						defense.center.x = model.at("FrontArm")->drawPos.x;
						defense.center.y = model.at("FrontArm")->drawPos.y;
						defense.radius = model.at("FrontArm")->sprite.getGlobalBounds().height / 2;
					}
					else {
						isDefending = false;
					}
					model.updateWithAnimation(animations[0]);

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


				// Attack Animation
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
				else if (estado == DANCING) {
					animations[1].update();
					model.updateWithAnimation(animations[1]);
				}



			}

			if (estado == INVISIBLE) {
				sumir();
			}
			else {
				aparecer();
			}

			projectiles[0].update();
		}

		void tocarBerimbau(RenderWindow* window) {

			static int thisFrames = 0;

			if (thisFrames == 120) {
				thisFrames = 0;
			}

			if (frames % 60 == 0) {
				facingRight = !facingRight;
			}

			estado = DANCING;

			if (facingRight) {
				berimbau.setPosition(
					position.x + berimbau.getGlobalBounds().width,
					position.y - berimbau.getGlobalBounds().height + (((thisFrames % 16) - 8))
				);
			}
			else {
				berimbau.setPosition(
					position.x - berimbau.getGlobalBounds().width,
					position.y - berimbau.getGlobalBounds().height + (((thisFrames % 16) - 8))
				);
			}

			window->draw(berimbau);
			thisFrames++;
		}

		void fatality(RenderWindow* window, Galo* galo2, RectangleShape fundo) override {

			Clock Timer;
			Timer.restart();

			estado = FATALITY;

			galo2->position.x = SCREEN_WIDTH / 2;

			position.x = SCREEN_WIDTH / 3;

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

			Text kalsawins("Kalsa Wins", mortal, SCREEN_WIDTH / 50);

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

			ExplosionEffect* exp = new ExplosionEffect(Vector2f(0, 0), 10);
			exp->sanguePreset();
			exp->depthSpdMin = -1;
			exp->depthSpdMax = 4;
			exp->depthMin = 100;
			exp->depthMax = 100;

			exp->mortal = false;

			int timeFrames = 0;

			struct GaloStats kalsaSt = { 100, 12, 12,  5, 6 , 20 };

			Kalsa kalsa2(kalsaSt, Rooster::state::STOPPED, false);
			Kalsa kalsa3(kalsaSt, Rooster::state::STOPPED, false);

			kalsa3.setPosition(Vector2f(SCREEN_WIDTH / 2, -500));
			caixinha.setPosition(kalsa3.getPosition());

			int blue = 255;
			int red = 255;
			int green = 255;


			int framesCinto = 0;

			bool istime = true;
			Music capoeira;
			capoeira.openFromFile("sounds\\somdeberimbau.ogg");
			capoeira.play();
			bool goBrega = true;
			Music aldairPlayboy;
			aldairPlayboy.openFromFile("sounds\\aldairplayboydjlowhan-senta-porra-aldair-playboy-996e8d9d-_mp3cut.net_.ogg");

			bool lets = true;

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

				if (time < 3000) {


					estado = STOPPED;
					tocarBerimbau(window);
					update();


					galo2->setState(DEFENDING);
					galo2->facingRight = false;


					galo2->update();

				}
				else if (time < 6000) {
					estado = STOPPED;
					tocarBerimbau(window);
					update();

					if (frames % 20 == 0) {
						galo2->setState(DEFENDING);
						galo2->facingRight = !facingRight;
					}
					galo2->update();

					kalsa2.setPosition(Vector2f((SCREEN_WIDTH * 3 / 4), kalsa2.getPosition().y));
					kalsa2.tocarBerimbau(window);
					kalsa2.update();
					kalsa2.show(*window);
				}
				else if (time < 9000) {

					capoeira.stop();
					if (green > 0)
						green--;
					if (blue > 0)
						blue--;
					if (red > 0)
						red--;


					fundo.setFillColor(Color(red, green, blue));


					facingRight = true;
					kalsa2.facingRight = false;

					position.x = SCREEN_WIDTH / 4;
					kalsa2.position.x = SCREEN_WIDTH * 3 / 4;

					estado = STOPPED;

					kalsa2.setState(STOPPED);


					if (framesCinto == 2) {
						kalsa2.especial();
						especial();
					}

					if (framesCinto == 5) {
						kalsa2.ultimateShot->getHitted = true;
						ultimateShot->getHitted = true;
					}
					if (framesCinto > 4) {
						galo2->getHitByKalsaFatalityHead(window, this);
						galo2->getHitByKalsaFatalityBody(window, &kalsa2);
						if (istime) {
							gritoSound.play();
							istime = false;
						}
						// insano
						if (timeFrames % 20 == 0) {

							Model model = galo2->getModel();

							exp->position = model.at("Body")->drawPos;

							exp->createMultipleParticles(500);

							timeFrames++;

						}
					}


					galo2->update();
					update();
					kalsa2.update();

					kalsa2.show(*window);

					framesCinto++;

				}
				else if (time > 9000) {

					gritoSound.stop();

					if (goBrega) {
						aldairPlayboy.play();
						goBrega = false;
					}

					if (kalsa3.getPosition().y < kalsa2.getPosition().y) {

						kalsa3.setPosition(Vector2f(SCREEN_WIDTH / 2, kalsa3.getPosition().y + 10));

					}
					else {

						kalsa3.setState(DANCING);
					}

					estado = DANCING;
					kalsa2.setState(DANCING);
					caixinha.setPosition(kalsa3.getPosition().x, kalsa3.getPosition().y - SCREEN_HEIGHT / 10);

					kalsa3.show(*window);
					kalsa3.update();
					window->draw(caixinha);

					galo2->update();
					update();
					kalsa2.update();

					kalsa2.show(*window);

					if (timeFrames % 20 == 0) {

						Model model = galo2->getModel();

						exp->position = model.at("Body")->drawPos;

						exp->createMultipleParticles(500);
					}

					timeFrames++;


					if (time > 10000) {
						
						

						if (lets)
							fatalitysound.play();
						lets = false;
						window->draw(fatal);
						if (time > 12000) {


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
				}

				if (time > 30000) {
					return;
				}

				updateWithoutPhysics();

				galo2->updateWithoutPhysics();

				window->display();
			}
		}


	};


}

#endif // GALOKALSA_H_INCLUDED