

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
            this->hiKick = new Ataques(6,
                8, 0.5, HitBox{ Vector2f(0, 0), 0 },
                20, 10, -PI / 4, milliseconds(1200), ""
            );

            this->louKick = new Ataques(7,
                5, 0.5, HitBox{ Vector2f(0, 0), 0 },
                20, 10, PI / 4, milliseconds(1000), ""
            );

            this->ultimateShot = new Ataques(8,
                0.9, 0.5, HitBox{ Vector2f(0, 0), 0 },
                10, 3, 0, milliseconds(1500),
                "sounds\\awp.ogg"
            );

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





            textura.loadFromFile("sprites/galoPeste.png");

            model.tex = &textura;
            model.loadModel("pesteModel.txt");
            model.autoSetBounds(model.at("Body"), model.at("BackLeg"), model.at("Head"));

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
                    Vector2f(model.at("BackArm")->drawPos.x,//- SCREEN_WIDTH/300 * model.xScl,
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
            else if (percentage < 2.05f / 3.f) {
                //ultimateShot->playSound();
            }
            else if (percentage < 2.2f / 3.f) {



                projectiles[0].setVisibility(true);
                projectiles[0].setScale(Vector2f(1, 1));

                projectiles[0].setPosition(
                    Vector2f(model.at("BackArm")->drawPos.x,
                        (floorY - projectiles[0].getSize().y)
                    )
                );



                if (facingRight) {
                    projectiles[0].setImpulse(3, 0);
                    projectiles[0].setScale(Vector2f(-0.2, 0.2));
                }

                else {
                    projectiles[0].setImpulse(-3, 0);
                    projectiles[0].setScale(Vector2f(0.2, 0.2));
                }


                ultimateShot->isAtacking = true;
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
            }
        }

        void updateAnimations() override {
            if (estadoUpdate) {
                model.resetToBase();
                animations[0].playingFrame = 0;
            }

            //weatherAnim(frames);


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
            }
            else if (estado == DEFENDING) {
                estado == STOPPED;
                /*
               animations[0].update();
               if (animations[0].playingFrame > 15) {
                    animations[0].playingFrame = 15;
               }
               // model.updateWithAnimation(animations[0]);
               */
            }
            else if (estado == STOPPED) {
                runReset();
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

            projectiles[0].update();
            projectiles[1].update();
            if (projectiles[0].getVisibility()) {

                int i = (frames % 30) / 10;

                projectiles[0].setTextureRec(IntRect(864 * i, 0, 864, 606));
              
                ultimateShot->hitbox.center.x = projectiles[0].getPosition().x - projectiles[0].getSize().y / 2;
                ultimateShot->hitbox.center.y = projectiles[0].getPosition().y;
                ultimateShot->hitbox.radius = projectiles[0].getSize().y/2;
            }
            
        }

        void fatality(RenderWindow* window,Galo* galo2, RectangleShape fundo)override {

            Clock Timer;
            Timer.restart();
            galo2->position.x = SCREEN_WIDTH / 2;
                        
            std::vector <corvo> corvos;

            effectsChuva chuva;

            Texture raio;
            raio.loadFromFile("sprites/lightning.png");
            Sprite lightning;
            lightning.setTexture(raio);
            lightning.setPosition(SCREEN_WIDTH/2,0);

            RectangleShape bright;

            bright.setFillColor(Color(255, 255, 255, 0));

            std::vector <Projectile> infestacao;

            for (int i = 0; i < 100; i++) {
             
            }

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
                        corvo *a= new corvo(rand() % 10,rand() % 10 - 5,Vector2f(0,randFloatRangeNormal(0, SCREEN_HEIGHT, SCREEN_HEIGHT)), Vector2f(0.2,0.2));
                        corvos.push_back(*a);
                        for (int i = 0; i < corvos.size(); i++) {
                            corvos[i].update();
                            corvos[i].draw(window);
                        }                     
                    }
                    else if (time < 5500) {                       
                        bright.setFillColor(Color(255, 255, 255, 255 - ((time - 5500) / 250) * 255));
                    }else if (time < 5750) {
                        window->draw(lightning);
                        for (int i = 0; i < corvos.size(); i++) {
                            corvos[i].update();
                            corvos[i].draw(window);
                        }
                    }
                    else if (time < 6000) {
                        bright.setFillColor(Color(255, 255, 255, 255 - ((time - 5500) / 250) * 255));
                    }
                    else if (time < 6250) {
                        bright.setFillColor(Color(255, 255, 255, 255 - ((time - 5500) / 250) * 255));
                    }
                    else if (time < 6500) {
                        lightning.setPosition(SCREEN_WIDTH/4, 0);
                        for (int i = 0; i < corvos.size(); i++) {
                            corvos[i].update();
                            corvos[i].draw(window);
                        }
                        window->draw(lightning);
                    }
                    else if (time < 6750) {
                        bright.setFillColor(Color(255, 255, 255, 255 - ((time - 5500) / 250) * 255));
                    }
                    else{
                        chuva.update();
                        chuva.draw(window);
                        for (int i = 0; i < corvos.size(); i++) {
                            corvos[i].update();
                            corvos[i].draw(window);
                        }
                        /*
                        float p = rand() % 2;
                        Projectile* rato = new Projectile(
                            Vector2f(p * SCREEN_WIDTH, floorY),
                            "sprites\\rato.png",
                            (rand() % 10 - p * 20), 0, Vector2f(0.2 - p * 0.4, 0.2),
                            IntRect(0, 0, 865, 606)
                        );
                        infestacao.push_back(*rato);
                        
                        for (int i = 0; i < infestacao.size(); i++) {
                            infestacao[i].setVisibility(true);
                            infestacao[i].update();
                            infestacao[i].draw(*window);
                        }*/

                    }
                                      
                }
                
                if (position.x - model.getBounds().width * abs(model.xScl) < galo2->position.x ) {
                    estado = RUNNING;
                    run();
                }
                else {
                    estado = STOPPED;
                }
                
             
                update();
                galo2->update();
                galo2->show(*window);

                show(*window);
                window->draw(bright);
                window->display();
            }
        }
        
    };


}

#endif // GALOBRUXO_H_INCLUDED