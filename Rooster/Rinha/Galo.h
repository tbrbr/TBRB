
#ifndef GALO_H_included
#define GALO_H_included

#include "Elementos.h"
#include "IAtaques.h"



namespace Rooster {

	/* a element is a small part of a rooster or any character available
	that way the animations will be smoother and easy to make for any rooster*/

	enum state {
		STOPPED = 0,
		RUNNING,
		DEFENDING,
		NOT_ATTACK = 0,
		LOW_KICK,
		HIGH_KICK,
		JUMP_KICK,
		SPECIAL,
		SUPER,//AVEMARIA DOIDO
		INVISIBLE,//not gonna lie this is harry potter shit
		FATALITY,
		DANCING
	};

	enum roosters {
		BOTAS,
		SNIPER,
		KALSA,
		PESTE_NEGRA,
		BRUXO,
	};

#define NUMGALOS 5



	const float floorY = (float)SCREEN_HEIGHT / 1.1;


	class LifeBar {
		Vector2i tam = { SCREEN_WIDTH / 3,SCREEN_HEIGHT / 54 };
		int spaceForTime = SCREEN_WIDTH / 6;
		int Maxhp;
		Text playerName;

		ConvexShape fillBar;

		RectangleShape life;
		RectangleShape fullLife;
		RectangleShape Damage;

		RectangleShape combo[10];

		Texture iron;
		Font mk11;

		const int maxStamina = 10;

		bool isP1;
		int yposition = SCREEN_HEIGHT / 8;
		int xposition;

		int framesOnMax = 0;
		int power = 0;
		int lastStamina = 0;
	public:

		int hp;
		int stamina = 0;

		int lastTam;
		Clock clock;
		Clock piscada;
		Time lastTime;

		//this is sick ngl
		bool onFire = false;


		LifeBar(int maxhp, bool isP1, const char* galoName) {
			Maxhp = maxhp;

			this->isP1 = isP1;
			int recLine = SCREEN_WIDTH / 99;
			fillBar.setPointCount(6);

			iron.loadFromFile("sprites/texturaFerro.png");
			fillBar.setTexture(&iron, true);
			mk11.loadFromFile("fonts/Mortal-Kombat-MK11.otf");
			playerName.setFont(mk11);
			playerName.setString(galoName);
			playerName.setCharacterSize(SCREEN_WIDTH / 50);

			fullLife.setOutlineThickness(SCREEN_WIDTH / 300);
			fullLife.setOutlineColor(Color::Black);
			fullLife.setFillColor(Color::Black);
			fillBar.setOutlineThickness(SCREEN_WIDTH / 300);
			fillBar.setOutlineColor(Color::Black);

			for (int i = 0; i < 10; i++) {
				combo[i].setSize(Vector2f(tam.x / 20, tam.y));
				combo[i].setOutlineThickness(SCREEN_WIDTH / 900);
				combo[i].setFillColor(Color::Transparent);
				combo[i].setOutlineColor(Color(200, 200, 200));
			}
			int comboy = (tam.y * 2) + yposition;

			if (isP1) {
				xposition = SCREEN_WIDTH / 12;
				fillBar.setPoint(0, sf::Vector2f(-recLine * 2, 0));
				fillBar.setPoint(1, sf::Vector2f(tam.x + recLine * 6, 0));
				fillBar.setPoint(2, sf::Vector2f(tam.x + recLine, tam.y + recLine * 3));
				fillBar.setPoint(3, sf::Vector2f(tam.x / 1.5, tam.y + recLine * 3));
				fillBar.setPoint(4, sf::Vector2f(tam.x / 2, tam.y + recLine));
				fillBar.setPoint(5, sf::Vector2f(0, tam.y + recLine));


				fillBar.scale(-1, 1);
				fillBar.setPosition(xposition - recLine * 4.5 + (tam.x + recLine * 5), yposition - recLine / 2);
				fullLife.setPosition(xposition, yposition);
				life.setPosition(xposition, yposition);
				playerName.setPosition(xposition + recLine, yposition + recLine);

				for (int i = 0; i < 10; i++) {
					int combox = xposition + tam.x / 2 + ((tam.x / 20) * i);
					combo[i].setPosition(combox, comboy);
				}

			}
			else {
				xposition = SCREEN_WIDTH / 12 + tam.x + spaceForTime;
				life.scale(-1, 1);
				fillBar.setPoint(0, sf::Vector2f(-recLine * 2, 0));
				fillBar.setPoint(1, sf::Vector2f(tam.x + recLine * 6, 0));
				fillBar.setPoint(2, sf::Vector2f(tam.x + recLine, tam.y + recLine * 3));
				fillBar.setPoint(3, sf::Vector2f(tam.x / 1.5, tam.y + recLine * 3));
				fillBar.setPoint(4, sf::Vector2f(tam.x / 2, tam.y + recLine));
				fillBar.setPoint(5, sf::Vector2f(0, tam.y + recLine));


				fillBar.setPosition(xposition - recLine / 2, yposition - recLine / 2);
				fullLife.setScale(-1, 1);
				fullLife.setPosition(xposition + tam.x, yposition);
				life.setPosition(xposition + tam.x, yposition);
				playerName.setPosition(xposition + tam.x - recLine - playerName.getGlobalBounds().width, yposition + recLine);
				Damage.setScale(-1, 1);

				for (int i = 0; i < 10; i++) {
					int combox = xposition + ((tam.x / 20) * i);
					combo[i].setPosition(combox, comboy);
				}
			}

			Color niceyellow(245, 205, 80);

			life.setFillColor(niceyellow);
			life.setSize(Vector2f((tam.x * hp) / Maxhp, tam.y));
			fullLife.setSize(Vector2f(tam.x, tam.y));





		}
		RectangleShape getRecLife() {
			return life;
		}

