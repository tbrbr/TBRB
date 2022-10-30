#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

struct ValBox{
    float x;
    float y;
    float wid;
    float hei;

    std::string input;

    std::string label;

    std::string strDisplay;

    std::string sVal;

    float fVal = 0;
    int decimalPrecision = 2;

    int iVal = 0;

    int textLimit = 20;

    int frames = 0;

    bool hovered = false;
    bool selected = false;
    bool confirmed = false;

    bool confirmOutOfFocus = true;

    bool labelSide = false;

    /// 0 == float, 1 == int, 2 == string
    int type = 2;


    void init2(){
        if(type != 2){
            textLimit = 8;
        }
    }

    void init(int ttype, float xx, float yy, float ww, float hh, int val){
        type = ttype;
        x = xx;
        y = yy;
        wid = ww;
        hei = hh;

        setValue(val);
        init2();
    }

    void init(int ttype, float xx, float yy, float ww, float hh, float val){
        type = ttype;
        x = xx;
        y = yy;
        wid = ww;
        hei = hh;

        setValue(val);
        init2();
    }

    void init(int ttype, float xx, float yy, float ww, float hh, std::string val){
        type = ttype;
        x = xx;
        y = yy;
        wid = ww;
        hei = hh;

        setValue(val);
        init2();
    }

    void updatePosSize(float xx, float yy, float ww, float hh){
        x = xx;
        y = yy;
        wid = ww;
        hei = hh;
    }

    void update(struct engineInfo& info){
        hovered = false;
        confirmed = false;

        if(selected){
            info.typing = true;

        }

        if(info.mouseInside(x, y, wid, hei)){
            hovered = true;

        }



        if(info.mouseState[0][1]){
            if(hovered){
                input = "";
                selected = true;
            } else if(confirmOutOfFocus && selected){
                if(type == 0){
                    setValue(fVal);
                } else if (type == 1){
                    setValue(iVal);
                } else {
                    setValue(sVal);
                }
                selected = false;

            }
        }

        if(selected){
            if(info.deleteChar){
                subText();
            } else if (info.newInput) {
                addText(info.lastChar);
            } else if (info.confirmInput){
                confirm();
                selected = false;
            }
        }

    }

    void draw(RenderWindow& window){
        RectangleShape rect(Vector2f(wid, hei));
        rect.setPosition(x, y);


        Color col = Color(100, 100, 100);



        if(selected){
            col.b -= 20;
            col.r -= 20;
            col.g -= 20;
            frames+=1;
        }

        if(hovered){
            col.b -= 10;
            col.r -= 10;
            col.g -= 10;
        }

        rect.setFillColor(col);
        rect.setOutlineColor(Color(150, 150, 150));
        rect.setOutlineThickness(2);

        window.draw(rect);


        float fontSize =  hei/1.4;
        Text t(input, font, fontSize);
        t.setFillColor(Color(255, 255, 255));
        t.setPosition(x, y + hei/2 - fontSize/2);

        window.draw(t);

        fontSize *= 0.8;


        Text tLabel(label, font, fontSize);
        tLabel.setFillColor(Color(255, 255, 255));

        if(labelSide){
            tLabel.setPosition(x + wid*1.1, y);
        } else {
            tLabel.setPosition(x, y + hei);
        }

        window.draw(tLabel);





        if(selected){
            col = Color(50, 50, 50);
            if(frames > 30){
                if(frames > 60){
                    frames = 0;
                }
                col.a = 0;
            }

            rect.setPosition(x + t.getGlobalBounds().width +4, y + hei*0.125);
            rect.setSize(Vector2f(2, hei*0.75));
            rect.setFillColor(col);
            rect.setOutlineColor(Color(150, 150, 150));
            rect.setOutlineThickness(0);

            window.draw(rect);
        }
    }

    void addText(char character){

        //std::cout << "Add Text "<< std::endl;
        if(input.length() < textLimit){


            if(type == 0){
                //std::cout << "Adding "<< std::endl;
                if(((int)character >= '0' && (int)character <= '9') || character == '.' || character == '-'){
                    //std::cout << "Opan " << std::endl;
                    input += character;
                    //std::cout << input << std::endl;
                }
            } else if(type == 1){
                if(((int)character >= '0' && (int)character <= '9') || character == '-'){
                    input += character;
                }
            } else if(type == 2){
                input += character;
            }

        }
    }

    void subText(){
        if(input.length() > 0){
            input.pop_back();
        }
    }

    void confirm(){
        confirmed = true;
        if(type == 0){
            if(input.length() == 0){
                fVal = 0;
            } else {


                try{

                    fVal = std::stof(input);

                    int thing = pow(10, decimalPrecision);

                    fVal = (float)((int)(fVal*thing))/thing;
                } catch(...){
                    fVal = 0;
                    input.clear();
                }

            }
        } else if(type == 1){
            if(input.length() == 0){
                iVal = 0;
            } else{
                try{
                    iVal = std::stoi(input);
                } catch(...){
                    iVal = 0;
                    input.clear();
                }
            }
        } else if(type == 2){
            sVal = input;
        }
    }

