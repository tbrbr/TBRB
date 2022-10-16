#ifndef BONEMANAGER_H_INCLUDED
#define BONEMANAGER_H_INCLUDED

struct dependBar{

    int id;

    int dependOn;

    std::vector<int> dependents;

    int depth;

    bool deleted = false;
};

void getAllDependents(std::vector<struct dependBar>& order, int id, std::vector<int>& dependents, int relDepth = 0){


    for(int i = 0; i < order[id].dependents.size(); i++){
        getAllDependents(order, order[id].dependents[i], dependents, relDepth+1);
    }

    dependents.push_back(id);
    if(relDepth == 0){
         std::vector<int > temp;
         for(int i = dependents.size()-1; i > -1; i--){
            temp.push_back(dependents[i]);
         }

         for(int i = 0; i < dependents.size(); i++){
            dependents[i] = temp[i];
         }

   }



}

void updateAllDepths(std::vector<struct dependBar>& order, int id, int depth){


    for(int i = 0; i < order[id].dependents.size(); i++){
        updateAllDepths(order, order[id].dependents[i], depth +1);
    }

    order[id].depth = depth;

}







struct BoneManager{

    std::vector<SpriteArea> areas;
    std::vector<Bone*> ossos;
    std::vector<BoneHandle*> boneHandles;

    Sprite sprSheet;
    Sprite sprToolbar;
    Sprite sprTrashcan;


    int areaSelected = -1;

    int toolSelected = 0;
    int toolNumber = 4;

    int elementSelected = -1;

    bool draggingBar = false;

    struct{
        float x = 0;
        float y = 0;
    }dependOff;




    std::vector<struct dependBar> dependBars;
    std::vector<int> dependBarOrder;

    float toolScl = 1;

    struct barListManager layerList;

    struct TimelineManager timeManager;

    bool renaming = false;
    struct ValBox renameBox;

    struct ValBox xWholeSclBox;
    struct ValBox yWholeSclBox;


    void init(Texture& t, Texture& toolbar, struct engineInfo& info){

        //info.GUI.dBar.wid = info.screenWidth;
        //info.GUI.dBar.y = info.screenHeight - info.GUI.dBar.hei;

        sprSheet.setTexture(t);
        info.sheetScl  = (float)(info.screenHeight - info.GUI.dBar.hei - info.GUI.uBar.hei)/sprSheet.getLocalBounds().height;
        sprSheet.setScale(info.sheetScl, info.sheetScl);
        info.GUI.lBar.wid = sprSheet.getGlobalBounds().width;
        sprSheet.setPosition(0, info.GUI.uBar.y + info.GUI.uBar.hei);




        sprTrashcan.setTexture(toolbar);
        sprTrashcan.setTextureRect(IntRect(12*2, 0, 12, 12));

        sprToolbar.setTexture(toolbar);
        toolScl  = (float)(info.GUI.dBar.hei)/sprToolbar.getLocalBounds().height;
        sprToolbar.setScale(toolScl, toolScl);





        layerList.init();

        layerList.wid = info.GUI.rBar.wid - info.GUI.rBar.lWid;
        layerList.hei = info.GUI.rBar.hei;
        layerList.x   = info.GUI.rBar.x;
        layerList.y   = info.GUI.rBar.y;

        float tMWid = 800;
        float tMHei = 20;
        float tMX = (info.screenWidth/2) - tMWid/2;
        float tMY = 500;
        timeManager.init(tMX, tMY, tMWid, tMHei, info);

        renameBox.init(2, info.screenWidth - 400, info.GUI.uBar.hei/2 - 30/2, 200, 30, "");
        renameBox.textLimit = 15;
        renameBox.confirmOutOfFocus = false;
        renameBox.label = "Element Name";

        xWholeSclBox.init(0, 20, info.GUI.uBar.hei/2 - 30/2, 40, 30, 1);
        xWholeSclBox.label = "XScl";
        yWholeSclBox.init(0, 120, info.GUI.uBar.hei/2 - 30/2, 40, 30, 1);
        yWholeSclBox.label = "YScl";



    }

