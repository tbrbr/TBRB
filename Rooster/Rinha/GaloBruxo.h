

#ifndef GALOBRUXO_H_INCLUDED
#define GALOBRUXO_H

#include "Galo.h"

namespace Rooster {

    class Bruxo : public Galo {

        Texture t;
        float legWalkAngFase = 0;
        Clock clockFatal;


    public:
        Bruxo(struct GaloStats _stats, int _state, bool isp1) : Galo(_stats, _state, isp1) {
            // Stats
            this->name = "Bruxo";
            
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
                10, 3, 0, milliseconds(2000),
                "sounds\\awp.ogg"
            );

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

            atacking = NOT_ATTACK;



            t.loadFromFile("sprites/galoBruxo.png");

            model.tex = &t;
            model.loadModel("models/bruxoModel.txt");
         

            

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

            model.at("Hat")->offset.y += vspeed/8;

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

            if (t > ultimateShot->timeLapse) {
                atacking = NOT_ATTACK;
            }

            float percentage = (float)t.asMilliseconds() / (ultimateShot->timeLapse.asMilliseconds());

            int angFix = (facingRight) ? 1 : -1;
            angFix = -1;

            static int angle = 0;
            angle++;

            if (percentage < 0.5f / 3.f) {

                float thisPercentage = percentage * 6;
            
                model.at("FrontArm")->angle = percentage * -90;
                model.at("BackArm")->angle = percentage * 90;
                model.at("Head")->angle = percentage * 30;
                model.at("Body")->angle = percentage * 30;
                model.at("FrontBigode")->angle = percentage * - 30;
                model.at("BackBigode")->angle = percentage * -30;
                projectiles[0].isTrans = false;

                projectiles[0].setImpulse(0, 0);
                projectiles[0].setSpriteAngle(angle);

                projectiles[0].setScale((float)SCREEN_WIDTH/7680 * percentage,(float) SCREEN_WIDTH / 7680 * percentage);

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
                float thisPercentage = (percentage * 3)/1.5;

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
                ultimateShot->playSound();
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
            }
            else if (percentage < 2.5f / 3.f) {

                static bool go = true;
                if (go) {
                    ultimateShot->playSound();
                }
                model.at("FrontArm")->angle = percentage * 90;

                model.at("Head")->angle = percentage * 30;
                model.at("Body")->angle = percentage * 30;
                model.at("FrontBigode")->angle = percentage * -30;
                model.at("BackBigode")->angle = percentage * -30;

                projectiles[1].setVisibility(true);

                if (facingRight) {
                    projectiles[1].setImpulse(20, 0);
                    projectiles[1].setScale((float)SCREEN_WIDTH / 15360 * percentage, (float)SCREEN_WIDTH / 15360 * percentage);
                }

                else {
                    projectiles[1].setImpulse(-20, 0);
                    projectiles[1].setScale((float)SCREEN_WIDTH / 15360 * percentage, (float)SCREEN_WIDTH / 15360 * percentage);
                }

                projectiles[1].update();

                ultimateShot->isAtacking = true;

            }
            else if (percentage < 2.9 / 3.f) {

                model.at("FrontArm")->angle *= 0.9;
                model.at("BackArm")->angle *= 0.9;

                model.at("Head")->angle *= 0.9;
                model.at("Body")->angle *= 0.9;
                model.at("FrontBigode")->angle *= 0.9;
                model.at("BackBigode")->angle *= 0.9;

            }
            else {
                projectiles[0].setVisibility(false);
                projectiles[1].setVisibility(false);

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


            if (percentage < 1.f / 3.f) {

                float thisPercentage = percentage * 3;
                model.at("FrontArm")->angle = 45 * sin(thisPercentage * PI / 2);
                model.at("BackArm")->angle = -20 * sin(thisPercentage * PI / 2);
                model.at("BackLeg")->angle = 20 * sin(thisPercentage * PI / 2);
                
                
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
            if (estadoUpdate) {
                model.resetToBase();
                animations[0].playingFrame = 0;               
            }
          

            



            if (estado == RUNNING) {
                runAnim();
            }
            else if (estado == DEFENDING) {
                

                static int angle = 0;
                angle++;
                
                projectiles[0].isTrans = true;

                Transform trans;
                trans.scale((float)SCREEN_WIDTH/3840,(float)SCREEN_HEIGHT/1440);

                if (facingRight) {
                                                     
                    projectiles[0].setImpulse(0, 0);
                    projectiles[0].setSpriteAngle(angle);
                    
                    projectiles[0].setTransfrom(trans);

                    projectiles[0].setPosition(
                        position.x * 2 + (projectiles[0].getLocalSize().x * 1.25),
                        position.y/2 + (projectiles[0].getLocalSize().y)
                    );
                   // trans.scale(-0.75, 1);
                    
                                        
                }
                else {
                    
                    projectiles[0].setSpriteAngle(-angle);

                    projectiles[0].setTransfrom(trans);

                    
                    projectiles[0].setPosition(
                        position.x * 2 - (projectiles[0].getLocalSize().x * 1.25),
                        position.y / 2 + (projectiles[0].getLocalSize().y)
                                             
                    );
                    
                    projectiles[0].setImpulse(0,0);
                   // trans.scale(-0.75, 1);
                    
                    
                }

                projectiles[0].setVisibility(true);
               // projectiles[0].update();

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

            if (atacking == HIGH_KICK) {
                // highAtackAnim();
            }
            else if (atacking == LOW_KICK) {
                // louKickAnim();
            }
            else if (atacking == SPECIAL) {
                 especialAnim();
            }

           // projectiles[0].update();

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

            Text bruxowins("Bruxo Wins", mortal, SCREEN_WIDTH / 50);

            bruxowins.setPosition(
                SCREEN_WIDTH / 2 - bruxowins.getGlobalBounds().width / 2,
                garra2.getPosition().y - bruxowins.getGlobalBounds().height
            );
            bruxowins.setFillColor(Color(250, 250, 250));
            bruxowins.setOutlineThickness(SCREEN_WIDTH / 700);
            bruxowins.setOutlineColor(Color(255, 255, 10));

           
            Music grito;
            grito.openFromFile("sounds/man-screaming-01.wav");
            grito.setLoop(false);


            model.resetToBase();

            // Testando adicionar partes extras
            
            
            model.addElement(*model.at("FrontArm"), "FrontArm2",0);
            model.at("FrontArm2")->setBaseAlpha(0);


            model.addElement(*model.at("FrontArm"), "FrontArm3",model.allBones.size() - 1);
            model.at("FrontArm3")->setBaseAngle(0);
            model.at("FrontArm3")->setBaseAlpha(0);


            model.addElement(*model.at("FrontArm"), "FrontArm4",0);
            model.at("FrontArm4")->setBaseAngle(0);
            model.at("FrontArm4")->setBaseAlpha(0);

            model.addElement(*model.at("FrontArm"), "FrontArm5", 0);
            model.at("FrontArm5")->setBaseAngle(0);
            model.at("FrontArm5")->setBaseAlpha(0);

            model.addElement(*model.at("BackArm"), "FrontArm6", model.allBones.size() - 1);
            model.at("FrontArm6")->sprite = model.at("BackArm")->sprite;
           
            model.at("FrontArm6")->setBaseAngle(0);
            model.at("FrontArm6")->setBaseAlpha(0);
            model.at("FrontArm6")->setBaseAttach(model.at("FrontArm")->getBaseAttach());
            
            
            

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
                    static int blue = 255;
                    static int red = 255;
                    static int green = 255;
                    if (green > 0)
                        green -= 2;
                    else
                        green = 0;
                    blue--;
                    red--;
                    fundo.setFillColor(Color(red, green, blue));

                    
                    model.at("Head")->angle = sin(time);
                    model.at("Corpo")->angle = sin(time);
                    
                }
                

              


                update();
                galo2->update();
                galo2->show(*window);

                show(*window);               
                window->display();
            }
        }
        
    };


}

#endif // GALOBRUXO_H_INCLUDED