		ConvexShape getBar() {
			return fillBar;
		}
		void setMaxHp(int maxhp) {
			Maxhp = maxhp;
		}
		int getMaxhp() {
			return Maxhp;
		}
		int gethp() {
			return hp;
		}
		void sethp(int hp) {
			this->hp = hp;
		}
		int getLifeBarWidth() {
			return tam.x;
		}
		int getLifeBarHeight() {
			return tam.y;
		}
		void resetPower() {

			this->power = 0;
			for (int i = 0; i < 10; i++) {
				combo[i].setFillColor(Color::Transparent);
			}
			onFire = false;
		}
		int getPower() {
			return power;
		}
		void resetBarHp() {
			update(Maxhp);
		}
		void draw(RenderWindow* window) {
			for (int i = 0; i < 10; i++) {
				window->draw(combo[i]);
			}
			window->draw(fillBar);
			window->draw(fullLife);
			window->draw(life);
			window->draw(Damage);
			window->draw(playerName);
		}

		void updateStamin(int stamina) {

			if (stamina > 10) {
				stamina = 10;
			}
			if (stamina > lastStamina) {
				power += stamina - lastStamina;
			}

			lastStamina = stamina;

			int red = 0 + (power * 25);
			int green = 255 - (power * 25);
			int blue = 0;
			int alpha = 255;


			if (power >= 10) {

				power = 10;

				framesOnMax++;

				alpha = (framesOnMax % 2) * 255;

				for (int i = 0; i < stamina; i++) {
					combo[i].setOutlineColor(Color::White);
				}

				red = 255;
				if (framesOnMax % 4 == 0) {
					green = 255;
					blue = 255;
				}
				else {
					green = 0;
					blue = 0;
				}
				onFire = true;
			}
			else {
				framesOnMax = 0;
				//onFire = false;
			}


			if (isP1) {
				for (int i = 0; i < power; i++)
					combo[i].setFillColor(Color(red, green, blue, alpha));

			}
			else {
				for (int i = 9; i >= 10 - power; i--)
					combo[i].setFillColor(Color(red, green, blue, alpha));
			}


		}
		