    void draw(sf::RenderWindow& window, struct engineInfo& info){



        /// Panel
        RectangleShape panel(Vector2f(sprSheet.getGlobalBounds().width, info.screenHeight));
        panel.setPosition(0,0);
        panel.setFillColor(Color(150, 150, 150));
        window.draw(panel);

        // Sprite
        window.draw(sprSheet);



        /// Inferior Bar
        RectangleShape fundo(Vector2f(info.GUI.dBar.wid, info.GUI.dBar.hei));
        fundo.setPosition(info.GUI.dBar.x,info.GUI.dBar.y);
        fundo.setFillColor(Color(100, 100, 200));
        window.draw(fundo);

        RectangleShape fundo2(Vector2f(info.GUI.dBar.hei, info.GUI.dBar.hei));
        fundo2.setPosition(info.GUI.dBar.toolX + toolSelected*info.GUI.dBar.hei,info.GUI.dBar.y);
        fundo2.setFillColor(Color(80, 80, 160));
        window.draw(fundo2);

        sprToolbar.setPosition(info.GUI.dBar.toolX, info.GUI.dBar.y);
        window.draw(sprToolbar);

        /// Up Bar
        RectangleShape fundo3(Vector2f(info.GUI.uBar.wid, info.GUI.uBar.hei));
        fundo3.setPosition(info.GUI.uBar.x,info.GUI.uBar.y);
        fundo3.setFillColor(Color(100, 100, 200));
        window.draw(fundo3);


        xWholeSclBox.draw(window);
        yWholeSclBox.draw(window);




        /// Selection
        RectangleShape select(Vector2f(info.selEnd.x-info.selStart.x, info.selEnd.y-info.selStart.y));
        select.setPosition(info.selStart.x, info.selStart.y);
        select.setFillColor(Color(100, 100, 100, 0));
        select.setOutlineColor(Color(255));
        select.setOutlineThickness(4);
        window.draw(select);



        /// Areas
        for(int i = 0; i < areas.size(); i++){
            RectangleShape a(Vector2f(15, 15));
            a.setPosition(i*(15+5) + 5, info.screenHeight-17.5);
            a.setFillColor(Color(200, 230, 180));
            a.setOutlineColor(Color::Black);
            a.setOutlineThickness(2);
            window.draw(a);

            Color col(200, 200, 200, 0);

            if(i == areaSelected){
                col.a = 100;
            }

            areas[i].draw(window, info.sheetScl, col, info);
        }




        layerList.draw(window, info);



        float barWid = info.GUI.rBar.wid;
        float barHei = info.GUI.rBar.hei - info.GUI.rBar.lY;
        float barX = info.GUI.rBar.x + info.GUI.rBar.lWid;
        float barY = info.GUI.rBar.y + info.GUI.rBar.lY;
        float layerHei = info.GUI.rBar.lHei;


        RectangleShape rightBar(Vector2f(barWid, barHei));
        rightBar.setPosition(barX, barY);
        rightBar.setFillColor(Color(200, 200, 200));
        window.draw(rightBar);



        for(int i = 0; i < dependBarOrder.size(); i++){

            int ind = dependBarOrder[i];

            float layerX = barX + 15 * dependBars[ind].depth;
            float layerY = barY + layerHei*i;

            if(ind == elementSelected && draggingBar){
               layerY = info.mouseY - dependOff.y;
            }



            Color col = Color((127*ind + 100)%255, (231*ind)%255, (ind*33)%255);

            RectangleShape depBar(Vector2f(barWid, layerHei));
            depBar.setPosition(layerX, layerY);
            depBar.setFillColor(col);
            window.draw(depBar);


            col = Color::Black;
            col.a = 100;
            depBar.setPosition(layerX + barWid/2, layerY);
            depBar.setFillColor(col);
            window.draw(depBar);


            Text ax;
            ax.setPosition( barX , layerY + layerHei/2 - 15/2);
            ax.setFillColor(Color::Black);
            ax.setOutlineColor(Color::White);
            ax.setOutlineThickness(2);
            ax.setFont(font);
            ax.setCharacterSize(15);


            if( boneHandles[ind]->bone->selected){

                /*
                std::stringstream str2;
                str2 << "Dependents " << (streamIntVec(dependBars[ind].dependents)) << "   DependOn [" ;
                str2 << (dependBars[ind].dependOn)  << "]  ID " << (dependBars[ind].id);
                str2 << std::endl << "  BarOrder " << streamIntVec(dependBarOrder) << "  Depth (" << dependBars[ind].depth << ")";

                ax.setString(str2.str());
                ax.setPosition(info.GUI.lBar.wid, 400);

                window.draw(ax);
                */

                sprTrashcan.setScale(2.2, 2.2);
                sprTrashcan.setPosition(barX + barWid/4, layerY + layerHei/2 - sprTrashcan.getGlobalBounds().height/2);

                window.draw(sprTrashcan);


            }


            std::stringstream str;

            str << ossos[ind]->name << " Id " << ind;

            ax.setString(str.str());
            window.draw(ax);









        }

        if(draggingBar){
            int barNumber = constrain((float)(info.mouseY - barY)/layerHei, 0, dependBarOrder.size()-1);
            float layerY = barY + layerHei*barNumber;

            bool inside  = ((info.mouseX - barX)/(barWid)) > 0.5 ? true : false;

            RectangleShape a(Vector2f(15, 15));
            a.setPosition( barX - 20, barY + layerY + layerHei/2 - 15/2);

            Color col = Color(200, 200, 250);
            if(inside){
                col.r = 250;
            }
            a.setFillColor(col);
            a.setOutlineColor(Color::Black);
            a.setOutlineThickness(2);
            window.draw(a);
        }




        timeManager.draw(window, info);






        /// Bones
        for(int i = 0; i < layerList.barIds.size(); i++){
            boneHandles[layerList.barIds[i]]->show(window, info);
        }

        for(int i = 0; i < dependBarOrder.size(); i++){

            int ind = dependBarOrder[i];
            if(boneHandles[ind]->bone->selected){
                boneHandles[ind]->showButtons(window, info);
            }
        }

        if(renaming){
            renameBox.draw(window);
        }



    }




