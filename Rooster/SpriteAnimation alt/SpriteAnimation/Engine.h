#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

float constrain(float val, float min, float max){
    if(val < min){
        return min;
    } else if(val > max){
        return max;
    }

    return val;
}

void printIntVec(std::vector<int> vec){
    std::cout << "[ ";
    for(int i = 0;i  < vec.size(); i++){
        std::cout << vec[i];
        if(i == vec.size()-1){
            std::cout << " ]";

        } else {
            std::cout << ", ";
        }
    }
}

std::string streamIntVec(std::vector<int> vec){
    std::stringstream a;
    a << "[ ";
    for(int i = 0;i  < vec.size(); i++){
        a << vec[i];
        if(i == vec.size()-1){


        } else {
            a << ", ";
        }
    }
    a << " ]";

    return a.str();
}



struct GUIInfo{
    struct{
        float wid = 320;
        float hei;
        float x;
        float y = 0;
        float lX = 40;
        float lY = 20;
        float lWid = 10;
        float lHei = 40;
    } rBar;

    struct{
        float wid = 400;
        float hei;
        float x = 0;
        float y = 0;
    } lBar;

    struct{
        float x = 500;
        float y = 450;
        float pHei = 20;
        float playWid = 400;
        float playPropXOffset = 100;
        float propWid = 100;
        float propX = 400 + 100;
        float propY = 0;
    } propBar;

    /// Down Bar
    struct{
        float wid;
        float hei = 40;
        float x = 0;
        float y;
        float toolX;
    } dBar;

    /// Up Bar
    struct{
        float wid;
        float hei = 40;
        float x = 0;
        float y;
    } uBar;

    bool update = false;
};



struct engineInfo{
    bool mouseState[2][3] = {{false, false, false},{false, false, false}};
    bool selecting = false;
    int mouseX = 0;
    int mouseY = 0;

    bool keyboardState[sf::Keyboard::KeyCount][3];

    float screenWidth = 1280;
    float screenHeight = 720;

    Vector2f selStart;
    Vector2f selEnd;

    float sheetScl = 1;

    int toolSelected = 0;

    float xWholeScl = 1;
    float yWholeScl = 1;
    float xWhole = 0;
    float yWhole = 0;
    float angWhole = 0;

    int sprX = 0;
    int sprY = 0;

    bool hoveringGUI = false;


    // Text Input
    char lastChar = ' ';
    bool newInput = false;
    bool deleteChar = false;
    bool confirmInput = false;

    bool typing = false;

    struct GUIInfo GUI;


    std::string usingModel;
    std::string usingAnim;


    void init(){

        usingModel = "pesteModel.txt";
        usingAnim = "pesteAgacha.txt";

        for(int i = 0; i < sf::Keyboard::KeyCount; i++){
            keyboardState[i][0] = false;
            keyboardState[i][1] = false;
            keyboardState[i][2] = false;
        }

        sprX = GUI.uBar.x;
        sprY = GUI.uBar.y + GUI.uBar.hei;


    }

    void update(){
        hoveringGUI = false;
        typing = false;
        newInput = false;
        deleteChar = false;
        confirmInput = false;
        GUI.update = false;


        GUI.uBar.wid = screenWidth;
        GUI.uBar.hei = 40;

        GUI.dBar.wid = screenWidth;
        GUI.dBar.hei = 40;
        GUI.dBar.y   = screenHeight-GUI.dBar.hei;

        GUI.lBar.hei = screenHeight - GUI.uBar.hei - GUI.dBar.hei;
        GUI.lBar.y   = GUI.uBar.y + GUI.uBar.hei;
        GUI.lBar.x   = 0;

        GUI.rBar.hei = screenHeight - GUI.uBar.hei - GUI.dBar.hei;
        GUI.rBar.y   = GUI.uBar.y + GUI.uBar.hei;
        GUI.rBar.x   = screenWidth - GUI.rBar.wid;
        GUI.rBar.lWid= GUI.rBar.wid/3;

        GUI.propBar.propX = GUI.propBar.playWid + GUI.propBar.playPropXOffset;


        GUI.dBar.toolX = GUI.lBar.x + GUI.lBar.wid;




        sprX = GUI.uBar.x;
        sprY = GUI.uBar.y + GUI.uBar.hei;





        for(int i = 0; i < sf::Keyboard::KeyCount; i++){
            bool keyState = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
            if(!keyboardState[i][0] && keyState){
                keyboardState[i][1] = true;
            } else {
                keyboardState[i][1] = false;
            }

            if(keyboardState[i][0] && !keyState){
                keyboardState[i][2] = true;
            } else {
                keyboardState[i][2] = false;
            }

            keyboardState[i][0] = keyState;
        }
    }


    void mouseUpdate(){
        mouseState[0][1] = false;
        mouseState[0][2] = false;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(!mouseState[0][0]){
                mouseState[0][1] = true;
            }
            mouseState[0][0] = true;

        } else {
            if(mouseState[0][0]){
                mouseState[0][2] = true;
            }
            mouseState[0][0] = false;

        }

        mouseState[1][1] = false;
        mouseState[1][2] = false;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            if(!mouseState[1][0]){
                mouseState[1][1] = true;
            }
            mouseState[1][0] = true;

        } else {
            if(mouseState[1][0]){
                mouseState[1][2] = true;
            }
            mouseState[1][0] = false;
        }

    }

    bool mouseInside(float x, float y, float wid, float hei){
        if(mouseX > x && mouseX < x+wid && mouseY > y && mouseY < y+hei){
            return true;
        }

        return false;
    }

};





struct SpriteArea{
    sf::IntRect texRect;

    int imgTotal = 1;
    int imgIndex = 0;

    Vector2i center;

    void init(){
        texRect.left = 0;
        texRect.top = 0;
        texRect.width  = 0;
        texRect.height = 0;

        center.x = 0;
        center.y = 0;
    }

    /*
    void draw(RenderWindow& window, float scl){
        RectangleShape select(Vector2f(texRect.width*scl, texRect.height*scl));
        select.setPosition(pos.x, pos.y);
        select.setFillColor(Color(100, 100, 100, 0));
        select.setOutlineColor(Color(255));
        select.setOutlineThickness(4);

        window.draw(select);
    }
    */

    void draw(RenderWindow& window, float scl, Color fillColor, struct engineInfo& info){
        RectangleShape select(Vector2f(texRect.width*scl, texRect.height*scl));

        select.setPosition(info.sprX + texRect.left*scl, info.sprY + texRect.top*scl);
        select.setFillColor(fillColor);
        select.setOutlineColor(Color(255));
        select.setOutlineThickness(4);

        window.draw(select);
    }
};




#endif // ENGINE_H_INCLUDED
