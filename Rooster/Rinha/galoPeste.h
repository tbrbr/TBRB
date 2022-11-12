

#ifndef GALOBRUXO_H_INCLUDED
#define GALOBRUXO_H

#include "Galo.h"

namespace Rooster {

    class Peste : public Galo {

        Texture textura;
        
      
        float legWalkAngFase = 0;
        float ArmSpinAngFase = 0;
        float Arm2SpinAngFase = 0;



    public:
        Peste(struct GaloStats _stats, int _state, bool isp1) : Galo(_stats, _state, isp1) {

            // Stats
            this->name = "Peste";



            // Creating Attacks
            this->hiKick = new Ataques(
                6, 1, HitBox{ Vector2f(0, 0), 0 },
                20, 10, -PI / 4, milliseconds(650), ""
            );

            this->louKick = new Ataques(
                7, 1, HitBox{ Vector2f(0, 0), 0 },
                20, 10, PI / 4, milliseconds(750), "sounds\\cartoon-mouse-96437.ogg"
            );

            this->ultimateShot = new Ataques(
                8, 0.9, HitBox{ Vector2f(0, 0), 0 },
                10, 3, 0, milliseconds(1000),
                "sounds\\Lightsaber.ogg"
            );
            this->superAtack = new Ataques(14, 10, HitBox{ Vector2f(0, 0), 0 }, 20, 10, 0, milliseconds(3000), "sounds\\mg34.ogg");

            Projectile* rato = new Projectile(
                Vector2f(0, 0),
                "sprites\\rato.png",
                0, 0, Vector2f(1, 1),
                IntRect(0, 0, 865, 606)
            );


            atacking = NOT_ATTACK;
            projectiles.push_back(*rato);

            Projectile* n2 = new Projectile(
                Vector2f(0, 0),
                "sprites/pestepower.png",
                0, 0, Vector2f(1, 1)            
            );

            n2->setOriginCenter();
            projectiles.push_back(*n2);

            Projectile* corvinho = new Projectile(
                Vector2f(0, 0),
                "sprites\\corvo.png",
                0, 0, Vector2f(1, 1),
                IntRect(0, 0, 500, 829)
            );
            projectiles.push_back(*corvinho);


            textura.loadFromFile("sprites/galoPeste.png");

            model.tex = &textura;
            model.loadModel("models/pesteModel.txt");
            model.autoSetBounds(model.at("Body"), model.at("BackLeg"), model.at("Head"));


            HitBox* hit = new HitBox;
            for (int i = 0; i < model.allBones.size(); i++) {

                hit->center = model.at(i)->drawPos;
                hit->radius = model.at(i)->sprite.getGlobalBounds().width / 2;

                hurtBox.push_back(*hit);
            }

            delete hit;

            struct Animation agacharAnim;
            agacharAnim.init("animations/pesteAgacha.txt");
            agacharAnim.playingSpeed = 0.5;
            agacharAnim.connectLoop = false;
            animations.push_back(agacharAnim);

            struct Animation danceAnim;
            danceAnim.init("animations/pesteDance.txt");
            danceAnim.playingSpeed = 0.1;
            danceAnim.connectLoop = true;
            animations.push_back(danceAnim);




            bar = new LifeBar(maxHp, isp1, name.c_str());

        }