    void update(engineInfo& info){

        //timeManager.changeSelectedBone();

        layerList.wid = info.GUI.rBar.lWid;
        layerList.hei = info.GUI.rBar.hei- info.GUI.rBar.lY;
        layerList.x   = info.GUI.rBar.x;
        layerList.y   = info.GUI.rBar.y + info.GUI.rBar.lY;


        info.toolSelected = toolSelected;

        if(info.mouseInside(info.GUI.dBar.toolX, info.GUI.dBar.y, info.GUI.dBar.hei*toolNumber, info.GUI.dBar.hei)){
            info.hoveringGUI = true;
            int ind = constrain(float(info.mouseX - info.GUI.dBar.toolX)/info.GUI.dBar.hei, 0, toolNumber);

            if(info.mouseState[0][1]){
                toolSelected = ind;
            }
        }




        // Selecting areas
        if(info.mouseState[0][1]){
            for(int i = 0; i < areas.size(); i++){

                float xx = i*(15+5) + 5;
                float yy = info.screenHeight-17.5;

                if(info.mouseInside(xx, yy, 15, 15)){
                    info.hoveringGUI = true;
                    areaSelected = i;
                }
            }
        }

        // Creating Bones
        if(info.mouseState[1][1]){
            if(areaSelected != -1){

                struct Bone* b = new struct Bone;

                //std::cout << "Everything nice" << std::endl;
                b->init(sprSheet.getTexture(), info);
                //std::cout << "Everything well" << std::endl;

                b->sprArea = areas[areaSelected];
                b->pos.x = info.mouseX;
                b->pos.y = info.mouseY;

                //std::cout << "Everything chill" << std::endl;
                ossos.push_back(b);


                BoneHandle* bH = new BoneHandle(b,  ossos, info);
                boneHandles.push_back(bH);




                struct dependBar st;
                st.id = ossos.size()-1;
                st.depth = 0;
                st.dependOn = -1;

                dependBars.push_back(st);
                dependBarOrder.push_back(ossos.size()-1);

                layerList.addBar(ossos.size()-1);

                timeManager.addBone();

            }
        }


       // if(info.typing == false){
            if(info.keyboardState[sf::Keyboard::LControl][0]){
                if(info.keyboardState[sf::Keyboard::N][2]){
                    int index = 0;
                    std::ifstream file("SniperModel.txt");
                    while(file.good()){

                        file.close();
                        index++;

                        std::string str = "SniperModel";
                        str += std::to_string(index);
                        str += ".txt";
                        file.open(str);
                    }
                    if(index != 0){
                        std::string str = "SniperModel";
                        str += std::to_string(index);
                        str += ".txt";

                        saveModel(str);
                    }else {
                        saveModel("SniperModel.txt");
                    }
                    //println("Nice creation");
                }

                if(info.keyboardState[sf::Keyboard::O][1]){
                    loadAnimation("FirstAnim.txt", info);
                }

                if(info.keyboardState[sf::Keyboard::L][2]){
                    loadModel("SniperModel.txt", info);
                   // println("Nice load");
                }

                if(info.keyboardState[sf::Keyboard::P][1]){
                    saveAnimation("SecondAnim.txt");
                    //println("Nice Anim creation");
                }
            }
       // }




        float barWid = info.GUI.rBar.wid;
        float barHei = info.GUI.rBar.hei - info.GUI.rBar.lY;
        float barX = info.GUI.rBar.x + info.GUI.rBar.lWid;
        float barY = info.GUI.rBar.y + info.GUI.rBar.lY;
        float layerHei = info.GUI.rBar.lHei;

        /// Selection creation
        if(info.mouseState[0][1]){
            if(info.mouseInside(0,0, sprSheet.getGlobalBounds().width, info.screenHeight)){
                info.selecting = true;
                info.selStart.x = info.mouseX;
                info.selStart.y = info.mouseY;
            }



            /// Selecting dependBars

            if(info.mouseInside(barX, barY, barWid, layerHei*dependBars.size())){



                info.hoveringGUI = true;
                draggingBar = true;

                int barNumber = constrain((float)(info.mouseY - barY)/layerHei, 0, dependBarOrder.size()-1);
                float layerY = barY + layerHei*barNumber;

                dependOff.y = info.mouseY - layerY;


                if(elementSelected == dependBarOrder[barNumber]){
                    if(info.mouseInside(barX + barWid/4, layerY + layerHei/2 - sprTrashcan.getGlobalBounds().height/2, sprTrashcan.getGlobalBounds().width, sprTrashcan.getGlobalBounds().height)){
                        if(info.toolSelected == 2){
                            removeBone(elementSelected);
                            elementSelected = -1;
                            draggingBar = false;
                        }
                    }
                }

                if(elementSelected != -1){
                    boneHandles[elementSelected]->bone->selected = false;

                    elementSelected = dependBarOrder[barNumber];
                    if(info.toolSelected == 3){
                        renameBox.selected = true;
                        renaming = true;
                        renameBox.setValue(ossos[elementSelected]->name);
                    }

                } else {
                    elementSelected = dependBarOrder[barNumber];
                }




                boneHandles[elementSelected]->bone->selected = true;
                //println("Selecting element " << boneHandles[elementSelected]->bone->name);
            }
        }



        /// Layer Order Update
        layerList.update(info);




        /// Drag Bar
        if(draggingBar){

            if(info.mouseState[0][2]){
                int barNumber = constrain((float)(info.mouseY - barY)/layerHei, 0, dependBarOrder.size()-1);
                float layerY = barY + layerHei*barNumber;

                bool inside  = ((info.mouseX - barX)/(barWid)) > 0.5 ? true : false;


                int otherInd = dependBarOrder[barNumber];
                int thisInd = elementSelected;

                if(otherInd != thisInd){

                    std::vector<int> allDependents;
                    getAllDependents(dependBars, thisInd, allDependents);
                    bool otherIsChild = false;
                    for(int i = 0; i < allDependents.size(); i++){
                        if(allDependents[i] == otherInd){
                            i = allDependents.size();
                            otherIsChild = true;
                        }
                    }



                    if(!otherIsChild){
                        if(inside){




                            boneHandles[thisInd]->addAttach(otherInd);
                            boneHandles[otherInd]->addChild(thisInd);
                            dependBars[otherInd].dependents.push_back(thisInd);


                            int oldDepend = dependBars[thisInd].dependOn ;
                            if(oldDepend != -1){
                                for(int i = 0; i < dependBars[oldDepend].dependents.size(); i++){
                                    if(dependBars[oldDepend].dependents[i] == thisInd){
                                        dependBars[oldDepend].dependents.erase(dependBars[oldDepend].dependents.begin() + i);
                                        i = dependBars[oldDepend].dependents.size();
                                    }
                                }
                            }


                            dependBars[thisInd].dependOn = otherInd;


                            updateAllDepths(dependBars, thisInd, dependBars[otherInd].depth+1);






                        } else {

                        // Order of thsi mai be improtant


                            int oldDepend = dependBars[thisInd].dependOn;
                            if(oldDepend != -1){
                                for(int i = 0; i < dependBars[oldDepend].dependents.size(); i++){
                                    if(dependBars[oldDepend].dependents[i] == thisInd){
                                        dependBars[oldDepend].dependents.erase(dependBars[oldDepend].dependents.begin() + i);
                                        i = dependBars[oldDepend].dependents.size();
                                    }
                                }
                            }


                            int otherDependOn = dependBars[otherInd].dependOn;
                            if(otherDependOn != -1){

                                boneHandles[thisInd]->addAttach(otherDependOn);
                                boneHandles[otherDependOn]->addChild(thisInd);
                                dependBars[otherDependOn].dependents.push_back(thisInd);


                                dependBars[thisInd].dependOn = otherDependOn;
                            } else {
                                boneHandles[thisInd]->removeAttach();

                                dependBars[thisInd].dependOn = -1;

                            }



                            updateAllDepths(dependBars, thisInd, dependBars[otherInd].depth);
                        }

                        for(int i = dependBarOrder.size()-1; i > -1; i--){



                            for(int j = 0; j < allDependents.size(); j++){
                                if(allDependents[j] == dependBarOrder[i]){
                                    dependBarOrder.erase(dependBarOrder.begin()+i);
                                    j = allDependents.size();
                                }
                            }

                        }



                        int otherOrder = -1;
                        for(int i = 0; i < dependBarOrder.size(); i++){
                            if(dependBarOrder[i] == otherInd){
                                otherOrder = i;
                                i = dependBarOrder.size();
                            }
                        }

                        std::vector<int> allOtherDependents;
                        getAllDependents(dependBars, otherInd, allOtherDependents);
                        int oSize = allOtherDependents.size();


                        for(int i = allDependents.size()-1; i > -1; i--){
                            dependBarOrder.insert(dependBarOrder.begin()+otherOrder+(inside?1:0) , allDependents[i]);
                        }

                    }

                }
                draggingBar = false;
            }


        }






        if(info.selecting){
            info.selEnd.x = info.mouseX;
            info.selEnd.y = info.mouseY;
            if(info.mouseState[0][0]){

            } else {
                info.selecting = false;

            }

        }



        if(timeManager.boneSelected != elementSelected){
            timeManager.changeSelectedBone(elementSelected);
        }





        timeManager.update(info);

        if(timeManager.hovered){
            info.hoveringGUI = true;
        }

        if(elementSelected != -1){
            if(timeManager.frameSelected.x != -1){

                bool kTrue = info.keyboardState[sf::Keyboard::K][1];
                bool fTrue = info.keyboardState[sf::Keyboard::F][1];
                bool sTrue = info.keyboardState[sf::Keyboard::S][1];
                if(kTrue || fTrue || sTrue){
                    int pType = timeManager.frameSelected.y;
                    struct Properties p;
                    p.init();
                    p.propertyId = pType;
                    p.frame = timeManager.frameSelected.x;

                    if(fTrue){
                        p.progressionType = 1;
                    } else if(sTrue){
                        p.progressionType = 2;
                    }

                    switch(pType){
                        case 0:
                            p.val = ossos[elementSelected]->center.x;
                            break;
                        case 1:
                            p.val = ossos[elementSelected]->center.y;
                            break;
                        case 2:
                            p.val = ossos[elementSelected]->attach.x;
                            break;
                        case 3:
                            p.val = ossos[elementSelected]->attach.y;
                            break;
                        case 4:
                            p.val = ossos[elementSelected]->offset.x;
                            break;
                        case 5:
                            p.val = ossos[elementSelected]->offset.y;
                            break;
                        case 6:
                            p.val = ossos[elementSelected]->xScl;
                            break;
                        case 7:
                            p.val = ossos[elementSelected]->yScl;
                            break;
                        case 8:
                            p.val = ossos[elementSelected]->angle;
                            break;
                    }


                    timeManager.createKeyFrameHere(elementSelected, pType, p);
                }
            }
        }



        bool hovered = false;
        int hoveredId = -1;
        for(int i = 0; i < dependBarOrder.size(); i++){

            int ind = dependBarOrder[i];

            boneHandles[ind]->update(info);


            if(!hovered){
                if(info.mouseState[0][1] && toolSelected == 0){
                    if(boneHandles[ind]->bone->hovered){
                        hovered = true;
                        //println("Hovering " << boneHandles[ind]->bone->name);
                        hoveredId = ind;
                        //println("Hovering ID " << boneHandles[hoveredId]->bone->name);
                    }
                }
            }
        }

        if(info.mouseState[0][1]){

                if(hovered){

                    //println("Hovering ID " << boneHandles[hoveredId]->bone->name);
                    if(elementSelected != -1){
                        boneHandles[elementSelected]->bone->selected = false;
                        //println("Desselecting element " << boneHandles[elementSelected]->bone->name);
                    }
                    elementSelected = hoveredId;
                    boneHandles[elementSelected]->bone->selected = true;
                    //println("Selecting element " << boneHandles[elementSelected]->bone->name);

                } else {
                    if(!info.hoveringGUI && ! toolSelected == 1){
                        if(elementSelected != -1){
                            boneHandles[elementSelected]->bone->selected = false;
                            //println("Desselecting element " << boneHandles[elementSelected]->bone->name);
                        }
                        elementSelected = -1;
                    }
                }


        }


        if(timeManager.clicked || timeManager.playing){
            float fPos = timeManager.frameSelected.x;
            if(timeManager.playing){
                fPos = timeManager.playingFrame;
            }
            for(int i = 0; i < timeManager.timeline.size(); i++){
                    if(timeManager.frameSelected.x != -1){




                        struct Properties p;
                        p = timeManager.getPropertyValue(i, 0, fPos);

                        if(p.exists){
                            ossos[i]->center.x = p.val;
                        }

                        p = timeManager.getPropertyValue(i, 1, fPos);

                        if(p.exists){
                            ossos[i]->center.y = p.val;
                        }

                        p = timeManager.getPropertyValue(i, 2, fPos);

                        if(p.exists){
                            ossos[i]->attach.x = p.val;
                        }

                        p = timeManager.getPropertyValue(i, 3, fPos);

                        if(p.exists){
                            ossos[i]->attach.y = p.val;
                        }

                        p = timeManager.getPropertyValue(i, 4, fPos);

                        if(p.exists){
                            ossos[i]->offset.x = p.val;
                        }

                        p = timeManager.getPropertyValue(i, 5, fPos);

                        if(p.exists){
                            ossos[i]->offset.y = p.val;
                        }

                        p = timeManager.getPropertyValue(i, 6, fPos);

                        if(p.exists){
                            ossos[i]->xScl = p.val;
                        }

                        p = timeManager.getPropertyValue(i, 7, fPos);

                        if(p.exists){
                            ossos[i]->yScl = p.val;
                        }


                        p = timeManager.getPropertyValue(i, 8, fPos);

                        if(p.exists){
                            ossos[i]->angle = p.val;
                        }


                    }

            }
        }



        if(renaming){
            renameBox.update(info);

            if(renameBox.confirmed){
                renaming = false;

                std::string name = renameBox.sVal;
                std::string addName = "";
                int index = 0;

                int ind = name.find("(");
                int ind2 = name.find(")");

                int cutChars = 0;

                if(ind != std::string::npos && ind2 != std::string::npos){
                    if(ind < ind2){
                        cutChars = name.size()-ind;
                    }
                }

                for(int i = 0; i < cutChars; i++){
                    name.pop_back();
                }

                bool findEqual = true;
                while(findEqual){

                    findEqual = false;
                    std::string completeName = name;
                    completeName += addName;

                    for(int i  = 0; i < ossos.size(); i++){
                        if(i != elementSelected){
                            if(ossos[i]->name == completeName){
                                findEqual = true;
                            }
                        }
                    }


                    if(findEqual){
                        index++;
                        addName = "(";
                        addName += std::to_string(index);
                        addName += ")";

                    }


                }

                name += addName;
                renameBox.setValue(name);

                if(elementSelected != -1){
                    ossos[elementSelected]->name = renameBox.sVal;
                }
            }
        }


        xWholeSclBox.update(info);
        if(xWholeSclBox.confirmed){
            info.xWholeScl = xWholeSclBox.fVal;
        }

        yWholeSclBox.update(info);
        if(yWholeSclBox.confirmed){
            info.yWholeScl = yWholeSclBox.fVal;
        }


        //if(info.GUI.update){
            for(int i = 0; i < boneHandles.size(); i++){
                boneHandles[i]->updateStuffPos(info);
            }
            timeManager.updatePosStuff(info);
        //}



    }

