#ifndef TIMELINEMANAGER_H_INCLUDED
#define TIMELINEMANAGER_H_INCLUDED

struct Properties{
    float centerX = 0;
    float centerY = 0;

    float attachX = 0;
    float attachY = 0;

    float offsetX = 0;
    float offsetY = 0;

    float xScl    = 0;
    float yScl    = 0;

    float angle   = 0;

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

struct TimelineManager{


    const int propertiesNumber = 9;

    // First Access is Bone/Element
    std::vector<std::vector<std::vector<struct Properties>>> timeline;

    std::vector<std::string> propertyName;

    std::vector<int> activeBones;

    float x = 0;
    float y = 0;
    int framesPerBar = 20;
    int framesTotal = 50;
    float wid = 500;
    float hei = 20;



    int frameX = 0;

    float frameWid = 1;

    /// Bone Selected == ID
    int boneSelected = -1;
    Vector2i frameSelected;
    Vector2i frameHovered;

    bool hovered = false;
    bool clicked = false;

    bool draggingFrame = false;

    bool playing = true;
    float playingFrame = 0;
    float playingSpeed = 0.1;
    bool connectLoop = false;

    Slider* frameXSlider;
    struct ValBox speedBox;
    struct ValBox frameNumBox;

    struct{
        float x = 0;
        float y = 0;
        float wid = 0;
        float hei = 0;
    } playButton;

    struct {
        float x = 0;
        float y = 0;
        float wid = 0;
        float hei = 0;
    } loopButton;

    struct {
        float x = 0;
        float y = 0;
        float wid = 80;
        float hei = 20;
    } spdBox;


    // Second Access Property Type
    // Third Access All KeyFrames in a line



    void init(struct engineInfo& info){
        x = 300;
        y = 500;
        init2();
        updatePosStuff(info);
    }

    void init(float xx, float yy, float ww, float hh, struct engineInfo& info){
        x = xx;
        y = yy;
        wid = ww;
        hei = hh;
        init2();
        updatePosStuff(info);
    }


    void init2(){
        for(int i = 0 ; i < propertiesNumber; i++){
            propertyName.push_back("Nothing");
        }

        propertyName[0] = "CenterX";
        propertyName[1] = "CenterY";
        propertyName[2] = "AttachX";
        propertyName[3] = "AttachY";
        propertyName[4] = "OffsetX";
        propertyName[5] = "OffsetY";
        propertyName[6] = "XScl";
        propertyName[7] = "YScl";
        propertyName[8] = "Angle";



        frameSelected.x = 0;
        frameSelected.y = -1;

        frameHovered.x = -1;
        frameHovered.y = -1;

        speedBox.init(0, x+spdBox.x, y+spdBox.y, spdBox.wid, spdBox.hei, 0.01f);
        speedBox.label = "Speed";

        frameNumBox.init(1, x, y, spdBox.wid, spdBox.hei, 50);
        frameNumBox.label = "Frames";

        frameXSlider = new Slider(x, y-hei, wid, 0, framesTotal-framesPerBar, 0);




    }

    void updatePosStuff(struct engineInfo& info){
        x = info.GUI.propBar.x;
        y = info.GUI.propBar.y;
        wid = info.GUI.propBar.playWid;
        hei = info.GUI.propBar.pHei;


        playButton.x = 0;
        playButton.y = hei*propertiesNumber;
        playButton.wid = hei;
        playButton.hei = hei;

        loopButton.x = playButton.x + playButton.wid + 10;
        loopButton.y = playButton.y;
        loopButton.wid = playButton.wid;
        loopButton.hei = playButton.hei;

        spdBox.x = x + loopButton.x + loopButton.wid + 10;
        spdBox.y = y + loopButton.y;
        spdBox.wid = 40;
        spdBox.hei = hei;

        speedBox.x = spdBox.x;
        speedBox.y = spdBox.y;
        speedBox.wid = spdBox.wid;
        speedBox.hei = spdBox.hei;

        frameNumBox.x = speedBox.x + speedBox.wid + 10;
        frameNumBox.y = speedBox.y;
        frameNumBox.wid = speedBox.wid;
        frameNumBox.hei = speedBox.hei;

        frameXSlider->x = frameNumBox.x + frameNumBox.wid +20;
        frameXSlider->y = y+hei*propertiesNumber;
        frameXSlider->len = (wid-(frameXSlider->x-x))-20;
        frameXSlider->hei = hei;


    }