        void weatherAnim(int frames) {
            model.at(CORPO)->angle += 0;
            model.at(RABO)->angle = sin(frames / 200.f) * 20;
        }
        void jumpAnim() {


            ArmSpinAngFase = -(vspeed / 8) * 45;
            Arm2SpinAngFase = -(vspeed / 8) * 45;

           
            model.at("FrontLeg")->angle = vspeed;
            model.at("BackLeg")->angle = vspeed;

            model.at("FrontLeg")->offset.y = (float)vspeed/2;
            model.at("BackLeg")->offset.y =(float) vspeed/2;
          
        }
        void cairAnim() {

            model.at("FrontLeg")->angle *= 0.9;
            model.at("BackLeg")->angle *= 0.9;

            model.at("FrontLeg")->offset.y *= 0.9;
            model.at("BackLeg")->offset.y *= 0.9;
            
        }
        void runAnim() {
            legWalkAngFase += hspeed;
            legWalkAngFase -= ((int)legWalkAngFase / 360) * 360;

            ArmSpinAngFase += hspeed;
            Arm2SpinAngFase -= ((int)ArmSpinAngFase / 360) * 360;

            model.at("FrontLeg")->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
            model.at("BackLeg")->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;
         

            model.at("FrontArm")->angle = sin(2 * PI * ArmSpinAngFase / 360) * 60;
            model.at("BackArm")->angle = -sin(2 * PI * ArmSpinAngFase / 360) * 60;

            
        }
        void runReset() {


            model.at("FrontLeg")->angle *= 0.8;
            model.at("BackLeg")->angle *= 0.8;

            model.at("FrontArm")->angle = 0;
            model.at("BackArm")->angle = 0;

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
            }

        }

        void super() override {
            if (atacking == NOT_ATTACK){
                bar->resetPower();
                atacking = SUPER;
                superAtack->init.restart();
            }
        }

