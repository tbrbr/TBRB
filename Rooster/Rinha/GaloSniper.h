#ifndef GALOSNIPER_H_INCLUDED
#define GALOSNIPER_H

#include "Galo.h"

namespace Rooster {

    class Sniper : public Galo {

        float legWalkAngFase = 0;
        float ArmSpinAngFase = 0;
        float Arm2SpinAngFase = 0;
        Ataques* lightAtk;
        
       
    public:
        Sniper(int atk, int def, int speed, int _state, Texture& _texture, bool isp1) : Galo(atk, def, speed, _state) {
            this->name = "Sniper";
            this->maxHp = 100;
            this->hp = 100;
            bar = new LifeBar(maxHp, isp1, name.c_str());
           

            this->lightAtk = new Ataques(0.9, 0.5,HitBox{Vector2f(0, 0), 0}, 10, 3,milliseconds(1000));

            r.setSize(Vector2f(20, 20));
            r.setPosition(SCREEN_WIDTH/4, (float) SCREEN_HEIGHT/1.4);

            model.tex = &_texture;
            model.loadModel("SniperModel.txt");

            struct Animation agacharAnim;
            agacharAnim.init("SecondAnim.txt");
            agacharAnim.playingSpeed = 0.5;
            agacharAnim.connectLoop = false;
            animations.push_back(agacharAnim);



        }


        void weatherAnim(int frames) {
            model.at(CORPO)->angle += 0;
            //model.at(CORPO)->update(r.getPosition().x, r.getPosition().y, 0);
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



            model.at(PERNA_FRENTE)->offset.y += vspeed / 8;
            model.at(PE_FRENTE)->angle += vspeed / 20;

            model.at(PERNA_ATRAS)->offset.y += vspeed / 16;
            model.at(PE_ATRAS)->angle += vspeed / 20;
            if (facingRight) {
                model.at(BIGODE_FRENTE)->angle += vspeed / 2;
                model.at(BIGODE_ATRAS)->angle += vspeed / 2;
            }
            else {
                model.at(BIGODE_FRENTE)->angle -= vspeed / 2;
                model.at(BIGODE_ATRAS)->angle -= vspeed / 2;
            }
        }
        void cairAnim() {
            model.at(PERNA_FRENTE)->offset.y = 0;
            model.at(PERNA_ATRAS)->offset.y = 0;

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
            model.at(PERNA_ATRAS)->offset.y *= 0.25;
            model.at(PE_FRENTE)->offset.y *= 0.25;
            model.at(PERNA_FRENTE)->offset.y *= 0.25;
            model.at(PE_ATRAS)->offset.y *= 0.25;

            model.at(CORPO)->offset.y = 0;
            model.at(PERNA_ATRAS)->offset.y = 0;
            model.at(PE_FRENTE)->offset.y = 0;
            model.at(PERNA_FRENTE)->offset.y = 0;
            model.at(PE_ATRAS)->offset.y = 0;


        }

        void defend() override {
            estado = DEFENDING;

        }



        void agachadinha() {


            //model.at(CORPO)->offset.y = 40;
            //model.at(PERNA_ATRAS)->offset.y = -20;
            //model.at(PE_FRENTE)->offset.y = -20;
            //model.at(PERNA_FRENTE)->offset.y = -20;
            //model.at(PE_ATRAS)->offset.y = -20;

            hspeed = 0;
        }


        void lightAtack() override {
            atacking = HIGH_KICK;
            lightAtk->init.restart();

        }




        void lightAtackAnim() {
            Time t = lightAtk->init.getElapsedTime();

            if (t > lightAtk->timeLapse) {
                atacking = STOPPED;
            }

            float percentage = (float)t.asMilliseconds() / (lightAtk->timeLapse.asMilliseconds());

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

            }
            else if (percentage < 2.9f / 3.f) {

                model.at(CORPO)->angle *= 0.9;
                model.at(PERNA_FRENTE)->angle *= 0.9;
                model.at(PERNA_ATRAS)->angle *= 0.9;
                model.at(PERNA_ATRAS)->offset.x = 0;
                model.at(PERNA_ATRAS)->offset.y = 0;
                model.at(ASA_ATRAS)->angle *= 0.9;
                model.at(ASA_FRENTE)->angle *= 0.9;
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

        void update() override {

            hitbox = { Vector2f(r.getPosition().x, r.getPosition().y), 30};

            if (air) {
                vspeed += peso * G / 100;
            }

            if (r.getPosition().y > (float) SCREEN_HEIGHT/1.399) {
                vspeed = 0;
                r.setPosition(r.getPosition().x, (float) SCREEN_HEIGHT/1.4);
                air = false;
            }

            if (estadoUpdate) {
                model.resetToBase();
                animations[0].playingFrame = 0;
            }

            r.move(hspeed, vspeed);
                         
            frames++;
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
            }
            else if (estado == DEFENDING) {
                animations[0].update();
                if (animations[0].playingFrame > 15) {
                    animations[0].playingFrame = 15;
                }
                model.updateWithAnimation(animations[0]);

            }
            else if(estado == STOPPED) {
                runReset();
            }

            if (atacking == HIGH_KICK) {
                lightAtackAnim();
            }
           

            bar->update(hp);


            model.pos = r.getPosition();
            model.xScl = 4 * (facingRight ? 1 : -1) * -(float)SCREEN_WIDTH / 5120;
            model.yScl = 4 * (float)SCREEN_WIDTH / 5120;



            model.update();


            estadoUpdate = false;



            //for (int i = 1; i < elementos.size(); i++) {

               // Element* elem = elementos.at(elementos.at(i)->attachId);
                //elementos.at(i)->update(elem->position.x, elem->position.y, elem->angle + elem->otherAngle);
            //}
            
           
        }
    };


}

#endif // GALOSNIPER_H_INCLUDED