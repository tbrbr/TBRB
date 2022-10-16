#ifndef BONEHANDLE_H_INCLUDED
#define BONEHANDLE_H_INCLUDED

class BoneHandle{
    public:
    struct Bone* bone;

    std::vector<struct Bone*>& allBones;


    BoneHandle(struct Bone* _bone, std::vector<struct Bone*>& _allBones, struct engineInfo& _info): allBones(_allBones){
        bone = _bone;
    }

    void show(sf::RenderWindow& window, struct engineInfo& info){
        /// Sprite
        // Probably wont use
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




        /// Frame
        if(info.toolSelected != 1 || bone->selected){
            Color rectColor(200,200, 200, 20);
            Color borderColor(255, 255, 255, 40);


            if(bone->hovered){
                rectColor.a = 40;
                borderColor.a = 100;
            }

            if(bone->selected){
                rectColor.a = 100;
            }


            float selWid = bone->sprArea.texRect.width *bone->finalXScl;
            float selHei = bone->sprArea.texRect.height*bone->finalYScl;

            RectangleShape select(Vector2f(selWid, selHei));
            select.setPosition(bone->pos.x, bone->pos.y);

            select.setFillColor(rectColor);
            select.setOutlineColor(borderColor);
            select.setOutlineThickness(4);

            window.draw(select);
        }
    }

    void showButtons(sf::RenderWindow& window, struct engineInfo& info){
        if(bone->selected){

            bone->drags[1].draw(window);

            bone->drags[2].draw(window);

            bone->drags[0].draw(window);

            bone->drags[4].draw(window);


            if(bone->attachId != -1){
                bone->drags[3].draw(window);
            }


            for(int i = 0; i < bone->sliderNum; i++){
                bone->sliders[i]->drawSlider(window);
            }

            for(int i = 0; i < bone->textBoxNum; i++){
                bone->boxes[i].draw(window);
            }


            sf::Text t;
            std::stringstream str;

            str << " | PosX: " << bone->pos.x << " | PosY: " << bone->pos.y << std::endl;
            str << " | AttachX: " << bone->attach.x << " | AttachY: " << bone->attach.y << std::endl;
            str << " | AreaWid: " << bone->sprArea.texRect.width << " | AreaHei: " << bone->sprArea.texRect.height << std::endl;
            str << " | MouseX: " << info.mouseX << " | MouseY: " << info.mouseY;
            str << " | Angle: " << bone->angle;

            t.setString(str.str());
            t.setCharacterSize(15);
            t.setColor(Color::Black);
            t.setFont(font);
            t.setPosition(info.GUI.dBar.toolX, 0);
            window.draw(t);

        }

    }



    void updateStuffPos(struct engineInfo& info){
        bone->updateStuffPos(info);
    }














    bool isHovered( struct engineInfo& info){
       // Hovering
        bool hovered = false;
        // Here we could include Hovering the Spheres and Sliders
        //std:: cout << " Hover " << std::endl;

        float xx = bone->pos.x;
        float yy = bone->pos.y;
        float ww = bone->sprArea.texRect.width*bone->finalXScl;
        float hh = bone->sprArea.texRect.height*bone->finalYScl;


        if(bone->finalXScl < 0){
            ww *= -1;
            xx -= ww;
        }

        if(bone->finalYScl < 0){
            hh *= -1;
            yy -= hh;
        }


        if(info.mouseInside( xx, yy, ww, hh)){

            hovered = true;
        }


        if(bone->selected){
            for(int i = 0; i < bone->dragNum; i++){
                if(bone->drags[i].hovered){
                    hovered = true;
                }
            }

            for(int i =0 ; i < bone->sliderNum; i++){
                if(bone->sliders[i]->hovered){
                    hovered = true;
                }
            }

            for(int i = 0; i < bone->textBoxNum; i++){
                if(bone->boxes[i].hovered){
                    hovered = true;

                }
            }
        }

        return hovered;
    }

