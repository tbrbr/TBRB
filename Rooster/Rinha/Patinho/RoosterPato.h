#ifndef ROOSTER_HPP_INCLUDED
#define ROOSTER_HPP_INCLUDED

struct Galinho
{
    float x;
    float y;
    float hspeed;
    float vspeed;
    float vaccel;


    bool isAlive;
};

struct SpriteMap{
    int textureId = -1;
    vector<IntRect> images;
    int imgNumber = 0;

    void addImages(int imgWid, int imgHei, int imgX, int imgY, int imgNumX, int imgNumY, Texture& texture){
        Vector2u size = texture.getSize();
        int texWid = size.x;
        int texHei = size.y;


        if(imgWid < 0 || imgHei < 0){
            return;
        }

        for(int i = 0; i < imgNumY; i++){
            for(int j = 0; j < imgNumX; j++){

                int xx = imgX + imgWid*j;
                int yy = imgY + imgHei*i;

                if(imgX >= 0 && xx + imgWid <= texWid && imgY >= 0 && yy + imgHei <= texHei){
                    IntRect newRect(xx, yy, imgWid, imgHei);
                    images.push_back(newRect);
                    imgNumber++;
                }
            }
        }
    }
};

struct GameInfo
{

    // Texturas
    Texture gun;
    Texture Mapa;
    Texture Mira;
    Texture Galo;
    Texture Light;
    Texture sniper;

    Texture chorro;
    Texture ratoSheet;


    // Sprites
    Sprite sgun;
    Sprite smap;
    Sprite smira;
    Sprite sgalo;
    Sprite sLight;
    Sprite sSniper;

    Sprite sChorro;
    SpriteMap sMapChorro;

    Sprite sRabo;
    SpriteMap sMapRabo;
    Sprite sRato;


    // Fontes
    Font fonte1;


    // Sound Buffer
    SoundBuffer sndBuffer;
    SoundBuffer sndBufferGalo;

    // Sound
    Sound sound;
    Sound soundGalo;



    // Vector dos Roosters
    vector <Galinho> roosters;

    // Coordenadas da Camera

    float viewWidth = SCREEN_WIDTH;
    float viewHeight = SCREEN_HEIGHT;

    float camX = 0;
    float camY = 0;

    float mapWidth = 0;
    float mapHeight = 0;

    bool Shot;

    int counter = 0;

    // Roosters abatidos
    int kills = 0;

    // Vidas
    int maxLives = 10;
    int lives = maxLives;

    // Miss Cooldown
    int missAnimationStart = 0;
    int missAnimationTimer = 0;

    int frames = 0;


    bool windowGrabbed = true;

} ;




#endif // ROOSTER_HPP_INCLUDED
