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
        DEFENDING,
        LOW_KICK = 0,
        HIGH_KICK,
        SLAP,
        JUMP_KICK,
        SPECIAL,
       

    };
    
    enum roosters {
        BOTAS,
        SNIPER,
        KALSA,
        PESTE_NEGRA,
        BRUXO,
    };

#define NUMGALOS 5


    class LifeBar {
        Vector2i tam = { SCREEN_WIDTH / 3,SCREEN_HEIGHT / 54 };
        int spaceForTime = SCREEN_WIDTH / 6;
        int Maxhp;
        Text playerName;

        ConvexShape fillBar;

        RectangleShape life;
        RectangleShape fullLife;
        RectangleShape Damage;
        Texture iron;
        Font mk11;
        
        bool isP1;
        int yposition = SCREEN_HEIGHT / 8;
        int xposition;
       
    public:

        int hp;

        int lastTam;
        Clock clock;
        Clock piscada;
        Time lastTime;

        LifeBar(int maxhp, bool isP1, const char * galoName) {
            Maxhp = maxhp;
            
            this->isP1 = isP1;
            int recLine = SCREEN_WIDTH / 99;
            fillBar.setPointCount(6);
            
            iron.loadFromFile("sprites/texturaFerro.png");
            fillBar.setTexture(&iron, true);
            mk11.loadFromFile("fonts/Mortal-Kombat-MK11.otf");
            playerName.setFont(mk11);
            playerName.setString(galoName);
            playerName.setCharacterSize(SCREEN_WIDTH / 50);

            fullLife.setOutlineThickness(SCREEN_WIDTH / 300);
            fullLife.setOutlineColor(Color::Black);
            fullLife.setFillColor(Color::Black);
            fillBar.setOutlineThickness(SCREEN_WIDTH / 300);
            fillBar.setOutlineColor(Color::Black);
           
            if (isP1) {
                xposition = SCREEN_WIDTH/12;
                fillBar.setPoint(0, sf::Vector2f(-recLine*2, 0));
                fillBar.setPoint(1, sf::Vector2f(tam.x + recLine * 6, 0));
                fillBar.setPoint(2, sf::Vector2f(tam.x + recLine, tam.y + recLine * 3));
                fillBar.setPoint(3, sf::Vector2f(tam.x / 1.5, tam.y + recLine * 3));
                fillBar.setPoint(4, sf::Vector2f(tam.x / 2, tam.y + recLine));
                fillBar.setPoint(5, sf::Vector2f(0, tam.y + recLine));

                
                fillBar.scale(-1, 1);
                fillBar.setPosition(xposition - recLine*4.5 + (tam.x + recLine * 5), yposition - recLine / 2);
                fullLife.setPosition(xposition, yposition);
                life.setPosition(xposition, yposition);
                playerName.setPosition(xposition + recLine, yposition + recLine);
            }
            else {
                xposition = SCREEN_WIDTH / 12 + tam.x + spaceForTime;
                life.scale(-1, 1);
                fillBar.setPoint(0, sf::Vector2f(-recLine * 2, 0));
                fillBar.setPoint(1, sf::Vector2f(tam.x + recLine * 6, 0));
                fillBar.setPoint(2, sf::Vector2f(tam.x + recLine, tam.y + recLine * 3));
                fillBar.setPoint(3, sf::Vector2f(tam.x / 1.5, tam.y + recLine * 3));
                fillBar.setPoint(4, sf::Vector2f(tam.x / 2, tam.y + recLine));
                fillBar.setPoint(5, sf::Vector2f(0, tam.y + recLine));


                fillBar.setPosition(xposition - recLine / 2, yposition - recLine / 2);
                fullLife.setScale(-1, 1);
                fullLife.setPosition(xposition + tam.x, yposition);
                life.setPosition(xposition + tam.x, yposition);
                playerName.setPosition(xposition + tam.x - recLine - playerName.getGlobalBounds().width, yposition + recLine);
                Damage.setScale(-1, 1);
            }
           
            Color niceyellow(245, 205, 80);
            
            life.setFillColor(niceyellow);
            life.setSize(Vector2f((tam.x * hp) / Maxhp, tam.y));
            fullLife.setSize(Vector2f(tam.x , tam.y));

            
            

        }
        RectangleShape getRecLife() {
            return life;
        }

        ConvexShape getBar() {
            return fillBar;
        }
        void setMaxHp(int maxhp) {
            Maxhp = maxhp;
        }
        int getMaxhp() {
            return Maxhp;
        }
        int getLifeBarWidth() {
            return tam.x;
        }
        int getLifeBarHeight() {
            return tam.y;
        }
        
        void draw(RenderWindow *window) {

            window->draw(fillBar);
            window->draw(fullLife);
            window->draw(life);
            window->draw(Damage);
            window->draw(playerName);
        }
       
        void update(int hp) {

            int oldTam = life.getGlobalBounds().width;
            int newTam = (tam.x * hp) / Maxhp;

            life.setSize(Vector2f(newTam, tam.y));

      
            if (oldTam > newTam) {
                Damage.setSize(Vector2f(lastTam - newTam, tam.y));
                Damage.setFillColor(Color::Color(145, 10, 10));
                if (isP1) {
                    Damage.setPosition(Vector2f(life.getGlobalBounds().left + newTam, life.getGlobalBounds().top));
                }
                else {
                    Damage.setPosition(Vector2f(life.getGlobalBounds().left, life.getGlobalBounds().top));
                }


                piscada.restart();
                clock.restart();
            }

            if (piscada.getElapsedTime().asMilliseconds() <= 30) {
                int t = piscada.getElapsedTime().asMilliseconds();

                int cor = (255 * sin(t))/(1+t/10);

                Damage.setFillColor(Color::Color((255 , cor, cor)));
                fullLife.setOutlineColor(Color::Color((255, cor, cor)));

            }
            else {
                Damage.setFillColor(Color::Color(145, 10, 10));
                fullLife.setOutlineColor(Color::Color(145, 10, 10));
            }
            

            if (clock.getElapsedTime().asSeconds() > 1) {
                Damage.setFillColor(Color::Black);
                fullLife.setOutlineColor(Color::Black);
                lastTam = life.getGlobalBounds().width;
                
            }
        }
        
    };



    class Galo{

    protected:
        
        int maxHp;
        int hp;
        int id;
        float peso;
        int atk;
        int def;
        int speed;
        int estado;
       
        std::string name;

        Sprite* sprite= new Sprite[9];
        RectangleShape r;
        Vector2f position;

        std::vector<int> elementDrawOrder;
        std::vector<Element*> elementos;
        bool air;
        float hspeed;
        float vspeed;
        int frames = 0;
        int initFrames = 0;
        
    public:
        int atacking;
        HitBox hitbox;
        LifeBar* bar;
        bool facingRight = false;
        
        


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



        Galo(int atk, int def, int speed, int _state) {
            
            hitbox = { Vector2f(r.getPosition().x, r.getPosition().y), 30 };
            
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
        int getState() {
            return this->estado;
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
        void apanhar(int dmg) {
            this->hp -= dmg;
            bar->update(hp);
        }

        void jump() {
            if (!air) {
                vspeed += (peso * (-8)) / 2;
                air = true;
            }
        }
        
        void run() {
            float acc = 0.5;

            if (facingRight) {
                hspeed = (hspeed + acc) > 10 ? 10 : (hspeed + acc);
                for (int i = 0; i < elementos.size(); i++) {
                    elementos.at(i)->scl.x = -(float)SCREEN_WIDTH / 5120;;
                    
                }
            }
            else {
                hspeed = (hspeed - acc) < -10 ? -10 : (hspeed - acc);
                for (int i = 0; i < elementos.size(); i++) {
                    elementos.at(i)->scl.x = (float)SCREEN_WIDTH / 5120;
                    
                }
            }
        }
        virtual void defend() = 0; 
        virtual void lightAtack() = 0;
 

        void show(sf::RenderWindow& window) {

            for (int i = 0; i < elementDrawOrder.size(); i++) {
                elementos.at(elementDrawOrder.at(i))->show(window);
            }
        }

        virtual void update() {

            hitbox = { Vector2f(r.getPosition().x, r.getPosition().y), 30 };

            if (air) {
                vspeed += peso * G / 100;
            }

            if (r.getPosition().y > (float) SCREEN_HEIGHT / 1.4) {
                vspeed = 0;
                r.setPosition(r.getPosition().x, (float)SCREEN_HEIGHT / 1.4);
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