        void superAnim() {
            Time t = superAtack->init.getElapsedTime();
            int time = t.asMilliseconds();

            if (t > superAtack->timeLapse) {
                superAtack->isAtacking = false;
                superAtack->getHitted = false;
                atacking = NOT_ATTACK;
            }


            int sizeCorvo[3] = { 500,748,643 };


            float percentage = (float)t.asMilliseconds() / (superAtack->timeLapse.asMilliseconds());


            if (percentage < 1.f / 3.f) {

                float thisPercentage = percentage * 3;
                model.at("FrontArm")->angle = -30;
                model.at("BackArm")->angle = 60 * thisPercentage;
                model.at("Body")->angle = 7;
                
            }
            else if (percentage < 1.25f / 3.f) {
                float thisPercentage = (percentage * 3) / 2;
                projectiles[2].setVisibility(true);

                if (facingRight) {
                    projectiles[2].setImpulse(30, 0);
                    projectiles[2].setScale(Vector2f(-0.5, 0.5));
                    projectiles[2].facingRight = true;
                }
                else {
                    projectiles[2].setImpulse(-30, 10);
                    projectiles[2].setScale(Vector2f(0.5, 0.5));
                    projectiles[2].facingRight = false;
                }

                projectiles[2].setPosition(model.at("BackArm")->drawPos.x, model.at("BackArm")->drawPos.y - projectiles[2].getSize().y/2);

              
                int sprSelected = frames % 3;
                int sprx = 0;

                if (sprSelected == 0) {
                    sprx = 0;
                }
                else if (sprSelected == 1) {
                    sprx = 500;
                }
                else if (sprSelected == 2) {
                    sprx = 500 + 748;
                }

                projectiles[2].setTextureRec(IntRect(sprx, 0, sizeCorvo[sprSelected], 829));
                projectiles[2].update();

                superAtack->isAtacking = true;
                projectiles[2].facingRight ?
                    superAtack->hitbox.center.x = projectiles[2].getPosition().x - projectiles[2].getSize().x / 2 :
                    superAtack->hitbox.center.x = projectiles[2].getPosition().x + projectiles[2].getSize().x / 2;
                superAtack->hitbox.center.y = projectiles[2].getPosition().y + projectiles[2].getSize().y / 2;
                superAtack->hitbox.radius = projectiles[2].getSize().y / 2;
            }
            else if (percentage < 2.9f / 3.f) {

                model.at("FrontArm")->angle *= 0.999;
                model.at("BackArm")->angle *= 0.999;
                model.at("Body")->angle *= 0.999;
                int sprSelected = frames % 3;
                int sprx = 0;

                if (sprSelected == 0) {
                    sprx = 0;
                }
                else if (sprSelected == 1) {
                    sprx = 500;
                }
                else if (sprSelected == 2) {
                    sprx = 500 + 748;
                }

                projectiles[2].setTextureRec(IntRect(sprx, 0, sizeCorvo[sprSelected], 829));
                projectiles[2].update();

                superAtack->isAtacking = true;
                projectiles[2].facingRight ?
                    superAtack->hitbox.center.x = projectiles[2].getPosition().x - projectiles[2].getSize().x / 2 :
                    superAtack->hitbox.center.x = projectiles[2].getPosition().x + projectiles[2].getSize().x / 2;
                superAtack->hitbox.center.y = projectiles[2].getPosition().y + projectiles[2].getSize().y / 2;
                superAtack->hitbox.radius = projectiles[2].getSize().y / 2;
            }
            else {
                model.at("FrontArm")->angle *= 0;
                model.at("BackArm")->angle *= 0;
                model.at("Body")->angle *= 0;

                
                superAtack->isAtacking = false;
            }





        }
        void especialAnim() {
            Time t = ultimateShot->init.getElapsedTime();
            int time = t.asMilliseconds();

            if (t > ultimateShot->timeLapse) {
                atacking = NOT_ATTACK;
            }

            float percentage = (float)t.asMilliseconds() / (ultimateShot->timeLapse.asMilliseconds());
            

            if (percentage < 1.f / 3.f) {

                float thisPercentage = percentage * 3;
                
                model.at("Body")->angle = 45 * sin(thisPercentage * PI / 2);
                model.at("FrontArm")->angle = -30 * sin(thisPercentage * PI / 2);
                model.at("BackLeg")->angle = -90 * sin(thisPercentage * PI / 2);
                model.at("Head")->angle = -20 * sin(thisPercentage * PI / 2);;
                model.at("FrontLeg")->offset.x = -5 * sin(thisPercentage * PI / 2);
                model.at("BackLeg")->offset.y = 5 * sin(thisPercentage * PI / 2);
                model.at("FrontArm")->angle = 45 * sin(thisPercentage * PI / 2);
                model.at("BackArm")->angle = 90 * sin(thisPercentage * PI / 2);
                
            }
            else if (percentage < 2.f / 3.f) {
                float thisPercentage = (percentage * 3)/2;

                model.at("Body")->angle = 45;
                model.at("FrontArm")->angle = -30;
                model.at("BackLeg")->angle = -90;
                model.at("FrontLeg")->angle = 0;
                model.at("Head")->angle = -20;
                model.at("FrontLeg")->offset.x = -5;
                model.at("BackLeg")->offset.y = 5;
                model.at("FrontArm")->angle = 45;
                model.at("BackArm")->angle = 90;

               

            }
            else if (percentage < 2.05f / 3.f) {
                ultimateShot->playSound();
            }
            else if (percentage < 2.2f / 3.f) {



                projectiles[1].setVisibility(true);
                projectiles[1].setScale(Vector2f(1, 1));

                projectiles[1].setPosition(
                    Vector2f(model.at("BackArm")->drawPos.x,
                        (model.at("BackArm")->drawPos.y - model.at("BackArm")->sprite.getGlobalBounds().height 
                         + projectiles[1].getSize().y / 2)
                    )
                );

                if (facingRight) {
                    projectiles[1].setImpulse(25, 10);
                    projectiles[1].setScale(Vector2f(0.1, 0.1));
                }

                else {
                    projectiles[1].setImpulse(-25, 10);
                    projectiles[1].setScale(Vector2f(-0.1, 0.1));
                }


                ultimateShot->isAtacking = true;
            }
            else if (percentage < 2.5f / 3.f) {

                model.at("Body")->angle -= 5;
                model.at("BackArm")->angle -= 5;
                model.at("FrontArm")->angle -= 5;
                model.at("Head")->angle -= 5;
               
                if (facingRight)
                    position.x += 2;
                else
                    position.x -= 2;
            }
            else if (percentage < 2.9 / 3.f) {
                model.at("Body")->angle *= 0.9;
                model.at("FrontArm")->angle *= 0.9;
                model.at("BackArm")->angle *= 0.9;
               
                model.at("Head")->angle *= 0.9;
            }
            else {
                model.at("Body")->angle = 0;
                model.at("FrontArm")->angle = 0;
                model.at("BackArm")->angle = 0;
                model.at("Head")->angle = 0;
            }
        }


