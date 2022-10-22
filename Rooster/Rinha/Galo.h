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
        NOT_ATTACK = 0,
        LOW_KICK,
        HIGH_KICK,
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
        Vector2f position;

        bool air;
        float hspeed;
        float vspeed;
        int frames = 0;
        int initFrames = 0;

        struct Model model;

        std::vector<struct Animation> animations;

        float floorY = (float)SCREEN_HEIGHT / 1.4;

    public:
        int atacking;
        HitBox hitbox;
        std::vector<HitBox> hurtBox;
        std::vector<Projectile> projectiles;
        LifeBar* bar;
        bool facingRight = false;
        bool estadoUpdate = false;

        // Timer of rooster frames when get hitted by an attack
        int invFrames = 0;
        int stunFrames = 0;

        Ataques* hiKick;
        Ataques* louKick;
        Ataques* ultimateShot;
        

        Galo(int atk, int def, int speed, int _state) { 
            this->atk = atk;
            this->def = def;
            this->speed = speed;
            this->estado = _state;
            this->peso = 2;
            this->air = false;
            this->hspeed = 0;
            this->vspeed = 0;
            this->position = Vector2f(0, 0);
        }

        //inline RectangleShape getSprite() {
            //return r;
        //}
        void inline setState(state estado) {
            if (estado != this->estado) {
                this->estadoUpdate = true;
            }
            this->estado = estado;
            
        }
        void inline setState(int estado) {
            if (estado != this->estado) {
                this->estadoUpdate = true;
            }
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
        virtual void apanhar(Ataques atk,bool direction) {
            this->hp -= atk.Damage;
            bar->update(hp);
        }

        void jump() {
            if (stunFrames <= 0) {
                if (!air) {
                    vspeed += (peso * (-8)) / 2;
                    air = true;
                }
            }
        }
        
        void run() {

            if (stunFrames <= 0) {
                float acc = 0.5;

                if (facingRight) {
                    hspeed = (hspeed + acc) > 10 ? 10 : (hspeed + acc);

                }
                else {
                    hspeed = (hspeed - acc) < -10 ? -10 : (hspeed - acc);

                }
            }
        } 
        virtual void defend() = 0; 
        virtual void highKick() = 0;
        virtual void lowKick() = 0;
        virtual void especial() = 0;

        void show(sf::RenderWindow& window) {

         
            model.draw(window);
            
            
            projectiles[0].draw(window);
            

            for (int i = 0; i < hurtBox.size(); i++) {

               
                //drawHitBox(window, hurtBox[i], sf::Color(255, 255, 255, 100));

            }

            if (hiKick->isAtacking) {
               // drawHitBox(window, hiKick->hitbox, sf::Color::Red);
            }

            



        }

        void drawHitBox(sf::RenderWindow& window, HitBox box, sf::Color col) {
            sf::CircleShape circle(box.radius);
            circle.setPosition(box.center.x, box.center.y);
            circle.setOrigin(box.radius, box.radius);
            circle.setFillColor(col);
            circle.setOutlineColor(sf::Color::Black);
            circle.setOutlineThickness(2);

            window.draw(circle);
        }

        virtual void update() {

           
            if (air) {
                vspeed += peso * Gravity / 100;
            }

            /*
            if (r.getPosition().y > floorY) {
                vspeed = 0;
                r.setPosition(r.getPosition().x, floorY);
                air = false;
            }
            */
            /// Meus planos
            
            if (position.y > floorY) {
                vspeed = 0;
                position.y = floorY;
                air = false;
            }
            

            //r.move(hspeed, vspeed);
            position.x += hspeed;
            position.y += vspeed;


            //model.pos = r.getPosition();
            model.pos = position;

            model.update();

            estadoUpdate = false;


        }
    };

}



#endif