    void setValue(int val){
        input = std::to_string(val);
        confirm();
    }

    void setValue(float val){
        input = std::to_string(val);
        int decimals = 0;
;
        for(int i = input.length()-1; i > -1; i--){
            if(input.at(i) != '.'){
                decimals++;
            } else {
                for(int j = 0; j < decimals-decimalPrecision; j++){
                    input.pop_back();
                }
                i = -1;

            }
        }
        confirm();
    }

    void setValue(std::string val){
        input = val;
        confirm();
    }

};



struct Button{
    float x =0;
    float y= 0;
    float wid = 0;
    float hei  = 0;
    Sprite sprite;

};




class Slider{

public:
  float x;
  float y;
  float sliderX;
  float len;
  float hei;
  float maxVal;
  float minVal;
  float val;

  bool moved;
  bool hovered;

  float sliderWid;
  float sliderHei;

  bool holded;
  float mouseXOff;
  //float mouseYOff;

  Slider(float _x, float _y, float _len, float _min, float _max, float _startVal){
    x = _x;
    y = _y;
    len = _len;
    maxVal = _max;
    minVal = _min;

    hei = 5;
    sliderWid = hei*4;
    sliderHei = hei*4;

    mouseXOff = 0;

    holded = false;
    moved = false;

    updateValue(_startVal);
  }

  void updateValue(float value){
    val = constrain(value, minVal, maxVal);
    sliderX = len*((val-minVal)/(maxVal-minVal));
  }

  void updateSlider(struct engineInfo& info){

    float xx = x+sliderX-(sliderWid/2);
    float yy = y+(hei/2)-(sliderHei/2);

    hovered = false;
    if(info.mouseInside(xx, yy, sliderWid, sliderHei)){
        hovered = true;
    }


    if(!holded){
      moved = false;
      if(info.mouseState[0][1]){


        if(hovered){
          holded = true;
          mouseXOff = (sliderWid/2)-(info.mouseX-xx);
        }
      }
    } else {
      moved = true;
      if(info.mouseState[0][0]){
        sliderX = constrain(info.mouseX-x+mouseXOff, 0, len);
      } else {
        holded = false;
      }
    }



    updateValue(((sliderX/len)*(maxVal-minVal))+minVal);
  }

  void drawSlider(sf::RenderWindow& window){

    //Line
     Color strokeColor(100);
     Color fillColor(60);

    RectangleShape select(Vector2f(len, hei));
    select.setPosition(x, y);
    select.setFillColor(fillColor);
    select.setOutlineColor(strokeColor);
    select.setOutlineThickness(2);

    window.draw(select);




     //Slider

    RectangleShape slider(Vector2f(sliderWid, sliderHei));
    slider.setPosition(x+sliderX-(sliderWid/2), y+(hei/2)-(sliderHei/2));
    slider.setFillColor(Color(200));
    slider.setOutlineColor(Color(200));

    window.draw(slider);


     //Valor
    // textAlign(LEFT, CENTER);
     //textSize(20);
     //text((int)val, x + len + (sliderWid/2) + 4, y);
  }
};


struct dragCircle{
    bool hovered = false;
    bool dragged = false;

    bool draggable = true;

    bool released = false;

    float x = 0;
    float y = 0;

    float prevX = 0;
    float prevY = 0;

    float rad = 10;
    Color col = Color::Red;

    void init(){

    }


    void draw(RenderWindow& window){
        CircleShape circle;
        circle.setRadius(rad);
        circle.setPosition(x-rad,y-rad);

         circle.setOutlineThickness(2);
        if(hovered || dragged){
            circle.setOutlineThickness(4);
        }

        circle.setOutlineColor(Color::Black);

        circle.setFillColor(col);

        window.draw(circle);
    }

    void update(struct engineInfo& info){

        released = false;
        hovered = false;

        prevX = x;
        prevY = y;

        if(info.mouseX > x - rad && info.mouseX < x + rad){
            if(info.mouseY > y - rad && info.mouseY < y + rad){
                hovered = true;
            }
        }


        if(draggable){
            if(!dragged){
                if(info.mouseState[0][1]){
                    if(hovered){

                        dragged = true;

                    }
                }
            } else {
                x = info.mouseX;
                y = info.mouseY;
                if(info.mouseState[0][1]){
                    dragged = false;
                    released = true;
                }
            }
        }
    }
};


struct barListManager{
    float x;
    float y;
    float wid;
    float hei;
    float barHei;

    bool hovered = false;
    int barHovered = -1;
    int barSelected = -1;

    float mouseXOff = 0;
    float mouseYOff = 0;

    bool draggingBar = false;

    std::vector<int> barIds;

    void init(){
        x = 0;
        y = 0;
        wid = 100;
        hei = 400;
        barHei = 40;

    }