    void changeSelectedBone(int id){
        boneSelected = id;

        frameSelected.y = -1;
        frameSelected.x = -1;
    }

    void addBone(){

        std::vector<std::vector<struct Properties>> prop;

        for(int i = 0 ; i < propertiesNumber; i++){
            std::vector<struct Properties> a;
            prop.push_back(a);
        }

        timeline.push_back(prop);
    }


    const struct Properties getProperty(int boneId, int propertyId, int pos){
        for(int i = 0 ; i < timeline[boneId][propertyId].size(); i++){
            if(timeline[boneId][propertyId][i].frame == pos){
                return timeline[boneId][propertyId][i];
            }

        }


        struct Properties p;
        if(propertyId == 0){
            println("Nao achou CenterX");
        }
        return p;
    }

    int getPropertyIndex(int boneId, int propertyId, int pos){
        for(int i = 0 ; i < timeline[boneId][propertyId].size(); i++){
            if(timeline[boneId][propertyId][i].frame == pos){
                return i;
            }

        }
        return -1;
    }

    void swapProperties(int boneId, int propertyId, int ind1, int ind2){
        struct Properties temp = timeline[boneId][propertyId][ind1];
        timeline[boneId][propertyId][ind1] = timeline[boneId][propertyId][ind2];
        timeline[boneId][propertyId][ind2] = temp;
    }

    void sortKeyFrames(int boneId, int propertyId){

        // Maybe works
        for(int i = 0 ; i < timeline[boneId][propertyId].size(); i++){
            for(int j = 0 ; j < (timeline[boneId][propertyId].size()-i-1); j++){
                if(timeline[boneId][propertyId][j].frame > timeline[boneId][propertyId][j+1].frame){
                    swapProperties(boneId, propertyId, j, j+1);
                }
            }
        }
    }

    void deleteKeyFrame(int boneId, int propertyId, int pos){
        int index = getPropertyIndex(boneId, propertyId, pos);

        if(index != -1){
            timeline[boneId][ propertyId].erase(timeline[boneId][propertyId].begin() + index);
        }
    }

    void createKeyFrameHere(int boneId, int propertyId, struct Properties p){
          p.frame = frameSelected.x;

          createKeyFrame(boneId, propertyId, p);
    }

    void createKeyFrame(int boneId, int propertyId, struct Properties p){

        deleteKeyFrame(boneId, propertyId, p.frame);

        timeline[boneId][propertyId].push_back(p);

        sortKeyFrames(boneId, propertyId);
    }


    bool changeKeyFramePosition(int boneId, int propertyId, int oldPos, int newPos){

        int newPosTest = getPropertyIndex(boneId, propertyId, newPos);

        if(newPosTest != -1){
            return false;
        }

        int oldPosIndex = getPropertyIndex(boneId, propertyId, oldPos);
        if(oldPosIndex == -1){
            return true;
        }

        timeline[boneId][propertyId][oldPosIndex].frame = newPos;

        sortKeyFrames(boneId, propertyId);

        return true;
    }


