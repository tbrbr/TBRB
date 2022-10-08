#ifndef GALOSNIPER_H_INCLUDED
#define GALOSNIPER_H

#include "Galo.h"

namespace Rooster {

    class Sniper : public Galo {

        float legWalkAngFase = 0;
        float ArmSpinAngFase = 0;
        float Arm2SpinAngFase = 0;

    public:
        Sniper(HitBox _hitbox, int atk, int def, int speed, int _state, Texture& _texture) : Galo(_hitbox, atk, def, speed, _state) {
            hitbox = _hitbox;
            this->peso = 2;
            this->air = false;
            this->hspeed = 0;
            this->vspeed = 0;
            r.setSize(Vector2f(20, 20));
            r.setPosition(400, 600);

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

        void LightAttack()override {

            if (frames - initFrames < 300) {
                elementos.at(CORPO)->angle = float((frames - initFrames) / 60) * (315);
            }
            else {
                elementos[CORPO]->angle = 0;
                isLightAttack = false;
            }

        }

        void HeavyAttack()override {}

        void update() override {


            if (air) {
                vspeed += peso * G / 100;
            }

            if (r.getPosition().y > 600) {
                vspeed = 0;
                r.setPosition(r.getPosition().x, 600);
                air = false;
            }

            r.move(hspeed, vspeed);

            /// Animacao das partes do corpo

            //these parts moves all the time to create weather like animations
            frames++;

            elementos.at(CORPO)->angle += 0;
            elementos.at(CORPO)->update(r.getPosition().x, r.getPosition().y, 0);
            elementos.at(RABO)->angle = sin(frames / 200.f) * 20;

            /******************************************************************/


            //jump animation
            if (air) {
                ArmSpinAngFase = (vspeed / 8) * 45;
                Arm2SpinAngFase = (vspeed / 8) * 45;

                elementos.at(PERNA_FRENTE)->offset.y += vspeed / 8;
                elementos.at(PE_FRENTE)->angle += vspeed / 20;

                elementos.at(PERNA_ATRAS)->offset.y += vspeed / 16;
                elementos.at(PE_ATRAS)->angle += vspeed / 20;

                elementos.at(BIGODE_FRENTE)->angle -= vspeed / 2;
                elementos.at(BIGODE_ATRAS)->angle -= vspeed / 2;
            }
            else {
                elementos.at(PERNA_FRENTE)->offset.y = 0;
                elementos.at(PERNA_ATRAS)->offset.y = 0;

                elementos.at(PE_FRENTE)->angle = 0;
                elementos.at(PE_ATRAS)->angle = 0;

                elementos.at(BIGODE_FRENTE)->angle = 345;
                elementos.at(BIGODE_ATRAS)->angle = 25;
            }

            elementos.at(ASA_FRENTE)->angle = ArmSpinAngFase;
            elementos.at(ASA_FRENTE)->offset.y = sin(frames / 200.f) * 5;
            elementos.at(ASA_ATRAS)->angle = Arm2SpinAngFase;
            elementos.at(ASA_ATRAS)->offset.y = sin(frames / 200.f) * 5;

            //running animation
            if (estado == RUNNING) {
                legWalkAngFase += hspeed;
                legWalkAngFase -= ((int)legWalkAngFase / 360) * 360;
                elementos.at(PERNA_FRENTE)->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
                elementos.at(PERNA_ATRAS)->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

                elementos.at(ASA_FRENTE)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
                elementos.at(ASA_ATRAS)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;

                elementos.at(BIGODE_FRENTE)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
                elementos.at(BIGODE_ATRAS)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;


            }
            else {
                legWalkAngFase *= 0.8;
                ArmSpinAngFase *= 0.8;
                Arm2SpinAngFase *= 0.8;

                elementos.at(PERNA_FRENTE)->angle = sin(2 * PI * legWalkAngFase / 360) * 60;
                elementos.at(PERNA_ATRAS)->angle = -sin(2 * PI * legWalkAngFase / 360) * 60;

                elementos.at(ASA_FRENTE)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
                elementos.at(ASA_ATRAS)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;

                elementos.at(BIGODE_FRENTE)->angle += sin(2 * PI * legWalkAngFase / 360) * 60;
                elementos.at(BIGODE_ATRAS)->angle += -sin(2 * PI * legWalkAngFase / 360) * 60;


            }


            for (int i = 1; i < elementos.size(); i++) {

                Element* elem = elementos.at(elementos.at(i)->attachId);
                elementos.at(i)->update(elem->position.x, elem->position.y, elem->angle + elem->otherAngle);
            }
            if (isLightAttack)
                this->LightAttack();
        }
    };


}

#endif // GALOSNIPER_H_INCLUDED