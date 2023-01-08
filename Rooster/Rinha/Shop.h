#pragma once


struct Ghosty {
	float x = 0;
	float y = 0;
	float hspd = 0;
	float vspd = 0;
	float spd = 4;

	float scl = 5;

	float addX = 0;
	float addY = 0;

	float shakeX = 0;
	float shakeY = 0;
	float shakeDuration = 0;
	float shakeAmplitude = 0;

	bool hovered = false;

	float dir = 1;

private:

	bool alive = true;

	sf::Sprite ghostSpr;
	SpriteMap ghostMap;

	sf::Sound hitSound;

public:

	void init(sf::Texture& texture, sf::SoundBuffer& hitSoundBuf) {




		ghostSpr.setTexture(texture);

		ghostMap.addImages(16, 16, 0, 0, 2, 1, (Vector2i)ghostSpr.getTexture()->getSize());
		ghostSpr.setTextureRect(ghostMap.images[0]);
		ghostSpr.setScale(5, 5);
		ghostSpr.setOrigin(8,8);


		hitSound.setBuffer(hitSoundBuf);
		hitSound.setVolume(50);

		y = 200;
		dir = 1;
		hspd = 5;

	}

	void update(Vector2f mousePos, float roomWid, float roomHei) {

		hspd = dir * spd;

		x += hspd;
		y += vspd;


		hovered = false;
		if (ghostSpr.getGlobalBounds().contains(mousePos)) {
			hovered = true;
		}

		if (hovered) {
			if (mainInput.mouseState[0][1]) {
				hit(roomWid, roomHei);
			}
		}

		if (shakeDuration > 0) {
			shakeDuration--;
			shakeAmplitude *= 0.98;

			shakeX = randFloatRange(-shakeAmplitude, shakeAmplitude);
			shakeY = randFloatRange(-shakeAmplitude, shakeAmplitude);
		}
		else {
			shakeAmplitude = 0;
			shakeX = 0;
			shakeY = 0;
		}
	}

	void draw(sf::RenderWindow& window, float frames) {

		ghostSpr.setTextureRect(ghostMap.images[(int)(frames / 10) % 2]);
		addY = sin(frames/10)*20;

		
		ghostSpr.setPosition(x+addX+shakeX, y+addY+shakeY);
		window.draw(ghostSpr);
	}

	void hit(float roomWid, float roomHei) {
		float pitch = randFloatRange(0.7, 1.3);
		hitSound.setPitch(pitch);
		hitSound.play();

		shakeDuration = 10;
		shakeAmplitude += 10;


		Effect* effect = new Effect();
		effect->poeiraPreset();
		effect->position.x = x;
		effect->position.y = y;
		effect->spreadPreset(60, 60);
		effect->createMultipleParticles(7);
		effect->mortal = true;
		effect->life = 100;

		mainPartSystem.addEffect(effect);




		dir = ((randInt(2) - 0.5) * 2);

		ghostSpr.setScale(5*dir, 5);

		x = (roomWid / 2) + roomWid * (- dir);
		y = roomHei/2 + randFloatRange(-roomHei/3, roomHei / 3);
	}
};











struct ShopRat {
	float x;
	float y;
	float hspd;
	float vspd;

	float scl = 10;

	float tailAnimation = 0;

	float addX = 0;
	float addY = 0;


	float shakeX = 0;
	float shakeY = 0;
	float shakeDuration = 0;
	float shakeAmplitude = 0;

	bool hovered = false;

private:
	sf::Texture ratTex;

	sf::Sprite ratBody;

	sf::Sprite ratTail;
	SpriteMap ratTailMap;

	sf::Sprite tableSpr;
	sf::Sprite signSpr;

	sf::SoundBuffer hitSoundBuf;
	sf::Sound hitSound;

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