		void update(int hp) {

			int oldTam = life.getGlobalBounds().width;
			int newTam = (tam.x * hp) / Maxhp;

			life.setSize(Vector2f(newTam, tam.y));

			if (oldTam > newTam) {
				Damage.setSize(Vector2f(lastTam - newTam, tam.y));
				Damage.setFillColor(Color::Color(145, 10, 10));
				if (isP1) {
					Damage.setPosition(Vector2f(life.getGlobalBounds().left + newTam, life.getGlobalBounds().top));
				}
				else {
					Damage.setPosition(Vector2f(life.getGlobalBounds().left, life.getGlobalBounds().top));
				}

				piscada.restart();
				clock.restart();
			}

			if (piscada.getElapsedTime().asMilliseconds() <= 30) {
				int t = piscada.getElapsedTime().asMilliseconds();

				int cor = (255 * sin(t)) / (1 + t / 10);

				Damage.setFillColor(Color::Color((255, cor, cor)));
				fullLife.setOutlineColor(Color::Color((255, cor, cor)));

			}
			else {
				Damage.setFillColor(Color::Color(145, 10, 10));
				fullLife.setOutlineColor(Color::Color(145, 10, 10));
			}


			if (clock.getElapsedTime().asSeconds() > 1) {
				Damage.setFillColor(Color::Black);
				fullLife.setOutlineColor(Color::Black);
				lastTam = life.getGlobalBounds().width;

			}
		}

	};



	struct GaloStats {
		int hp;
		int speed;
		int atk;
		int def;
		int peso;
		int jumpSpd;
	};



	class Galo {

	protected:

		// Identificadores
		int id;
		std::string name;

		// Stats
		int maxHp;
		float hp;
		int atk;
		int def;
		int speed;
		float peso;
		int estado;

		struct GaloStats stats;


		// Physics
		float hspeed;
		float hspeedLimit;
		float hAcc;

		float vspeed;
		float vspeedLimit;
		float jumpSpeed;


		bool air;
		// im still trying
		bool isPoisoned = false;

		// Frames for Animation
		int frames = 0;



		std::vector<struct Animation> animations;

		Texture star;
		Sprite estrelinha;
		Texture burned;
		Sprite burning;
		int hits = 0;

		Font comboFont;
		Text comboText;

		SoundBuffer bufferFire;
		Sound fireSound;

	public:

		int comboCounter;

		// Models and Animations
		struct Model model;

		Vector2f position;

		// Attacks and Hitboxes
		int atacking;
		bool isDefending = false;
		HitBox defense;
		std::vector<HitBox> hurtBox;
		std::vector<Projectile> projectiles;

		bool attackStart = false;

		Ataques* hiKick;
		Ataques* louKick;
		Ataques* ultimateShot;
		Ataques* superAtack;

		bool noGravity = true;


		// Lifebar
		LifeBar* bar;


		// Invulnerability
		bool invunerable = false;
		int invFrames = 0;

		// Stunning
		bool stunned = false;
		int stunFrames = 0;
		int coolDownFrames = 0;



		bool facingRight = false;
		bool estadoUpdate = false;

		bool isp1;

		//man this is gonna be so sick
		bool onFire = false;