        void louKickAnim() {
            Time t = louKick->init.getElapsedTime();
            int time = t.asMilliseconds();
            if (t > louKick->timeLapse) {
                atacking = STOPPED;
            }

            float percentage = (float)t.asMilliseconds() / (louKick->timeLapse.asMilliseconds());



            if (percentage < 1.75f / 3.f) {

                float thisPercentage = (percentage * 3) / 1.75;



                projectiles[1].setImpulse(0, 0);

                projectiles[1].setScale(
                    0.5 * thisPercentage,
                    0.25 * thisPercentage
                );


                projectiles[1].setPosition(
                    position.x,
                    floorY
                );

                projectiles[1].setVisibility(true);
            }
            else if (percentage < 2.5f / 3.f) {
                float thisPercentage = (percentage * 3) / 2.5;

                projectiles[1].setScale(
                    0.5 - 0.5 * thisPercentage,
                    0.25 - 0.25 * thisPercentage
                );
            }
            else
                projectiles[1].setVisibility(false);


            if (percentage < 1.f / 3.f) {

                float thisPercentage = percentage * 3;


                model.at("Body")->angle = 0;
                model.at("BackArm")->angle = -70 + sin(2 * PI * time / 360) * 20;
                model.at("FrontArm")->angle = 0;
                model.at("Head")->angle = -10;
                model.at("BackLeg")->offset.y = -10;
                model.at("FrontLeg")->offset.y = -10;
                model.at("BackLeg")->angle = -10;
                model.at("FrontLeg")->angle = -10;

                position.y += 10;

            }
            else if (percentage < 2.f / 3.f) {
                float thisPercentage = percentage * 3;

                model.at("Body")->angle = 0;
                model.at("BackArm")->angle = -70 + sin(2 * PI * time / 360) * 20;
                model.at("FrontArm")->angle = 0;
                model.at("Head")->angle = -10;
                model.at("BackLeg")->offset.y = -10;
                model.at("FrontLeg")->offset.y = -10;
                model.at("BackLeg")->angle = -10;
                model.at("FrontLeg")->angle = -10;
                
            }
            else if (percentage < 2.2f / 3.f) {

                projectiles[0].setVisibility(true);
                projectiles[0].setScale(Vector2f(1, 1));

                projectiles[0].setPosition(Vector2f(model.at("BackArm")->drawPos.x,floorY - projectiles[0].getSize().y));

                if (facingRight) {
                    projectiles[0].setImpulse(3, 0);
                    projectiles[0].setScale(Vector2f(-0.2, 0.2));
                    projectiles[0].facingRight = true;
                }
                else {
                    projectiles[0].setImpulse(-3, 0);
                    projectiles[0].setScale(Vector2f(0.2, 0.2));
                    projectiles[0].facingRight = false;
                }

                louKick->isAtacking = true;
            }
            else if (percentage < 2.5f / 3.f) {


            }
            else if (percentage < 2.9 / 3.f) {

                model.at("Body")->angle *= 0.9;
                model.at("FrontArm")->angle *= 0.9;
                model.at("BackLeg")->angle *= 0.9;
                model.at("FrontLeg")->angle *= 0.9;
                model.at("Head")->angle *= 0.9;
                model.at("FrontLeg")->offset.x *= 0.9;
                model.at("BackLeg")->offset.y *= 0.9;
                model.at("FrontArm")->angle *= 0.9;
                model.at("BackArm")->angle *= 0.9;
            }
            else {
                model.at("Body")->angle = 0;
                model.at("FrontArm")->angle = 0;
                model.at("BackArm")->angle = 0;
                model.at("Head")->angle = 0;
                
            }

        }

