
#include "..\\entradas.h"
#pragma warning(disable : 4996)

class Pato {

    GameInfo info;
    Text FPS;
    Text txtScore;

    static void restartGame(GameInfo & info) {

        info.lives = info.maxLives;
        info.missAnimationStart = 0;
        info.missAnimationTimer = 0;
        info.kills = 0;
        info.frames = 0;
        info.roosters.clear();
        info.roosters.push_back(newRooster(info));
        info.particles.clear();

    }

    static float TextMoveX(Text * __over) {
        int x = SCREEN_WIDTH;
        int finalXPosition = SCREEN_WIDTH / 2 - __over->getGlobalBounds().width / 2;

        float movex = x - finalXPosition;
        movex = movex / (FRAMERATE_LIMIT * 1.5);
        return movex;

    }

    inline static float BarMoveX() {
        return (float) SCREEN_WIDTH / (FRAMERATE_LIMIT * 1.5);
    }

   
 
    static bool GameOverScreen(RenderWindow* window) {

        Font font;
        font.loadFromFile("..\\Rinha\\fonts\\Melted Monster.ttf");
        Text __game("Game", font, SCREEN_HEIGHT * 0.3);
        Text __over("Over", font, SCREEN_HEIGHT * 0.3);

        __game.setFillColor(Color::Red);
        __over.setFillColor(Color::Red);

        __over.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT * 0.45);
        __game.setPosition(__game.getGlobalBounds().width * -1, SCREEN_HEIGHT * 0.15);

        RectangleShape bar[2];
        bar[0].setSize(Vector2f(SCREEN_WIDTH, 9));
        bar[1].setSize(Vector2f(SCREEN_WIDTH, 9));

        bar[0].setPosition(SCREEN_WIDTH, SCREEN_HEIGHT * 0.10);
        bar[1].setPosition(-SCREEN_WIDTH, SCREEN_HEIGHT * 0.90);

        bar[0].setFillColor(Color::Red);
        bar[1].setFillColor(Color::Red);

        const float finalXPosition = (float) SCREEN_WIDTH / 2 - __over.getGlobalBounds().width / 2;

        float movex = TextMoveX(&__over);
        float barx = BarMoveX();

