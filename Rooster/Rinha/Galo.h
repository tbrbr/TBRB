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
        FATALITY,  
        DANCING
    };
    
    enum roosters {
        BOTAS,
        SNIPER,
        KALSA,
        PESTE_NEGRA,
        BRUXO,
    };

    #define NUMGALOS 5

    

    const float floorY = (float)SCREEN_HEIGHT / 1.1;

    
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
        int gethp() {
            return hp;
        }
        void sethp(int hp) {
            this->hp = hp;
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



    struct GaloStats {
        int hp;
        int speed;
        int atk;
        int def;
        int peso;
        int jumpSpd;
    };



    class Galo{

    protected:
        
        // Identificadores
        int id;
        std::string name;

        // Stats
        int maxHp;
        float hp;
        int atk;
        int def;
        int speed;
        float peso;
        int estado;

        struct GaloStats stats;   

        
        // Physics
        float hspeed;
        float hspeedLimit;
        float hAcc;

        float vspeed;
        float vspeedLimit;
        float jumpSpeed;
        

        bool air;
        // im still trying
        bool isPoisoned = false;

        // Frames for Animation
        int frames = 0;


     
        std::vector<struct Animation> animations;

        Texture star;
        Sprite estrelinha;

    public:

        // Models and Animations
        struct Model model;

        Vector2f position;

        // Attacks and Hitboxes
        int atacking;
        bool isDefending = false;
        HitBox defense;
        std::vector<HitBox> hurtBox;
        std::vector<Projectile> projectiles;

        bool attackStart = false;

        Ataques* hiKick;
        Ataques* louKick;
        Ataques* ultimateShot;

        bool noGravity = false;


        // Lifebar
        LifeBar* bar;


        // Invulnerability
        bool invunerable = false;
        int invFrames = 0;

        // Stunning
        bool stunned = false;
        int stunFrames = 0;
        int coolDownFrames = 0;



        bool facingRight = false;
        bool estadoUpdate = false;

        bool isp1;
        

        Galo(struct GaloStats stats, int _state, bool isp1) { 

            // Stats
            this->stats = stats;

            this->maxHp = stats.hp;
            this->hp = stats.hp;
            this->atk = stats.atk;
            this->def = stats.def;
            this->speed = stats.speed;
            this->peso = stats.peso;
            this->jumpSpeed = -stats.jumpSpd;


            // States
            this->estado = _state;
            this->air = false;

            // Physics
            this->hspeed = 0;
            this->vspeed = 0;
            this->hspeedLimit = this->speed;
            this->vspeedLimit = 10;
            this->hAcc = 0.5;

            star.loadFromFile("sprites\\estrelinhas.png");
            estrelinha.setTexture(star);
            estrelinha.setScale((float)SCREEN_WIDTH / 7680, (float)SCREEN_HEIGHT / 4320);

            this->position = Vector2f(0, 0);
            this->isp1 = isp1;
            if (isp1)
                position.x = SCREEN_WIDTH / 4;
            else
                position.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;

            position.y = floorY;

        }

        void setPosition(Vector2f pos) {
            this->position = pos;
        }

        void resetPosition() {
            if (isp1)
                position.x = SCREEN_WIDTH / 4;
            else
                position.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;

            position.y = floorY;
        }

        // States
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


        // Set Hspeed
        void inline setHspeed(float spd) {
            hspeed = spd;
        }



        int inline getFrames() {
            return frames;
        }

        int getMaxhp() {
            return maxHp;
        }
        int gethp() {
            return hp;
        }
        void sethp(int hp) {
            this->hp = hp;
        }

        virtual void apanhar(Ataques atk, bool direction){


            if (!invunerable) {
              
                hp -= atk.Damage/stats.def;

                // Calculando os impulsos
                atk.createBlood(mainPartSystem);


                vspeed += sin(atk.angle) * atk.KnockBack;
                hspeed += cos(atk.angle) * atk.KnockBack;


                if (!direction) {
                    hspeed *= -1;
                }

                // Tempo de perda de controle sobre o Rooster
                stunFrames = atk.Stun*2;
                stunned = true;

                // Tempo de invulnerabilidade
                invFrames = 30;
                invunerable = true;

                bar->update(hp);

                atk.playSound();

            }


        }
        virtual void apanharByKalsa(Galo * g2, RenderWindow * af) {
           
            float frames = ultimateShot->init2.getElapsedTime().asMilliseconds();
            float maxFrames = ultimateShot->timeLapse2.asMilliseconds();

            if (frames > maxFrames) {
                ultimateShot->getHitted = false;
            }
            
                     
            

            Vector2f nextPosition = position;



            float perc = (float)frames / maxFrames;
            
            if (perc < 0.4) {
                
               
                if(((int)frames)%3 == 0) {
                    g2->facingRight = !g2->facingRight;
                }

             
                g2->position.x += facingRight?
                    ((position.x - g2->position.x + 200) * frames * 2)/maxFrames:
                    ((position.x - g2->position.x - 200) * frames * 2)/maxFrames;
                
                
            }
            else if (perc < 0.7) {
                g2->drawEstrelinhas(af);
                
                int add = 45;

                g2->model.at("Head")->xScl *= -1;
                
                
               
            }
            else {
                if (g2->model.at("Head")->xScl < 0) {
                    g2->model.at("Head")->xScl *= -1;
                }
            }
            
         
        }
        void jump() {

            if ((!stunned || stunFrames < 0) && atacking == NOT_ATTACK) {
                stunned = false;
                if (!air) {
                    vspeed += jumpSpeed;
                    air = true;
                }
            }
        }
        
        void run(bool facingRight) {

            if ((!stunned || stunFrames < 0) && atacking == NOT_ATTACK) {

                estado = RUNNING;
                this->facingRight = facingRight;

                stunned = false;

                float acc = hAcc * ((facingRight) ? 1:-1);

                hspeed = constrain(hspeed + acc, -hspeedLimit, hspeedLimit);

            }
        } 


        virtual void defend() = 0; 

        virtual void defended(Galo& galo2,Ataques * atk,bool facingRight) {
            Ataques* ataque = new Ataques(*atk);
            ataque->Damage *= 0.25;
            ataque->KnockBack *= 0.25;
            apanhar(*ataque, facingRight);
        }

        virtual void highKick() = 0;
        virtual void lowKick() = 0;
        virtual void especial() = 0;

        void show(sf::RenderWindow& window) {


           
            model.draw(window);
            
            for (int i = 0; i < projectiles.size(); i++) {
                if(!projectiles[i].NULO)
                    if (projectiles[i].isTrans)
                        projectiles[i].drawTrans(window);
                    else
                        projectiles[i].draw(window);             
            }
            
                
            if (SHOWDEBUG) {
                for (int i = 0; i < hurtBox.size(); i++) {


                    drawHitBox(window, hurtBox[i], sf::Color(255, 255, 255, 100));

                }

                if (ultimateShot->isAtacking) {
                    drawHitBox(window, ultimateShot->hitbox, sf::Color::Red);
                }

                if (louKick->isAtacking) {
                    drawHitBox(window, louKick->hitbox, sf::Color::Red);
                }

                if (hiKick->isAtacking) {
                    drawHitBox(window, hiKick->hitbox, sf::Color::Red);
                }
                if (isDefending) {
                    drawHitBox(window, defense, sf::Color::Green);
                }

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

        
        virtual void updatePhysics() {

            // Timers
            frames++;

            if (invFrames <= 0) {
                invunerable = false;
            }
            else {
                invFrames--;
            }

            if (stunFrames <= -400) {
                stunned = false;
            }
            else {
                stunFrames--;
            }

            

            // Gravity


            if (position.y < floorY) {
                air = true;
            }



            if (air && !noGravity) {
                vspeed += peso * Gravity / 100;
            }


            /// Meus planos foram realizados !!!
            // Floor Collision

            FloatRect galoBounds = model.getBounds();

            if (position.y > floorY) {
                vspeed = 0;
                position.y = floorY;
                air = false;
            }

            // Wall collision
            
            
            if (position.x > SCREEN_WIDTH - ((model.bounds.width - model.center.x) * abs(model.xScl))) {
                
                if (stunned) {
                    hspeed *= -0.8;
                }
                else {
                    hspeed = 0;
                }

                position.x = SCREEN_WIDTH - ((model.bounds.width - model.center.x) * abs(model.xScl));
            }

            if (position.x < model.center.x * abs(model.xScl)) {
                if (stunned) {
                    hspeed *= -0.8;
                }
                else {
                    hspeed = 0;
                }
                position.x = model.center.x * abs(model.xScl);
            }
            

            if (estado != RUNNING && !stunned) {
                hspeed = 0;
            }

            if (stunned && stunFrames < 30) {
                hspeed *= 0.95;
                vspeed *= 0.98;
            }
            
            if (isPoisoned) {
                hp -= 0.5;
            }



            position.x += hspeed;
            position.y += vspeed;
        }


        virtual void updateAnimations() = 0;

        
        virtual void fatality(RenderWindow* window, Galo* galo2, RectangleShape fundo) {

        }


        virtual void update() {


            updatePhysics();


            // Hurtbox update
            for (int i = 0; i < hurtBox.size(); i++) {

                hurtBox[i].center = model.at(i)->drawPos;
                hurtBox[i].radius = model.at(i)->sprite.getGlobalBounds().width / 2;

            }


            // Projectiles
            // KEKEKEKEKEEKEEKEKKEKEKKEKEKKEKEKEKEEKEKKEKEKEKEKEKEKEKEKKEKEKEKEKEKEKKEK
            /*pare de tentar ajudar e destruir o restp da miinhda vdasidnbhasvgy
            for (int i = 0; i < projectiles.size(); i++) {
                projectiles[i].update();
            }*/


            updateAnimations();


            // Health Bar Update
            bar->update(hp);





            model.pos.x = position.x ;
            model.pos.y = position.y ;

            float resizeScl = (float)SCREEN_WIDTH / 5120;

            model.xScl = 4 * (facingRight ? -1 : 1) * resizeScl;
            model.yScl = 4 * resizeScl;
            model.update();

            estadoUpdate = false;
        }

        void drawEstrelinhas(RenderWindow* window) {

            
            
            
            
            if (frames % 5 == 0) {
                estrelinha.setScale(estrelinha.getScale().x * -1, estrelinha.getScale().y);
            }
           if(estrelinha.getScale().x > 0)
               estrelinha.setPosition(position.x - model.bounds.width/2, position.y - model.bounds.height*1.2);
           else
               estrelinha.setPosition(position.x + model.bounds.width/2, position.y - model.bounds.height*1.2);
            window->draw(estrelinha);

        }
    };

}



#endif