        void highAtackAnim() {
            Time t = hiKick->init.getElapsedTime();

            if (t > hiKick->timeLapse) {
                atacking = STOPPED;
            }

            float percentage = (float)t.asMilliseconds() / (hiKick->timeLapse.asMilliseconds());

            if (percentage < 1 / 3.f) {

                float thisPercentage = percentage * 6;

                model.at("FrontArm")->angle = -90 * sin(thisPercentage * PI / 2);

                model.at("BackArm")->angle = 60 * sin(thisPercentage * PI / 2);

                model.at("Head")->angle = 20 * sin(thisPercentage * PI / 2);
             
                model.at("Body")->angle = 20 * sin(thisPercentage * PI / 2);

                model.at("BackLeg")->angle = 15 * sin(thisPercentage * PI / 2);
                model.at("FrontLeg")->angle = -20 * sin(thisPercentage * PI / 2);

          
            }
            else if (percentage < 2.f / 3.f) {
                float thisPercentage = (percentage/2 * 3);

                model.at("Body")->angle = 1 * sin(thisPercentage * PI / 2);;
                model.at("FrontArm")->angle = -10 * sin(thisPercentage * PI / 2);
                model.at("BackArm")->angle = -45 * sin(thisPercentage * PI / 2);
                model.at("Head")->angle = -10 * sin(thisPercentage * PI / 2);

                model.at("FrontLeg")->angle = -15 * sin(thisPercentage * PI / 2);
                model.at("BackLeg")->angle = 20 * sin(thisPercentage * PI / 2);
                if(facingRight)
                    hiKick->hitbox.center.x = model.at("BackArm")->drawPos.x + model.at("BackArm")->sprite.getGlobalBounds().width - 20;
                else 
                    hiKick->hitbox.center.x = model.at("BackArm")->drawPos.x - model.at("BackArm")->sprite.getGlobalBounds().width + 20;

                hiKick->hitbox.center.y = model.at("BackArm")->drawPos.y - model.at("BackArm")->sprite.getGlobalBounds().height/4;

                hiKick->hitbox.radius = 40;
                hiKick->isAtacking = true;
                
            }
            else if (percentage < 2.9f / 3.f) {

                model.at("Body")->angle *= 0.9;
                model.at("BackLeg")->angle *= 0.9;               
                model.at("FrontArm")->angle *= 0.9;
                model.at("BackArm")->angle *= 0.9;               
                model.at("Head")->angle *= 0.9;
                hiKick->isAtacking = false;
            }
            else {
                model.at("Body")->angle = 0;
                model.at("BackLeg")->angle = 0;
                model.at("FrontArm")->angle = 0;
                model.at("BackArm")->angle = 0;
                model.at("Head")->angle *= 0;
                hiKick->isAtacking = false;
            }
        }

