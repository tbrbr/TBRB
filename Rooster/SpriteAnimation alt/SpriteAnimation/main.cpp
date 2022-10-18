#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <map>


#define FRAMERATE_LIMIT 60
#define println(x) std::cout << x << std::endl



using namespace sf;


sf::Font font;


#include "Engine.h"

#include "Galo.h"

#include "GUI.h"

#include "Bone.h"

#include "BoneHandle.h"

#include "TimelineManager.h"

#include "BoneManager.h"

struct AnimationKeyFrame{

    float val = 0;


    int frame = 0;

    bool exists = false;

    int id = -1;
    int propertyId = 0;
    int progressionType = 0;

    void init(){
        exists = true;
    }
};

struct Animation{


    const int propertiesNumber = 9;

    // First Access is Bone/Element
    std::vector<std::vector<std::vector<struct AnimationKeyFrame>>> timeline;

    std::vector<std::string> propertyName;

    int framesTotal = 50;
    bool playing = true;
    float playingFrame = 0;
    float playingSpeed = 0.1;
    bool connectLoop = false;

    void init(std::string filename){
        std::ifstream file(filename);
        timeline.clear();


        if(file.is_open()){
            std::string str;
            std::getline(file, str);

            if(str == "2"){
                std::getline(file, str);

                if(str == "Elements"){
                    std::getline(file, str);

                    if(str == "{"){


                        // For each Element
                        std::getline(file, str); // Gets element name

                        std::vector<std::vector<std::vector<struct AnimationKeyFrame>>> elementsPropertiesKeyframes;

                        while(str != "}"){
                            // For each Property
                            std::getline(file, str); // {
                            std::getline(file, str); // Gets property name

                            std::vector<std::vector<struct AnimationKeyFrame>> propertiesKeyframes;

                            while(str != "}"){
                                // For each KeyFrame
                                std::getline(file, str); // {

                                std::vector<struct AnimationKeyFrame> keyframes;

                                std::getline(file, str); // [
                                while(str != "}"){

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

                        if(str == "Frames"){
                            std::getline(file, str);
                            framesTotal  = std::stof(str);
                        }

                        if(str == "Speed"){
                            std::getline(file, str);
                            playingSpeed = std::stof(str);
                        }

                    }
                } else {
                    return;
                }

            } else {
                std::cout << "Animation Unable to Load" << std::endl;
                std::cout << "Animation Version " << str << " Not supported" << std::endl;
            }

        }




    }

    void update(){
        playingFrame += playingSpeed;
        if(playingFrame > framesTotal){
            playingFrame = 0;
        }
    }

    struct AnimationKeyFrame weightedPropertyMean(struct AnimationKeyFrame p1, struct AnimationKeyFrame p2, float w1){
        struct AnimationKeyFrame p;
        p.init();

        p = p1;

        float w2 = 1 - w1;

        p.val = p1.val * w1 + p2.val * w2;

        return p;

    }

    struct AnimationKeyFrame getPropertyValue(int boneId, int propertyId, float framePos){


        int index = -1;


        for(int i = 0; i < timeline[boneId][propertyId].size(); i++){
            if(timeline[boneId][propertyId][i].frame > framePos){
                index = i;
                i = timeline[boneId][propertyId].size();
            }
        }




        if(index != -1){
            if(index != 0 || connectLoop){


                struct AnimationKeyFrame p = timeline[boneId][propertyId][index];


                struct AnimationKeyFrame pPrev;

                float frameDif = p.frame - pPrev.frame;
                float frameRel = framePos - pPrev.frame;

                if(connectLoop && index == 0){
                    pPrev = timeline[boneId][propertyId][timeline[boneId][propertyId].size()-1];
                    frameDif = p.frame  - (pPrev.frame - framesTotal);
                    frameRel = framePos - (pPrev.frame - framesTotal);
                } else {
                    pPrev = timeline[boneId][propertyId][index-1];
                    frameDif = p.frame - pPrev.frame;
                    frameRel = framePos - pPrev.frame;
                }




                if(frameDif == 0){
                    return timeline[boneId][propertyId][index];
                }



                float perc = 1 - (frameRel/frameDif);


                if(pPrev.progressionType == 0){

                    float w1 = perc;
                    return weightedPropertyMean(pPrev, p, w1);

                } else if(pPrev.progressionType == 1){

                    float w1 = perc*perc;
                    return weightedPropertyMean(pPrev, p, w1);

                } else if(pPrev.progressionType == 2){

                    float w1 = 1 - ((1-perc)*(1-perc));
                    return weightedPropertyMean(pPrev, p, w1);

                } else {
                    float w1 = 1;
                    return weightedPropertyMean(pPrev, p, w1);
                }


            } else {
                //println("llew34");

                return timeline[boneId][propertyId][index];
            }
        } else {
            /// Here i should use the base values
            int framesNum  = timeline[boneId][propertyId].size()-1;
            if(framesNum >= 0){

                if(connectLoop){
                    struct AnimationKeyFrame p = timeline[boneId][propertyId][0];


                    struct AnimationKeyFrame pPrev = timeline[boneId][propertyId][timeline[boneId][propertyId].size()-1];

                    float frameDif = p.frame  - (pPrev.frame - framesTotal);
                    float frameRel = framePos - pPrev.frame;






                    if(frameDif == 0){
                        return timeline[boneId][propertyId][index];
                    }



                    float perc = 1 - (frameRel/frameDif);


                    if(pPrev.progressionType == 0){

                        float w1 = perc;
                        return weightedPropertyMean(pPrev, p, w1);

                    } else if(pPrev.progressionType == 1){

                        float w1 = perc*perc;
                        return weightedPropertyMean(pPrev, p, w1);

                    } else if(pPrev.progressionType == 2){

                        float w1 = 1 - ((1-perc)*(1-perc));
                        return weightedPropertyMean(pPrev, p, w1);

                    } else {
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







struct Element{
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

        void init(sf::Texture* t){
            sprite.setTexture(*t);

            sprite.setTextureRect(sprArea.texRect);
        }

        void setBaseProperties(Vector2i center, Vector2f attach, Vector2f offset, float xScl, float yScl, float angle, int attachId, struct SpriteArea sprArea){
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

        void resetToBase(){
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

class ElementHandle{



    int id = -1;
    std::vector<struct Element*>& allBones;

    public:
    struct Element* bone;


    ElementHandle(std::vector<struct Element*>& _allBones, int id) : allBones(_allBones){
        this->id = id;
        this->bone = allBones[id];
    }


    void draw(sf::RenderWindow& window){


        bone->sprite.setTextureRect(bone->sprArea.texRect);

        bone->sprite.setPosition(bone->drawPos);

        bone->sprite.setOrigin((Vector2f)bone->center);

        float sclFixAng = bone->finalAngle;
        if(bone->finalXScl < 0){
            sclFixAng *=  -1;
        }
        if(bone->finalYScl < 0){
            sclFixAng *=  -1;
        }

        bone->sprite.setScale(bone->finalXScl, bone->finalYScl);
        bone->sprite.setRotation(sclFixAng);

        window.draw(bone->sprite);
    }

    void update(){
        if(bone->attachId != -1){
            const struct Element b = *allBones[bone->attachId];


            bone->finalAngle = bone->angle + b.finalAngle;

            bone->finalXScl = bone->xScl * bone->xWholeScl;
            bone->finalYScl = bone->yScl * bone->yWholeScl;



            float attachXRotated = b.finalXScl * bone->attach.x;
            float attachYRotated = b.finalYScl * bone->attach.y;


            // Transforms from degrees to radians
            float correctedAngle = b.finalAngle;
            if(b.finalXScl < 0){
                correctedAngle *= -1;
            }
            if(b.finalYScl < 0){
                correctedAngle *= -1;
            }


            correctedAngle = 3.141592*correctedAngle/180;




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
            bone->pos.x = xx - bone->center.x*bone->finalXScl + bone->offset.x*b.xWholeScl;
            bone->pos.y = yy - bone->center.y*bone->finalYScl + bone->offset.y*b.yWholeScl;

            bone->drawPos.x = bone->pos.x + bone->center.x*bone->finalXScl;
            bone->drawPos.y = bone->pos.y + bone->center.y*bone->finalYScl;

        } else {



            bone->finalAngle = bone->angle;
            bone->finalXScl  = bone->xScl * bone->xWholeScl;
            bone->finalYScl  = bone->yScl * bone->yWholeScl;

            bone->pos.x = bone->xWhole - bone->center.x*bone->finalXScl;
            bone->pos.y = bone->yWhole - bone->center.y*bone->finalYScl;


            bone->drawPos.x = bone->pos.x + bone->center.x*bone->finalXScl;
            bone->drawPos.y = bone->pos.y + bone->center.y*bone->finalYScl;
        }
    }

};




















struct Model{
    std::vector<Element*> allBones;
    std::vector<ElementHandle*> allHandles;
    std::vector<int> drawOrder;
    std::vector<int> executeOrder;

    std::map<std::string,int> boneMap;

    sf::Texture* tex;

    Vector2f pos;
    Vector2f angle;
    float xScl = 1;
    float yScl = 1;

    bool valid = false;

    void draw(sf::RenderWindow& window){
         /// Bones Drawing
        if(valid){
            for(int i = 0; i < drawOrder.size(); i++){
                allHandles[drawOrder[i]]->draw(window);
            }
        }
    }

    void update(){
        /// Bones Update
        if(valid){
            for(int i = 0; i < executeOrder.size(); i++){
                allHandles[executeOrder[i]]->bone->xWholeScl = xScl;
                allHandles[executeOrder[i]]->bone->yWholeScl = yScl;
                allHandles[executeOrder[i]]->bone->xWhole    = pos.x;
                allHandles[executeOrder[i]]->bone->yWhole    = pos.y;

                allHandles[executeOrder[i]]->update();
            }
        }
    }

    void updateWithAnimation(struct Animation& anim){

        float fPos = anim.playingFrame;

        for(int i = 0; i < anim.timeline.size(); i++){


            struct AnimationKeyFrame p;
            p = anim.getPropertyValue(i, 0, fPos);

            if(p.exists){
                allBones[i]->center.x = p.val;
            }

            p = anim.getPropertyValue(i, 1, fPos);

            if(p.exists){
                allBones[i]->center.y = p.val;
            }

            p = anim.getPropertyValue(i, 2, fPos);

            if(p.exists){
                allBones[i]->attach.x = p.val;
            }

            p = anim.getPropertyValue(i, 3, fPos);

            if(p.exists){
                allBones[i]->attach.y = p.val;
            }

            p = anim.getPropertyValue(i, 4, fPos);

            if(p.exists){
                allBones[i]->offset.x = p.val;
            }

            p = anim.getPropertyValue(i, 5, fPos);

            if(p.exists){
                allBones[i]->offset.y = p.val;
            }

            p = anim.getPropertyValue(i, 6, fPos);

            if(p.exists){
                allBones[i]->xScl = p.val;
            }

            p = anim.getPropertyValue(i, 7, fPos);

            if(p.exists){
                allBones[i]->yScl = p.val;
            }


            p = anim.getPropertyValue(i, 8, fPos);

            if(p.exists){
                allBones[i]->angle = p.val;
            }


        }

    }

    void loadModel(std::string filename){
        std::ifstream file(filename);

        println("Loading Model");
        if(file.is_open()){


            std::string line;
            std::getline (file, line);

            int version = std::stoi(line);


            println("Checking Version");

            if(version == 1){
                println("Model Version " << version);
                allBones.clear();
                allHandles.clear();
                drawOrder.clear();
                executeOrder.clear();

                std::getline (file, line);

                println("Ordem de Execucao");
                if(line == "Execution Order"){
                    std::getline (file, line);
                    if(line == "{"){
                        std::getline (file, line);
                        while(line != "}"){
                            executeOrder.push_back(std::stoi(line));
                            std::getline (file, line);
                        }
                    }
                }
                std::getline (file, line);

                println("Ordem de desenho");
                if(line == "Draw Order"){
                    std::getline (file, line);
                    if(line == "{"){
                        std::getline (file, line);
                        while(line != "}"){
                            drawOrder.push_back(std::stoi(line));
                            std::getline (file, line);
                        }
                    }
                }

                std::getline (file, line);


                println("Carregando Elementos");
                if(line == "Elements"){
                    std::getline (file, line);
                    if(line == "{"){
                        std::getline (file, line);
                        while(line != "}"){


                            int id = std::stoi(line);

                            println("Loading Element " << id);

                            std::getline (file, line);
                            std::string name = "";
                            if(line != "*"){
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


                            std::getline (file, line);
                            if(line == "["){
                                float fVal = 0;
                                int iVal = 0;
                                std::getline (file, line);
                                fVal = std::stof(line);

                                center.x = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                center.y = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                attach.x = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                attach.y = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                offset.x = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                offset.y = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                xScl = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                yScl = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                angle = fVal;

                                /// Atach Id is int
                                std::getline (file, line);
                                iVal = std::stof(line);

                                attachId = iVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                sprArea.texRect.left = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                sprArea.texRect.top = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                sprArea.texRect.width = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                sprArea.texRect.height = fVal;

                                std::getline (file, line);
                            }else {
                                deleted = true;

                            }


                            std::getline (file, line);


                            newBone->setBaseProperties((Vector2i)center, attach, offset, xScl, yScl, angle, attachId, sprArea);
                            newBone->name = name;


                            allBones.push_back(newBone);

                            // For the deleted Objects we should have a weird name
                            boneMap[name] = allBones.size()-1;

                        }
                    }

                }






                for(int i = 0; i < allBones.size(); i++){
                    ElementHandle* newBoneHandle = new ElementHandle(allBones, i);
                    allHandles.push_back(newBoneHandle);
                }


                std::cout << "Sucesso" << std::endl;

            } else {
                std::cout << "Model Version not supported" << std::endl;
            }

        }

        file.close();



        valid = true;
    }

};



















int main(){

    RenderWindow* window = new RenderWindow(VideoMode(1800, 720), "TBRB");
    window->setFramerateLimit(FRAMERATE_LIMIT);



    Rooster::HitBox hb;
    Texture t;
    t.loadFromFile("sprites/galoKalsa.png");

    Texture texToolbar;
    texToolbar.loadFromFile("sprites/toolbar.png");

    Rooster::Galo galo(hb, 20, 20, 20, Rooster::state::STOPPED, t);


    struct engineInfo info;
    info.init();
    info.update();

    info.screenWidth = window->getSize().x;
    info.screenHeight = window->getSize().y;




    struct BoneManager bManager;

    font.loadFromFile("fonts/whitrabt.ttf");

    bManager.init(t, texToolbar, info);

    struct Model modelo;

    modelo.tex = &t;
    modelo.loadModel("SniperModel1.txt");

    modelo.xScl = 1;

    struct Animation anima;
    anima.init("SecondAnim.txt");
    anima.connectLoop = true;







    int frames = 0;



    while (window->isOpen()) {
            frames ++;
        Event e;
        while (window->pollEvent(e)) {
            if (e.type == Event::Closed) {
                window->close();

            }

            if (e.type == Event::KeyPressed) {

                if(e.key.code == Keyboard::Enter){
                    if(!info.selecting){
                        struct SpriteArea area;

                        area.init();
                        area.center.x = 0;
                        area.center.y = 0;



                        area.texRect.left = info.selStart.x/info.sheetScl;
                        area.texRect.top  = (info.selStart.y-info.GUI.uBar.hei)/info.sheetScl;
                        area.texRect.width =  (info.selEnd.x - info.selStart.x)/info.sheetScl;
                        area.texRect.height = (info.selEnd.y - info.selStart.y)/info.sheetScl;

                        //area.pos.x =                     area.texRect.left*info.sheetScl;
                        //area.pos.y = info.GUI.uBar.hei + area.texRect.top *info.sheetScl;

                        bManager.areas.push_back(area);
                    }

                    info.confirmInput = true;
                }else if(e.key.code == Keyboard::Equal){
                    anima.init("SecondAnim.txt");
                } else if(e.key.control){


                    if(e.key.code == Keyboard::Num1){
                        bManager.toolSelected = 0;
                    } else if(e.key.code == Keyboard::Num2){
                        bManager.toolSelected = 1;
                    } else if(e.key.code == Keyboard::Num3){
                        bManager.toolSelected = 2;
                    }


                }

            } else if(e.type == Event::MouseMoved){

                info.mouseX = e.mouseMove.x;
                info.mouseY = e.mouseMove.y;
            } else if (e.type == Event::TextEntered) {



                    if (e.text.unicode < 128) {

                        //std::cout << "Arcor" << std::endl;
                        if(e.text.unicode > 31){
                            info.lastChar = (static_cast<char>(e.text.unicode));
                            //std::cout << info.lastChar << std::endl;
                            info.newInput = true;

                        } else if (e.text.unicode == 3 || e.text.unicode == 8){
                            info.deleteChar = true;
                            //std::cout << "Delete" << std::endl;
                        }


                    }


            }

        }



        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            galo.setState(Rooster::state::RUNNING);
            galo.facingRight = true;
            galo.animRun();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            galo.setState(Rooster::state::RUNNING);
            galo.facingRight = false;
            galo.animRun();
        } else {
            galo.setState(Rooster::state::STOPPED);
            galo.setHspeed(0);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            galo.attacking = true;
        } else {
            galo.attacking = false;
        }















        window->clear();


        RectangleShape fundo(Vector2f(info.screenWidth, info.screenHeight));
        fundo.setPosition(0,0);
        fundo.setFillColor(Color(100, 100, 100));


        anima.update();




        modelo.updateWithAnimation(anima);
        modelo.update();
        modelo.xScl = (((frames%2000)/1000)*2 )-1;

        //modelo.yScl = cos((float)frames/32);
        modelo.pos = galo.getSprite().getPosition();
        //modelo.pos.y = 150;
        info.mouseUpdate();

        galo.update(info.mouseX, info.mouseY);
        bManager.update(info);





        window->draw(fundo);

        bManager.draw(*window, info);

        //galo.show(*window);

        modelo.draw(*window);

        info.update();

        window->display();

    }



    return 0;
}
