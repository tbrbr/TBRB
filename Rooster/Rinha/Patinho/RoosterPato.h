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




struct Particle
{
    float x = 0;
    float y = 0;
    float hspeed = 0;
    float vspeed = 0;
    float vaccel = 0.2;

    Color col = Color::Red;

    int life = 0;
    bool isStuck = false;


    bool isAlive = true;

    void draw(float camX, float camY, RenderWindow& window) {

        RectangleShape rect(Vector2f(5, 5));
        rect.setFillColor(col);
        rect.setPosition(x - camX, y - camY);

        window.draw(rect);
    }

    void update() {

        if (!isStuck) {
            if (rand() % 1000 == 0) {
                isStuck = true;
            }
            vspeed += vaccel;
            x += hspeed;
            y += vspeed;
        }
        else if (rand() % 200 == 0) {
            vspeed += vaccel;
            x += hspeed / 10;
            y += vspeed / 10;
        }

        life--;

        if (life < 0) {
            isAlive = false;
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
    Texture border;

    // Sprites
    Sprite sgun;
    Sprite smap;
    Aim smira = Aim(Vector2f(10, 10), 6, Color::Color(255, 0, 0));
    Sprite sgalo;
    Sprite sLight;
    Sprite sSniper;

    Sprite sChorro;
    SpriteMap sMapChorro;

    Sprite sRabo;
    SpriteMap sMapRabo;
    Sprite sRato;

    Sprite sBorder;

    Sprite sTile;


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

    /// Vector das Particles
    vector <Particle> particles;

    // Coordenadas da Camera

    float viewWidth = SCREEN_WIDTH;
    float viewHeight = SCREEN_HEIGHT;

    float camX = 0;
    float camY = 0;

    float mapWidth = 0;
    float mapHeight = 0;

    bool Shot;
    float sensi = 1;
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

    ~GameInfo() {
        particles.clear();
        roosters.clear();
    }

};

#endif // ROOSTER_HPP_INCLUDED