		Galo(struct GaloStats stats, int _state, bool isp1) {

			// Stats
			this->stats = stats;

			this->maxHp = stats.hp;
			this->hp = stats.hp;
			this->atk = stats.atk;
			this->def = stats.def;
			this->speed = stats.speed;
			this->peso = stats.peso;
			this->jumpSpeed = -stats.jumpSpd;


			// States
			this->estado = _state;
			this->air = false;

			// Physics
			this->hspeed = 0;
			this->vspeed = 0;
			this->hspeedLimit = this->speed;
			this->vspeedLimit = 10;
			this->hAcc = 0.5;

			//me desculpe por deixar feio || excuse me for leaving it looking like mota

			star.loadFromFile("sprites\\estrelinhas.png");
			estrelinha.setTexture(star);
			estrelinha.setScale((float)SCREEN_WIDTH / 7680, (float)SCREEN_HEIGHT / 4320);

			comboFont.loadFromFile("fonts\\Act_Of_Rejection.ttf");

			comboText.setFont(comboFont);
			comboText.setCharacterSize(SCREEN_WIDTH / 30);
			comboText.setFillColor(Color::Yellow);
			comboText.setOutlineThickness(SCREEN_WIDTH / 900);
			comboText.setOutlineColor(Color(255, 255, 10));
			burned.loadFromFile("sprites\\Burning.png");
			burning.setTexture(burned);

			bufferFire.loadFromFile("sounds\\on-fire.ogg");
			fireSound.setBuffer(bufferFire);

			this->position = Vector2f(0, 0);


			this->isp1 = isp1;

			if (isp1)
				position.x = SCREEN_WIDTH / 4;
			else
				position.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;

			position.y = floorY;

		}

		inline string getName() {
			return this->name;
		}

		int getHits() {
			return this->hits;
		}

		Vector2f getPosition() {
			return this->position;
		}

		void setPosition(Vector2f pos) {
			this->position = pos;
		}

		void resetPosition() {
			if (isp1)
				position.x = SCREEN_WIDTH / 4;
			else
				position.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;

			position.y = floorY;
		}

		Model getModel() {
			return model;
		}

		// States
		void inline setState(state estado) {
			if (estado != this->estado) {
				this->estadoUpdate = true;
			}
			this->estado = estado;

		}

		void inline setState(int estado) {
			if (estado != this->estado) {
				this->estadoUpdate = true;
			}
			this->estado = estado;


		}
		int getState() {
			return this->estado;
		}


		// Set Hspeed
		void inline setHspeed(float spd) {
			hspeed = spd;
		}



		int inline getFrames() {
			return frames;
		}

		int getMaxhp() {
			return maxHp;
		}
		int gethp() {
			return hp;
		}
		void sethp(int hp) {
			this->hp = hp;
		}


		virtual void apanhar(Ataques atk, bool direction) {


			if (!invunerable) {

				static int lastFrameHit = frames;

				hits++;

				if (hits > 2 && (frames - lastFrameHit > 90)) {
					hits = 1;
				}

				lastFrameHit = frames;

				hp -= atk.Damage / stats.def;

				// Calculando os impulsos
				atk.createBlood(mainPartSystem);


				vspeed += sin(atk.angle) * atk.KnockBack;
				hspeed += cos(atk.angle) * atk.KnockBack;


				if (!direction) {
					hspeed *= -1;
				}

				// Tempo de perda de controle sobre o Rooster
				stunFrames = atk.Stun;
				stunned = true;

				// Tempo de invulnerabilidade
				invFrames = atk.invFrames;
				invunerable = true;

				bar->update(hp);

				atk.playSound();

			}


		}
		virtual void apanharByKalsa(Galo* g2, RenderWindow* af) {

			float frames = ultimateShot->init2.getElapsedTime().asMilliseconds();
			float maxFrames = ultimateShot->timeLapse2.asMilliseconds();

			if (frames > maxFrames) {
				ultimateShot->getHitted = false;
			}




			Vector2f nextPosition = position;



			float perc = (float)frames / maxFrames;

			if (perc < 0.4) {


				if (((int)frames) % 3 == 0) {
					g2->facingRight = !g2->facingRight;
				}


				g2->position.x += facingRight ?
					((position.x - g2->position.x + 200) * frames * 2) / maxFrames :
					((position.x - g2->position.x - 200) * frames * 2) / maxFrames;


			}
			else if (perc < 0.7) {
				g2->drawEstrelinhas(af);

				int add = 45;

				g2->model.at("Head")->xScl *= -1;



			}
			else {
				if (g2->model.at("Head")->xScl < 0) {
					g2->model.at("Head")->xScl *= -1;
				}
			}


		}
		void jump() {

			if ((!stunned || stunFrames < 0) && atacking == NOT_ATTACK) {
				stunned = false;
				if (!air) {
					vspeed += jumpSpeed;
					air = true;
				}
			}
		}

