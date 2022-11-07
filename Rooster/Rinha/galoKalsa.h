
#ifndef GALOKALSA_H_INCLUDED
#define GALOKALSA_H

#include "Galo.h"

namespace Rooster {

    class Kalsa : public Galo {

        Texture t;
        float legWalkAngFase = 0;
        float ArmSpinAngFase = 0;
        float Arm2SpinAngFase = 0;



    public:
        Kalsa(struct GaloStats _stats, int _state, bool isp1) : Galo(_stats, _state, isp1) {
            this->name = "Kalsa";

            bar = new LifeBar(maxHp, isp1, name.c_str());

    
            this->hiKick = new Ataques(
                3,15, HitBox{ Vector2f(0, 0), 0 },
                20, 10, -PI / 4, milliseconds(650), "sounds\\fist-punch-or-kick-7171.ogg"
            );
            this->louKick = new Ataques(
                4,10, HitBox{ Vector2f(0, 0), 0 },
                20, 10, PI / 4, milliseconds(500), "sounds\\rooster-crowing-80322.ogg"
            );

            this->ultimateShot = new Ataques(
                5 ,70, HitBox{ Vector2f(0, 0),0},
                5, 3, 0, milliseconds(750),
                "sounds\\scorpion-get_over_here.ogg", milliseconds(2000)
            );
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
            if (atacking == NOT_ATTACK)
                atacking = SUPER;
            superAtack->init.restart();
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
                }
            }
        }
        
    
            
         
        void louKickAnim() {
            Time t = louKick->init.getElapsedTime();

            if (t > louKick->timeLapse ) {
                atacking = STOPPED;
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

                model.at("Body")->angle = -75 ;
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
                }
                else if (estado == DEFENDING) {
                    animations[0].update();
                    if (animations[0].playingFrame > 15) {
                        animations[0].playingFrame = 15;
                    }
                    model.updateWithAnimation(animations[0]);

                }
                else if (estado == STOPPED) {
                    runReset();
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
                }
                else if (atacking == LOW_KICK) {
                    louKickAnim();
                }
                else if (atacking == SPECIAL) {
                    especialAnim();
                }
                else if (estado == DANCING) {
                    animations[1].update();
                    model.updateWithAnimation(animations[1]);
                }
                else if (estado == INVISIBLE) {
                    sumir();
                }

                if (estado != INVISIBLE) {
                    aparecer();
                }


            }
            
            projectiles[0].update();
        }
             
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

                if (time < 1500) {

                    static int blue = 255;
                    static int red = 255;
                    static int green = 255;

                    if (green > 0)
                        green -= 2;
                    else
                        green = 0;

                    if (red > 0)
                        red -= 2;
                    else
                        green = 0;

                    if(frames % 3 == 0)
                        blue--;
                    

                    fundo.setFillColor(Color(red, green, blue));





                }
                else if (time < 2500) {
                    float thisTime = time - 1500;

                 

                }
                else if (time < 3000) {

                   

                }
                else if (time < 6000) {

                    float thisTime = (time - 2500) / 6000;

                    static bool istime = true;
                    if (istime) {
                        gritoSound.play();
                        istime = false;
                    }
                    position.y = SCREEN_HEIGHT / 2;


                  

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
                        static bool lets = true;

                        if (lets)
                            fatalitysound.play();
                        lets = false;
                        window->draw(fatal);
                        if (time > 8000) {
                            if (time < 12000) {
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

#endif // GALOKALSA_H_INCLUDED