    void update(struct engineInfo& info){



        bone->xWholeScl = info.xWholeScl;
        bone->yWholeScl = info.yWholeScl;
        bone->xWhole = info.xWhole;
        bone->yWhole = info.yWhole;



        // Hovering
        bone->hovered = isHovered(info);
        if(bone->hovered){
            info.hoveringGUI = true;
        }

        // Selecting
        /*
        if(info.mouseState[0][1] && info.toolSelected == 0){
            if(bone->hovered){
                bone->selected = true;
            } else if(!info.hoveringGUI){
                bone->selected = false;
            }
        }
        */





        /// Sliders, Buttons and Stuff
        if(bone->selected){


            for(int i = 0; i < bone->dragNum; i++){
                bone->drags[i].update(info);
            }



            /// Position dragger
            if(bone->attachId == -1){
                if(bone->drags[1].dragged){
                    bone->pos.x = bone->drags[1].x + 10;
                    bone->pos.y = bone->drags[1].y + 10;
                } else {
                    bone->drags[1].x = bone->pos.x - 10;
                    bone->drags[1].y = bone->pos.y - 10;
                }
            } else {

                /// Maybe manipulate the offset here
                if(bone->drags[1].dragged){
                    if(info.xWholeScl != 0){
                        bone->offset.x += (bone->drags[1].x - bone->drags[1].prevX)/info.xWholeScl;
                    }

                    if(info.yWholeScl){
                        bone->offset.y += (bone->drags[1].y - bone->drags[1].prevY)/info.yWholeScl;
                    }
                } else {
                    bone->drags[1].x = bone->pos.x - 10;
                    bone->drags[1].y = bone->pos.y - 10;
                }
            }




            /// Center dragger on Texture
            if(bone->drags[2].dragged){

                bone->center.x = (bone->drags[2].x - info.sprX)/info.sheetScl - bone->sprArea.texRect.left;
                bone->center.y = (bone->drags[2].y - info.sprY)/info.sheetScl - bone->sprArea.texRect.top;

            }else {

                bone->drags[2].x = info.sprX + (bone->center.x + bone->sprArea.texRect.left)*info.sheetScl;
                bone->drags[2].y = info.sprY + (bone->center.y + bone->sprArea.texRect.top)*info.sheetScl;
            }


            /// Attach dragger on Texture
            if(bone->attachId != -1){
                if(bone->drags[3].dragged){

                    bone->attach.x = (bone->drags[3].x - info.sprX)/info.sheetScl - allBones[bone->attachId]->sprArea.texRect.left;
                    bone->attach.y = (bone->drags[3].y - info.sprY)/info.sheetScl - allBones[bone->attachId]->sprArea.texRect.top;

                }else {

                    bone->drags[3].x = info.sprX + (allBones[bone->attachId]->sprArea.texRect.left + bone->attach.x)*info.sheetScl;
                    bone->drags[3].y = info.sprY + (allBones[bone->attachId]->sprArea.texRect.top  + bone->attach.y)*info.sheetScl;
                }
            }




            /// Center dragger on Bone
            if(bone->drags[0].released){


               // println("Working great");
                float xx = bone->drags[0].x - bone->drawPos.x;
                float yy = bone->drags[0].y - bone->drawPos.y;

                //println("bone->center.x" << bone->center.x << " bone->center.y" << bone->center.y );

                bone->center.x += xx/bone->finalXScl;
                bone->center.y += yy/bone->finalYScl;
                //println("bone->center.x" << bone->center.x << " bone->center.y" << bone->center.y );

            } else if(!bone->drags[0].dragged){


                bone->drags[0].x = bone->drawPos.x;
                bone->drags[0].y = bone->drawPos.y;
            }




            /// Angle dragger on Bone
            if(!bone->drags[4].dragged){


                float correctedAngle = 3.141592*bone->angle/180;

                bone->drags[4].x = bone->drawPos.x + cos(correctedAngle)*100;
                bone->drags[4].y = bone->drawPos.y + sin(correctedAngle)*100;
            } else {


                float xxPrev = bone->drags[4].prevX - bone->drawPos.x;
                float yyPrev = bone->drags[4].prevY - bone->drawPos.y;

                float angPrev = 0;

                if(xxPrev != 0){
                    angPrev = 180*atan(yyPrev/xxPrev)/3.141592;

                    if(xxPrev < 0){
                        angPrev += 180;
                    }

                    if(angPrev < 0){
                        angPrev = 360 + angPrev;
                    }
                }

                float xx = bone->drags[4].x - bone->drawPos.x;
                float yy = bone->drags[4].y - bone->drawPos.y;



                float ang = 0;
                if(xx != 0){
                    ang = 180*atan(yy/xx)/3.141592;

                    if(xx < 0){
                        ang += 180;
                    }
                    if(ang < 0){
                        ang = 360 + ang;
                    }
                }


                if(xxPrev != 0 && xx != 0){
                    float angStep = ang - angPrev;



                    float angStepSign = (angStep > 0) ? 1: -1;


                    if(angStep*angStepSign > 180){
                        angStep = -angStepSign*360 + angStep;
                    }


                    bone->angle += angStep;



                }

                    float correctedAngle = 3.141592*bone->angle/180;

                    bone->drags[4].x = bone->drawPos.x + cos(correctedAngle)*100;
                    bone->drags[4].y = bone->drawPos.y + sin(correctedAngle)*100;

            }



            /// Angle Slider
            for(int i = 0; i < bone->sliderNum; i++){
                bone->sliders[i]->updateSlider(info);
            }


            for(int i = 0; i < bone->textBoxNum; i++){
                bone->boxes[i].update(info);

            }


            if(bone->boxes[bone->EAngle].confirmed){
                bone->angle = bone->boxes[bone->EAngle].fVal;
            }
            if(!bone->boxes[bone->EAngle].selected){
                bone->boxes[bone->EAngle].setValue(bone->angle);
            }


            if(bone->boxes[bone->EXScl].confirmed){
                bone->xScl = bone->boxes[bone->EXScl].fVal;
            }
            if(!bone->boxes[bone->EXScl].selected){
                bone->boxes[bone->EXScl].setValue(bone->xScl);
            }

            if(bone->boxes[bone->EYScl].confirmed){
                bone->yScl = bone->boxes[bone->EYScl].fVal;
            }
            if(!bone->boxes[bone->EYScl].selected){
                bone->boxes[bone->EYScl].setValue(bone->yScl);
            }

            if(bone->boxes[bone->EAttachX].confirmed){
                bone->attach.x = bone->boxes[bone->EAttachX].fVal;
            }
            if(!bone->boxes[bone->EAttachX].selected){
                bone->boxes[bone->EAttachX].setValue(bone->attach.x);
            }

            if(bone->boxes[bone->EAttachY].confirmed){
                bone->attach.y = bone->boxes[bone->EAttachY].fVal;
            }
            if(!bone->boxes[bone->EAttachY].selected){
                bone->boxes[bone->EAttachY].setValue(bone->attach.y);
            }

            if(bone->boxes[bone->EOffsetX].confirmed){
                bone->offset.x = bone->boxes[bone->EOffsetX].fVal;
            }
            if(!bone->boxes[bone->EOffsetX].selected){
                bone->boxes[bone->EOffsetX].setValue(bone->offset.x);
            }

            if(bone->boxes[bone->EOffsetY].confirmed){
                bone->offset.y = bone->boxes[bone->EOffsetY].fVal;
            }
            if(!bone->boxes[bone->EOffsetY].selected){
                bone->boxes[bone->EOffsetY].setValue(bone->offset.y);
            }




            if(bone->boxes[bone->ECenterX].confirmed){
                bone->center.x = bone->boxes[bone->ECenterX].fVal;
            }
            if(!bone->boxes[bone->ECenterX].selected){
                bone->boxes[bone->ECenterX].setValue(bone->center.x);
            }

            if(bone->boxes[bone->ECenterY].confirmed){
                bone->center.y = bone->boxes[bone->ECenterY].fVal;
            }
            if(!bone->boxes[bone->ECenterY].selected){
                bone->boxes[bone->ECenterY].setValue(bone->center.y);
            }



        }










        if(bone->attachId != -1){
            const struct Bone b = *allBones[ bone->attachId];

            /// This is somewhat redundant
            // But could be useful when deattaching
            bone->otherAngle    = b.finalAngle;





            bone->finalAngle = bone->angle + bone->otherAngle*(1-bone->ignoreOtherAngle);
            //bone->finalAngle = bone->angle + bone->otherAngle;


            bone->finalXScl = bone->xScl * bone->xWholeScl;
            bone->finalYScl = bone->yScl * bone->yWholeScl;


            bone->otherPos.x    = b.pos.x;
            bone->otherPos.y    = b.pos.y;
            bone->otherCenter   = b.center;

            /// We still need to have xScl and yScl in here if we want for it to flip correctly





            float attachXRotated = b.finalXScl * bone->attach.x;
            float attachYRotated = b.finalYScl * bone->attach.y;

            float ignoreP = (1-bone->ignoreOtherPos);



            // Transforms from degrees to radians
            float correctedAngle = bone->otherAngle;
            if(b.finalXScl < 0){
                correctedAngle *= -1;
            }
            if(b.finalYScl < 0){
                correctedAngle *= -1;
            }


            correctedAngle = 3.141592*correctedAngle/180;






            /// Calculating the attach based on the otherAngle
            attachYRotated = bone->ignoreOtherPos*attachYRotated + ignoreP*(b.finalXScl * sin(correctedAngle) * bone->attach.x + b.finalYScl * cos(correctedAngle) * bone->attach.y);
            attachXRotated = bone->ignoreOtherPos*attachXRotated + ignoreP*(b.finalXScl * cos(correctedAngle) * bone->attach.x - b.finalYScl * sin(correctedAngle) * bone->attach.y);

            //attachYRotated = b.finalXScl * sin(correctedAngle) * bone->attach.x + b.finalYScl * cos(correctedAngle) * bone->attach.y;
            //attachXRotated = b.finalXScl * cos(correctedAngle) * bone->attach.x - b.finalYScl * sin(correctedAngle) * bone->attach.y;


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

            bone->xWholeAttach = bone->xWhole;
            bone->yWholeAttach = bone->yWhole;

            bone->finalAngle = bone->angle;
            bone->finalXScl  = bone->xScl * bone->xWholeScl;
            bone->finalYScl  = bone->yScl * bone->yWholeScl;


            bone->drawPos.x = bone->pos.x + bone->center.x*bone->finalXScl;
            bone->drawPos.y = bone->pos.y + bone->center.y*bone->finalYScl;
        }

        /// Rotation issue may be correct by otherAngle


    }

