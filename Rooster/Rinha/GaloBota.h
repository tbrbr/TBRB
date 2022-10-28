#pragma once

#ifndef GALOBOTA_H_INCLUDED
#define GALOBOTA_H

#include "Galo.h"

namespace Rooster {

    class Bota : public Galo {

        Texture t;
        float legWalkAngFase = 0;
        float ArmSpinAngFase = 0;
        float Arm2SpinAngFase = 0;



    public:
        Bota(struct GaloStats _stats, int _state, bool isp1) : Galo(_stats, _state, isp1) {
            this->name = "Bota";

            bar = new LifeBar(maxHp, isp1, name.c_str());

            this->peso = 4;


            this->hiKick = new Ataques(
                3,
                8, 0.5, HitBox{ Vector2f(0, 0), 0 },
                20, 10, -PI / 4, milliseconds(1200), ""
            );
            this->louKick = new Ataques(4,
                5, 0.5, HitBox{ Vector2f(0, 0), 0 },
                20, 10, PI / 4, milliseconds(1000), ""
            );

            this->ultimateShot = new Ataques(5,
                0.9, 160, HitBox{ Vector2f(0, 0), 0 },
                10, 3, 0, milliseconds(1000),
                "sounds\\scorpion-get_over_here.ogg", milliseconds(2000)
            );

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

            if (isp1)
                position.x = SCREEN_WIDTH / 4;
            else
                position.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;

            position.y = floorY;






            t.loadFromFile("sprites/galoBota.png");

            model.tex = &t;
            model.loadModel("botaModel.txt");
            model.autoSetBounds(model.at("Body"),  model.at("Body"), model.at("Head"));

            HitBox* hit = new HitBox;
            for (int i = 0; i < model.allBones.size(); i++) {

                hit->center = model.at(i)->drawPos;
                hit->radius = model.at(i)->sprite.getGlobalBounds().width / 2;

                hurtBox.push_back(*hit);
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
        void especialAnim() {
            Time t = ultimateShot->init.getElapsedTime();

            if (t > ultimateShot->timeLapse) {
                atacking = NOT_ATTACK;

            }


            float percentage = (float)t.asMilliseconds() / (ultimateShot->timeLapse.asMilliseconds());

            int angFix = (facingRight) ? 1 : -1;
            angFix = -1;

            if (!ultimateShot->getHitted) {
                if (percentage < 1.f / 3.f) {

                    float thisPercentage = percentage * 3;
                    model.at("FrontEyebrow")->offset.y += 0.5;
                    model.at("BackEyebrow")->offset.y += 0.5;

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


                    projectiles[0].setPosition(
                        Vector2f(model.at("BackArm")->drawPos.x,
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

                    if (facingRight) {
                        projectiles[0].setPosition(
                            Vector2f(
                                model.at("BackArm")->drawPos.x + (projectiles[0].getSize().x / 2.5 * thisPercentage),
                                model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4
                            )
                        );
                    }
                    else {
                        projectiles[0].setPosition(
                            Vector2f(
                                model.at("BackArm")->drawPos.x - (projectiles[0].getSize().x / 2.5 * thisPercentage),
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
                                model.at("BackArm")->drawPos.x - (projectiles[0].getSize().y * thisPercentage),
                                model.at("BackArm")->drawPos.y - projectiles[0].getSize().y / 4
                            )
                        );
                    }
                    else {
                        projectiles[0].setPosition(
                            Vector2f(
                                model.at("BackArm")->drawPos.x + (projectiles[0].getSize().y * thisPercentage),
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
                        Vector2f(model.at("BackArm")->drawPos.x,
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
                }
            }
        }




        void louKickAnim() {
            Time t = louKick->init.getElapsedTime();

            if (t > louKick->timeLapse) {
                atacking = STOPPED;
            }

            float percentage = (float)t.asMilliseconds() / (louKick->timeLapse.asMilliseconds());


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



            }
            else if (percentage < 2.9f / 3.f) {

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

            }
            else if (percentage < 2.9f / 3.f) {

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
                ///animations[0].playingFrame = 0;
            }


            //model.at("FrontArm")->angle = ArmSpinAngFase;
            //model.at("BackArm")->angle = Arm2SpinAngFase;

            if (stunFrames <= 0) {


                if (estado != RUNNING) {
                    hspeed = 0;
                }





                // Attack Animation
                if (atacking == HIGH_KICK) {
                    //highAtackAnim();
                }
                else if (atacking == LOW_KICK) {
                    //louKickAnim();
                }
                else if (atacking == SPECIAL) {
                    //especialAnim();
                }
            }

            //projectiles[0].update();


        }


    };


}

#endif // GALOBOTA_H_INCLUDED