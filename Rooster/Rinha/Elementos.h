#ifndef ELEMENTOS_H_INCLUDED
#define ELEMENTOS_H_INCLUDED

#include <SFML/Graphics.hpp>
using namespace sf;

struct AnimationKeyFrame {

    float val = 0;


    int frame = 0;

    bool exists = false;

    int id = -1;
    int propertyId = 0;
    int progressionType = 0;

    void init() {
        exists = true;
    }
};

struct Animation {


    const int propertiesNumber = 9;

    // First Access is Bone/Element
    std::vector<std::vector<std::vector<struct AnimationKeyFrame>>> timeline;

    std::vector<std::string> propertyName;

    int framesTotal = 50;
    bool playing = true;
    float playingFrame = 0;
    float playingSpeed = 0.1;
    bool connectLoop = false;

    ~Animation() {
        timeline.clear();
        propertyName.clear();
    }

    void init(std::string filename) {
        std::ifstream file(filename);
        timeline.clear();


        if (file.is_open()) {
            std::string str;
            std::getline(file, str);

            if (str == "2") {
                std::getline(file, str);

                if (str == "Elements") {
                    std::getline(file, str);

                    if (str == "{") {


                        // For each Element
                        std::getline(file, str); // Gets element name

                        std::vector<std::vector<std::vector<struct AnimationKeyFrame>>> elementsPropertiesKeyframes;

                        while (str != "}") {
                            // For each Property
                            std::getline(file, str); // {
                            std::getline(file, str); // Gets property name

                            std::vector<std::vector<struct AnimationKeyFrame>> propertiesKeyframes;

                            while (str != "}") {
                                // For each KeyFrame
                                std::getline(file, str); // {

                                std::vector<struct AnimationKeyFrame> keyframes;

                                std::getline(file, str); // [
                                while (str != "}") {

                                    struct AnimationKeyFrame keyframe;
                                    keyframe.init();

                                    std::getline(file, str); // Val
                                    keyframe.val = std::stof(str);

                                    std::getline(file, str); // Frame
                                    keyframe.frame = std::stoi(str);

                                    std::getline(file, str); // ProgressionType
                                    keyframe.progressionType = std::stoi(str);

                                    std::getline(file, str); // PropertyId
                                    keyframe.propertyId = std::stoi(str);

                                    keyframes.push_back(keyframe);

                                    std::getline(file, str); // ]
                                    std::getline(file, str); // [ or } if end of list
                                }

                                propertiesKeyframes.push_back(keyframes);

                                std::getline(file, str); // Property Name or }

                            }

                            elementsPropertiesKeyframes.push_back(propertiesKeyframes);

                            std::getline(file, str); // } end all elements or Element
                        }

                        timeline = elementsPropertiesKeyframes;

                        std::getline(file, str);

                        if (str == "Frames") {
                            std::getline(file, str);
                            framesTotal = std::stof(str);
                        }

                        if (str == "Speed") {
                            std::getline(file, str);
                            playingSpeed = std::stof(str);
                        }

                    }
                }
                else {
                    return;
                }

            }
            else {
                std::cout << "Animation Unable to Load" << std::endl;
                std::cout << "Animation Version " << str << " Not supported" << std::endl;
            }

        }

    }

    void update() {
        playingFrame += playingSpeed;
        if (playingFrame > framesTotal) {
            playingFrame = 0;
        }
    }

    struct AnimationKeyFrame weightedPropertyMean(struct AnimationKeyFrame p1, struct AnimationKeyFrame p2, float w1) {
        struct AnimationKeyFrame p;
        p.init();

        p = p1;

        float w2 = 1 - w1;

        p.val = p1.val * w1 + p2.val * w2;

        return p;

    }

    struct AnimationKeyFrame getPropertyValue(int boneId, int propertyId, float framePos) {


        int index = -1;


        for (int i = 0; i < timeline[boneId][propertyId].size(); i++) {
            if (timeline[boneId][propertyId][i].frame > framePos) {
                index = i;
                i = timeline[boneId][propertyId].size();
            }
        }




