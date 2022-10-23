#ifndef GALO_H_included
#define GALO_H_included

namespace Rooster {

typedef struct{
    sf::Vector2 xCenter;
    int radius;
}HitBox;

class Galo {
    HitBox hitbox;
    int hp;
    int id;
    int atk;
    int def;
    int speed;
    sf::Sprite sprite;

    Galo();





};



}



#endif
