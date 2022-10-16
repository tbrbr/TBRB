#ifndef BONE_H_INCLUDED
#define BONE_H_INCLUDED

struct Bone{
    struct SpriteArea sprArea;

    sf::Sprite sprite;

    int id = -1;

    bool hasCenter = false;

    Vector2i center;
    Vector2i otherCenter;

    std::vector<int> dependents;

    int attachId = -1;
    Vector2f attach;

    Vector2f offset;

    Vector2f pos;
    Vector2f otherPos;

    Vector2f drawPos;

    Vector2f counterPos;

    float xScl;
    float yScl;

    float finalXScl;
    float finalYScl;

    float xWholeScl;
    float yWholeScl;
    float xWhole;
    float yWhole;
    float xWholeAttach;
    float yWholeAttach;
    float angWhole;

    Vector2f lastIgnorePos;

    float angle = 0;
    float otherAngle = 0;
    float finalAngle = 0;

    float ignoreOtherAngle = 0;
    float ignoreOtherPos = 0;

    bool hovered = false;
    bool selected = false;

    std::string name;


    int dragNum = 5;
    struct dragCircle drags[5];



    int sliderNum = 0;
    class Slider* sliders[3];

    int textBoxNum = 9;
    struct ValBox boxes[9];


    enum Properties{
        ECenterX,
        ECenterY,
        EAttachX,
        EAttachY,
        EOffsetX,
        EOffsetY,
        EXScl,
        EYScl,
        EAngle
    };


    void init2(struct engineInfo& info){


        name = " ";



        finalXScl = xScl;
        finalYScl = yScl;

        xWholeScl = 1;
        yWholeScl = 1;

        xWhole = info.xWhole;
        yWhole = info.yWhole;

        xWholeAttach = xWhole;
        yWholeAttach = yWhole;

        angWhole = 0;

        lastIgnorePos.x = 0;
        lastIgnorePos.y = 0;



        // Angle
        angle = 0;

        xScl = 0.25;
        yScl = xScl;

        // Relative to Center of part this is attached to
        attach.x = 0;
        attach.y = 0;

        offset.x = 0;
        offset.y = 0;

        center.x = 0;
        center.y = 0;


        // Position
        pos.x = 0;
        pos.y = 0;


        sprArea.init();






        float propX = info.GUI.propBar.x + info.GUI.propBar.propX;


        float propYOff = info.GUI.propBar.pHei;

        float propsY = info.GUI.propBar.y + info.GUI.propBar.propY;

        float boxWid  = info.GUI.propBar.propWid;
        float boxYOff = 0;

        float propHei  = info.GUI.propBar.pHei;

        struct ValBox angBox;
        angBox.init(0, propX, propsY+boxYOff+propYOff*EAngle, boxWid, propHei, angle);
        boxes[EAngle] = angBox;
        boxes[EAngle].label = "Angle";
        boxes[EAngle].labelSide = true;

        struct ValBox xSclBox;
        xSclBox.init(0, propX, propsY+boxYOff+propYOff*EXScl, boxWid, propHei, xScl);
        boxes[EXScl] = xSclBox;
        boxes[EXScl].label = "xScale";
        boxes[EXScl].labelSide = true;


        struct ValBox ySclBox;
        ySclBox.init(0, propX, propsY+boxYOff+propYOff*EYScl, boxWid, propHei, yScl);
        boxes[EYScl] = ySclBox;
        boxes[EYScl].label = "yScale";
        boxes[EYScl].labelSide = true;

        struct ValBox xAttachBox;
        xAttachBox.init(0, propX, propsY+boxYOff+propYOff*EAttachX, boxWid, propHei, attach.x);
        boxes[EAttachX] = xAttachBox;
        boxes[EAttachX].label = "xAttach";
        boxes[EAttachX].labelSide = true;


        struct ValBox yAttachBox;
        yAttachBox.init(0, propX, propsY+boxYOff+propYOff*EAttachY, boxWid, propHei, attach.y);
        boxes[EAttachY] = yAttachBox;
        boxes[EAttachY].label = "yAttach";
        boxes[EAttachY].labelSide = true;


        struct ValBox xOffsetBox;
        xOffsetBox.init(0, propX, propsY+boxYOff+propYOff*EOffsetX, boxWid, propHei, offset.x);
        boxes[EOffsetX] = xOffsetBox;
        boxes[EOffsetX].label = "xOffset";
        boxes[EOffsetX].labelSide = true;


        struct ValBox yOffsetBox;
        yOffsetBox.init(0, propX, propsY+boxYOff+propYOff*EOffsetY, boxWid, propHei, offset.y);
        boxes[EOffsetY] = yOffsetBox;
        boxes[EOffsetY].label = "yOffset";
        boxes[EOffsetY].labelSide = true;


        struct ValBox xCenterBox;
        xCenterBox.init(0, propX, propsY+boxYOff+propYOff*ECenterX, boxWid, propHei, center.x);
        boxes[ECenterX] = xCenterBox;
        boxes[ECenterX].label = "xCenter";
        boxes[ECenterX].labelSide = true;


        struct ValBox yCenterBox;
        yCenterBox.init(0, propX, propsY+boxYOff+propYOff*ECenterY, boxWid, propHei, center.y);
        boxes[ECenterY] = yCenterBox;
        boxes[ECenterY].label = "yCenter";
        boxes[ECenterY].labelSide = true;




        struct dragCircle d1; // Center
        d1.col = Color::White;
        d1.rad = 6;


        struct dragCircle d2; // Position / Offset
        d2.col = Color::Red;
        d2.rad = 9;
        //d2.draggable = false;

        struct dragCircle d3; // Center
        d3.col = Color::Green;
        d3.rad = 6;

        struct dragCircle d4; // Attach
        d4.col = Color::Magenta;
        d4.rad = 6;

        struct dragCircle d5; // Angle
        d5.col = Color(250, 180, 0);
        d5.rad = 6;



        drags[0] = d1;
        drags[1] = d2;
        drags[2] = d3;
        drags[3] = d4;
        drags[4] = d5;
    }

    void init(const sf::Texture* tex, struct engineInfo& info){
        sprite.setTexture(*tex);
        init2(info);
    }


    void init(sf::Texture& tex, struct engineInfo& info){
        sprite.setTexture(tex);
        init2(info);
    }

    void removeAttach(){
        attach.x = 0;
        attach.y = 0;
        attachId = -1;
        angle += otherAngle;
        otherAngle = 0;
    }



    void updateStuffPos(struct engineInfo& info){

        float propX = info.GUI.propBar.x + info.GUI.propBar.propX;


        float propYOff = info.GUI.propBar.pHei;

        float propsY = info.GUI.propBar.y + info.GUI.propBar.propY;

        float boxWid  = info.GUI.propBar.propWid;
        float boxYOff = 0;

        float propHei  = info.GUI.propBar.pHei;

        for(int i = 0; i < textBoxNum; i++){
            boxes[i].updatePosSize(propX, propsY+boxYOff+propYOff*i, boxWid, propHei);
        }

    }

};


#endif // BONE_H_INCLUDED
