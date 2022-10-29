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
                40, 10, -PI / 3, milliseconds(1200), ""
            );
            this->louKick = new Ataques(4,
                5, 0.5, HitBox{ Vector2f(0, 0), 0 },
                20, 10, PI, milliseconds(1000), ""
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




            // mortal fodase?

            model.at("Head")->offset.y += vspeed/5;
            

            model.at("Body")->angle += vspeed / 100;
            model.at("Head")->angle = -model.at("Body")->angle/5;


            model.at("Body")->yScl -= vspeed / 10000;
            model.at("Body")->xScl += vspeed / 10000;

        }
        void cairAnim() {

            model.at("Head")->offset.y = 0;
            model.at("Head")->angle = 0;
            model.at("Body")->angle *= 0.7;
            model.at("Body")->yScl = model.at("Body")->getBaseScale().y;
            model.at("Body")->xScl = model.at("Body")->getBaseScale().x;

        }
        void runAnim() {

            legWalkAngFase += hspeed;
            legWalkAngFase -= ((int)legWalkAngFase / 360) * 360;

            model.at("Body")->center.y = model.at("Body")->getBaseCenter().y + abs(sin(2 * PI * legWalkAngFase / 360) * 60) * 1;
            
            

        }
        void runReset() {
            legWalkAngFase *= 0.8;
            ArmSpinAngFase *= 0.8;
            Arm2SpinAngFase *= 0.8;

            model.at("Body")->center.y = model.at("Body")->getBaseCenter().y;

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
                    

                }
                else if (percentage < 2.f / 3.f) {

                    float thisPercentage = (percentage * 3) / 2;
                   

                    ultimateShot->isAtacking = true;
                    ultimateShot->hitbox.center.y = projectiles[0].getPosition().y + projectiles[0].getSize().y / 2;
                    ultimateShot->hitbox.radius = projectiles[0].getSize().x / 10;


                }
                else if (percentage < 2.5f / 3.f) {

                    float thisPercentage = (percentage * 3) / 2.5;
                   
                    ultimateShot->isAtacking = true;
                    ultimateShot->hitbox.center.y = projectiles[0].getPosition().y + projectiles[0].getSize().y / 2;
                    ultimateShot->hitbox.radius = projectiles[0].getSize().x / 10;
                }
                else if (percentage < 2.9 / 3.f) {
                    float thisPercentage = (percentage * 3) / 2.9;

                   
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

                }
            }
            else {

                if (percentage < 2.f / 3.f) {

                    float thisPercentage = (percentage * 3) / 2;


                    ultimateShot->isAtacking = true;
                    ultimateShot->hitbox.center.y = projectiles[0].getPosition().y + projectiles[0].getSize().y / 2;
                    ultimateShot->hitbox.radius = projectiles[0].getSize().x / 10;


                }
                else if (percentage < 2.5f / 3.f) {

                    float thisPercentage = (percentage * 3) / 2.5;
                  
                }
                else if (percentage < 2.9 / 3.f) {
                    float thisPercentage = (percentage * 3) / 2.9;

                    
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

                model.at("Head")->angle = -20 * sin(thisPercentage * PI / 2);

                model.at("Body")->offset.y = -20 * thisPercentage;
                model.at("Body")->angle = 45 * sin(thisPercentage * PI / 2);
            }
            else if (percentage < 2.f / 3.f) {

                model.at("Body")->angle = -75;



                model.at("Head")->angle = 45;
                model.at("Head")->offset.x = -15;

                louKick->hitbox.center = model.at("Head")->drawPos;
                louKick->hitbox.radius = model.at("Head")->sprite.getGlobalBounds().width / 2;
                louKick->isAtacking = true;



            }
            else if (percentage < 2.9f / 3.f) {

                model.at("Head")->angle *= 0.9;
                model.at("Head")->offset.x *= 0.9;

                model.at("Body")->angle *= 0.9;
                louKick->isAtacking = false;

            }
            else {


                model.at("Head")->angle = 0;
                model.at("Head")->offset.x = 0;

                model.at("Body")->angle = 0;
                louKick->isAtacking = false;
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

               
                model.at("Head")->angle = -20 * sin(thisPercentage * PI / 2);

            }
            else if (percentage < 1.f / 3.f) {
                float thisPercentage = percentage * 3;

                model.at("Body")->angle = -60 * sin(thisPercentage * PI / 2);
               

            }
            else if (percentage < 2.f / 3.f) {

                model.at("Body")->angle = 60;
             

                hiKick->hitbox.center = model.at("Head")->drawPos;
                hiKick->hitbox.radius = model.at("Head")->sprite.getGlobalBounds().width / 2;
                hiKick->isAtacking = true;

            }
            else if (percentage < 2.9f / 3.f) {

                model.at("Body")->angle *= 0.9;
                model.at("Head")->angle *= 0.9;
                hiKick->isAtacking = false;
            }
            else {
                model.at("Body")->angle = 0;
                model.at("Head")->angle = 0;
            }
        }




        void updateAnimations() override {
            // Abaixo temos
            // CA OS TO TAL

            //if (estadoUpdate) {
               //model.resetToBase();
                ///animations[0].playingFrame = 0;
            //}




            //model.at("FrontArm")->angle = ArmSpinAngFase;
            //model.at("BackArm")->angle = Arm2SpinAngFase;

            if (stunFrames <= 0) {


                if (air) {
                    jumpAnim();
                }
                else {
                    cairAnim();
                    if (estado == RUNNING) {
                        runAnim();
                    }
                    else if (estado == DEFENDING && !atacking) {
                        model.at("Head")->offset.y = 60;
                    }


                }

            if (estado == STOPPED) {
                runReset();
            }





                // Attack Animation
                if (atacking == HIGH_KICK) {
                    highAtackAnim();
                }
                else if (atacking == LOW_KICK) {
                    louKickAnim();
                }
                else if (atacking == SPECIAL) {
                    especialAnim();
                }




            }

            //projectiles[0].update();


        }


    };


}

#endif // GALOBOTA_H_INCLUDED