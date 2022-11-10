#ifndef PATINHO_HPP_INCLUDED
#define PATINHO_HPP_INCLUDED

#include <math.h>
#include <sstream>
#include <vector>

using namespace std;
using namespace sf;


#include "RoosterPato.h"
#include "Fps.h"


float randF(float range = 1) {
    int precision = 10000;
    return range * (float)(rand() % precision) / precision;
}

float randRange(float min, float max) {
    return randF(max - min) + min;
}


/// Cria novos Roosters
Galinho newRooster(GameInfo& info)
{

    Galinho newRooster;

    newRooster.x = rand() % (int)(info.mapWidth - info.viewWidth)  + info.viewHeight;
    newRooster.y = info.mapHeight;

    newRooster.vspeed = (-(float)info.kills/20) - 8;

    newRooster.hspeed = (float)((rand()%4)-2);

    newRooster.vaccel = 0.03;

    return newRooster;
}

Particle newParticle(float x, float y, float hspd, float vspd) {
    Particle newParticle;

    newParticle.x = x;
    newParticle.y = y;

    newParticle.hspeed = hspd;
    newParticle.vspeed = vspd;

    return newParticle;
}

void addParticle(GameInfo& info, float x, float y, float hspd, float vspd){
    info.particles.push_back(newParticle(x, y, hspd, vspd));
}

void addParticle(GameInfo& info, Particle part){
    info.particles.push_back(part);
}


/// Cria e Adiciona novos Roosters no vector
void addRooster(GameInfo& info)
{
    info.roosters.push_back(newRooster(info));
}

void SpriteInit(GameInfo& info,RenderWindow& window)
{
    /// Inicializando as texturas
    info.Mapa.loadFromFile("sprites/mapa.png");
    info.gun.loadFromFile("sprites/gun.png");
    info.Galo.loadFromFile("sprites/galo.png");
    info.Light.loadFromFile("sprites/muzzleF.png");
    info.sniper.loadFromFile("sprites/oldSniper.png");
    info.ratoSheet.loadFromFile("sprites/ratShopSheet.png");

    info.chorro.loadFromFile("sprites/chorro.png");

    /// Criando os sprites
    info.sgun.setTexture(info.gun);
    info.smap.setTexture(info.Mapa);

    
   
    info.sgalo.setTexture(info.Galo);
    info.sLight.setTexture(info.Light);
    info.sSniper.setTexture(info.sniper);

    info.sChorro.setTexture(info.chorro);
    info.sMapChorro.addImages(32, 40, 0, 0, 2, 1, info.chorro.getSize());

    info.sRabo.setTexture(info.ratoSheet);
    info.sMapRabo.addImages(12, 16, 0, 38, 6, 2, info.ratoSheet.getSize());

    info.sRato.setTexture(info.ratoSheet);
    info.sRato.setTextureRect(IntRect(32, 0, 32, 38));

    /// Carregando fontes
    info.fonte1.loadFromFile("fonts/Daydream.ttf");


    /// Sons
    info.sndBuffer.loadFromFile("sounds/gunshot.wav");
    info.sndBufferGalo.loadFromFile("sounds/galoDeath.ogg");

    info.sound.setBuffer(info.sndBuffer);
    info.soundGalo.setBuffer(info.sndBufferGalo);


    // Ajustando os sprites
    info.sgun.scale(0.8,0.8);
    info.sSniper.setScale(4, 4);

    info.sRabo.setScale(4, 4);
    info.sRato.setScale(4, 4);

    info.sChorro.setScale(3, 3);

    info.sgun.setPosition(
        SCREEN_WIDTH / 2 - info.sgun.getGlobalBounds().width/2 + SCREEN_WIDTH/5,
        SCREEN_HEIGHT - info.sgun.getGlobalBounds().height
    );
    info.sLight.setPosition(
        SCREEN_WIDTH / 2 - info.sgun.getGlobalBounds().width / 2 + SCREEN_WIDTH / 7,
        SCREEN_HEIGHT - info.sgun.getGlobalBounds().height
    );


}

void gamePlay(GameInfo& info, RenderWindow& window, Event e)
{   
    int newMousePositionX = e.mouseMove.x;
    int newMousePositionY = e.mouseMove.y;

    Vector2u pos = window.getSize();

    int mainMousePositionX = pos.x/2;
    int mainMousePositionY = pos.y/2;

    int xDif =  newMousePositionX - mainMousePositionX;
    int yDif =  newMousePositionY - mainMousePositionY;


    if (xDif != 0) {
        info.camX += xDif * info.sensi;
    }


    if (yDif != 0) {
        info.camY += yDif * info.sensi;
    }
  


    if(info.camX < 0)
        info.camX = 0;
    if(info.camX > info.mapWidth - info.viewWidth)
        info.camX = info.mapWidth - info.viewWidth;
    if(info.camY < 0)
        info.camY = 0;
    if(info.camY > info.mapHeight - info.viewHeight)
        info.camY = info.mapHeight - info.viewHeight;

    Mouse::setPosition(Vector2i {mainMousePositionX,mainMousePositionY},window);
}