    void addChild(int id){
        bone->dependents.push_back(id);
    }

    void removeChild(int id){
        for(int i = 0; i < bone->dependents.size(); i++){
            if(bone->dependents[i] == id){
                if(allBones[bone->dependents[i]]->attachId == bone->id){
                    allBones[bone->dependents[i]]->removeAttach();
                }
                bone->dependents.erase(bone->dependents.begin() + i);

            }
        }

    }



    /// This goes inside Bone not here
    void removeAttach(){
        bone->attachId = -1;

        // Maybe some compensation here !!
        bone->attach.x = 0;
        bone->attach.y = 0;

        bone->angle += bone->otherAngle*(1-bone->ignoreOtherAngle);

        bone->otherAngle = 0;
        bone->offset.x = 0;
        bone->offset.y = 0;
    }

    /// This goes inside Bone not here
    void addAttach(int id){

        removeAttach();


        bone->attachId = id;


        bone->angle -= allBones[id]->finalAngle *(1-bone->ignoreOtherAngle);


        const struct Bone b = *allBones[ bone->attachId];

        float correctedAngle = b.finalAngle;
        if(b.finalXScl < 0){
            correctedAngle *=  -1;
        }
        if(b.finalYScl < 0){
            correctedAngle *=  -1;
        }

        correctedAngle = 3.141592*correctedAngle/180;




        float rotOCenterX = b.finalXScl * cos(correctedAngle) * b.center.x - b.finalYScl * sin(correctedAngle) * b.center.y;
        float rotOCenterY = b.finalXScl * sin(correctedAngle) * b.center.x + b.finalYScl * cos(correctedAngle) * b.center.y;

        float rotX = b.drawPos.x - (rotOCenterX);
        float rotY = b.drawPos.y - (rotOCenterY);

        float atXDif = bone->drawPos.x -rotX;
        float atYDif = bone->drawPos.y -rotY;





        float rotXAt = atXDif*(bone->ignoreOtherPos);
        float rotYAt = atYDif*(bone->ignoreOtherPos);




        rotXAt += (1-bone->ignoreOtherPos) *( cos(-correctedAngle) * atXDif - sin(-correctedAngle) * atYDif);
        rotYAt += (1-bone->ignoreOtherPos) *( sin(-correctedAngle) * atXDif + cos(-correctedAngle) * atYDif);



        rotXAt /= b.finalXScl;
        rotYAt /= b.finalYScl;

        bone->attach.x = rotXAt;
        bone->attach.y = rotYAt;

        //std::cout << " ATX: " << bone->attach.x <<
    }

};

#endif // BONEHANDLE_H_INCLUDED