    void removeDependent(int barId, int dependentId){
        for(int i = 0; i < dependBars[barId].dependents.size(); i ++){
            if(dependBars[barId].dependents[i] == dependentId){
                dependBars[barId].dependents.erase(dependBars[barId].dependents.begin()+i);
                return;
            }
        }
    }

    void removeDependentOrder(){

    }



    void removeBone(int id){
        std::cout << "Removing Bone " << std::endl;



        dependBars[id].deleted = true;

        const struct dependBar thisBar = dependBars[id];




        int dependOn = thisBar.dependOn;
        if(dependOn != -1){
            removeDependent(dependOn, id);
        }

        for(int i = 0 ; i < thisBar.dependents.size(); i++){
            boneHandles[thisBar.dependents[i]]->removeAttach();


            dependBars[thisBar.dependents[i]].dependOn = dependOn;

            if(dependOn != -1){
                dependBars[dependOn].dependents.push_back(thisBar.dependents[i]);
                boneHandles[thisBar.dependents[i]]->addAttach(dependOn);
            }
        }


        //::vector<int> dependentsIds;
        //getAllDependents(dependBars, id, dependentsIds);

        if(dependOn == -1){
            updateAllDepths(dependBars, id, -1);
        } else {
            updateAllDepths(dependBars, id, dependBars[dependOn].depth);
        }


        std::cout << streamIntVec(dependBarOrder) << std::endl;


        for(int i = 0; i < dependBarOrder.size(); i++){
            if(dependBarOrder[i] == id){
                dependBarOrder.erase(dependBarOrder.begin() + i);
                i = dependBarOrder.size();
            }

        }


        layerList.removeBar(id);

        std::cout << streamIntVec(dependBarOrder) << std::endl;

    }