void closeWindow(RenderWindow& window, GameInfo& info)
{

    if(info.windowGrabbed)
    {
        window.setMouseCursorGrabbed(false);
        window.setMouseCursorVisible(true);
        info.windowGrabbed = false;
    }
    else
    {
        window.setMouseCursorGrabbed(true);
        window.setMouseCursorVisible(false);
        info.windowGrabbed = true;
    }

}
void shoot(GameInfo& info)
{

    info.sound.play();
    info.Shot = true;



    int miraX = SCREEN_WIDTH/2 + info.camX;
    int miraY = SCREEN_HEIGHT/2 + info.camY;


    int roosterNumber = info.roosters.size();

    for(int i = 0; i < roosterNumber; i++)
    {
        Galinho thisRooster = info.roosters.at(i);
        int xx = thisRooster.x;
        int yy = thisRooster.y;



        if(miraX > xx && miraX < xx + info.sgalo.getGlobalBounds().width &&
                miraY > yy && miraY < yy + info.sgalo.getGlobalBounds().height)
        {
            info.kills++;

            float val = 1 + ((float)(rand()%100) - 50)/200;

            info.soundGalo.setPitch(val);
            info.soundGalo.play();

            int partNum = rand() % 40 + 400;
            int margin = 10;
            for (int j = 0; j < partNum; j++) {
                float partX = xx + randRange(margin, info.sgalo.getGlobalBounds().width - margin);
                float partY = yy + randRange(margin, info.sgalo.getGlobalBounds().height - margin);
                float partHspd = randRange(-3, 3);
                float partVspd = randRange(-3, 3);
                Particle part = newParticle(partX, partY, partHspd, partVspd);
                part.isStuck = (rand() % 6 == 0) ? true : false;
                part.life = rand() % 300 + 400;
                addParticle(info, part);
            }

            if(sqrt(info.kills) > info.roosters.size()){
                addRooster(info);
            }
            info.roosters.at(i) = newRooster(info);
        }
    }

}

void updateInfo(GameInfo& info, RenderWindow& window)
{

    /// Updating Rooster
    int roosterNumber = info.roosters.size();

    for(int i = 0; i < roosterNumber; i++)
    {

        Galinho thisRooster = info.roosters.at(i);

        thisRooster.vspeed += thisRooster.vaccel;

        thisRooster.x += thisRooster.hspeed;
        thisRooster.y += thisRooster.vspeed;

        float minX = info.viewWidth/2;
        float maxX = + info.mapWidth - (info.viewWidth)/2 - info.sgalo.getGlobalBounds().width;

        if(thisRooster.x < minX){
            thisRooster.x = minX;
            thisRooster.hspeed *=  -1;
        } else if (thisRooster.x > maxX){
            thisRooster.x = maxX;
            thisRooster.hspeed *= -1;
        }


        if(thisRooster.vspeed > 0 && thisRooster.y > info.mapHeight){
            thisRooster = newRooster(info);
            info.lives--;

            /// Animacao do Cachorro
            if(!(info.missAnimationTimer > 0)){
                info.missAnimationStart = 30;
                info.missAnimationTimer = 60;
            } else if(info.missAnimationTimer > 30){
                info.missAnimationTimer = 60;
            } else {
                info.missAnimationStart = 30 - info.missAnimationTimer;
                info.missAnimationTimer = 60;
            }


            /// Gameover
            if(info.lives < 1){
            }
        }
        for (int i = 0; i < info.particles.size(); i++) {
            if (info.particles.at(i).isAlive) {
                info.particles.at(i).update();
            }
            else {
                info.particles.erase(info.particles.begin() + i);
                i--;
            }

        }

        info.roosters.at(i) = thisRooster;
    }

    /// Updating gun cooldown
    if(info.counter == 20)
    {
        info.counter = -1;
        info.Shot = false;
    }

    info.counter++;

    /// Miss timer
    if(info.missAnimationStart > 0){
        info.missAnimationStart--;
    } else if(info.missAnimationTimer > 0){
        info.missAnimationTimer--;
    }

    info.frames++;

}

void drawStuff(GameInfo& info, RenderWindow& window){


    // Drawing Map
    info.smap.setPosition(-info.camX, -info.camY);
    window.draw(info.smap);

    int partNum = info.particles.size();
    for (int i = 0; i < partNum; i++) {
        info.particles.at(i).draw(info.camX, info.camY, window);
    }

   // Drawing all Roosters
    int roosterNumber = info.roosters.size();

    for(int i = 0; i < roosterNumber; i++)
    {

        Galinho thisRooster = info.roosters.at(i);

        info.sgalo.setPosition(thisRooster.x - info.camX,
                               thisRooster.y - info.camY);

        window.draw(info.sgalo);
    }

    // Drawing shot light
    if(info.Shot)
        window.draw(info.sLight);

    // Drawing Gun
    window.draw(info.sgun);

    int miraX = SCREEN_WIDTH / 2 + info.camX;
    int miraY = SCREEN_HEIGHT / 2 + info.camY;

   
    info.smira.draw(&window);
   // window.draw(info.smira.s);

    // Drawing Cachorro
    if(info.missAnimationTimer > 0){

        float chorroY = 0;
        float chorroHei = info.sChorro.getGlobalBounds().height;

        if(info.missAnimationStart > 0 || info.missAnimationTimer > 30){
            chorroY = ((float)info.missAnimationStart/30)*chorroHei;
        } else {
            chorroY = ((float)(30 - info.missAnimationTimer)/30)*chorroHei;
        }


        info.sChorro.setPosition(0, chorroY + info.viewHeight - chorroHei);


        info.sChorro.setTextureRect(info.sMapChorro.images.at((info.frames%10)/5));

        window.draw(info.sChorro);
    }


    info.sRabo.setPosition(12*6, 10*4);
    info.sRabo.setTextureRect(info.sMapRabo.images.at(info.sMapRabo.imgNumber*((float)(info.frames % 100)) / 100));
    window.draw(info.sRabo);

    window.draw(info.sRato);


    if(!info.windowGrabbed){
        sf::Vector2f rectSize = (sf::Vector2f) window.getSize();
        sf::RectangleShape rectangle = sf::RectangleShape(rectSize);

        rectangle.setFillColor(sf::Color(0, 0, 0, 200));

        window.draw(rectangle);
    }
}



#endif // PATINHO_HPP_INCLUDED
