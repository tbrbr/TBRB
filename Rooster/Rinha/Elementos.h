#ifndef ELEMENTOS_H_INCLUDED
#define ELEMENTOS_H_INCLUDED

#include <SFML/Graphics.hpp>
using namespace sf;

enum bodyParts {
    CORPO,
    CABECA,
    RABO,
    ASA_FRENTE,
    ASA_ATRAS,
    PERNA_FRENTE,
    PE_FRENTE,
    PERNA_ATRAS,
    PE_ATRAS,
    BIGODE_FRENTE,
    BIGODE_ATRAS
};

class Element {

public:


    sf::Sprite sprite;

    Vector2f size;
    Vector2f texPos;
    Vector2f position;
    Vector2f center;
    Vector2f attach;
    Vector2f offset;

    int attachId = -1;

    Vector2f scl;

    float angle;

    float otherAngle = 0;

    Vector2f otherPos;

    Element(sf::Texture& text, int xTex, int yTex, int wid, int hei, int xPin, int yPin, int xAttach, int yAttach) {

        sprite.setTexture(text);


        // Retangulo do sprite na textura
        texPos.x = xTex;
        texPos.y = yTex;
        size.x = wid;
        size.y = hei;

        sprite.setTextureRect(sf::IntRect(xTex, yTex, wid, hei));

        // Centro de rotacao do sprite
        center.x = xPin - xTex;
        center.y = yPin - yTex;

        sprite.setOrigin(center.x, center.y);


        // Relative to Center of part this is attached to
        attach.x = xAttach;
        attach.y = yAttach;

        // Angulo e escala
        angle = 0;
        scl.x = 0.25;
        scl.y = 0.25;

        offset.x = 0;
        offset.y = 0;
    }



    void show(sf::RenderWindow& window) {
        sprite.setPosition(position);
        sprite.setRotation(angle + otherAngle);
        sprite.setScale(scl.x, scl.y);
        sprite.setOrigin(center.x, center.y);
        window.draw(sprite);

    }



    /// Updates element position based on the Part it's attached to
    void update(float otherX, float otherY, float otherAng) {

        float fixAngle = 3.141592 * otherAng / 180;

        /// Calculating actualized position...


        position.x = offset.x + otherX + scl.x * attach.x * cos(fixAngle) - scl.y * attach.y * sin(fixAngle);
        position.y = offset.y + otherY + scl.x * attach.x * sin(fixAngle) + scl.y * attach.y * cos(fixAngle);

        otherAngle = otherAng;

    }
};


#endif // ELEMENTOS_H_INCLUDED