    float getFloatString(std::string& line, int start){
        std::string str = "";
        int ind = start;
        char c = line[ind];
        while(c != '\0' && c != '\n'){
            str += c;
        }

        return std::stof(str);
    }


    void clearModel(){
        ossos.clear();
        layerList.reset();
        dependBars.clear();
        boneHandles.clear();
        dependBarOrder.clear();

        println(ossos.size());
        println(layerList.barIds.size());
        println(dependBars.size());
        println(boneHandles.size());
        println(dependBarOrder.size());

        println("Resetando elementos");
    }

    void clearTimeline(){
        timeManager.timeline.clear();

        println("Resetando animation");
    }


    void loadAnimation(std::string filename, struct engineInfo& info){
        std::ifstream file(filename);


        if(file.is_open()){
            std::string str;
            std::getline(file, str);

            if(str == "2"){
                std::getline(file, str);

                clearTimeline();

                if(str == "Elements"){
                    std::getline(file, str);

                    if(str == "{"){


                        // For each Element
                        std::getline(file, str); // Gets element name

                        std::vector<std::vector<std::vector<struct Properties>>> elementsPropertiesKeyframes;

                        while(str != "}"){
                            // For each Property
                            std::getline(file, str); // {
                            std::getline(file, str); // Gets property name

                            std::vector<std::vector<struct Properties>> propertiesKeyframes;

                            while(str != "}"){
                                // For each KeyFrame
                                std::getline(file, str); // {

                                std::vector<struct Properties> keyframes;

                                std::getline(file, str); // [
                                while(str != "}"){

                                    struct Properties keyframe;
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

                        timeManager.timeline = elementsPropertiesKeyframes;

                        std::getline(file, str);

                        if(str == "Frames"){
                            std::getline(file, str);
                            timeManager.framesTotal  = std::stof(str);
                        }

                        if(str == "Speed"){
                            std::getline(file, str);
                            timeManager.playingSpeed = std::stof(str);
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

    void loadModel(std::string name, struct engineInfo& info){


        std::ifstream file(name);

        if(file.is_open()){


            std::string line;
            std::getline (file, line);

            int version = std::stoi(line);


             println("Checking Version");
            if(version == 1){
                println("Model Version " << version);
                clearModel();

                std::getline (file, line);

                println("Ordem de Execucao");
                if(line == "Execution Order"){
                    std::getline (file, line);
                    if(line == "{"){
                        std::getline (file, line);
                        while(line != "}"){
                            dependBarOrder.push_back(std::stoi(line));
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
                            layerList.addBar(std::stoi(line));
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

                            struct Bone* newBone = new struct Bone;
                            newBone->init(sprSheet.getTexture(), info);
                            newBone->pos.x = info.screenWidth/2;
                            newBone->pos.y = info.screenHeight/2;
                            struct dependBar newBar;

                            std::getline (file, line);
                            if(line == "["){
                                float fVal = 0;
                                int iVal = 0;
                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->center.x = fVal;


                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->center.y = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->attach.x = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->attach.y = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->offset.x = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->offset.y = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->xScl = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->yScl = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->angle = fVal;

                                /// Atach Id is int
                                std::getline (file, line);
                                iVal = std::stof(line);

                                newBone->attachId = iVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->sprArea.texRect.left = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->sprArea.texRect.top = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->sprArea.texRect.width = fVal;

                                std::getline (file, line);
                                fVal = std::stof(line);

                                newBone->sprArea.texRect.height = fVal;


                                newBone->name = name;
                                std::getline (file, line);
                            }else {
                                deleted = true;

                            }


                            std::getline (file, line);


                            newBar.id = id;
                            newBar.deleted = deleted;
                            newBar.dependOn = newBone->attachId;

                            dependBars.push_back(newBar);

                            ossos.push_back(newBone);

                        }
                    }

                }


                for(int i = 0; i < dependBars.size(); i++){
                    dependBars[i].depth = 0;
                    for(int j = 0; j < dependBars.size(); j++){
                        if(dependBars[j].dependOn == i){
                            dependBars[i].dependents.push_back(j);
                        }
                    }
                }

                for(int i = 0; i < dependBars.size(); i++){
                    if(dependBars[i].dependOn == -1){
                        updateAllDepths(dependBars, i, 0);
                    }
                }




                for(int i = 0; i < ossos.size(); i++){
                    BoneHandle* newBoneHandle = new BoneHandle(ossos[i], ossos, info);
                    boneHandles.push_back(newBoneHandle);
                    timeManager.addBone();
                }




                println(streamIntVec(dependBarOrder));
                println(streamIntVec(layerList.barIds));

                for(int i = 0; i < ossos.size(); i++){
                    println("Osso " << i << "  Angle: " << ossos[i]->angle);
                }

                for(int i = 0; i < dependBars.size(); i++){
                    println("Bar " << i << "  deleted: " << dependBars[i].deleted);
                }

                std::cout << "Sucesso" << std::endl;

            } else {
                std::cout << "Model Version not supported" << std::endl;
            }

        }

        file.close();

    }



    void saveAnimation(std::string name){
        std::ofstream file(name);


        if(file.is_open()){
            file << "2" << std::endl;

            file << "Elements" << std::endl;
            file << "{" << std::endl;

            for(int j = 0; j < timeManager.timeline.size(); j++){
                file << "Element " << j << std::endl;
                file << "{" << std::endl;
                for(int i = 0 ; i < timeManager.timeline[j].size(); i++){
                    file << timeManager.propertyName[i] << std::endl;
                    file << "{" << std::endl;
                    for(int k = 0; k < timeManager.timeline[j][i].size(); k++){
                        file << "[" << std::endl;
                        file << timeManager.timeline[j][i][k].val << std::endl;
                        file << timeManager.timeline[j][i][k].frame << std::endl;
                        file << timeManager.timeline[j][i][k].progressionType << std::endl;
                        file << timeManager.timeline[j][i][k].propertyId << std::endl;
                        file << "]" << std::endl;
                    }
                    file << "}" << std::endl;
                }
                file << "}" << std::endl;
            }

            file << "}" << std::endl;
            file << "Frames" << std::endl;
            file << timeManager.framesTotal << std::endl;
            file << "Speed" << std::endl;
            file << timeManager.playingSpeed << std::endl;
        }
    }

    void saveModel(std::string name){
        std::ofstream file(name);

        println("Criando..");



        float fPos = 0;

        for(int i = 0; i < timeManager.timeline.size(); i++){
            if(timeManager.frameSelected.x != -1){
                struct Properties p;
                p = timeManager.getPropertyValue(i, 0, fPos);

                if(p.exists){
                    ossos[i]->center.x = p.centerX;
                }

                p = timeManager.getPropertyValue(i, 1, fPos);

                if(p.exists){
                    ossos[i]->center.y = p.centerY;
                }

                p = timeManager.getPropertyValue(i, 2, fPos);

                if(p.exists){
                    ossos[i]->attach.x = p.attachX;
                }

                p = timeManager.getPropertyValue(i, 3, fPos);

                if(p.exists){
                    ossos[i]->attach.y = p.attachY;
                }

                p = timeManager.getPropertyValue(i, 4, fPos);

                if(p.exists){
                    ossos[i]->offset.x = p.offsetX;
                }

                p = timeManager.getPropertyValue(i, 5, fPos);

                if(p.exists){
                    ossos[i]->offset.y = p.offsetY;
                }

                p = timeManager.getPropertyValue(i, 6, fPos);

                if(p.exists){
                    ossos[i]->xScl = p.xScl;
                }

                p = timeManager.getPropertyValue(i, 7, fPos);

                if(p.exists){
                    ossos[i]->yScl = p.yScl;
                }


                p = timeManager.getPropertyValue(i, 8, fPos);

                if(p.exists){
                    ossos[i]->angle = p.angle;
                }
            }

        }



        if(file.is_open()){
            file << "1" << std::endl;

            file << "Execution Order" << std::endl;
            file << "{" << std::endl;

            for(int i = 0; i < dependBarOrder.size(); i++){
                file << dependBarOrder[i] << std::endl;
            }

            file << "}" << std::endl;


            file << "Draw Order" << std::endl;
            file << "{" << std::endl;

            for(int i = 0; i < dependBarOrder.size(); i++){
                file << layerList.barIds[i] << std::endl;
            }

            file << "}" << std::endl;


            file << "Elements" << std::endl;
            file << "{" << std::endl;

            for(int i = 0; i < dependBars.size(); i++){

                if(dependBars[i].deleted){
                    file <<  i  << std::endl;
                    file << "*" << std::endl;
                    file << "*" << std::endl;
                } else {

                    file <<  i  << std::endl;

                    std::string str = "*";
                    if(ossos[i]->name != ""){
                        str = ossos[i]->name;
                    }

                    file << str << std::endl;

                    file << "[" << std::endl;

                    // CenterX
                    file << ossos[i]->center.x << std::endl;

                    // CenterY
                    file << ossos[i]->center.y << std::endl;

                    // AttachX
                    file << ossos[i]->attach.x << std::endl;

                    // AttachY
                    file << ossos[i]->attach.y << std::endl;

                    // OffsetX
                    file << ossos[i]->offset.x << std::endl;

                    // OffsetY
                    file << ossos[i]->offset.y << std::endl;

                    // XScl
                    file << ossos[i]->xScl << std::endl;

                    // YScl
                    file << ossos[i]->yScl << std::endl;

                    // Angle
                    file << ossos[i]->angle << std::endl;

                    // Attach Id
                    file << ossos[i]->attachId << std::endl;

                    file << ossos[i]->sprArea.texRect.left   << std::endl;
                    file << ossos[i]->sprArea.texRect.top    << std::endl;
                    file << ossos[i]->sprArea.texRect.width  << std::endl;
                    file << ossos[i]->sprArea.texRect.height << std::endl;



                    file << "]" << std::endl;
                }


            }

            file << "}" << std::endl;








        }
        file.close();

        println("Criou!");
    }



};

#endif // BONEMANAGER_H_INCLUDED