    void reset(){
        hovered = false;
        barHovered = -1;
        barSelected = -1;

        mouseXOff = 0;
        mouseYOff = 0;

        draggingBar = false;

        barIds.clear();
    }

    void addBar(int id, int position = -1){

        if(position != -1){
            barIds.insert(barIds.begin()+position, id);
        } else {
            barIds.insert(barIds.begin()+barIds.size(), id);
        }
    }

    void removeBar(int id){
        for(int i =0; i< barIds.size(); i++){
            if(barIds[i] == id){
                barIds.erase(barIds.begin() + i);
                i = barIds.size();
            }
        }
    }

    void update(struct engineInfo& info){

        hovered = false;
        barHovered = -1;

        if(barIds.size() > 0){
            if(info.mouseInside(x, y, wid, hei)){
                hovered = true;

                int id = constrain((float)(info.mouseY-y)/barHei, 0, barIds.size()-1);


                barHovered = id;


                if(info.mouseState[0][1]){

                    mouseXOff = info.mouseX - x;
                    mouseYOff = info.mouseY - (y + barHei*id);

                    barSelected = id;
                    draggingBar = true;
                }
            }
        }

        if(info.mouseState[0][2]){
            if(draggingBar){
                if(barSelected != -1){
                    if(barHovered != -1){
                        if(barHovered != barSelected){
                            if(barHovered > barSelected){


                                int tempId =  barIds[barSelected];

                                barIds.erase(barIds.begin()+barSelected);
                                barIds.insert(barIds.begin()+barHovered, tempId);




                            } else {

                                int tempId =  barIds[barSelected];

                                barIds.erase(barIds.begin()+barSelected);
                                barIds.insert(barIds.begin()+barHovered +1, tempId);
                            }
                        }
                    }
                }

                barSelected = -1;
                draggingBar = false;
            }
        }
    }

    void draw(RenderWindow& window, struct engineInfo& info){

        Color colFundo = Color(100);
        RectangleShape fundo(Vector2f(wid, hei));
        fundo.setPosition(x, y);
        fundo.setFillColor(colFundo);
        window.draw(fundo);


        for(int i = 0; i < barIds.size(); i++){


            int addI = 0;
            if(draggingBar && barSelected != -1){
                if(i > barHovered){
                    addI++;
                }

                if(i > barSelected){
                    addI--;
                }
            }


            float layerX = x;
            float layerY = y + barHei*(i+addI);

            if(i != barSelected){

                Color col = Color((127*barIds[i] + 100)%255, (231*barIds[i])%255, (barIds[i]*33)%255);

                RectangleShape depBar(Vector2f(wid, barHei));
                depBar.setPosition(layerX, layerY);
                depBar.setFillColor(col);
                window.draw(depBar);


                col = Color::Black;
                col.a = 100;
                depBar.setSize(Vector2f(wid/2, barHei));
                depBar.setPosition(layerX + wid/2, layerY);
                depBar.setFillColor(col);
                window.draw(depBar);

                if(i == barHovered){
                    RectangleShape lilBar(Vector2f(wid, barHei/3));
                    lilBar.setPosition(layerX, layerY + barHei*2/3);
                    lilBar.setFillColor(col);
                    window.draw(lilBar);
                }



                Text ax;
                ax.setPosition( x , layerY + barHei/2 - 15/2);
                ax.setFillColor(Color::Black);
                ax.setOutlineColor(Color::White);
                ax.setOutlineThickness(2);
                ax.setFont(font);
                ax.setCharacterSize(15);

                std::stringstream str;
                str << "Id " << barIds[i];

                ax.setString(str.str());

                window.draw(ax);
            }



        }

        if(draggingBar && barSelected != -1){

            int i = barSelected;
            float layerX = x;
            float layerY = y + barHei*i;


            layerY = info.mouseY - mouseYOff;



            Color col = Color((127*barIds[i] + 100)%255, (231*barIds[i])%255, (barIds[i]*33)%255);

            RectangleShape depBar(Vector2f(wid, barHei));
            depBar.setPosition(layerX, layerY);
            depBar.setFillColor(col);
            window.draw(depBar);


            col = Color::Black;
            col.a = 100;
            depBar.setSize(Vector2f(wid/2, barHei));
            depBar.setPosition(layerX + wid/2, layerY);
            depBar.setFillColor(col);
            window.draw(depBar);

            if(i == barHovered){
                RectangleShape lilBar(Vector2f(wid, barHei/3));
                lilBar.setPosition(layerX, layerY + barHei*2/3);
                lilBar.setFillColor(col);
                window.draw(lilBar);
            }



            Text ax;
            ax.setPosition( x , layerY + barHei/2 - 15/2);
            ax.setFillColor(Color::Black);
            ax.setOutlineColor(Color::White);
            ax.setOutlineThickness(2);
            ax.setFont(font);
            ax.setCharacterSize(15);

            std::stringstream str;
            str << "Id " << barIds[i];

            ax.setString(str.str());

            window.draw(ax);

        }
    }
};





#endif // GUI_H_INCLUDED
