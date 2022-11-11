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

        Texture puffTex;

    public:
        Bota(struct GaloStats _stats, int _state, bool isp1) : Galo(_stats, _state, isp1) {
            this->name = "Bota";

            bar = new LifeBar(maxHp, isp1, name.c_str());




            

            atacking = NOT_ATTACK;





            // Criando modelo
            t.loadFromFile("sprites/galoBota.png");

            model.tex = &t;
            model.loadModel("models/botaModel.txt");
            model.autoSetBounds(model.at("Body"),  model.at("Body"), model.at("Head"));
            println("Bota Carregou");



         


            // Hurtboxes
            HitBox* hit = new HitBox;

            // Too much hit box 


            for (int i = 0; i < model.allBones.size(); i++) {

                hit->center = model.at(i)->drawPos;
                hit->radius = model.at(i)->sprite.getGlobalBounds().width / 2;

                hurtBox.push_back(*hit);
            }
            delete hit;


            //Ataques                 (id,Stun,hitbox,                 Damage,KnockBack,angle,Time,const char* txt)
            this->hiKick = new Ataques(11, 8, HitBox{ Vector2f(0, 0), 0 }, 40, 10, -PI / 3, milliseconds(650), "");
            hiKick->hitbox.radius = 20 * abs(model.xScl);

            this->louKick = new Ataques( 12, 5, HitBox{ Vector2f(0, 0), 0 }, 20, 10, -PI / 3, milliseconds(500), "");
            louKick->hitbox.radius = 25 * abs(model.xScl);

            this->ultimateShot = new Ataques( 13, 10, HitBox{ Vector2f(0, 0), 0 },10, 10, PI / 2, milliseconds(500),"");
            ultimateShot->hitbox.radius = 5 * abs(model.xScl);

            this->superAtack = new Ataques(14, 20, HitBox{ Vector2f(0, 0), 0 }, 20, 10, 0, milliseconds(800), "sounds\\mg34.ogg");
            superAtack->hitbox.radius = 5 * abs(model.xScl);


            // Puff
            puffTex.loadFromFile("sprites/botaProjectile.png");

            SpriteMap puffSprMap;
            puffSprMap.addImages(16, 16, 0, 0, 2, 1, (Vector2i)puffTex.getSize());

            Projectile* puff = new Projectile(
                Vector2f(0, 0),
                "sprites/botaProjectile.png",
                0, 0, Vector2f(5, 5), puffSprMap
            );

            puff->setOriginCenter(Vector2f(puff->getSprite().getLocalBounds().width/2, (puff->getSprite().getLocalBounds().height)));
            puff->setSpriteImageSpeed(0.05);
            puff->setScale(model.xScl*4, model.xScl*4);
            puff->setMortality(true);
            puff->setLife(200);
            puff->setScaleSpeed(0.005, 0.005);
            puff->active = false;
           

            projectiles.push_back(*puff);






            struct Animation agacharAnim;
            agacharAnim.init("animations/SecondAnim.txt");
            agacharAnim.playingSpeed = 1;
            agacharAnim.connectLoop = false;
            animations.push_back(agacharAnim);

            struct Animation danceAnim;
            danceAnim.init("animations/botaDance.txt");
            danceAnim.playingSpeed = 0.1;
            danceAnim.connectLoop = true;
            animations.push_back(danceAnim);

        }







        void weatherAnim(int frames) {
            model.at("Body")->yScl = model.at("Body")->getBaseScale().y * ruleOfThree(sin((float)frames/20), -1, 1, 0.95, 1.05);   
            model.at("Body")->xScl = model.at("Body")->getBaseScale().x * ruleOfThree(sin((float)frames/20), -1, 1, 1.05, 0.95);
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
                vspeed = 0;
            }

        }
        void super() override {
            if (atacking == NOT_ATTACK) {
                atacking = SUPER;
                superAtack->init.restart();
            }

        }


        void superAnim() {
            Time t = superAtack->init.getElapsedTime();

            if (atacking != NOT_ATTACK) {
                if (t > superAtack->timeLapse) {
                    atacking = NOT_ATTACK;
                    superAtack->isAtacking = false;
                    superAtack->getHitted = false;
                    return;
                }


                if (superAtack->getHitted || !air) {
                    atacking = NOT_ATTACK;

                    vspeed = -4;

                    if (!air) {

                        vspeed = 0;

                        float xx = model.pos.x;
                        float yy = model.pos.y;
                        projectiles[0].setPosition(xx, Rooster::floorY);

                        float faceSign = facingRight ? 1 : -1;

                        projectiles[0].setImpulse(faceSign * 16, 0);
                        projectiles[0].setFriction(0.96);
                        projectiles[0].setVisibility(true);
                        projectiles[0].active = true;
                        projectiles[0].setLife(100);
                 
                        projectiles[0].setScaleMultiplier(0, 0);
                        projectiles[0].facingSign = faceSign;
                        
                    }

                    

                    superAtack->isAtacking = false;
                    superAtack->getHitted = false;
                    return;


                }

            }



            float percentage = (float)t.asMilliseconds() / (superAtack->timeLapse.asMilliseconds());


            if (!superAtack->getHitted) {
                if (percentage < 1.f / 3.f) {

                    float thisPercentage = percentage * 3;

                    model.at("Head")->offset.y *= 0.5;

                    float oPerc = ((thisPercentage / 2) + 1);
                    model.at("Body")->xScl = model.at("Body")->getBaseScale().x * oPerc;
                    model.at("Body")->yScl = model.at("Body")->getBaseScale().y * oPerc;



                }
                else if (percentage < 2.f / 3.f) {


                    float thisPercentage = ruleOfThree(percentage, float(1 / 3), float(2 / 3), 0, 1);


                    model.at("Head")->offset.y = 0;

                    float oPerc = 1.5;

                    model.at("Body")->xScl = model.at("Body")->getBaseScale().x * oPerc;
                    model.at("Body")->yScl = model.at("Body")->getBaseScale().y * oPerc;


                    vspeed = 50;

                    superAtack->isAtacking = true;
                    superAtack->hitbox.center.x = model.at("Body")->drawPos.x;
                    superAtack->hitbox.center.y = model.at("Body")->drawPos.y + 100 * model.yScl;
                }
                else if (percentage < 2.9f / 3.f) {

                    float thisPercentage = ruleOfThree(percentage, float(2 / 3), float(2.9 / 3), 0, 1);

                    vspeed = 50;

                    superAtack->isAtacking = true;
                    superAtack->hitbox.center.x = model.at("Body")->drawPos.x;
                    superAtack->hitbox.center.y = model.at("Body")->drawPos.y + 100 * model.yScl;
                }
                else {
                    superAtack->isAtacking = false;


                }
            }
            else {
                superAtack->isAtacking = false;
            }
        }

        void especialAnim() {

            Time t = ultimateShot->init.getElapsedTime();

            if (atacking != NOT_ATTACK) {
                if (t > ultimateShot->timeLapse) {
                    atacking = NOT_ATTACK;
                    ultimateShot->isAtacking = false;
                    ultimateShot->getHitted = false;
                    return;
                }
                

                if (ultimateShot->getHitted || !air) {
                    atacking = NOT_ATTACK;


                    vspeed = -10;
                    //println("Bateu " << ultimateShot->getHitted);

                    ultimateShot->isAtacking = false;
                    ultimateShot->getHitted = false;
                    return;


                }
               
            }



            float percentage = (float)t.asMilliseconds() / (ultimateShot->timeLapse.asMilliseconds());


            if (!ultimateShot->getHitted) {
                if (percentage < 1.f / 3.f) {

                    float thisPercentage = percentage * 3;

                    model.at("Head")->offset.y *= 0.5;

                    float oPerc = ((thisPercentage / 2) + 1);
                    model.at("Body")->xScl = model.at("Body")->getBaseScale().x * oPerc;
                    model.at("Body")->yScl = model.at("Body")->getBaseScale().y * oPerc;

                    

                }
                else if (percentage < 2.f / 3.f) {

                   
                    float thisPercentage = ruleOfThree(percentage, float(1 / 3), float(2 / 3), 0, 1);


                    model.at("Head")->offset.y = 0;

                    float oPerc = 1.5;

                    model.at("Body")->xScl = model.at("Body")->getBaseScale().x * oPerc;
                    model.at("Body")->yScl = model.at("Body")->getBaseScale().y * oPerc;


                    vspeed = 30;

                    ultimateShot->isAtacking = true;
                    ultimateShot->hitbox.center.x = model.at("Body")->drawPos.x;
                    ultimateShot->hitbox.center.y = model.at("Body")->drawPos.y + 100*model.yScl;
                }
                else if (percentage < 2.9f / 3.f) {

                    float thisPercentage = ruleOfThree(percentage, float(2 / 3), float(2.9 / 3), 0, 1);

                    vspeed = 30;

                    ultimateShot->isAtacking = true;
                    ultimateShot->hitbox.center.x = model.at("Body")->drawPos.x;
                    ultimateShot->hitbox.center.y = model.at("Body")->drawPos.y + 100 * model.yScl;
                }
                else {
                    ultimateShot->isAtacking = false;


                }
            }
            else {
                ultimateShot->isAtacking = false;
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
                louKick->hitbox.center.x -= 100 * model.xScl;
                
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
             

                hiKick->hitbox.center = model.at("Body")->drawPos;
                hiKick->hitbox.center.x -= 100*model.xScl;
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
                    if (!atacking) {
                        weatherAnim(frames);
                    }
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
                else if (atacking == SUPER) {
                    superAnim();
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


            projectiles[0].update();

            if (projectiles[0].death) {
                Effect* effect = new Effect();
                effect->poeiraPreset();
                effect->mortal = true;
                effect->life = 100;

                float wid = projectiles[0].getSprite().getGlobalBounds().width;
                float hei = projectiles[0].getSprite().getGlobalBounds().height;
                

                for (int i = 0; i < 6; i++) {
                    float randDist = randFloat(wid/3);
                    float randAngle = randFloat(2*PI);

                    float xx = cos(randAngle)*randDist + projectiles[0].getPosition().x - (wid/2)*projectiles[0].facingSign;
                    float yy = sin(randAngle) * randDist + projectiles[0].getPosition().y - hei/2;

                    effect->position.x = xx;
                    effect->position.y = yy;

                    effect->createParticle();
                }

                mainPartSystem.addEffect(effect);
            }
        }

        



        /*
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

            Text botawins("Bota Wins", mortal, SCREEN_WIDTH / 50);

            botawins.setPosition(
                SCREEN_WIDTH / 2 - botawins.getGlobalBounds().width / 2,
                garra2.getPosition().y - botawins.getGlobalBounds().height
            );
            botawins.setFillColor(Color(250, 250, 250));
            botawins.setOutlineThickness(SCREEN_WIDTH / 700);
            botawins.setOutlineColor(Color(255, 255, 10));


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


            Texture milhoTex;
            milhoTex.loadFromFile("sprites/milho.png");

            Sprite milhoSpr(milhoTex);
            milhoSpr.setScale(10, 10);
            milhoSpr.setPosition(0, -200);


            SoundBuffer powerupSndBuf;
            powerupSndBuf.loadFromFile("sounds/Powerup.ogg");
            Sound powerupSnd;
            powerupSnd.setBuffer(powerupSndBuf);


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



                }
                else if (time < 2500) {
                    float thisTime = time - 1500;

                    perc = thisTime / 1000;

                  
                    position.y = SCREEN_HEIGHT - ((SCREEN_HEIGHT / 2) * perc);

                }
                else if (time < 3000) {


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
                            window->draw(botawins);
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
            */
    };


}

#endif // GALOBOTA_H_INCLUDED