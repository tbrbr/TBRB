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

struct Aim {
public:
    RectangleShape aim[4];
    RectangleShape px = RectangleShape(Vector2f(1, 1));
    int size;

    Aim(Vector2f _size, int spaceBetween, Color color = Color::Green) {

        size = _size.x * 2 + spaceBetween;

        for (int i = 0; i < 4; i++)
            aim[i].setFillColor(color);
        px.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

        px.setFillColor(color);

        aim[0].setSize(Vector2f(_size.x, 2));
        aim[1].setSize(Vector2f(_size.x, 2));
        aim[2].setSize(Vector2f(2, _size.y));
        aim[3].setSize(Vector2f(2, _size.y));

        aim[0].setPosition(SCREEN_WIDTH / 2 - _size.x - spaceBetween, SCREEN_HEIGHT / 2);//13
        aim[1].setPosition(SCREEN_WIDTH / 2 + spaceBetween, SCREEN_HEIGHT / 2);//22

        aim[2].setPosition(SCREEN_WIDTH / 2 - 1, SCREEN_HEIGHT / 2 - _size.y - spaceBetween + 1);//cima
        aim[3].setPosition(SCREEN_WIDTH / 2 - 1 , SCREEN_HEIGHT / 2 + spaceBetween);//baixo

    }

    void draw(RenderWindow* window) {
        for (int i = 0; i < 4; i++)
            window->draw(aim[i]);
        window->draw(px);
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
    Aim smira = Aim(Vector2f(10, 10), 6, Color::Red);
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