		void run(bool facingRight) {

			if ((!stunned || stunFrames < 0) && atacking == NOT_ATTACK) {

				estado = RUNNING;
				this->facingRight = facingRight;

				stunned = false;

				float acc = hAcc * ((facingRight) ? 1 : -1);

				hspeed = constrain(hspeed + acc, -hspeedLimit, hspeedLimit);

			}
		}


		virtual void defend() = 0;

		virtual void defended(Galo& galo2, Ataques* atk, bool facingRight) {
			Ataques* ataque = new Ataques(*atk);
			ataque->Damage *= 0.25;
			ataque->KnockBack *= 0.25;
			apanhar(*ataque, facingRight);
		}

		virtual void highKick() = 0;
		virtual void lowKick() = 0;
		virtual void especial() = 0;

		void show(sf::RenderWindow& window) {



			model.draw(window);

			for (int i = 0; i < projectiles.size(); i++) {
				if (!projectiles[i].NULO)
					if (projectiles[i].isTrans)
						projectiles[i].drawTrans(window);
					else
						projectiles[i].draw(window);
			}


			if (SHOWDEBUG) {
				for (int i = 0; i < hurtBox.size(); i++) {


					drawHitBox(window, hurtBox[i], sf::Color(255, 255, 255, 100));

				}

				if (ultimateShot->isAtacking) {
					drawHitBox(window, ultimateShot->hitbox, sf::Color::Red);
				}

				if (louKick->isAtacking) {
					drawHitBox(window, louKick->hitbox, sf::Color::Red);
				}

				if (hiKick->isAtacking) {
					drawHitBox(window, hiKick->hitbox, sf::Color::Red);
				}
				if (superAtack->isAtacking) {
					drawHitBox(window, superAtack->hitbox, sf::Color::Red);
				}

				if (isDefending) {
					drawHitBox(window, defense, sf::Color::Green);
				}

			}
			if (comboCounter > 2) {
				window.draw(comboText);
			}
		}


		void drawHitBox(sf::RenderWindow& window, HitBox box, sf::Color col) {
			sf::CircleShape circle(box.radius);
			circle.setPosition(box.center.x, box.center.y);
			circle.setOrigin(box.radius, box.radius);
			circle.setFillColor(col);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(2);

			window.draw(circle);
		}


		virtual void updatePhysics() {

			// Timers
			frames++;

			if (invFrames <= 0) {
				invunerable = false;
			}
			else {
				invFrames--;
			}

			if (stunFrames <= -100) {
				stunned = false;
			}
			else {
				stunFrames--;
			}

			updateHits();

			bar->updateStamin(comboCounter);

			// Gravity

			onFire = bar->onFire;
			//println(onFire);

			if (position.y < floorY) {
				air = true;
			}

			if (air && !noGravity) {
				vspeed += peso * Gravity / 100;
			}


			/// Meus planos foram realizados !!!
			// Floor Collision

			FloatRect galoBounds = model.getBounds();

			if (position.y > floorY) {
				vspeed = 0;
				position.y = floorY;
				air = false;
			}

			// Wall collision


			if (position.x > SCREEN_WIDTH - ((model.bounds.width - model.center.x) * abs(model.xScl))) {

				if (stunned) {
					hspeed *= -0.8;
				}
				else {
					hspeed = 0;
				}

				position.x = SCREEN_WIDTH - ((model.bounds.width - model.center.x) * abs(model.xScl));
			}

			if (position.x < model.center.x * abs(model.xScl)) {
				if (stunned) {
					hspeed *= -0.8;
				}
				else {
					hspeed = 0;
				}
				position.x = model.center.x * abs(model.xScl);
			}


			if (estado != RUNNING && !stunned) {
				hspeed = 0;
			}

			if (stunned && stunFrames < 30) {
				hspeed *= 0.95;
				vspeed *= 0.98;
			}

			if (isPoisoned) {
				hp -= 0.5;
			}



			position.x += hspeed;
			position.y += vspeed;
		}


