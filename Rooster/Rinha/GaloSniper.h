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

            addElement(_texture, 26, 517, 479, 461, 250, 712, 0, 0, -1); // Corpo

            addElement(_texture, 64, 38, 318, 434, 243, 420, 138, 595, CORPO); // Cabeca

            addElement(_texture, 517, 565, 460, 517, 628, 834, 435, 824, CORPO); // Rabo

            addElement(_texture, 464, 264, 331, 233, 748, 380, 300, 670, CORPO); // AsaFrente

            addElement(_texture, 464, 264, 331, 233, 748, 380, 150, 700, CORPO); // AsaTras

            addElement(_texture, 100, 993, 144, 157, 202, 1015, 387, 930, CORPO); // Perna Frente

            addElement(_texture, 7, 1229, 260, 186, 173, 1242, 130, 1134, PERNA_FRENTE); // pe frente

            addElement(_texture, 100, 993, 144, 157, 202, 1015, 260, 910, CORPO); // Perna tras

            addElement(_texture, 7, 1229, 260, 186, 173, 1242, 130, 1134, PERNA_ATRAS); // pe tras

            addElement(_texture, 828, 66, 86, 106, 850, 80, 185, 364, CABECA);// bigode frente

            addElement(_texture, 828, 66, 86, 106, 850, 80, 142, 369, CABECA); // bigode atras

            elementDrawOrder.push_back(RABO);
            elementDrawOrder.push_back(ASA_ATRAS);
            elementDrawOrder.push_back(PE_ATRAS);
            elementDrawOrder.push_back(PERNA_ATRAS);
            elementDrawOrder.push_back(BIGODE_ATRAS);
            elementDrawOrder.push_back(ASA_FRENTE);
            elementDrawOrder.push_back(PE_FRENTE);
            elementDrawOrder.push_back(PERNA_FRENTE);
            elementDrawOrder.push_back(CORPO);
            elementDrawOrder.push_back(CABECA);
            elementDrawOrder.push_back(BIGODE_FRENTE);
            elementDrawOrder.push_back(ASA_FRENTE);

            elementos[BIGODE_FRENTE]->angle = 345;
            elementos[BIGODE_ATRAS]->angle = 25;
        }

        void weatherAnim(int frames) {
            elementos.at(CORPO)->angle += 0;
            elementos.at(CORPO)->update(r.getPosition().x, r.getPosition().y, 0);
            elementos.at(RABO)->angle = sin(frames / 200.f) * 20;
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
            
           

            elementos.at(PERNA_FRENTE)->offset.y += vspeed / 8;
            elementos.at(PE_FRENTE)->angle += vspeed / 20;

            elementos.at(PERNA_ATRAS)->offset.y += vspeed / 16;
            elementos.at(PE_ATRAS)->angle += vspeed / 20;
            if (facingRight) {
                elementos.at(BIGODE_FRENTE)->angle += vspeed / 2;
                elementos.at(BIGODE_ATRAS)->angle += vspeed / 2;
            }
            else {
                elementos.at(BIGODE_FRENTE)->angle -= vspeed / 2;
                elementos.at(BIGODE_ATRAS)->angle -= vspeed / 2;
            }
        }
        void cairAnim() {
            elementos.at(PERNA_FRENTE)->offset.y = 0;
            elementos.at(PERNA_ATRAS)->offset.y = 0;

            elementos.at(PE_FRENTE)->angle = 0;
            elementos.at(PE_ATRAS)->angle = 0;

            elementos.at(BIGODE_FRENTE)->angle = 345;
            elementos.at(BIGODE_ATRAS)->angle = 25;
        }
        void runAnim() {
            legWalkAngFase += hspeed;
            legWalkAngFase -= ((int)legWalkAngFase / 360) * 360;
            elementos.at(PERNA_FRENTE)->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
            elementos.at(PERNA_ATRAS)->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

            elementos.at(ASA_FRENTE)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;
            elementos.at(ASA_ATRAS)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;

            elementos.at(BIGODE_FRENTE)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
            elementos.at(BIGODE_ATRAS)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;
        }
        void runReset() {
            legWalkAngFase *= 0.8;
            ArmSpinAngFase *= 0.8;
            Arm2SpinAngFase *= 0.8;

            elementos.at(PERNA_FRENTE)->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
            elementos.at(PERNA_ATRAS)->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

            elementos.at(ASA_FRENTE)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
            elementos.at(ASA_ATRAS)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;

            elementos.at(BIGODE_FRENTE)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
            elementos.at(BIGODE_ATRAS)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;

            elementos[CORPO]->offset.y *= 0.8;

        }
        void defend() override{
            estado = DEFENDING;
            
        }
        void agachadinha() {

            elementos[CORPO]->offset.y += SCREEN_HEIGHT / 100;
            elementos[PERNA_ATRAS]->offset.y -= SCREEN_HEIGHT / 100;
            elementos[PERNA_FRENTE]->offset.y -= SCREEN_HEIGHT / 100;
        }

        void lightAtack() override {
            atacking = HIGH_KICK;
            lightAtk->init.restart();
        
        }

        void lightAtackAnim(){
            Time t = lightAtk->init.getElapsedTime();

            if (t > lightAtk->timeLapse) {
                atacking = STOPPED;
            }

            float percentage = (float) t.asMilliseconds()/(lightAtk->timeLapse.asMilliseconds());

            int angFix = (facingRight) ? 1 : -1;
            

            if (percentage < 1.f / 3.f) {
                

                float thisPercentage = percentage * 3;
                elementos[CORPO]->angle = angFix * 45 * -sin(thisPercentage*PI/2);
                elementos[PERNA_FRENTE]->angle = angFix * -320;
                elementos[PERNA_ATRAS]->angle = angFix * 90 * -sin(thisPercentage * PI / 2);
                elementos[ASA_ATRAS]->angle = angFix * 45 * -sin(thisPercentage * PI / 2);
                elementos[ASA_FRENTE]->angle = angFix * 90 * sin(thisPercentage * PI / 2);

            } else if (percentage < 2.f / 3.f) {
                float thisPercentage = percentage * 3;
                elementos[CORPO]->angle = angFix * -45;
                elementos[PERNA_FRENTE]->angle = angFix * -320;
                elementos[PERNA_ATRAS]->angle = angFix * -90;
                elementos[PERNA_ATRAS]->offset.x = angFix * SCREEN_WIDTH/75;
                elementos[PERNA_ATRAS]->offset.y =  -SCREEN_WIDTH / 75;
                elementos[ASA_ATRAS]->angle = angFix * -45;
                elementos[ASA_FRENTE]->angle = angFix * 90;

            } else if(percentage < 2.9f / 3.f) {
     
                elementos[CORPO]->angle *= 0.9;
                elementos[PERNA_FRENTE]->angle *= 0.9;
                elementos[PERNA_ATRAS]->angle *= 0.9;
                elementos[PERNA_ATRAS]->offset.x = 0;
                elementos[PERNA_ATRAS]->offset.y = 0;
                elementos[ASA_ATRAS]->angle *= 0.9;
                elementos[ASA_FRENTE]->angle *= 0.9;
            }
            else {
                elementos[CORPO]->angle = 0;
                elementos[PERNA_FRENTE]->angle = 0;
                elementos[PERNA_ATRAS]->angle = 0;
                elementos[PERNA_ATRAS]->offset.x = 0;
                elementos[PERNA_ATRAS]->offset.y = 0;
                elementos[ASA_ATRAS]->angle = 0;
                elementos[ASA_FRENTE]->angle = 0;
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

            r.move(hspeed, vspeed);
                         
            frames++;
            weatherAnim(frames);
            
             
            if (air) {
                jumpAnim();
            }
            else {
                cairAnim();
            }


            elementos.at(ASA_FRENTE)->angle = ArmSpinAngFase;
            elementos.at(ASA_ATRAS)->angle = Arm2SpinAngFase;
            
            if (estado == RUNNING) {    
                runAnim();
            }
            else if (estado == DEFENDING) {
                agachadinha();
            }
            else if(estado == STOPPED) {
                runReset();
            }

            if (atacking == HIGH_KICK) {
                lightAtackAnim();
            }
           

            bar->update(hp);

            for (int i = 1; i < elementos.size(); i++) {

                Element* elem = elementos.at(elementos.at(i)->attachId);
                elementos.at(i)->update(elem->position.x, elem->position.y, elem->angle + elem->otherAngle);
            }
            
           
        }
    };


}

#endif // GALOSNIPER_H_INCLUDED