        if (index != -1) {
            if (index != 0 || connectLoop) {


                struct AnimationKeyFrame p = timeline[boneId][propertyId][index];


                struct AnimationKeyFrame pPrev;

                float frameDif = p.frame - pPrev.frame;
                float frameRel = framePos - pPrev.frame;

                if (connectLoop && index == 0) {
                    pPrev = timeline[boneId][propertyId][timeline[boneId][propertyId].size() - 1];
                    frameDif = p.frame - (pPrev.frame - framesTotal);
                    frameRel = framePos - (pPrev.frame - framesTotal);
                }
                else {
                    pPrev = timeline[boneId][propertyId][index - 1];
                    frameDif = p.frame - pPrev.frame;
                    frameRel = framePos - pPrev.frame;
                }




                if (frameDif == 0) {
                    return timeline[boneId][propertyId][index];
                }



                float perc = 1 - (frameRel / frameDif);


                if (pPrev.progressionType == 0) {

                    float w1 = perc;
                    return weightedPropertyMean(pPrev, p, w1);

                }
                else if (pPrev.progressionType == 1) {

                    float w1 = perc * perc;
                    return weightedPropertyMean(pPrev, p, w1);

                }
                else if (pPrev.progressionType == 2) {

                    float w1 = 1 - ((1 - perc) * (1 - perc));
                    return weightedPropertyMean(pPrev, p, w1);

                }
                else {
                    float w1 = 1;
                    return weightedPropertyMean(pPrev, p, w1);
                }


            }
            else {
                //println("llew34");

                return timeline[boneId][propertyId][index];
            }
        }
        else {
            /// Here i should use the base values
            int framesNum = timeline[boneId][propertyId].size() - 1;
            if (framesNum >= 0) {

                if (connectLoop) {
                    struct AnimationKeyFrame p = timeline[boneId][propertyId][0];


                    struct AnimationKeyFrame pPrev = timeline[boneId][propertyId][timeline[boneId][propertyId].size() - 1];

                    float frameDif = p.frame - (pPrev.frame - framesTotal);
                    float frameRel = framePos - pPrev.frame;






                    if (frameDif == 0) {
                        return timeline[boneId][propertyId][index];
                    }



                    float perc = 1 - (frameRel / frameDif);


                    if (pPrev.progressionType == 0) {

                        float w1 = perc;
                        return weightedPropertyMean(pPrev, p, w1);

                    }
                    else if (pPrev.progressionType == 1) {

                        float w1 = perc * perc;
                        return weightedPropertyMean(pPrev, p, w1);

                    }
                    else if (pPrev.progressionType == 2) {

                        float w1 = 1 - ((1 - perc) * (1 - perc));
                        return weightedPropertyMean(pPrev, p, w1);

                    }
                    else {
                        float w1 = 1;
                        return weightedPropertyMean(pPrev, p, w1);
                    }
                }

                return timeline[boneId][propertyId][framesNum];
            }
        }


        struct AnimationKeyFrame p;
        p.exists = false;
        return p;


    }
};




struct SpriteArea {
    sf::IntRect texRect;

    int imgTotal = 1;
    int imgIndex = 0;

    Vector2i center;

    void init() {
        texRect.left = 0;
        texRect.top = 0;
        texRect.width = 0;
        texRect.height = 0;

        center.x = 0;
        center.y = 0;
    }

    void draw(RenderWindow& window, float scl) {
        RectangleShape select(Vector2f(texRect.width * scl, texRect.height * scl));
        select.setPosition(texRect.left * scl, texRect.top * scl);
        select.setFillColor(Color(100, 100, 100, 0));
        select.setOutlineColor(Color(255));
        select.setOutlineThickness(4);

        window.draw(select);
    }

    void draw(RenderWindow& window, float scl, Color fillColor) {
        RectangleShape select(Vector2f(texRect.width * scl, texRect.height * scl));
        select.setPosition(texRect.left * scl, texRect.top * scl);
        select.setFillColor(fillColor);
        select.setOutlineColor(Color(255));
        select.setOutlineThickness(4);

        window.draw(select);
    }
};





struct Element {
private:
    // Base Properties
    Vector2i baseCenter;
    Vector2f baseAttach;
    Vector2f baseOffset;
    float baseXScl;
    float baseYScl;
    float baseAngle;
    int baseAttachId = -1;

    struct SpriteArea baseSprArea;


public:
    // Changeable Properties
    Vector2i center;
    Vector2f attach;
    Vector2f offset;

    float xScl;
    float yScl;
    float angle = 0;

    int attachId = -1;



    // Extra stuff
    struct SpriteArea sprArea;
    sf::Sprite sprite;
    Vector2f pos;
    Vector2f drawPos;
    int id = -1;

    float finalXScl;
    float finalYScl;

    float otherAngle = 0;
    float finalAngle = 0;