		virtual void updateAnimations() = 0;

		virtual void fatality(RenderWindow* window, Galo* galo2, RectangleShape fundo) {

		}

		virtual void catalize() {
			if (onFire) {
				//...

				bar->resetPower();
			}
		}

		virtual void super() = 0;


		void updateHits() {

			comboText.setString(to_string(comboCounter) + " Hits!");
			if (isp1)
				comboText.setPosition(SCREEN_WIDTH / 4 - comboText.getGlobalBounds().width / 2, SCREEN_HEIGHT / 5);
			else
				comboText.setPosition(SCREEN_WIDTH - (SCREEN_WIDTH / 4 - comboText.getGlobalBounds().width / 2), SCREEN_HEIGHT / 5);
			int colorYellow = 255 - (comboCounter * 25);
			if (colorYellow < 0) {
				colorYellow = 0;
			}
			int colorRed = 255 - comboCounter * 2;
			comboText.setColor(Color(colorRed, colorYellow, 0));

		}

		virtual void update() {


			updatePhysics();


			// Hurtbox update
			for (int i = 0; i < hurtBox.size(); i++) {

				hurtBox[i].center = model.at(i)->drawPos;
				hurtBox[i].radius = model.at(i)->sprite.getGlobalBounds().width / 2;

			}


			updateAnimations();


			// Health Bar Update
			bar->update(hp);





			model.pos.x = position.x;
			model.pos.y = position.y;

			float resizeScl = (float)SCREEN_WIDTH / 5120;

			model.xScl = 4 * (facingRight ? -1 : 1) * resizeScl;
			model.yScl = 4 * resizeScl;
			model.update();

			estadoUpdate = false;
		}

		virtual void updateWithoutPhysics() {

			model.pos.x = position.x;
			model.pos.y = position.y;

			float resizeScl = (float)SCREEN_WIDTH / 5120;

			model.xScl = 4 * (facingRight ? -1 : 1) * resizeScl;
			model.yScl = 4 * resizeScl;
			model.update();

			estadoUpdate = false;
		}

