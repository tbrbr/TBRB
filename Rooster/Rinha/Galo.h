#ifndef GALO_H_included
#define GALO_H_included

#include "IAtaques.h"
#include "Elementos.h"

namespace Rooster {

    /* a element is a small part of a rooster or any character available
    that way the animations will be smoother and easy to make for any rooster*/

    enum state {
        STOPPED = 0,
        RUNNING,
        LOW_KICK,
        HIGH_KICK,
        SLAP,
        JUMP,
        JUMP_KICK,
        SPECIAL,
        DEFENDING,
        RIGHT

    };
    enum roosters {
        BOTAS,
        SNIPER,
        KALSA,
        PESTE_NEGRA,
        BRUXO,

    };

    typedef struct {
        Vector2i xCenter;
        int radius;
    } HitBox;

    class Galo : public IAtaques{

    protected:
        HitBox hitbox;
        int hp;
        int id;
        float peso;
        int atk;
        int def;
        int speed;
        int estado;

        Sprite* sprite = new Sprite[9];
        RectangleShape r;


        std::vector<int> elementDrawOrder;
        std::vector<Element*> elementos;


        bool air;
        float hspeed;
        float vspeed;
        int frames = 0;
        int initFrames = 0;

    public:

        bool facingRight = false;
        bool attacking = false;
        bool isLightAttack = false;
        void addElement(sf::Texture& tex, float xTex, float yTex, float wid,
            float hei, float xCenter, float yCenter, float xAttach,
            float yAttach, int idAttach) {

            float xAt = 0;
            float yAt = 0;
            if (idAttach != -1) {
                xAt = xAttach - (elementos.at(idAttach)->texPos.x + elementos.at(idAttach)->center.x);
                yAt = yAttach - (elementos.at(idAttach)->texPos.y + elementos.at(idAttach)->center.y);
            }

            Element* part = new Element(tex, xTex, yTex, wid, hei, xCenter, yCenter, xAt, yAt);
            part->attachId = idAttach;
            elementos.push_back(part);
        }



        Galo(HitBox _hitbox, int atk, int def, int speed, int _state) {
            hitbox = _hitbox;
            this->atk = atk;
            this->def = def;
            this->speed = speed;
            this->estado = _state;
            this->peso = 2;
            this->air = false;
            this->hspeed = 0;
            this->vspeed = 0;
        }

        inline RectangleShape getSprite() {
            return r;
        }
        void inline setState(state estado) {
            this->estado = estado;
        }
        void inline setState(int estado) {
            this->estado = estado;
        }
        void inline setHspeed(float spd) {
            hspeed = spd;
        }
        void inline setInitFrames(int initframes) {
            initFrames = initframes;
        }
        int inline getFrames() {
            return frames;
        }


        void animJump() {
            if (!air) {
                vspeed += (peso * (-8)) / 2;
                air = true;
            }
        }

        void animRun() {
            float acc = 0.5;

            if (facingRight) {
                hspeed = (hspeed + acc) > 10 ? 10 : (hspeed + acc);
                for (int i = 0; i < elementos.size(); i++) {
                    elementos.at(i)->scl.x = -0.25;
                }
            }
            else {
                hspeed = (hspeed - acc) < -10 ? -10 : (hspeed - acc);
                for (int i = 0; i < elementos.size(); i++) {
                    elementos.at(i)->scl.x = 0.25;
                }
            }
        }


        void show(sf::RenderWindow& window) {

            for (int i = 0; i < elementDrawOrder.size(); i++) {
                elementos.at(elementDrawOrder.at(i))->show(window);
            }
        }

        virtual void update() {

            if (air) {
                vspeed += peso * G / 100;
            }

            if (r.getPosition().y > 600) {
                vspeed = 0;
                r.setPosition(r.getPosition().x, 600);
                air = false;
            }

            r.move(hspeed, vspeed);


            for (int i = 1; i < elementos.size(); i++) {

                Element* elem = elementos.at(elementos.at(i)->attachId);
                elementos.at(i)->update(elem->position.x, elem->position.y, elem->angle + elem->otherAngle);
            }
        }
    };

}



#endif