    void draw(RenderWindow& window, struct engineInfo& info){


        if(boneSelected != -1){

            RectangleShape playBut(Vector2f(playButton.wid, playButton.hei));
            playBut.setPosition(playButton.x + x, playButton.y + y);
            if(playing){
                playBut.setFillColor(Color(200, 60, 60));
                playBut.setOutlineThickness(2);
            } else {
                playBut.setFillColor(Color(250, 100, 100));
                playBut.setOutlineThickness(0);
            }

            playBut.setOutlineColor(Color(255, 255, 255));
            window.draw(playBut);

            RectangleShape loopBut(Vector2f(loopButton.wid, loopButton.hei));
            loopBut.setPosition(loopButton.x + x, loopButton.y + y);
            if(connectLoop){
                loopBut.setFillColor(Color(100, 240, 60));
                loopBut.setOutlineThickness(2);
            } else {
                loopBut.setFillColor(Color(20, 100, 20));
                loopBut.setOutlineThickness(0);
            }

            loopBut.setOutlineColor(Color(255, 255, 255));
            window.draw(loopBut);

            speedBox.draw(window);
            frameNumBox.draw(window);


            for(int i = 0; i < propertiesNumber; i++){
                float xx = x;
                float yy = y + hei*i;

                float fontSize = hei;
                Text tLabel(propertyName[i], font, fontSize);
                tLabel.setFillColor(Color(255, 255, 255));
                tLabel.setPosition(xx +wid + 10, yy-4);

                window.draw(tLabel);

                RectangleShape panel(Vector2f(wid, hei));
                panel.setFillColor(Color(60));
                panel.setOutlineThickness(2);
                panel.setOutlineColor(Color(255));
                panel.setPosition(xx, yy);
                window.draw(panel);



                for(int j = 0; j < framesPerBar; j++){

                    RectangleShape line(Vector2f(2, hei));
                    line.setFillColor(Color(80));
                    line.setOutlineThickness(2);
                    line.setOutlineColor(Color(150));
                    line.setPosition(xx + (j*frameWid) + frameWid/2, yy);
                    window.draw(line);

                    if(frameHovered.y == i){
                        if(j+frameX == frameHovered.x){
                            RectangleShape select(Vector2f(frameWid, hei));
                            select.setFillColor(Color(255, 255, 255, 100));
                            select.setOutlineThickness(2);
                            select.setOutlineColor(Color(200));
                            select.setPosition(xx + (j*frameWid), yy);
                            window.draw(select);
                        }
                    }

                    for(int k = 0; k < timeline[boneSelected][i].size(); k++){
                        if(j+frameX == timeline[boneSelected][i][k].frame){

                            // Draw KeyFrame
                            RectangleShape rect(Vector2f(frameWid, hei));
                            rect.setPosition(xx + (j*frameWid), yy);

                            const struct Properties p = timeline[boneSelected][i][k];

                            if((frameSelected.y == i && frameSelected.x == j+frameX)){



                                if(draggingFrame){
                                    rect.setPosition(info.mouseX, yy);
                                } else {


                                    std::string str = propertyName[i];
                                    str += " ";

                                    float val = 0;
                                    /*
                                    switch(p.propertyId){
                                        case 0:
                                            val = p.centerX;
                                            break;

                                        case 1:
                                            val = p.centerY;
                                            break;

                                        case 2:
                                            val = p.attachX;
                                            break;

                                        case 3:
                                            val = p.attachY;
                                            break;

                                        case 4:
                                            val = p.offsetX;
                                            break;

                                        case 5:
                                            val = p.offsetY;
                                            break;

                                        case 6:
                                            val = p.xScl;
                                            break;

                                        case 7:
                                            val = p.yScl;
                                            break;

                                        case 8:
                                            val = p.angle;
                                            break;
                                    }
                                    */

                                    val = p.val;


                                    str += std::to_string(val);
                                    Text tLabel2( str , font, fontSize/2);
                                    tLabel2.setFillColor(Color(255, 255, 255));
                                    tLabel2.setPosition(xx +wid + 10, y-fontSize);

                                    window.draw(tLabel2);


                                }

                            }


                            if(p.progressionType == 0){
                                rect.setFillColor(Color(130));
                            } else if (p.progressionType == 1){
                                rect.setFillColor(Color(250, 160 , 160));

                            }else if (p.progressionType == 2){
                                rect.setFillColor(Color(200, 200 , 250));
                            }else if (p.progressionType == 3){
                                rect.setFillColor(Color(250, 160 , 250));
                            }
                            rect.setOutlineThickness(2);
                            rect.setOutlineColor(Color(200));

                            window.draw(rect);

                        }
                    }


                    if(frameSelected.y == i){
                        if(j+frameX == frameSelected.x){
                            RectangleShape select(Vector2f(frameWid, hei));
                            select.setFillColor(Color(200, 200, 100, 0));
                            select.setOutlineThickness(3);
                            select.setOutlineColor(Color(250));
                            select.setPosition(xx + (j*frameWid), yy);
                            window.draw(select);
                        }
                    }

                }
            }

            if(playing){
                RectangleShape line(Vector2f(4, hei*propertiesNumber));
                line.setFillColor(Color(250, 200, 200));
                line.setOutlineThickness(2);
                line.setOutlineColor(Color(200));
                line.setPosition(x + (playingFrame-frameX)*frameWid, y);
                window.draw(line);
            }

            frameXSlider->drawSlider(window);
        }


    }