        while (window->isOpen()) {
          

            float temp = __over.getPosition().x - finalXPosition;
            if (temp < movex) {
                movex = temp;
                barx = bar[0].getPosition().x;
            }
            else if (temp == 0) {
                movex = 0;
                barx = 0;
            }
            __over.move(-movex, 0);
            __game.move(movex, 0);

            bar[0].move(-barx, 0);
            bar[1].move(barx, 0);


            Event e;
            while (window->pollEvent(e)) {
                if (e.type == Event::KeyPressed) {
                    if (__over.getPosition().x == finalXPosition) {
                        if (e.key.code == sf::Keyboard::Escape) {
                            return false;
                        }
                        if (e.key.code == sf::Keyboard::Enter) {
                            return true;
                        }
                    }

                    movex = __over.getPosition().x - finalXPosition;
                    barx = bar[0].getPosition().x;
  
                }
            }

            window->clear();
            window->draw(__game);
            window->draw(__over);
            window->draw(bar[0]);
            window->draw(bar[1]);
            window->display();
        }

    }

    static float BarToSensi(const RectangleShape & BAR, const RectangleShape & POSITION) {

        // float sizex = BAR.getSize().x;
        float position = POSITION.getPosition().x - BAR.getPosition().x;
        position = position <= 0 ? 0.01 : position;
        return position / 100;

    }

    static inline float SentiToBar(float sensi) {
        return sensi * 100;
    }

    static float BarToRGB(const RectangleShape& BAR, const RectangleShape& POSITION) {

        // float sizex = BAR.getSize().x;
        float position = POSITION.getPosition().x - BAR.getPosition().x;
        return floor(position * 255 / BAR.getSize().x);
    }

    static inline float RGBToBar(const RectangleShape & bar, float color) {
        return floor(color * bar.getSize().x  / 255);
    }

    static void configScreen(RenderWindow* window, GameInfo& info)
    {

        Texture __t;
        __t.loadFromFile("..\\Rinha\\Patinho\\pause.jpg");

        RectangleShape background;
        background.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        background.setPosition(0, 0);
        background.setTexture(&__t);


        Font font;
        font.loadFromFile("..\\Rinha\\fonts\\blops.ttf");

        Text sensi(LANG.getLine(LANGUAGE::SENSI), font, SCREEN_HEIGHT / 50);
        Text cor(LANG.getLine(LANGUAGE::AIM_COLOR), font, SCREEN_HEIGHT / 50);
        Text back(LANG.getLine(LANGUAGE::BACK), font, SCREEN_HEIGHT / 50);

        sensi.setPosition(SCREEN_WIDTH / 2 - sensi.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.15);
        cor.setPosition(SCREEN_WIDTH / 2 - cor.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.30);
        back.setPosition(SCREEN_WIDTH / 2 - back.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.80);

        RectangleShape __back(Vector2f(back.getGlobalBounds().width, back.getGlobalBounds().height * 2));
        __back.setPosition(back.getPosition().x, back.getPosition().y - __back.getSize().y / 4);
        __back.setFillColor(Color::Transparent);


        RectangleShape bars[4];
        RectangleShape _position[4];

        int space = SCREEN_HEIGHT * 0.08;
        int py = sensi.getPosition().y + sensi.getGlobalBounds().height + space;


        for (int i = 0; i < 4; i++) {
            bars[i].setSize(Vector2f(SCREEN_WIDTH * 0.3, 3));
        }
        bars[0].setPosition(SCREEN_WIDTH / 2 - bars[0].getSize().x / 2, py);

        py = cor.getPosition().y + cor.getGlobalBounds().height + space;

        for (int i = 1; i < 4; i++) {
            bars[i].setPosition(SCREEN_WIDTH / 2 - bars[i].getSize().x / 2, py);
            py = bars[i].getPosition().y + bars[i].getGlobalBounds().height + space;
        }

        bars[1].setFillColor(Color::Red);
        bars[2].setFillColor(Color::Green);
        bars[3].setFillColor(Color::Blue);


        for (int i = 0; i < 4; i++) {
           

            _position[i].setSize(Vector2f(6, bars[i].getSize().y * 8));

           
            _position[i].setPosition(bars[i].getPosition().x, bars[i].getPosition().y - _position[i].getSize().y / 4);
        }

        _position[0].move(SentiToBar(info.sensi),0);


        _position[1].move(RGBToBar(bars[1], info.smira.aim[0].getFillColor().r), 0);
        _position[2].move(RGBToBar(bars[2], info.smira.aim[0].getFillColor().g), 0);
        _position[3].move(RGBToBar(bars[3], info.smira.aim[0].getFillColor().b), 0);

        Aim aim(Vector2f(10, 10), 6, info.smira.aim[0].getFillColor());

        for (int i = 0; i < 4; i++) {
            aim.aim[i].move(0, SCREEN_WIDTH * 0.1);
        }



        int mousex, mousey;
        int __temp = -1;

        while (window->isOpen()) {

            mousex = Mouse::getPosition(*window).x;
            mousey = Mouse::getPosition(*window).y;

            Event e;

            while (window->pollEvent(e)) {
                if (e.type == Event::Closed) {
                    window->close();
                }



                if (e.type == Event::MouseButtonPressed) {

                    if (ButtonCheck::isButtonComMouseNele(__back, mousex, mousey)) {
                        for (int i = 0; i < 4; i++)
                        {
                            info.smira.aim[i].setFillColor(aim.aim[0].getFillColor());
                        }
                        info.smira.px.setFillColor(aim.aim[0].getFillColor());

                        std::fstream config("config.ini", ios::out | ios::trunc);
                        config << info.sensi << std::endl;
                        config << (int)info.smira.aim[0].getFillColor().r << " " << (int)info.smira.aim[0].getFillColor().g << " " << (int)info.smira.aim[0].getFillColor().b;
                        config.close();

                        return;
                    }

                    __temp = ButtonCheck::checkButtonHover(bars, mousex, mousey, 0, 3);
                    if (__temp != -1) {
                        _position[__temp].setPosition(mousex, _position[__temp].getPosition().y);
                    }
                    else {
                        __temp = ButtonCheck::checkButtonHover(_position, mousex, mousey, 0, 3);
                        if (__temp != -1)
                            _position[__temp].setPosition(mousex, _position[__temp].getPosition().y);
                    }

                }

            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (__temp != -1) {
                    _position[__temp].setPosition(mousex, _position[__temp].getPosition().y);
                    if (__temp == 0) {
                        info.sensi = BarToSensi(bars[__temp], _position[__temp]);
                    }
                 
                }
              
            }

            for (int i = 0; i < 4; i++) {
                if (_position[i].getPosition().x < bars[i].getPosition().x) {
                    _position[i].setPosition(bars[i].getPosition().x, _position[i].getPosition().y);
                }
                if (_position[i].getPosition().x > bars[i].getPosition().x + bars[i].getSize().x) {
                    _position[i].setPosition(bars[i].getPosition().x + bars[i].getSize().x, _position[i].getPosition().y);   
                }
            }

            if(__temp > 0)
                for (int i = 0; i < 4; i++) {
                    if (__temp == 1) {
                        aim.aim[i].setFillColor(Color(BarToRGB(bars[1], _position[1]), aim.aim[0].getFillColor().g, aim.aim[0].getFillColor().b));
                    }
                    else if (__temp == 2) {
                        aim.aim[i].setFillColor(Color(aim.aim[0].getFillColor().r, BarToRGB(bars[2], _position[2]), aim.aim[0].getFillColor().b));
                    }
                    else if (__temp == 3) {
                        aim.aim[i].setFillColor(Color(aim.aim[0].getFillColor().r, aim.aim[0].getFillColor().g, BarToRGB(bars[3], _position[3])));
                    }
                }

            if (ButtonCheck::isButtonComMouseNele(__back, mousex, mousey)) {
                back.setFillColor(Color::Yellow);
            }
            else {
                back.setFillColor(Color::White);
            }

            window->clear();
            window->draw(background);
            window->draw(sensi);
            window->draw(cor);
            window->draw(__back);
            window->draw(back);

            for (int i = 0; i < 4; i++) {
                window->draw(bars[i]);
                window->draw(_position[i]);
               
            }

            for (int i = 0; i < 4; i++) {
                window->draw(aim.aim[i]);
            }
            window->display();
        }
    }


    static int PauseMenu(RenderWindow* window, GameInfo & info) {


        Texture __t;
        __t.loadFromFile("..\\Rinha\\Patinho\\pause.jpg");

        RectangleShape background;
        background.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        background.setPosition(0, 0);
        background.setTexture(&__t);

        window->setMouseCursorGrabbed(false);
        window->setMouseCursorVisible(true);

        const float spaceBetween = 20;
        int yposition = SCREEN_HEIGHT * 0.20;

        Font font;
        font.loadFromFile("..\\Rinha\\fonts\\blops.ttf");

        Text* t[3];
        RectangleShape rec[3];

       
        t[0] = new Text(LANG.getLine(LANGUAGE::RESUME), font, SCREEN_HEIGHT / 30);
        t[1] = new Text(LANG.getLine(LANGUAGE::SETTINGS), font, SCREEN_HEIGHT / 30);
        t[2] = new Text(LANG.getLine(LANGUAGE::QUIT), font, SCREEN_HEIGHT / 30);

        for (int i = 0; i < 3; i++) {
            rec[i].setFillColor(Color::Transparent);
            rec[i].setSize(Vector2f(t[i]->getGlobalBounds().width * 2, t[i]->getGlobalBounds().height * 3));
            rec[i].setPosition(SCREEN_WIDTH / 2 - rec[i].getSize().x / 2, (yposition * (i + 1)) + spaceBetween * i);
        }


        for (int i = 0; i < 3; i++) {
            t[i]->setFillColor(Color::White);
            t[i]->setPosition(rec[i].getPosition().x + rec[i].getSize().x / 2 - (t[i]->getGlobalBounds().width / 2), rec[i].getPosition().y + rec[i].getSize().y / 2 - (t[i]->getGlobalBounds().height / 2));
        }

        while (window->isOpen()) {

            Event e;
            while (window->pollEvent(e)) {
                if (e.type == Event::MouseButtonPressed) {

                    int i = ButtonCheck::checkButtonHover(rec, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y, 0, 2);

                    if (i == 0 || i == 2) {
                        window->setMouseCursorVisible(false);
                        for (int i = 0; i < 3; i++) {
                            delete t[i];
                        }
                        return i;
                    }
                   
                    else if (i == 1) {
                        configScreen(window, info);
                        i = -1;
                    }
                
                }
            }
            int i = ButtonCheck::checkButtonHover(rec, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y, 0, 2);
            if (i != -1) {
                t[i]->setFillColor(Color::Yellow);
            }
            else {
                for (int iterator = 0; iterator < 3; iterator++) {
                    t[iterator]->setFillColor(Color::White);
                }
            }
       

            window->clear();
            window->draw(background);
            for (int i = 0; i < 3; i++) {
                window->draw(rec[i]);
                window->draw(*t[i]);
            }

            window->display();
        }

    }