    float xWholeScl = 1;
    float yWholeScl = 1;
    float xWhole = 0;
    float yWhole = 0;
    float xWholeAttach = 0;
    float yWholeAttach = 0;
    float angWhole = 0;

    std::string name = "";

    bool valid = false;

    void init(sf::Texture* t) {
        sprite.setTexture(*t);

        sprite.setTextureRect(sprArea.texRect);
    }


    SpriteArea getBaseArea() {
        return baseSprArea;
    }

    Vector2i getBaseCenter() {
        return baseCenter;
    }

    Vector2f getBaseAttach() {
        return baseAttach;
    }

    Vector2f getBaseOffset() {
        return baseOffset;
    }

    Vector2f getBaseScale() {
        return Vector2f(baseXScl, baseYScl);
    }

    float getBaseAngle() {
        return baseAngle;
    }





    void setBaseProperties(Vector2i center, Vector2f attach, Vector2f offset, float xScl, float yScl, float angle, int attachId, struct SpriteArea sprArea) {
        this->center = center;
        this->baseCenter = center;

        this->attach = attach;
        this->baseAttach = attach;

        this->offset = offset;
        this->baseOffset = offset;

        this->xScl = xScl;
        this->baseXScl = xScl;

        this->yScl = yScl;
        this->baseYScl = yScl;

        this->angle = angle;
        this->baseAngle = angle;

        this->sprArea = sprArea;
        this->baseSprArea = sprArea;

        this->attachId = attachId;
        this->baseAttachId = attachId;

        sprite.setTextureRect(this->sprArea.texRect);

        valid = true;
    }

    void resetToBase() {
        center = baseCenter;
        attach = baseAttach;
        offset = baseOffset;
        xScl = baseXScl;
        yScl = baseYScl;
        angle = baseAngle;
        sprArea = baseSprArea;
        attachId = baseAttachId;
    }


};

class ElementHandle {

    int id = -1;
    std::vector<struct Element*>& allBones;

public:



    struct Element* bone;

    ~ElementHandle() {
        allBones.clear();
        delete bone;
    }

    ElementHandle(std::vector<struct Element*>& _allBones, int id) : allBones(_allBones) {
        this->id = id;
        this->bone = allBones[id];
    }


    void draw(sf::RenderWindow& window) {


        bone->sprite.setTextureRect(bone->sprArea.texRect);

        bone->sprite.setPosition(bone->drawPos);

        bone->sprite.setOrigin((Vector2f)bone->center);

        float sclFixAng = bone->finalAngle;
        if (bone->finalXScl < 0) {
            sclFixAng *= -1;
        }
        if (bone->finalYScl < 0) {
            sclFixAng *= -1;
        }

        bone->sprite.setScale(bone->finalXScl, bone->finalYScl);
        bone->sprite.setRotation(sclFixAng);

        window.draw(bone->sprite);
    }

    void update() {
        if (bone->attachId != -1) {
            const struct Element b = *allBones[bone->attachId];


            bone->finalAngle = bone->angle + b.finalAngle;

            bone->finalXScl = bone->xScl * bone->xWholeScl;
            bone->finalYScl = bone->yScl * bone->yWholeScl;



            float attachXRotated = b.finalXScl * bone->attach.x;
            float attachYRotated = b.finalYScl * bone->attach.y;


            // Transforms from degrees to radians
            float correctedAngle = b.finalAngle;
            if (b.finalXScl < 0) {
                correctedAngle *= -1;
            }
            if (b.finalYScl < 0) {
                correctedAngle *= -1;
            }


            correctedAngle = 3.141592 * correctedAngle / 180;




            /// Calculating the attach based on the otherAngle
            attachYRotated = b.finalXScl * sin(correctedAngle) * bone->attach.x + b.finalYScl * cos(correctedAngle) * bone->attach.y;
            attachXRotated = b.finalXScl * cos(correctedAngle) * bone->attach.x - b.finalYScl * sin(correctedAngle) * bone->attach.y;

            float rotOCenterX = b.finalXScl * cos(correctedAngle) * b.center.x - b.finalYScl * sin(correctedAngle) * b.center.y;
            float rotOCenterY = b.finalXScl * sin(correctedAngle) * b.center.x + b.finalYScl * cos(correctedAngle) * b.center.y;

            float rotX = b.drawPos.x - (rotOCenterX);
            float rotY = b.drawPos.y - (rotOCenterY);

            // Purple attach pin position
            float xx = rotX + attachXRotated;
            float yy = rotY + attachYRotated;



            /// Position equals the attach minus center plus offset
            bone->pos.x = xx - bone->center.x * bone->finalXScl + bone->offset.x * b.xWholeScl;
            bone->pos.y = yy - bone->center.y * bone->finalYScl + bone->offset.y * b.yWholeScl;

            bone->drawPos.x = bone->pos.x + bone->center.x * bone->finalXScl;
            bone->drawPos.y = bone->pos.y + bone->center.y * bone->finalYScl;

        }
        else {



            bone->finalAngle = bone->angle;
            bone->finalXScl = bone->xScl * bone->xWholeScl;
            bone->finalYScl = bone->yScl * bone->yWholeScl;

            bone->pos.x = bone->xWhole - bone->center.x * bone->finalXScl;
            bone->pos.y = bone->yWhole - bone->center.y * bone->finalYScl;


            bone->drawPos.x = bone->pos.x + bone->center.x * bone->finalXScl;
            bone->drawPos.y = bone->pos.y + bone->center.y * bone->finalYScl;
        }
    }

};



