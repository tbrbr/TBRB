
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

    static inline bool isButtonComMouseNele(RectangleShape rec, int mousex, int mousey) {
        return mousex >= rec.getPosition().x && mousex < rec.getSize().x + rec.getPosition().x 
            && mousey >= rec.getPosition().y && mousey < rec.getSize().y + rec.getPosition().y;
        
    }
    
    static int checkButtonHover(RectangleShape * rec, int mousex, int mousey, int i) {
        if (isButtonComMouseNele(rec[i], mousex, mousey)) {
            return i;
        }
        return i == 2 ? -1 : checkButtonHover(rec, mousex, mousey, i + 1);
    }

    static int PauseMenu(RenderWindow* window) {



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
            rec[i].setSize(Vector2f(SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.1));
            rec[i].setOutlineColor(Color::Blue);
            rec[i].setOutlineThickness(1);
            rec[i].setPosition(SCREEN_WIDTH / 2 - rec[i].getSize().x / 2, (yposition * (i + 1)) + spaceBetween * i);
        }

       
        t[0] = new Text("Resume", font, SCREEN_HEIGHT / 50);
        t[1] = new Text("Sense do capa", font, SCREEN_HEIGHT / 50);
        t[2] = new Text("QUIT", font, SCREEN_HEIGHT / 50);


        for (int i = 0; i < 3; i++) {
            t[i]->setFillColor(Color::White);
            t[i]->setPosition(rec[i].getPosition().x + rec[i].getSize().x / 2 - (t[i]->getGlobalBounds().width / 2), rec[i].getPosition().y + rec[i].getSize().y / 2 - (t[i]->getGlobalBounds().height / 2));
        }

        while (window->isOpen()) {

            Event e;
            while (window->pollEvent(e)) {
                if (e.type == Event::MouseButtonPressed) {

                    int i = checkButtonHover(rec, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y, 0);

                    if (i == 0) {
                        window->setMouseCursorGrabbed(true);
                        window->setMouseCursorVisible(false);
                        return i;
                    }
                    else if (i == 2) {
                        return i;
                    }
                    else if (i == 3) {
                        //nada
                    }


                
                }

                if (e.type == Event::KeyPressed) {
                    window->close();
                }
            }

            int j = checkButtonHover(rec, Mouse::getPosition(*window).x, Mouse::getPosition(*window).y, 0);

            if (j != -1) {
                rec[j].setFillColor(Color::Color(200, 200, 200, 34));
            }
            else {
                for (int k = 0; k < 3; k++) {
                    rec[k].setFillColor(Color::Black);
                }
            }

            window->clear();
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
                    int i = PauseMenu(&window);
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



