
class Pato {

    GameInfo info;
    Text FPS;
    Text txtScore;
 
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

    void patinho(RenderWindow& window) {
        Event e;

        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Escape)
                    closeWindow(window, info);
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



