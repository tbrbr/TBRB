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

    

    void update(Vector2f mousePos, bool mouseClick, int inputType, char lastChar){
        hovered = false;
        confirmed = false;

        if(pointInside(mousePos, x, y, wid, hei)){
            hovered = true;
        }



        if(mouseClick){
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
            if(inputType == 2){
                subText();
            } else if (inputType == 0) {
                addText(lastChar);
            } else if (inputType == 1){
                confirm();
                selected = false;
            }
        }

    }


    void update(bool mouseClick, int inputType, char lastChar) {
        update(mainInput.mousePos, mouseClick, inputType, lastChar);
    }

    void update(Vector2f mousePos, int inputType, char lastChar) {
        update(mousePos, mainInput.mouseState[0][1], inputType, lastChar);
    }

    void update(int inputType, char lastChar) {
        update(mainInput.mouseState[0][1], inputType, lastChar);
    }

    void draw(RenderWindow& window, sf::Font& font){
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

    void draw(RenderWindow& window) {
        draw(window, basicFont);
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



struct Button {

private:
    float x;
    float y;
    float wid;
    float hei;

public:
    bool hovered = false;
    bool clicked = false;
    bool down = false;

    bool holding = false;

    std::string label;

    sf::Color color;

    bool hasSprite = false;
    sf::Sprite sprite;


    void setPosition(float xx, float yy) {
        x = xx;
        y = yy;
    }

    void setSize(float ww, float hh) {
        wid = ww;
        hei = hh;
    }

    void init(float xx, float yy, float ww, float hh) {
        x = xx;
        y = yy;
        wid = ww;
        hei = hh;

        label = "";

        color = Color::White;
    }



    void update(Vector2f mousePos, bool mouseState, bool mouseClick) {
        hovered = false;
        clicked = false;
        down = false;

        if (pointInside(mousePos, x, y, wid, hei)) {
            hovered = true;
        }

        if (mouseClick) {
            if (hovered) {
                clicked = true;
                down = true;
            }
            else {
                down = false;
            }
        }

        if (down) {
            if (!mouseState) {
                down = false;
            }
        }
    }


    void update(Vector2f mousePos) {
        update(mousePos, mainInput.mouseState[0][0], mainInput.mouseState[0][1]);
    }

    void update() {
        update(mainInput.mousePos, mainInput.mouseState[0][0], mainInput.mouseState[0][1]);
    }





    void draw(RenderWindow& window) {
        draw(window, basicFont);
    }

    void draw(RenderWindow& window, sf::Font font) {
        RectangleShape rect(Vector2f(wid, hei));
        rect.setPosition(x, y);


        Color col = color;



        if (down) {
            col.b -= 20;
            col.r -= 20;
            col.g -= 20;
        }

        if (hovered) {
            col.b -= 10;
            col.r -= 10;
            col.g -= 10;
        }

        rect.setFillColor(col);
        rect.setOutlineColor(Color(150, 150, 150));
        rect.setOutlineThickness(2);

        window.draw(rect);

        if (hasSprite) {
            sprite.setColor(col);
            sprite.setPosition(x, y);
            window.draw(sprite);
        }
        else {
            float fontSize = hei / 1.4;
            Text t(label, font, fontSize);
            float textWid = t.getGlobalBounds().width;


            t.setFillColor(Color(255, 255, 255));
            t.setPosition(x + wid / 2 - textWid / 2, y + hei / 2 - fontSize / 2);

            window.draw(t);
        }
    }
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

  void updateSlider(Vector2f mousePos, bool mouseClick, bool mouseState){

    float xx = x+sliderX-(sliderWid/2);
    float yy = y+(hei/2)-(sliderHei/2);

    hovered = false;
    if(pointInside(mousePos, xx, yy, sliderWid, sliderHei)){
        hovered = true;
    }


    if(!holded){
      moved = false;
      if(mouseClick){


        if(hovered){
          holded = true;
          mouseXOff = (sliderWid/2)-(mousePos.x-xx);
        }
      }
    } else {
      moved = true;
      if(mouseState){
        sliderX = constrain(mousePos.x -x+mouseXOff, 0, len);
      } else {
        holded = false;
      }
    }



    updateValue(((sliderX/len)*(maxVal-minVal))+minVal);
  }

  void updateSlider(Vector2f mousePos) {
      updateSlider(mousePos, mainInput.mouseState[0][1], mainInput.mouseState[0][0]);
  }

  void updateSlider() {
      updateSlider(mainInput.mousePos);
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




#endif // GUI_H_INCLUDED