		hitSoundBuf.loadFromFile("sounds/HitRat.ogg");
		hitSound.setBuffer(hitSoundBuf);
		hitSound.setVolume(50);
	}

	void update(Vector2f mousePos) {
		hovered = false;
		if (ratBody.getGlobalBounds().contains(mousePos)) {
			hovered = true;
		}

		if (hovered) {
			if (mainInput.mouseState[0][1]) {
				hit(mousePos);
			}
		}

		if (shakeDuration > 0) {
			shakeDuration--;
			shakeAmplitude *= 0.98;
			
			shakeX = randFloatRange(-shakeAmplitude, shakeAmplitude);
			shakeY = randFloatRange(-shakeAmplitude, shakeAmplitude);
		}
		else {
			shakeAmplitude = 0;
			shakeX = 0;
			shakeY = 0;
		}
	}

	void draw(sf::RenderWindow& window) {


		ratTail.setTextureRect(ratTailMap.images[int(ratTailMap.imgNumber * tailAnimation)]);
		ratTail.setPosition(x+2*scl, y-6*scl);
		window.draw(ratTail);

		signSpr.setPosition(x - 16 * scl, y - 18 * scl);
		window.draw(signSpr);


		ratBody.setPosition(x-8*scl  + addX + shakeX, shakeY + addY+y-10*scl);
		window.draw(ratBody);

		
		tableSpr.setPosition(x-16 * scl, y - 18 * scl);
		window.draw(tableSpr);
	}

	void hit(Vector2f hitPos) {
		float pitch = randFloatRange(0.7, 1.3);
		hitSound.setPitch(pitch);
		hitSound.play();

		shakeDuration = 10;
		shakeAmplitude += 10;


		Effect* effect = new Effect();
		effect->poeiraPreset();
		effect->position = hitPos;
		effect->spreadPreset(60, 60);
		effect->createMultipleParticles(7);
		effect->mortal = true;
		effect->life = 100;

		mainPartSystem.addEffect(effect);

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

	

	sf::Texture ghostTex;
	ghostTex.loadFromFile("sprites/botaProjectile.png");

	sf::SoundBuffer hitSoundBuf;
	hitSoundBuf.loadFromFile("sounds/HitRat.ogg");
	
	struct ShopRat rat;
	rat.init();
	rat.x = roomWid / 2;
	rat.y = roomHei / 2;

	struct Ghosty ghost;
	ghost.init(ghostTex, hitSoundBuf);


	sf::Music shopMusic;
	shopMusic.openFromFile("sounds/RatShop.ogg");
	shopMusic.setLoop(true);
	shopMusic.play();


	sf::Music rainAmbience;
	rainAmbience.openFromFile("sounds/chuva.ogg");
	rainAmbience.setVolume(10);
	rainAmbience.play();


	Rooster::Effect* rainEffect = new Rooster::AreaEffect(FloatRect(-100, -100, roomWid + 100, 100), Color::Blue);
	rainEffect->rainPreset();
	rainEffect->sclSet(0.3, 0.1);
	rainEffect->hspdSet(1, 0.2);
	rainEffect->vspdSet(7, 0.5);
	rainEffect->mortal = false;

	mainPartSystem.addEffect(rainEffect);

	Rooster::Effect* splashEffect = new Rooster::ExplosionEffect(Vector2f(0, 0), 2);
	splashEffect->tilesPreset();
	splashEffect->sclSet(0.15, 0.03);
	splashEffect->isHSV = true;
	splashEffect->hueMax = 240;
	splashEffect->hueMin = 240;
	splashEffect->satMax = 0.3;
	splashEffect->satMin = 0.2;
	splashEffect->lightMax = 1;
	splashEffect->lightMin = 0.8;
	splashEffect->mortal = false;

	mainPartSystem.addEffect(splashEffect);

	// Ghost Projectile
	sf::Texture cornSeedTex;
	cornSeedTex.loadFromFile("sprites/cornSeed.png");

	sf::Sprite cornSeedSpr(cornSeedTex);
	float cornScale = 5;
	cornSeedSpr.setScale(cornScale, cornScale);
	cornSeedSpr.setPosition(roomWid - cornSeedSpr.getGlobalBounds().width, roomHei - cornSeedSpr.getGlobalBounds().height);
	

	sf::Text cashCount("0000", basicFont, 50);
	cashCount.setFillColor(Color::White);
	cashCount.setOutlineColor(Color(150, 150, 150));
	cashCount.setOutlineThickness(3);
	cashCount.setPosition(roomWid - cornSeedSpr.getGlobalBounds().width - cashCount.getGlobalBounds().width - 10, roomHei - cornSeedSpr.getGlobalBounds().height);






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

		
		Vector2f mousePos = window->mapPixelToCoords((Vector2i)mainInput.mousePos);
		rat.update(mousePos);


		
		float songRatio = shopMusic.getPlayingOffset() / shopMusic.getDuration();

		rat.addY = 20*(((int)(songRatio*44 + 0.2)) % 2);

		rat.tailAnimation = (float)(int(frames) % 150) / 150;
		rat.draw(*window);



		rainEffect->createMultipleParticles(1);


		float wid = 300;
		float xx = (roomWid / 2) - wid / 2;
		float hei = 50;
		float yy = (roomHei / 2) - 150;

		RectangleShape colision(Vector2f(wid, hei));
		colision.setPosition(xx, yy);
		colision.setFillColor(Color(250, 100, 40, 160));
		colision.setOutlineColor(Color(250, 150, 100));
		colision.setOutlineThickness(4);

		//window->draw(colision);


		for (int i = 0; i < rainEffect->getParticleNum(); i++) {
			Rooster::Particle* part = rainEffect->getParticle(i);

			if (part->position.y > roomHei * (0.8 + part->depth / 50) ||
				colision.getGlobalBounds().contains(part->position)
				) {
				splashEffect->position = part->position;
				splashEffect->createMultipleParticles(2);
				part->active = false;
			}
		}

		mainPartSystem.update();
		mainPartSystem.draw(*window);



		window->draw(cornSeedSpr);

		cashCount.setString(fixedDigits(globalInfo.cash, 4));
		window->draw(cashCount);



		ghost.update(mousePos, roomWid, roomHei);
		ghost.draw(*window, frames);





		window->display();
	}

	delete rainEffect;

	return;

}