		void drawEstrelinhas(RenderWindow* window) {

			if (frames % 5 == 0) {
				estrelinha.setScale(estrelinha.getScale().x * -1, estrelinha.getScale().y);
			}
			if (estrelinha.getScale().x > 0)
				estrelinha.setPosition(position.x - abs(model.getBounds().width) / 2, position.y - model.getBounds().height * 1.2);
			else
				estrelinha.setPosition(position.x + abs(model.getBounds().width) / 2, position.y - model.getBounds().height * 1.2);
			window->draw(estrelinha);

		}
		void sumir() {
			model.alpha = 0;
		}
		void aparecer() {
			model.alpha = 1;
		}
		bool getHitByBruxoSuper(RenderWindow* window) {

			static int thisFrames = 0;

			int maxFrames = 120;
			if (thisFrames == 0) {
				fireSound.play();
			}

			if (thisFrames > maxFrames) {
				thisFrames = 0;
				estado = STOPPED;
				fireSound.stop();
				return false;
			}

			estado = INVISIBLE;

			//vamos dividir as 17 imagens igualmentes em 60 frames
			int imgSpace = maxFrames / 17;
			int wid = 115;
			int hei = 135;
			int hei2 = 120;
			int hei3 = 46;

			//to mo cansado
			IntRect manoTaFoda;
			manoTaFoda.width = wid;

			if (imgSpace * 5 > thisFrames) {
				manoTaFoda.height = hei;
				manoTaFoda.top = 0;
			}
			else if (imgSpace * 10 > thisFrames) {
				manoTaFoda.height = hei;
				manoTaFoda.top = hei;
			}
			else if (imgSpace * 25 > thisFrames) {
				manoTaFoda.height = hei2;
				manoTaFoda.top = hei * 2;
			}
			else {
				manoTaFoda.height = hei3;
				manoTaFoda.top = hei * 2 + hei2;
			}

			manoTaFoda.left = ((int)(thisFrames / imgSpace) % 5) * wid;

			burning.setTextureRect(manoTaFoda);
			burning.setScale(SCREEN_WIDTH / 480, SCREEN_HEIGHT / 270);

			if (facingRight) {
				burning.setPosition(position.x - burning.getGlobalBounds().width / 2, position.y - burning.getGlobalBounds().height);
			}
			else {
				burning.setPosition(position.x - burning.getGlobalBounds().width / 2, position.y - burning.getGlobalBounds().height);
			}



			window->draw(burning);

			thisFrames++;
			return true;
		}
		void getHitByBruxoFatality() {

			static int thisFrames = 0;
			thisFrames++;

			if (frames < 60)
				position.y = SCREEN_HEIGHT / 2;
			else if (frames > 60 && position.y < floorY) {
				position.y++;
			}

			for (int i = 0; i < model.allBones.size(); i++) {

				if (i < model.allBones.size() / 2) {
					model.at(i)->offset.x += i % 4 - 2;
					model.at(i)->offset.y -= 2;

				}
				else {
					model.at(i)->offset.x += i % 4 - 2;
					model.at(i)->offset.y += 2;

				}
			}


		}
		void explodir() {
			static int  thisFrames = 0;
			if (thisFrames < 100) {
				for (int i = 0; i < model.allBones.size(); i++) {
					if (model.at(i) == model.at("Head")) {
						continue;
					}
					model.at(i)->offset.x += (i % 2 - 4);
					model.at(i)->offset.y += (i % 4 - 8) * 2;
				}
				if (model.at("Head")->drawPos.x > SCREEN_WIDTH / 2) {
					model.at("Head")->offset.x -= 1;
				}
				else if (model.at("Head")->drawPos.x < SCREEN_WIDTH / 2)  {
					model.at("Head")->offset.x += 1;
				}
				
				if (model.at("Head")->drawPos.y < floorY) {
					model.at("Head")->offset.y += 1;
				}

			}
			else {
				for (int i = 0; i < model.allBones.size(); i++) {
					if (model.at(i) == model.at("Head")) {
						continue;
					}
					model.at(i)->offset.x += (i % 4 - 2);
					model.at(i)->offset.y += 9;
				}
			
				
					model.at("Head")->angle += thisFrames % 20 - 10;
				

			}
			thisFrames++;
		}


		void getHitByKalsaFatalityBody(RenderWindow* window, Galo* g2) {

			static float thisFrames = 0;
			float maxFrames = 180;

			if (thisFrames > maxFrames) {
				thisFrames = 0;
			}

			float perc = (float)thisFrames / maxFrames;

			static int firstPosition = position.x;
			if (perc < 0.7) {

				position.x = firstPosition + (g2->position.x - firstPosition) * perc;
			}
			
			thisFrames++;
		}
		void getHitByKalsaFatalityHead(RenderWindow* window, Galo* g2) {

			static float thisFrames = 0;
			float maxFrames = 180;

			if (thisFrames > maxFrames) {

				thisFrames = 0;
			}

			
			static int firstPosition = model.at("Head")->drawPos.x;

			float perc = (float)thisFrames / maxFrames;

			if (perc < 0.7) {

				
				model.at("Head")->xScl *= -1;
				model.at("Head")->offset.x = 1000 * perc;
				model.at("Head")->offset.y = 200 * perc;
			}

			thisFrames++;
		}

	};

}



#endif