public:
    Pato(RenderWindow& window) {
        SpriteInit(info, window);

        info.mapWidth = info.smap.getGlobalBounds().width;
        info.mapHeight = info.smap.getGlobalBounds().height;

        window.setMouseCursorVisible(false);
        window.setMouseCursorGrabbed(true);

        addRooster(info);
        /// Textos
        FPS.setString("0");
        FPS.setFont(info.fonte1);
        FPS.setCharacterSize(30);

        txtScore.setString("Score: " + info.kills);
        txtScore.setFont(info.fonte1);
        txtScore.setCharacterSize(30);
        txtScore.setPosition(0, window.getSize().y - 80);


        {
            std::fstream config("config.ini", std::ios::in);
            if (config.fail()) {
                config.close();
                config.open("config.ini", std::ios::out | std::ios::trunc);
                config << info.sensi << " ";
                config << (int)info.smira.aim[0].getFillColor().r << " " << (int)info.smira.aim[0].getFillColor().g << " " << (int)info.smira.aim[0].getFillColor().b;
                config.close();

                exit(0);
            }
            config.close();
        }

        FILE* file = fopen("config.ini", "r");
        


        int r = 255, g = 0, b = 0;
        float sensi;

        fscanf(file, "%f %d %d %d", &sensi, &r, &g, &b);
        cout << r << endl << g << endl << b << endl;

        for (int i = 0; i < 4; i++) {
            info.smira.aim[i].setFillColor(Color::Color(r, g, b));
        }
        info.smira.px.setFillColor(Color::Color(r, g, b));
        info.sensi = sensi;
        fclose(file);

    }

    void patinho(RenderWindow& window, int & option) {
        Event e;
        
        window.setMouseCursorVisible(false);

        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Escape) {
                    int i = PauseMenu(&window, info);
                    if (i == 2) {
                        option = Rooster::MENU_PRINCIPAL;
                        restartGame(info);
                        return;
                    }

                }
                   
            }

            if (info.windowGrabbed)
                if (e.type == Event::MouseMoved)
                    gamePlay(info, window, e);

            if (e.type == Event::MouseButtonPressed)
            {
                if (e.mouseButton.button == Mouse::Left)
                    shoot(info);

            }

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::C) {
                    shoot(info);
                }
            }
        }

        window.clear();

        
        if (info.lives == 0) {

            restartGame(info);

            if (GameOverScreen(&window)) {
                option = Rooster::ISPATOTIME;
            }
            else
                option = Rooster::MENU_PRINCIPAL;
            window.setMouseCursorVisible(true);
            return;
        }
        

        FPS.setString("FPS: " + GetFrameRate());
        txtScore.setString(LANG.getLine(LANGUAGE::SCORE) + ": " + IntToString(info.kills));

        if (info.windowGrabbed) {
            updateInfo(info, window);
        }

        drawStuff(info, window);

        window.draw(FPS);
        window.draw(txtScore);

        for (int i = 0; i < info.lives; i++) {

            float sniperX = info.viewWidth - (i + 1) * (info.sSniper.getGlobalBounds().width + 10);
            float sniperY = info.viewHeight - info.sSniper.getGlobalBounds().height;

            // Icone de Sniper
            info.sSniper.setColor(Color::White);
            info.sSniper.setPosition(sniperX, sniperY);
            window.draw(info.sSniper);
        }
       
        window.display();
    }

};