struct Model {
    std::vector<Element*> allBones;
    std::vector<ElementHandle*> allHandles;
    std::vector<int> drawOrder;
    std::vector<int> executeOrder;

    sf::Texture* tex;

    Vector2f pos;
    Vector2f angle;
    float xScl = 1;
    float yScl = 1;

    bool valid = false;

    std::map<std::string, int> boneMap;

    IntRect bounds;
    Vector2f center;


    void setBounds(IntRect bounds, Vector2f center) {
        this->bounds = bounds;
        this->center = center;
    }

    void autoSetBounds(Element* mainBody, Element* floorPart, Element* ceilingPart) {

        if (valid) {

            resetToBase();
            update();

            float centerX = mainBody->drawPos.x;
            float centerY = mainBody->drawPos.y;

            float wid = mainBody->sprArea.texRect.width * mainBody->finalXScl;

            float bottomY = floorPart->pos.y + floorPart->sprArea.texRect.height * floorPart->finalYScl;
            float topY    = ceilingPart->pos.y;



            bounds.top = 0;
            bounds.left = 0;
            bounds.height = (bottomY - topY) / yScl;
            bounds.width = wid / xScl;

            center.x = wid / 2;
            center.y = centerY - topY;
        }


    }




    void draw(sf::RenderWindow& window) {
        /// Bones Drawing
        if (valid) {
            for (int i = 0; i < drawOrder.size(); i++) {
                allHandles[drawOrder[i]]->draw(window);
            }

            drawBounds(window);
        }
    }

    void drawBounds(sf::RenderWindow& window) {

        float xSclAbs = abs(xScl);
        float ySclAbs = abs(yScl);

        sf::RectangleShape rect(Vector2f(bounds.width * xSclAbs, bounds.height * ySclAbs));
        rect.setPosition(pos.x , pos.y - (bounds.height - center.y) * ySclAbs);
        rect.setOrigin(center.x*xSclAbs, center.y*ySclAbs);

        rect.setFillColor(Color(0, 0, 0, 0));
        rect.setOutlineColor(Color(0, 0, 0));
        rect.setOutlineThickness(4);
        window.draw(rect);

    }

    void update() {
        /// Bones Update
        if (valid) {
            for (int i = 0; i < executeOrder.size(); i++) {
                allHandles[executeOrder[i]]->bone->xWholeScl = xScl;
                allHandles[executeOrder[i]]->bone->yWholeScl = yScl;
                allHandles[executeOrder[i]]->bone->xWhole = pos.x;
                allHandles[executeOrder[i]]->bone->yWhole = pos.y - (bounds.height - center.y)*yScl;

                allHandles[executeOrder[i]]->update();
            }
        }
    }

    FloatRect getBounds() {
        return FloatRect(pos.x - center.x*xScl, pos.y - center.y*yScl, bounds.width*xScl, bounds.height*yScl);
    }

    Element* at(int id) {

        return allBones[id];
    }

    Element* at(std::string name) {
        int id = boneMap.at(name);
        return allBones[id];
    }

    void resetToBase() {
        for (int i = 0; i < allBones.size(); i++) {
            allBones[i]->resetToBase();
        }
    }

