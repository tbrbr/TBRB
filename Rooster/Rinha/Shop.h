#pragma once




struct ShopRat {
	float x;
	float y;
	float hspd;
	float vspd;

	float scl = 10;

	float tailAnimation = 0;

	float addY = 0;

private:
	sf::Texture ratTex;

	sf::Sprite ratBody;

	sf::Sprite ratTail;
	SpriteMap ratTailMap;

	sf::Sprite tableSpr;
	sf::Sprite signSpr;

public:

	void init() {

		
		ratTex.loadFromFile("sprites/ratShopSheet.png");

		ratBody.setTexture(ratTex);
		ratBody.setTextureRect(sf::IntRect(40, 7, 16, 21));
		ratBody.setScale(scl, scl);

		ratTail.setTexture(ratTex);
		
		ratTailMap.addImages(12, 16, 0, 38, 6, 2, ratTex.getSize());
		ratTail.setScale(scl, scl);

		tableSpr.setTexture(ratTex);
		tableSpr.setTextureRect(sf::IntRect(0, 0, 36,38));
		tableSpr.setScale(scl, scl);

		signSpr.setTexture(ratTex);
		signSpr.setTextureRect(sf::IntRect(64, 0, 32, 38));
		signSpr.setScale(scl, scl);
	}

	void draw(sf::RenderWindow& window) {


		ratTail.setTextureRect(ratTailMap.images[int(ratTailMap.imgNumber * tailAnimation)]);
		ratTail.setPosition(x+2*scl, y-6*scl);
		window.draw(ratTail);

		signSpr.setPosition(x - 16 * scl, y - 18 * scl);
		window.draw(signSpr);


		ratBody.setPosition(x-8*scl, addY+y-10*scl);
		window.draw(ratBody);

		
		tableSpr.setPosition(x-16 * scl, y - 18 * scl);
		window.draw(tableSpr);
	}
};


void shopMenu(RenderWindow* window) {

	float roomWid = 1280;
	float roomHei = 720;


	sf::View view;
	if (true) {

		Vector2f size = (Vector2f)window->getSize();

		float wid = roomWid;
		float hei = roomHei;
		float xScl = (float)size.x / wid;
		float yScl = (float)size.y / hei;

		if (xScl > yScl) {
			wid *= yScl;
			hei = size.y;
		}
		else {

			hei *= xScl;
			wid = size.x;
		}

		xScl = wid / (float)size.x;
		yScl = hei / (float)size.y;

		sf::FloatRect area(0.f, 0.f, 1280, 720);
		view.setSize(area.width, area.height);
		view.setCenter(area.width / 2, area.height / 2);
		view.setViewport(FloatRect((1 - xScl) / 2, (1 - yScl) / 2, xScl, yScl));
		window->setView(view);
	}

	

	
	struct ShopRat rat;
	rat.init();
	rat.x = roomWid / 2;
	rat.y = roomHei / 2;


	sf::Music shopMusic;
	shopMusic.openFromFile("sounds/RatShop.ogg");
	shopMusic.setLoop(true);
	shopMusic.play();




	// Ghost Projectile
	sf::Texture ghostTex;
	if (!ghostTex.loadFromFile("sprites/botaProjectile.png")) {
		println("Could not load Ghost On Mapeamento2");
	}


	sf::Sprite ghostSpr(ghostTex);
	SpriteMap ghostSprMap;
	ghostSprMap.addImages(16, 16, 0, 0, 2, 1, (Vector2i)ghostSpr.getTexture()->getSize());
	ghostSpr.setTextureRect(ghostSprMap.images[0]);
	ghostSpr.setScale(5, 5);

	float ghostX = 0;
	float ghostY = 0;
	float ghostBaseY = roomHei / 2;
	float ghostSpd = 4;
	float dir = 1;
	float ghostScale = 5;


	int buttonSelected = -1;
	bool listeningForKeybind = false;

	int playerSelected = 0;



	bool updateLabels = true;



	float frames = 0;

	while (window->isOpen()) {

		frames++;

		
		mainInput.update();


		Event e;
		while (window->pollEvent(e))
		{

			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::Escape)
				{
					window->setView(window->getDefaultView());

					return;
				}
			}

			if (e.type == Event::MouseMoved) {
				mainInput.mousePos = Vector2f(e.mouseMove.x, e.mouseMove.y);
			}

			if (e.type == Event::MouseWheelScrolled) {
				mainInput.mouseScroll = e.mouseWheelScroll.delta;
			}

			if (e.type == Event::Closed)
			{
				window->close();
			}


			if (e.type == sf::Event::Resized)
			{
				float wid = roomWid;
				float hei = roomHei;
				float xScl = (float)e.size.width / wid;
				float yScl = (float)e.size.height / hei;

				if (xScl > yScl) {
					wid *= yScl;
					hei = e.size.height;
				}
				else {

					hei *= xScl;
					wid = e.size.width;
				}

				xScl = wid / (float)e.size.width;
				yScl = hei / (float)e.size.height;

				sf::FloatRect area(0.f, 0.f, roomWid, roomHei);
				view.setSize(area.width, area.height);
				view.setCenter(area.width / 2, area.height / 2);
				view.setViewport(FloatRect((1 - xScl) / 2, (1 - yScl) / 2, xScl, yScl));
				window->setView(view);

			}


		}



		window->clear();

		
		
		float songRatio = shopMusic.getPlayingOffset() / shopMusic.getDuration();

		rat.addY = 20*(((int)(songRatio*44 + 0.2)) % 2);

		rat.tailAnimation = (float)(int(frames) % 150) / 150;
		rat.draw(*window);





		ghostSpr.setTextureRect(ghostSprMap.images[(int)(frames / 10) % 2]);
		if (dir > 0) {
			if (ghostX > roomWid * 3) {
				ghostX = roomWid * 3;
				dir = -1;
				ghostSpr.setScale(-ghostScale, ghostScale);
			}
			ghostX += dir * ghostSpd;
			ghostY = cos(frames / 10.f) * 20;
		}
		else {
			if (ghostX < -roomWid * 2) {
				ghostX = -roomWid * 2;
				dir = 1;
				ghostSpr.setScale(ghostScale, ghostScale);
			}
			ghostX += dir * ghostSpd;
			ghostY = cos(frames / 10.f) * 20;
		}
		ghostSpr.setPosition(ghostX, ghostY + ghostBaseY);



		window->draw(ghostSpr);


		mainPartSystem.update();
		mainPartSystem.draw(*window);



		window->display();
	}

	return;

}