    void update(struct engineInfo& info){
        frameWid = ((float)wid/framesPerBar);


        if(frameXSlider->hovered){
            info.hoveringGUI = true;
        }

        clicked = false;
        hovered = false;

        if(!playing){


            if(boneSelected != -1){

                frameXSlider->updateSlider(info);
                frameX = (int)frameXSlider->val;


                if(info.mouseInside(playButton.x + x, playButton.y + y, playButton.wid, playButton.hei)){
                    info.hoveringGUI = true;
                    if(info.mouseState[0][1]){
                        playing = true;

                    }
                }

                if(info.mouseInside(loopButton.x + x, loopButton.y + y, loopButton.wid, loopButton.hei)){
                    info.hoveringGUI = true;
                    if(info.mouseState[0][1]){

                        if(connectLoop){
                            connectLoop = false;
                        } else {
                            connectLoop = true;
                        }
                    }
                }

                speedBox.update(info);

                if(speedBox.confirmed){
                    playingSpeed = speedBox.fVal;
                }

                frameNumBox.update(info);

                if(frameNumBox.confirmed){
                    framesTotal = frameNumBox.iVal;
                    frameXSlider->maxVal = framesTotal;
                    frameXSlider->updateValue(frameX);
                }

                frameHovered.x = -1;
                frameHovered.y = -1;

                if(info.mouseInside(x, y, wid, hei*propertiesNumber)){
                    frameHovered.x = frameX + constrain((int)(info.mouseX-x)/frameWid, 0, framesPerBar-1);
                    frameHovered.y = constrain((int)(info.mouseY-y)/hei, 0, framesPerBar-1);

                    hovered = true;


                    if(info.mouseState[0][1]){
                        clicked = true;
                        if(!draggingFrame){
                            frameSelected = frameHovered;


                            for(int k = 0; k < timeline[boneSelected][frameSelected.y].size(); k++){
                                if(frameSelected.x == timeline[boneSelected][frameSelected.y][k].frame){
                                    draggingFrame = true;
                                    std::cout << " Detected KeyFrame " << std::endl;

                                }
                            }
                        }

                    }

                    if(info.mouseState[0][2]){
                        if(draggingFrame && frameSelected.x != -1){
                            if(frameSelected.y == frameHovered.y){

                                /// Bone Selected may give problems
                                if(!changeKeyFramePosition(boneSelected, frameSelected.y, frameSelected.x, frameHovered.x)){
                                }

                                frameSelected.x = frameHovered.x;
                            }
                        }
                        draggingFrame = false;
                    }

                    if(info.keyboardState[sf::Keyboard::Delete][1]){
                        deleteKeyFrame(boneSelected, frameSelected.y, frameSelected.x);
                    }
                }
            }
        } else {



            playingFrame += playingSpeed;
            if(playingFrame > framesTotal){
                playingFrame = 0;
                frameX = 0;
                frameXSlider->updateValue(frameX);
            }

            if(playingFrame-frameX > framesPerBar){
                frameX += framesPerBar;
                frameXSlider->updateValue(frameX);
            }

            if(info.mouseInside(playButton.x +x, playButton.y + y, playButton.wid, playButton.hei)){
                info.hoveringGUI = true;
                if(info.mouseState[0][1]){
                    playing = false;
                    playingFrame = 0;
                }


            }
        }
    }

    struct Properties weightedPropertyMean(struct Properties p1, struct Properties p2, float w1){
        struct Properties p;
        p.init();

        p = p1;

        float w2 = 1 - w1;

        /*
        p.angle = p1.angle*w1 + p2.angle*w2;
        p.attachX = p1.attachX*w1 + p2.attachX*w2;
        p.attachY = p1.attachY*w1 + p2.attachY*w2;
        p.offsetX = p1.offsetX*w1 + p2.offsetX*w2;
        p.offsetY = p1.offsetY*w1 + p2.offsetY*w2;
        p.centerX = p1.centerX*w1 + p2.centerX*w2;
        p.centerY = p1.centerY*w1 + p2.centerY*w2;
        p.xScl = p1.xScl*w1 + p2.xScl*w2;
        p.yScl = p1.yScl*w1 + p2.yScl*w2;
        */

        p.val = p1.val * w1 + p2.val * w2;

        return p;

    }

    struct Properties getPropertyValue(int boneId, int propertyId, float framePos){


        int index = -1;


        for(int i = 0; i < timeline[boneId][propertyId].size(); i++){
            if(timeline[boneId][propertyId][i].frame > framePos){
                index = i;
                i = timeline[boneId][propertyId].size();
            }
        }




        if(index != -1){
            if(index != 0 || connectLoop){


                struct Properties p = timeline[boneId][propertyId][index];


                struct Properties pPrev;

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
                    struct Properties p = timeline[boneId][propertyId][0];


                    struct Properties pPrev = timeline[boneId][propertyId][timeline[boneId][propertyId].size()-1];

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


        struct Properties p;
        p.exists = false;
        return p;


    }


};


#endif // TIMELINEMANAGER_H_INCLUDED