    void updateWithAnimation(struct Animation& anim) {

        float fPos = anim.playingFrame;

        for (int i = 0; i < anim.timeline.size(); i++) {

            if (allBones.size() > i) {

                struct AnimationKeyFrame p;
                p = anim.getPropertyValue(i, 0, fPos);

                if (p.exists) {
                    allBones[i]->center.x = p.val;
                }

                p = anim.getPropertyValue(i, 1, fPos);

                if (p.exists) {
                    allBones[i]->center.y = p.val;
                }

                p = anim.getPropertyValue(i, 2, fPos);

                if (p.exists) {
                    allBones[i]->attach.x = p.val;
                }

                p = anim.getPropertyValue(i, 3, fPos);

                if (p.exists) {
                    allBones[i]->attach.y = p.val;
                }

                p = anim.getPropertyValue(i, 4, fPos);

                if (p.exists) {
                    allBones[i]->offset.x = p.val;
                }

                p = anim.getPropertyValue(i, 5, fPos);

                if (p.exists) {
                    allBones[i]->offset.y = p.val;
                }

                p = anim.getPropertyValue(i, 6, fPos);

                if (p.exists) {
                    allBones[i]->xScl = p.val;
                }

                p = anim.getPropertyValue(i, 7, fPos);

                if (p.exists) {
                    allBones[i]->yScl = p.val;
                }


                p = anim.getPropertyValue(i, 8, fPos);

                if (p.exists) {
                    allBones[i]->angle = p.val;
                }
            }


        }

    }

    void loadModel(std::string filename) {
        std::ifstream file(filename);

        println("Loading Model");
        if (file.is_open()) {


            std::string line;
            std::getline(file, line);

            int version = std::stoi(line);


            println("Checking Version");

            if (version == 1) {
                println("Model Version " << version);
                allBones.clear();
                allHandles.clear();
                drawOrder.clear();
                executeOrder.clear();

                std::getline(file, line);

                println("Ordem de Execucao");
                if (line == "Execution Order") {
                    std::getline(file, line);
                    if (line == "{") {
                        std::getline(file, line);
                        while (line != "}") {
                            executeOrder.push_back(std::stoi(line));
                            std::getline(file, line);
                        }
                    }
                }
                std::getline(file, line);

                println("Ordem de desenho");
                if (line == "Draw Order") {
                    std::getline(file, line);
                    if (line == "{") {
                        std::getline(file, line);
                        while (line != "}") {
                            drawOrder.push_back(std::stoi(line));
                            std::getline(file, line);
                        }
                    }
                }

                std::getline(file, line);


                println("Carregando Elementos");
                if (line == "Elements") {
                    std::getline(file, line);
                    if (line == "{") {
                        std::getline(file, line);
                        while (line != "}") {


                            int id = std::stoi(line);

                            println("Loading Element " << id);

                            std::getline(file, line);
                            std::string name = "";
                            if (line != "*") {
                                name = line;
                            }

                            println("Element Name " << name);

                            bool deleted = false;

                            struct Element* newBone = new struct Element;
                            newBone->init(tex);

                            Vector2f center;
                            Vector2f attach;
                            Vector2f offset;
                            float xScl = 0;
                            float yScl = 0;
                            float angle = 0;
                            int attachId = -1;
                            struct SpriteArea sprArea;
                            sprArea.init();


                            std::getline(file, line);
                            if (line == "[") {
                                float fVal = 0;
                                int iVal = 0;
                                std::getline(file, line);
                                fVal = std::stof(line);

                                center.x = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                center.y = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                attach.x = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                attach.y = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                offset.x = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                offset.y = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                xScl = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                yScl = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                angle = fVal;

                                /// Atach Id is int
                                std::getline(file, line);
                                iVal = std::stof(line);

                                attachId = iVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                sprArea.texRect.left = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                sprArea.texRect.top = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                sprArea.texRect.width = fVal;

                                std::getline(file, line);
                                fVal = std::stof(line);

                                sprArea.texRect.height = fVal;

                                std::getline(file, line);

                                boneMap[name] = id;

                            }
                            else {
                                deleted = true;

                            }


                            std::getline(file, line);


                            newBone->setBaseProperties((Vector2i)center, attach, offset, xScl, yScl, angle, attachId, sprArea);
                            newBone->name = name;


                            allBones.push_back(newBone);

                        }
                    }

                }






                for (int i = 0; i < allBones.size(); i++) {
                    ElementHandle* newBoneHandle = new ElementHandle(allBones, i);
                    allHandles.push_back(newBoneHandle);
                }


                std::cout << "Sucesso" << std::endl;

            }
            else {
                std::cout << "Model Version not supported" << std::endl;
            }

        }

        file.close();



        valid = true;
    }

};






#endif // ELEMENTOS_H_INCLUDED
