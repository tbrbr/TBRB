
#include "..\\entradas.h"

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

    void updateSensi() {
            
    }

    static inline bool isButtonComMouseNele(RectangleShape rec, int mousex, int mousey) {
        return mousex >= rec.getPosition().x - 2 && mousex <= rec.getSize().x + rec.getPosition().x + 2
            && mousey >= rec.getPosition().y - 2  && mousey <= rec.getSize().y + rec.getPosition().y + 2;
        
    }
    
    static int checkButtonHover(RectangleShape * rec, int mousex, int mousey, int i, int __finalCondition) {
        if (mousey == -1) {
            if (hasBarInMouseX(rec[i], mousex, i + 1)) {
                return i;
            }
            else {
                return i == __finalCondition ? -1 : hasBarInMouseX(rec[i], mousex, i + 1);
            }
        }
        if (isButtonComMouseNele(rec[i], mousex, mousey)) {
            return i;
        }
        return i == __finalCondition ? -1 : checkButtonHover(rec, mousex, mousey, i + 1, __finalCondition);
    }

    static int hasBarInMouseX(RectangleShape rec, int mousex, int size) {
        for (int i = 0; i < size; i++) {
            if (mousex >= rec.getPosition().x && mousex <= rec.getSize().x + rec.getPosition().x) {
                return i;
            }
        }
        return -1;
    }

    static void configScreen(RenderWindow* window, GameInfo& info)
    {

        Font font;
        font.loadFromFile("..\\Rinha\\fonts\\blops.ttf");

        Text sensi("Sensi", font, SCREEN_HEIGHT / 50);
        Text cor("Cor da Mira", font, SCREEN_HEIGHT / 50);
        Text back("Voltar", font, SCREEN_HEIGHT / 50);

        sensi.setPosition(SCREEN_WIDTH / 2 - sensi.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.15);
        cor.setPosition(SCREEN_WIDTH / 2 - cor.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.30);
        back.setPosition(SCREEN_WIDTH / 2 - back.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.80);

        RectangleShape __back(Vector2f(back.getGlobalBounds().width, back.getGlobalBounds().height * 2));
        __back.setPosition(back.getPosition());
        __back.setFillColor(Color::Transparent);


        RectangleShape bars[4];
        RectangleShape _barEnd[4][2];
        RectangleShape _position[4];



        for (int i = 0; i < 4; i++) {
            bars[i].setSize(Vector2f(SCREEN_WIDTH * 0.3, 3));
            bars[i].setPosition(SCREEN_WIDTH / 2 - bars[i].getSize().x / 2, i * 100 + 10);
        }

        for (int i = 0; i < 4; i++) {
            for(int j = 0; j < 2; j++)
                _barEnd[i][j].setSize(Vector2f(6, bars[i].getSize().y * 5));

            _position[i].setSize(Vector2f(6, bars[i].getSize().y * 8));

            _barEnd[i][0].setPosition(bars[i].getPosition().x - _barEnd[i][0].getSize().x, bars[i].getPosition().y - _barEnd[i][0].getSize().y / 2.5);;
            _barEnd[i][1].setPosition(bars[i].getSize().x + bars[i].getPosition().x, bars[i].getPosition().y - _barEnd[i][0].getSize().y / 2.5 );
            _position[i].setPosition(bars[i].getPosition().x, bars[i].getPosition().y - _position[i].getSize().y / 4);
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

                    if (isButtonComMouseNele(__back, mousex, mousey)) {
                        return;
                    }

                    __temp = checkButtonHover(bars, mousex, mousey, 0, 3);
                    if (__temp != -1) {
                        _position[__temp].setPosition(mousex, _position[__temp].getPosition().y);
                    }
                    else {
                        __temp = checkButtonHover(_position, mousex, mousey, 0, 3);
                        if(__temp != -1)
                         _position[__temp].setPosition(mousex, _position[__temp].getPosition().y);
                    }

                }

                if (e.type == Event::MouseButtonReleased) {
                    
                }

            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (__temp != -1) {
                    _position[__temp].setPosition(mousex, _position[__temp].getPosition().y);
                }
            }

            window->clear();
            window->draw(sensi);
            window->draw(cor);
            window->draw(__back);
            window->draw(back);


            for (int i = 0; i < 4; i++) {
                window->draw(bars[i]);
                window->draw(_position[i]);
                for (int j = 0; j < 2; j++)
                    window->draw(_barEnd[i][j]);
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

        Text * t[3];

        RectangleShape rec[3];
        for (int i = 0; i < 3; i++) {
            rec[i].setFillColor(Color::Black);
            rec[i].setSize(Vector2f(SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.2));
            rec[i].setOutlineColor(Color::Blue);
            rec[i].setOutlineThickness(1);
            rec[i].setPosition(SCREEN_WIDTH / 2 - rec[i].getSize().x / 2, (yposition * (i + 1)) + spaceBetween * i);
        }

       
        t[0] = new Text("Resume", font, SCREEN_HEIGHT / 50);
        t[1] = new Text("CONFIG", font, SCREEN_HEIGHT / 50);
        t[2] = new Text("QUIT", font, SCREEN_HEIGHT / 50);


        for (int i = 0; i < 3; i++) {
            t[i]->setFillColor(Color::White);
            t[i]->setPosition(rec[i].getPosition().x + rec[i].getSize().x / 2 - (t[i]->getGlobalBounds().width / 2), rec[i].getPosition().y + rec[i].getSize().y / 2 - (t[i]->getGlobalBounds().height / 2));
        }

        while (window->isOpen()) {

            Event e;
            while (window->pollEvent(e)) {
                if (e.type == Event::MouseButtonPressed) {

                    int i = checkButtonHover(rec, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y, 0, 2);

                    if (i == 0) {
                        window->setMouseCursorGrabbed(true);
                        window->setMouseCursorVisible(false);
                        return i;
                    }
                    else if (i == 2) {
                        return i;
                    }
                    else if (i == 1) {
                        configScreen(window, info);
                        i = -1;
                    }
                
                }
            }

            int j = checkButtonHover(rec, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y, 0, 2);

            if (j != -1) {
                rec[j].setFillColor(Color::Transparent);
            }
            else {
                for (int k = 0; k < 3; k++) {
                    rec[k].setFillColor(Color::Black);
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
    }

    void patinho(RenderWindow& window, int & option) {
        Event e;
        

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

            return;
        }
        

        FPS.setString("FPS: " + GetFrameRate());
        txtScore.setString("Score: " + IntToString(info.kills));

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