        void updateAnimations() override {

            if (estadoUpdate) {
                model.resetToBase();
                animations[0].playingFrame = 0;
            }

            //weatherAnim(frames);

            if (!stunned) {
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
                    isDefending = false;
                }
                else if (estado == DEFENDING) {
                    estado = STOPPED;
                    animations[0].update();
                    if (animations[0].playingFrame > 15) {
                        animations[0].playingFrame = 15;
                        isDefending = true;
                        defense.center.x = model.at("Body")->drawPos.x;
                        defense.center.y = model.at("Body")->drawPos.y;
                        defense.radius = model.at("Body")->sprite.getGlobalBounds().height / 2;
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


                if (atacking == HIGH_KICK) {
                    highAtackAnim();
                }
                else if (atacking == LOW_KICK) {
                    louKickAnim();
                }
                else if (atacking == SPECIAL) {
                    especialAnim();
                }
                else if (atacking == SUPER) {
                    superAnim();
                }
                else if (estado == DANCING) {
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

            projectiles[0].update();
            projectiles[1].update();

            ultimateShot->hitbox.center = projectiles[1].getPosition();
            ultimateShot->hitbox.radius = projectiles[1].getSize().y / 2;
            
            if (projectiles[1].getPosition().x > SCREEN_WIDTH || projectiles[0].getPosition().x < 0) {
                          
                projectiles[1].setVisibility(false);
                ultimateShot->isAtacking = false;
            }


            if (projectiles[0].getVisibility()) {

                static bool playS = true;
                if (playS) {
                    louKick->playSound();
                    playS = false;
                }

                louKick->soundCollision.setLoop(true);
                
                if (projectiles[0].getPosition().x > SCREEN_WIDTH || projectiles[0].getPosition().x < 0) {
                    louKick->soundCollision.setLoop(false);
                    playS = true;
                    projectiles[0].setVisibility(false);
                    louKick->isAtacking = false;
                }

                int i = (frames % 30) / 10;

                projectiles[0].setTextureRec(IntRect(864 * i, 0, 864, 606));

                if (projectiles[0].facingRight) {
                    louKick->hitbox.center.x = projectiles[0].getPosition().x - projectiles[0].getSize().y / 2;
                }
                else {
                    louKick->hitbox.center.x = projectiles[0].getPosition().x + projectiles[0].getSize().y / 2;
                }
                
                louKick->hitbox.center.y = projectiles[0].getPosition().y;
                louKick->hitbox.radius = projectiles[0].getSize().y/2;
            }


            
        }

        void fatality(RenderWindow* window,Galo* galo2, RectangleShape fundo)override {
            
            Clock Timer;
            Timer.restart();
            galo2->position.x = SCREEN_WIDTH / 4;
            position.x = SCREEN_WIDTH / 4 + model.getBounds().width * abs(model.xScl);
            Texture Corvo;
            Corvo.loadFromFile("sprites/corvo.png");
            std::vector <corvo> corvos;

            effectsChuva chuva;

            Texture raio;
            raio.loadFromFile("sprites/lightning.png");
            Sprite lightning;
            lightning.setTexture(raio);
            lightning.setPosition(SCREEN_WIDTH/2,0);

            RectangleShape bright;
            bright.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
            bright.setFillColor(Color(255, 255, 255, 0));

           
            effectsInfestacaoDeRatos socorro;

            hiKick->setTimeLapse(milliseconds(750));

            Font mortal;
            mortal.loadFromFile("fonts/Mortal-Kombat-MK11.otf");
            Text fatal("FATALITY", mortal, SCREEN_WIDTH/10);
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
            opening.setFillColor(Color(255,255,0));
            opening.setOutlineColor(Color::Yellow);
            opening.setSize(Vector2f(0,SCREEN_HEIGHT/100));

            Text peste("Peste Wins", mortal, SCREEN_WIDTH / 50);

            peste.setPosition(
                SCREEN_WIDTH / 2 - peste.getGlobalBounds().width / 2,
                garra2.getPosition().y - peste.getGlobalBounds().height
            );
            peste.setFillColor(Color(250, 250, 250));
            peste.setOutlineThickness(SCREEN_WIDTH / 700);
            peste.setOutlineColor(Color(255, 255, 10));

            SoundBuffer bufferRaio;
            bufferRaio.loadFromFile("sounds/raio.ogg");
            Sound trovao;
            trovao.setBuffer(bufferRaio);
            Music somdechuva;
            somdechuva.openFromFile("sounds/chuva.ogg");
            somdechuva.setVolume(80);
            Music grito;
            grito.openFromFile("sounds/man-screaming-01.wav");
            grito.setLoop(false);
            

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

            Music fatalpeste;
            fatalpeste.openFromFile("sounds/fatalpeste.ogg");
            fatalpeste.setVolume(60);         
            fatalpeste.play();



            ExplosionEffect* exp = new ExplosionEffect(Vector2f(0, 0), 10);
            exp->sanguePreset();
            exp->depthSpdMin = -1;
            exp->depthSpdMax = 4;
            exp->depthMin = 100;
            exp->depthMax = 100;

            exp->mortal = false;


            int timeFrames = 0;
            galo2->update();


            while (window->isOpen()) {

                int time = Timer.getElapsedTime().asMilliseconds();

                
                window->clear();
                window->draw(fundo);

                Event e;
                while (window->pollEvent(e))
                {
                    if (e.type == Event::Closed)
                    {
                        window->close();
                    }

                }
                if (time < 3500) {
                    static int color = 255;                    
                    color--;
                    fundo.setFillColor(Color(color,color,color));

                }
                else if (time > 3500) {
                    if (time < 4500) {
                        corvo *a= new corvo(
                            rand() % 10,rand() % 10 - 5,
                            Vector2f(0,randFloatRangeNormal(0, SCREEN_HEIGHT, SCREEN_HEIGHT)),
                            Vector2f(0.2,0.2),Corvo
                        );
                        corvos.push_back(*a);
                        for (int i = 0; i < corvos.size(); i++) {
                            corvos[i].update();
                            corvos[i].draw(window);
                        }                     
                    }
                    else if (time < 5500) {   
                        trovao.play();
                        bright.setFillColor(Color(255, 255, 255,255));

                    }else if (time < 5750) {
                        bright.setFillColor(Color(255, 255, 255, 0));
                        window->draw(lightning);
                        for (int i = 0; i < corvos.size(); i++) {
                            corvos[i].update();
                            corvos[i].draw(window);
                        }
                    }
                    else if (time < 6000) {
                        trovao.play();
                        bright.setFillColor(Color(255, 255, 255, 255));
                        
                        
                        galo2->run(true);
                    }
                    else if (time < 6500) {
                        galo2->setState(STOPPED);
                        bright.setFillColor(Color(255, 255, 255, 0));

                        lightning.setPosition(SCREEN_WIDTH/4, 0);
                        for (int i = 0; i < corvos.size(); i++) {
                            corvos[i].update();
                            corvos[i].draw(window);
                        }
                        window->draw(lightning);
                    }
                    else if (time < 6750) {
                        bright.setFillColor(Color(255, 255, 255, 255));
                        somdechuva.play();
                        grito.play();
                    }
                    else {
                        bright.setFillColor(Color(255, 255, 255, 0));
                        chuva.update();
                        chuva.draw(window);
                        for (int i = 0; i < corvos.size(); i++) {
                            corvos[i].update();
                            corvos[i].draw(window);
                        }
                        socorro.update();
                        socorro.draw(window);
                        highKick();


                        // Falido
                        if (timeFrames  % 20 == 0) {

                            Model model = galo2->getModel();

                            exp->position = model.at("Body")->drawPos;

                            exp->createMultipleParticles(500);
                        }
                        timeFrames++;


                        
                        if (time > 8000) {
                            static bool lets = true;
                            if(lets)
                                fatalitysound.play();
                            lets = false;
                            window->draw(fatal);
                            if (time > 10000) {
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
                                    SCREEN_WIDTH/2 - opening.getSize().x/2,
                                    garra2.getPosition().y + garra2.getGlobalBounds().height/1.5);                                
                                
                                window->draw(opening);
                                window->draw(garra1);
                                window->draw(garra2);
                                window->draw(peste);
                            }
                        }
                    }                                    
                }
                
                if (position.x - (model.getBounds().width * abs(model.xScl))/1.5 < galo2->position.x ) {
                    estado = RUNNING;
                    run(true);
                }
                else {
                    estado = STOPPED;
                }
                

                
             
                update();
                galo2->update();
                galo2->show(*window);

                show(*window);
                window->draw(bright);

                exp->update();
                exp->draw(*window); 

                window->display();

                if (time > 15000) {
                    return;
                }
               

            }
        }
        
    };


}

#endif // GALOBRUXO_H_INCLUDED